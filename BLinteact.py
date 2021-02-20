import serial
import time

print("Start")
# port="/dev/tty.HC-06-DevB" #This will be different for various devices and on windows it will probably be a COM port.
port = "COM9"
hc05=serial.Serial(port, 9600)#Start communications with the bluetooth unit
print("HC05 Connected")
port2 = "COM7"
esp=serial.Serial(port2, 115200)#Start communications with the bluetooth unit
print("ESP32 Connected")
esp.flushInput() #This gives the bluetooth a little kick
hc05.flushInput() #This gives the bluetooth a little kick

for i in range(60): #send 5 groups of data to the bluetooth
	# hc05.write(b"BOOP "+str.encode(str(i)))#These need to be bytes not unicode, plus a number
	input_data=hc05.readline()#This reads the incoming data. In this particular example it will be the "Hello from Blue" line
	print(input_data.decode())#These are bytes coming in so a decode is needed
	input_data = input_data.decode()
	if '0' in input_data:
		print("i am 0")
		esp.write(b"0")
	if '1' in input_data:
		print("I am 1")
		esp.write(b"1")
	time.sleep(0.1) #A pause between bursts
hc05.close() #Otherwise the connection will remain open until a timeout which ties up the /dev/thingamabob
print("HC05 Close")
esp.write(b"0")
esp.close()
print("ESP32 Close")
print("Done")