#!/usr/bin/python
#coding: utf-8

import sys,socket,time
import random, string
import struct

host = "10.23.70.34"
port = 5555

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(("0.0.0.0", 5555))

for i in xrange(0,10):
	buffer = [chr(i)]
	buffer.extend([random.choice(string.ascii_letters) for _ in range(1023)])
	buffer = ''.join(buffer)
	buffer = struct.pack("1024c", *buffer)
	print len(buffer)
	sock.sendto(buffer, (host, port))
	msg,(saddr,sport) = sock.recvfrom(1024)
	print msg
	time.sleep(1)
sock.shutdown(1)
