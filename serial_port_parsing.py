##############
## Script listens to serial port and writes contents into a file
##############
## requires pySerial to be installed 
import serial
import requests
import json

params = {}

url = 'http://35.203.153.82:3000/sensor'
serial_port = '/dev/cu.usbmodem14421'
baud_rate = 115200 #In arduino, Serial.begin(baud_rate)
#write_to_file_path = "/Users/xinhaixiong/Desktop/hardware_class/arduino_code/output.txt";

#output_file = open(write_to_file_path, "w+")
# serial print format: first_motion_sensor_status, second_motion_sensor_status, third_motion_sensor_status, first_weight_reading, second_weight_reading
ser = serial.Serial(serial_port, baud_rate)
while True:
	try:
		line = ser.readline()
		line = line.decode("utf-8") #ser.readline returns a binary, convert to string
		params_array = line[:-2].split(",")
		if len(params_array) != 7:
			continue
		params["first_motion_sensor_status"] = params_array[0]
		params["second_motion_sensor_status"] = params_array[1]
		params["third_motion_sensor_status"] = params_array[2]
		params["first_weight_reading"] = params_array[3]
		params["second_weight_reading"] = params_array[4]
		params["third_weight_reading"] = params_array[5]
		params["fourth_weight_reading"] = params_array[6]
		print(params)
		result = requests.post(url, json=params)
		if (result.status_code == 200):
			data = json.loads(result.text)
			print(data)
		else:
			print("error")
	except Exception as ex:
		print("exception")
		continue