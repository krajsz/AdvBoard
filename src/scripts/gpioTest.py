import RPi.GPIO as GPIO
from time import sleep

ledPin = 33
btnPin = 31
def blinkLed():
	while True:
		GPIO.output(ledPin, GPIO.HIGH)
		sleep(1)
		GPIO.output(ledPin, GPIO.LOW)
		sleep(1)
def setup():
	GPIO.setmode(GPIO.BOARD)
	GPIO.setup(ledPin, GPIO.OUT)
	GPIO.setup(btnPin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
	GPIO.add_event_detect(btnPin, GPIO.RISING, callback=buttonPressedCallback)
	GPIO.output(ledPin, GPIO.HIGH)
	
def destroy():
		GPIO.output(ledPin, GPIO.LOW)
		GPIO.cleanup()
		
def buttonPressedCallback(channel):
	print ('Button pressed')
	
if __name__=='__main__':
	setup()
	try:
		blinkLed()
	except KeyboardInterrupt:
		destroy()
