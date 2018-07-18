#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import os
import json
import signal
import serial
import RPi.GPIO as GPIO
import Adafruit_DHT as DHT
import Adafruit_ADXL345 as Accel
import pynmea2
import datetime

from enum import Enum, unique

from subprocess import call
from threading import Thread

from time import sleep
from time import time

#Globals

#consts
BLINK_ENABLED = True

ledPin = 33
btnPin = 31

GPS_RETRY_COUNT = 5
#gps stuff
gpsSerial = serial.Serial('/dev/ttyS0', baudrate=9600, timeout=None)



#sensor types
@unique
class SensorType(Enum):
	Temperature = 1
	Acceleration = 2
	Humidity = 3
	GPSPosition = 4
	Speed = 5
	
customSensorIdProvided = False

#ADXL345 accelerometer instance
accelerometer = Accel.ADXL345()

#button/led/reading controlling conditions (mostly)
dataValidResponse = False
isRecordingMode = False
isInitializingMode = False
isDataValid = False
buttonDownTime = -1
buttonUpTime = -1
buttonPressDuration = -1

#sensor data
jsonData = json.dumps('')
currentData = []
selectedSensorsTypeIdDict = dict()
ledDelay = -1
fileName = "/home/pi/" + str(datetime.datetime.now()) + ".json"
dataFile = open(fileName,"w+")
isFirstDataWrite = True

#conditions for sensor readings
readTemperature = True
readAcceleration = True
readHumidity = True
readGpsPosition = True
readSpeed = True

def restartPi():
	destroy()
	call ("sudo reboot", shell=True)
	
def ledOn(on):
    if on:
        GPIO.output(ledPin, GPIO.HIGH)
    else:
        GPIO.output(ledPin, GPIO.LOW)

def blinkLed(delaySec):
	global BLINK_ENABLED
	if BLINK_ENABLED:
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
	blinkLed(0.1)

#read sensors
def readSensors():
	global readTemperature
	global readAcceleration
	global readGpsPosition
	global readSpeed
	global readHumidity
	global currentData
	global isFirstDataWrite
	global GPS_RETRY_COUNT
	if readTemperature or readHumidity:
		humidity, temperature = DHT.read_retry(DHT.DHT11, 26)
		print "Temperature:" + str(temperature) + " Humidity: " + str(humidity)
		if readTemperature:
			if temperature:
				addSensorToData(selectedSensorsTypeIdDict[SensorType.Temperature], int(temperature))
		if readHumidity:
			if humidity:
				addSensorToData(selectedSensorsTypeIdDict[SensorType.Humidity], int(humidity))
	if readAcceleration:
		x, y, z = accelerometer.read()
		#assuming sensor is set to -2/+2g ( G_range / 2^10 with 10 bits)
		xg = x * 0.003906
		yg = y * 0.003906
		if x and y:
			vals = [xg, yg]
			addSensorToData(selectedSensorsTypeIdDict[SensorType.Acceleration], vals)
	if readGpsPosition or readSpeed:
		if gpsSerial.isOpen():
			isPositionData = False
			isSpeedData = False
			gpsSpeedData = 0
			gpsPosData = dict()
			retryCount = 0
			while (not isPositionData and not isSpeedData) and (retryCount < GPS_RETRY_COUNT):
				gpsData = gpsSerial.readline()
				print "GPSData: " + gpsData
				lat = -1
				lon = -1
				print "retry: " + str(retryCount)
				if gpsData.startswith("$GPGGA"):
					retryCount = retryCount + 1
					print "GPGGA: " + gpsData
					gpsDataSplit = gpsData.split(",")
					print "LEN: " + str(len(gpsDataSplit))

					if len(gpsDataSplit) == 14:
						if len(gpsDataSplit[2]) >= 1:
							lat = float(gpsDataSplit[2])/ 100.0
						if len(gpsDataSplit[4]) >= 1:
							lon = float(gpsDataSplit[4])/ 100.0
						print "---"
						print lat
						print lon
						print "---"
						posData = []
						if lat != -1 and lon != -1:
							posData.append(lat)
							posData.append(lon)
							gpsPosData["pos"] = posData
						alt = float(gpsDataSplit[9])
						if alt:
							gpsPosData["alt"] = alt
						if alt or (lat and lon):
							addSensorToData(selectedSensorsTypeIdDict[SensorType.GPSPosition], gpsPosData)
							isPositionData = True
				elif gpsData.startswith("$GPGLL"):
					print "GPGLL: " + gpsData
					retryCount = retryCount + 1
					gpsDataSplit = gpsData.split(",")
					print "LEN: " + str(len(gpsDataSplit))
					if len(gpsDataSplit) == 8:
						if len(gpsDataSplit[1]) >= 1:
							lat = float(gpsDataSplit[1])/ 100.0
						if len(gpsDataSplit[3]) >= 1:
							lon = float(gpsDataSplit[3])/ 100.0
						print "---"
						print lat
						print lon
						print "---"
						posData = []
						if lat != -1 and lon != -1:
								posData.append(lat)
								posData.append(lon)
								gpsPosData["pos"] = posData
								addSensorToData(selectedSensorsTypeIdDict[SensorType.GPSPosition], gpsPosData)

								isPositionData = True
				elif gpsData.startswith("$GPRMC"):
					retryCount = retryCount + 1
					print "GPRMC: " + gpsData
					gpsDataSplit = gpsData.split(",")
					print "LEN: " + str(len(gpsDataSplit))
					if len(gpsDataSplit) >= 12:
						if len(gpsDataSplit[3]) >= 1:
							lat = float(gpsDataSplit[3])/ 100.0
						if len(gpsDataSplit[5]) >= 1:
							lon = float(gpsDataSplit[5])/ 100.0
						
						posData = []
						print "---"
						print lat
						print lon
						print "---"
						if lat != -1 and lon != -1:
							posData.append(lat)
							posData.append(lon)
							gpsPosData["pos"] = posData
							addSensorToData(selectedSensorsTypeIdDict[SensorType.GPSPosition], gpsPosData)
							isPositionData = True
				if gpsData.startswith("$GPVTG"):
					retryCount = retryCount + 1
					print "GPVTG: " + gpsData
					gpsDataSplit = gpsData.split(",")
					print "LEN: " + str(len(gpsDataSplit))
					if len(gpsDataSplit) == 10:
						speedKmh = gpsDataSplit[7]
						print "Speed" + str(speedKmh)
						if speedKmh:
							print "Speed: " + str(speedKmh)
							addSensorToData(selectedSensorsTypeIdDict[SensorType.Speed], gpsSpeedData)

							gpsSpeedData = float(speedKmh)
							isSpeedData = True
		else:
			print ("gpsSerialClosed")
			#while not isPositionData:
		if isInitializingMode:
			print json.dumps(currentData, indent=4)
		if isRecordingMode:
		#write in file
			print "Writing in file"
			if isFirstDataWrite:
				with open(fileName,"a") as dataf:
					dataf.write("\"sensorData\": [")
				isFirstDataWrite = False
			with open(fileName,"a") as dataf:
				dataf.write(json.dumps(currentData, indent=4))
				dataf.write(",")

		data = currentData
		currentData = []
		return data
