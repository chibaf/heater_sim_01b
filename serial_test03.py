import serial
import time
val = 0
ser =serial.Serial("/dev/cu.usbmodem14101", 9600)
time.sleep(2)
while 1:
	val = input()
	
	if val=='a':
		break;
	a = int(val).to_bytes(1, byteorder="little")
	ser.write(a)
	print(a)
	line=ser.readline()
	print(line)
ser.close()