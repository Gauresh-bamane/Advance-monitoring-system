import serial
import time
import paho.mqtt.client as mqtt
import string


ser = serial.Serial("/dev/rfcomm0", 9600)
ser.write(str.encode('Start\r\n'))

def on_connect(client, userdata, flags, rc): # func for making connection
	print("Connected to MQTT")
	print("Connection returned result: " + str(rc) )
	
	client.subscribe("ifn649")
def on_message(client, userdata, msg): # Func for Sending msg
	s="".join(map(chr,msg.payload))
	#print (msg.payload)
	m= int(s)
    #print("value of m"+"|"+ m)
	switch(m, s)

def switch(m,s):
    if m ==1:
        print("BUZZ")
        ser.write(str.encode('BUZZER_ON'))
    else:
        print("...")
        #ser.write(str.encode('BUZZER_OFF'))
        
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("13.54.211.159", 1883, 60)

client.loop_forever()

