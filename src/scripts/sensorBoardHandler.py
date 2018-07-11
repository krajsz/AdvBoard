#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import json

import RPi.GPIO as GPIO
import Adafruit_DHT as DHT
import Adafruit_ADXL345 as Accel

from time import sleep

#Globals
ledPin = 33
btnPin = 31
accelerometer = Accel.ADXL345()
dataValidResponse = False
isRecordingBlinking = False
isInitializingLedBlinking = False
isDataValid = False
jsonData = json.dumps('')
sensorIds = list()
sensorTypes = list()
ledDelay = 1

def ledOn(on):
    if on:
        GPIO.output(ledPin, GPIO.HIGH)
    else:
        GPIO.output(ledPin, GPIO.LOW)

def blinkLed(delaySec):
    ledDelay = delaySec

    ledOn(True)
    sleep(delaySec)
    ledOn(False)
    sleep(delaySec)

#blink the LED when recording, 1 sec delay
def recordingLedBlinking():
    blinkLed(1)

#blink the LED when , 0.5sec delay
def initializingLedBlinking():
    blinkLed(0.25)

#read sensors
def readSensors():
    if readTemp:
        hum, temp = DHT.read_retry(Adafruit_DHT.DHT11, 26)
        print "Temperature:" + str(temp) + " Humidity: " + str(hum)

    if readAccel:
        x, y, z = accelerometer.read()
        print('X={0}, Y={1}, Z={2}'.format(x, y, z))

#RPi GPIO setup
def setup():
    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(ledPin, GPIO.OUT)
    GPIO.setup(btnPin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
    GPIO.add_event_detect(btnPin, GPIO.RISING, callback=buttonPressedCallback)
    ledOn(True)

def readStdin():
    for data in sys.stdin.readline():
        print data
        dataStr = "data:OK"
        #data validation result

        if not isDataValid:
            if "data" in dataStr:
                ok = dataStr.split(":")[1]
                if ok == "OK":
                    initializingLedBlinking = False
                    isDataValid = True
                    ledOn(True)
                else if ok == "NOK":
                    ledOn(False)
                else:
                #this shouldn't happen

#cleanup on exit
def destroy():
    GPIO.output(ledPin, GPIO.LOW)
    GPIO.cleanup()
#callback function for the button

def buttonPressedCallback(channel):
        if not isInitializingLedBlinking:
            isInitializingLedBlinking = True
            print ('Button pressed, initializing')
        else if not isRecordingBlinking:
            if isDataValid:
                isInitializingLedBlinking = False
                isRecordingBlinking = True
                print ('Button pressed, recording')
        else if isRecordingBlinking:
            isRecordingBlinking = False
            ledOn(True)
def main():
    setup()
    try:
        i = 0
        while True:
            print ('Started')
            print (sys.argv)
            if i > 30:
                readStdin()
            else:
                i = i+1

            if isInitializingLedBlinking:
                initializingLedBlinking()

            if isRecordingBlinking:
                recordingLedBlinking()
                readSensors()

            if ledDelay > 0:
                sleep(ledDelay)
            else:
                sleep(0.2)
    except KeyboardInterrupt:
        destroy()

if __name__ == '__main__':
                    main()        