def addSensorToData(sensorId, sensorValue):
	sensorData = dict()
	sensorData["id"] = int(sensorId)
	sensorData["value"] = sensorValue
	currentData.append(sensorData)

#RPi GPIO setup
def setup():
	GPIO.setmode(GPIO.BOARD)
	GPIO.setup(ledPin, GPIO.OUT)
	GPIO.setup(btnPin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
	GPIO.add_event_detect(btnPin, GPIO.BOTH, callback=buttonPressedCallback)
	signal.signal(signal.SIGTERM, destroy)
	signal.signal(signal.SIGINT, destroy)
	signal.signal(signal.SIGABRT, destroy)
	signal.signal(signal.SIGILL, destroy)

	dataFile.close()
	for sensorType in SensorType:
		selectedSensorsTypeIdDict[sensorType] = sensorType.value
	ledOn(True)

#read from stdin
def readStdin():
	global isDataValid
	global isInitializingMode

	for data in sys.stdin.readline():
		print ("Data" + str(data))
		dataStr = "data:OK"
		#data validation result

		if not isDataValid:
			if "data" in dataStr:
				ok = dataStr.split(":")[1]
				if ok == "OK":
					isInitializingMode = False
					isDataValid = True
					ledOn(True)
				elif ok == "NOK":
					ledOn(False)
				else:
					pass
				#this shouldn't happen

#cleanup on exit
def destroy(arg=None,arg1=None):
	global dataFile
	
	print dataFile.name
	GPIO.output(ledPin, GPIO.LOW)
	GPIO.cleanup()
	gpsSerial.close()
	with open(fileName, "a") as dataf:	
		dataf.seek(-1, os.SEEK_END)
		dataf.truncate()
		dataf.write("]")
    
#callback function for the button
def buttonPressedCallback(channel):
	global isInitializingMode
	global isRecordingMode
	global isDataValid
	global buttonDownTime 
	global buttonUpTime
	global buttonPressDuration
	global dataFile
	
	if GPIO.input(btnPin) == 0:
		buttonDownTime = time()
	if GPIO.input(btnPin) == 1:
		buttonUpTime = time()		
		buttonPressDuration = buttonUpTime - buttonDownTime;
		print ("Elapsed: " + str(buttonPressDuration))
	
	#initializing
	if not isInitializingMode and not isRecordingMode and not isDataValid:
		if buttonPressDuration > 1 and buttonPressDuration < 2:
			isInitializingMode = True
			print ('Button pressed, initializing')

			checkSensorsThread = Thread(target = checkSensors)
			checkSensorsThread.start()
			checkSensorsThread.join()
	#start reading
	elif not isRecordingMode and isDataValid:
		if buttonPressDuration > 2:
			if isDataValid:
				isInitializingMode = False
				isRecordingMode = True
				print ('Button pressed, recording')
	#stopReading
	elif isRecordingMode:
		if buttonPressDuration > 0.2:
			print ("Stopping recording")
			isRecordingMode = False
			ledOn(True)
			with open(fileName,"a") as dataf:
				dataf.write("]")
		
	if buttonPressDuration > 6:
		restartPi()
def checkSensors():
	isTemperatureOk = False
	isAccelerometerOk = False
	isHumidityOk = False
	isSpeedOk = False
	isGPSPositionOk = False
	
	global readTemperature
	global readAcceleration
	global readHumidity
	global readGpsPosition
	global readSpeed
	global isDataValid
	global customSensorIdProvided
	global isInitializingMode
	
	if not readTemperature:
		isTemperatureOk = True
	if not readHumidity:
		isHumidityOk = True
	if not readAcceleration:
		isAccelerometerOk = True
	if not readGpsPosition:
		isGPSPositionOk = True
	if not readSpeed:
		isSpeedOk = True

	retryCount = 0
	#TODO add GPS too
	while (retryCount < 10) and (not isHumidityOk and not isTemperatureOk and not isAccelerometerOk):
		data = readSensors()
		if customSensorIdProvided:
			if readTemperature:
				pass
			if readHumidity:
				pass
			if readAcceleration:
				pass
			if readGpsPosition:
				pass
			if readSensors:
				pass
		else:
			print data
			for sensorData in data:
				sensorDataValue = sensorData["value"]
				if sensorData["id"] == SensorType.Acceleration.value:
					if len(sensorDataValue) == 2:
						if sensorDataValue[0] and sensorDataValue[1]:
							isAccelerometerOk = True
							print "Accel OK"
						else:
							isAccelerometerOk = False
							print "Accel NOK"
					else:
						isAccelerometerOk = False
						print "Accel NOK"
				elif sensorData["id"] == SensorType.Temperature.value:
					if sensorDataValue:
						if sensorDataValue > -50 and sensorDataValue < 50:
							isTemperatureOk = True
							print "Temp OK"
						else:
							print "Temp NOK"
							isTemperatureOk = False
					else:
						isTemperatureOk = False
						print "Temp NOK"
					print "Temp: " + str(sensorData["value"])
				elif sensorData["id"] == SensorType.Humidity.value:
					if sensorDataValue:
						if sensorDataValue >= 0 and sensorDataValue <= 100:
							print "Hum OK"
							isHumidityOk = True
						else:
							print "Hum NOK"
							isHumidityOk = False
					else:
						print "Hum NOK"
						isHumidityOk = False
					print "Hum: " + str(sensorData["value"])
				elif sensorData["id"] == SensorType.GPSPosition.value:
					pass
				elif sensorData["id"] == SensorType.Speed.value:
					pass
				print "Data: " + str(sensorData)
				#TODO add GPS too
			if isTemperatureOk and isHumidityOk and isAccelerometerOk:
				isDataValid = True
				isInitializingMode = False
				print "Data valid"
				ledOn(True)
				break	
	#data was invalid, turn off led
	if retryCount == GPS_RETRY_COUNT and not isDataValid:
		isInitializingMode = False
		isDataValid = False
		print "Led off"
		ledOn(False)
def main():
	setup()

	try:
		print ('Started')
		print (sys.argv)
		i = 0
		global isInitializingMode
		global isRecordingMode
		global ledDelay
		while True:
			print (str(i))
			if i > 100:
				readStdin() 
				print("Reading from stdin")
				break
			else:
				i = i+1

			#if isInitializingMode:
			#	ledDelay = -1
			#	initializingLedBlinking()
			#if isRecordingMode:
			#	recordingLedBlinking()
			#	readSensors()
			recordingLedBlinking()
			readSensors()
			#if ledDelay < 0:
			#	sleep(0.5)
				
	#on ctrl+c
	except KeyboardInterrupt:
		destroy()
	finally:
		destroy()
if __name__ == '__main__':
	main()        
