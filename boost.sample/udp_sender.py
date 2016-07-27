#!/usr/bin/python
#coding: utf-8

import sys,socket,time
import random, string
import struct

host = "10.1.3.104"
port = 5555

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.connect((host,port))

for i in xrange(0,10000):
	buffer = str(i)
	buffer = buffer.join([random.choice(string.ascii_letters+string.digits) for _ in range(2000)])
	buffer = struct.pack("!2001s", buffer)
	sock.sendall(buffer)
	#print str
	time.sleep(1)
sock.shutdown(1)
