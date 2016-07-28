#!/usr/bin/python
#coding: utf-8

import sys,socket,time
import random, string
import struct

host = "10.1.3.104"
port = 5555

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.connect((host,port))

for i in xrange(0,256):
	buffer = [chr(i)]
	buffer.extend([random.choice(string.ascii_letters) for _ in range(4095)])
	buffer = ''.join(buffer)
	buffer = struct.pack("4096c", *buffer)
	print len(buffer)
	sock.sendall(buffer)
	time.sleep(1)
sock.shutdown(1)
