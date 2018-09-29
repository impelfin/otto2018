import csv
import sys
import io
import os

with open('test2.txt') as tf:
	with open('body.html', 'w') as body:
		body.write('')
	line = tf.readline()
	cnt = 1

	while line:
		line2 = line.replace('\n\n', '\n').rstrip()
		parts = line2.split(",")
		x = parts[0]
		y = parts[1].replace(' ','')
		#print(x, y)
		if (x==0.00) and (y==0.00) :
			break
		with open('body.html', 'a') as body:
			body.write("		<circle cx = \"{}\" cy = \"{}\" r = \"2\" stroke = \"black\" stroke-width=\"1\" fill=\"black\"></circle>\n".format(float(x)/10+600, float(y)/10+600))
		line = tf.readline()
		cnt += 1

	with open('head.html','r') as head:
		with open('basemap.html','w') as basemap:
			basemap.write(head.read())
	with open('body.html','r') as body:
		with open('basemap.html','a') as basemap:
			basemap.write(body.read())
	with open('tail.html','r') as tail:
		with open('basemap.html','a') as basemap:
			basemap.write(tail.read())