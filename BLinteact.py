import serial
import time

print("Start")
# port="/dev/tty.HC-06-DevB" #This will be different for various devices and on windows it will probably be a COM port.
port = "COM9"

hc05=serial.Serial(port, 9600)#Start communications with the bluetooth unit
print("Connected")
hc05.flushInput() #This gives the bluetooth a little kick
for i in range(50): #send 5 groups of data to the bluetooth
	hc05.write(b"BOOP "+str.encode(str(i)))#These need to be bytes not unicode, plus a number
	input_data=hc05.readline()#This reads the incoming data. In this particular example it will be the "Hello from Blue" line
	print(input_data.decode())#These are bytes coming in so a decode is needed
	time.sleep(0.1) #A pause between bursts
hc05.close() #Otherwise the connection will remain open until a timeout which ties up the /dev/thingamabob
print("Done")

# port2 = "COM7"
# esp=serial.Serial(port, 115200)#Start communications with the bluetooth unit
# print("Connected")
# esp.flushInput() #This gives the bluetooth a little kick
# # bluetooth.write(b"0")
# state = 0
# for i in range(10):
#     if state == 0:
#         esp.write(b"1")
#         state = 1
#     else:
#         esp.write(b"0")
#         state = 0
#     time.sleep(1)
# esp.close() #Otherwise the connection will remain open until a timeout which ties up the /dev/thingamabob
print("Done")