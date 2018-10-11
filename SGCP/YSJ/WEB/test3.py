import csv
import sys
import io
import os
import webbrowser
import glob

with open('body.html', 'w') as body:
	body.write('')

lidar = glob.glob('LIDAR*.txt')
leng = len(lidar)

while True :	
	
	print(lidar[0])

	with open(lidar[0]) as tf:
		line = tf.readline()
		cnt = 1
	
		while line:
			line2 = line.replace('\n\n', '\n').rstrip()
			parts = line2.split(",")
			x = float(parts[0])
			y = float(parts[1].replace(" ",""))
			#print(x, y)
			if x == 0.0 and y == 0.0 :
				with open('body.html', 'a') as body:
					body.write("<!--		<circle cx = \"{}\" cy = \"{}\" r = \"2\" stroke = \"black\" stroke-width=\"1\" fill=\"black\"></circle>-->\n".format(float(x)/10+600, float(y)/10+600))
			else :
				with open('body.html', 'a') as body:
					body.write("		<circle cx = \"{}\" cy = \"{}\" r = \"2\" stroke = \"black\" stroke-width=\"1\" fill=\"black\"></circle>\n".format(float(x)/10+600, float(y)/10+600))
			line = tf.readline()
			cnt += 1
	
	del lidar[0]

	if len(lidar) == 0 :
		break
		
with open('head.html','r') as head:
	with open('basemap.html','w') as basemap:
		basemap.write(head.read())
with open('body.html','r') as body:
	with open('basemap.html','a') as basemap:
		basemap.write(body.read())
with open('tail.html','r') as tail:
	with open('basemap.html','a') as basemap:
		basemap.write(tail.read())
