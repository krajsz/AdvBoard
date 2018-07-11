#!/usr/bin/python

import sys
import Adafruit_DHT

while True:
	hum, temp = Adafruit_DHT.read_retry(Adafruit_DHT.DHT11, 26)
	print str(temp) + " " + str(hum)
