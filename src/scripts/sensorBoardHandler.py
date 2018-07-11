#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import json

import threading

import RPi.GPIO as GPIO
import Adafruit_DHT as DHT
import Adafruit_ADXL345 as Accel

from time import sleep
from time import time

#Globals

#pin setups
ledPin = 33
btnPin = 31

#ADXL345 accelerometer instance
accelerometer = Accel.ADXL345()

#button/led/reading controlling conditions (mostly)
dataValidResponse = False
isRecordingBlinking = False
isInitializingLedBlinking = False
isDataValid = True
blinkEnabled = True
buttonDownTime = -1
buttonUpTime = -1
buttonPressDuration = -1

#sensor data
jsonData = json.dumps('')
sensorIds = list()
sensorTypes = list()

ledDelay = -1

#conditions for sensor readings
readTemp = True
readAccel = True

def ledOn(on):
    if on:
        GPIO.output(ledPin, GPIO.HIGH)
    else:
        GPIO.output(ledPin, GPIO.LOW)

def blinkLed(delaySec):
	global blinkEnabled
	if blinkEnabled:
		ledOn(True)
		sleep(delaySec)
		ledOn(False)
		sleep(delaySec)

#blink the LED when recording, 1 sec delay
def recordingLedBlinking():
	print ("Recording blink")
	blinkLed(1)

#blink the LED when , 0.5sec delay
def initializingLedBlinking():
	print ("Initializing blink")
	blinkLed(0.25)

#read sensors
def readSensors():
	global readTemp
	global readAccel

	if readTemp:
		hum, temp = DHT.read_retry(DHT.DHT11, 26)
		print "Temperature:" + str(temp) + " Humidity: " + str(hum)

	if readAccel:
		x, y, z = accelerometer.read()
		print('X={0}, Y={1}, Z={2}'.format(x, y, z))

#RPi GPIO setup
def setup():
    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(ledPin, GPIO.OUT)
    GPIO.setup(btnPin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
    GPIO.add_event_detect(btnPin, GPIO.BOTH, callback=buttonPressedCallback)
    ledOn(True)

#read from stdin
def readStdin():
	global isDataValid
	global initializingLedBlinking

	for data in sys.stdin.readline():
		print ("Data" + str(data))
		dataStr = "data:OK"
		#data validation result

		if not isDataValid:
			if "data" in dataStr:
				ok = dataStr.split(":")[1]
				if ok == "OK":
					initializingLedBlinking = False
					isDataValid = True
					ledOn(True)
				elif ok == "NOK":
					ledOn(False)
				else:
					pass
				#this shouldn't happen

#cleanup on exit
def destroy():
    GPIO.output(ledPin, GPIO.LOW)
    GPIO.cleanup()
    
#callback function for the button
def buttonPressedCallback(channel):
	global isInitializingLedBlinking
	global isRecordingBlinking
	global isDataValid
	global buttonDownTime 
	global buttonUpTime
	global buttonPressDuration

	if GPIO.input(btnPin) == 0:
		buttonDownTime = time()
	if GPIO.input(btnPin) == 1:
		buttonUpTime = time()		
		buttonPressDuration = buttonUpTime - buttonDownTime;
		print ("Elapsed: " + str(buttonPressDuration))
	
	#initialize
	if not isInitializingLedBlinking and not isRecordingBlinking:
		if buttonPressDuration > 1 and buttonPressDuration < 3:
			isInitializingLedBlinking = True
			print ('Button pressed, initializing')
	#start reading
	elif not isRecordingBlinking:
		if buttonPressDuration > 3:
			if isDataValid:
				isInitializingLedBlinking = False
				isRecordingBlinking = True
				print ('Button pressed, recording')
	#stopReading
	elif isRecordingBlinking:
		if buttonPressDuration > 0.2:
			print ("Stopping recording")
			isRecordingBlinking = False
			ledOn(True)
		
def main():
    setup()
    try:
		print ('Started')
		print (sys.argv)
		i = 0
		global isInitializingLedBlinking
		global isRecordingBlinking
		global ledDelay
		while True:
			print (str(i))
			if i > 30:
				readStdin() 
				print("Reading from stdin")
				break
			else:
				i = i+1

			if isInitializingLedBlinking:
				initializingLedBlinking()

			if isRecordingBlinking:
				recordingLedBlinking()
				readSensors()

			if ledDelay < 0:
				sleep(0.2)
	#on ctrl+c
    except KeyboardInterrupt:
        destroy()

if __name__ == '__main__':
                    main()        
