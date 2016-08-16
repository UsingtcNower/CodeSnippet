#!/usr/bin/python
import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(("0.0.0.0", 5555))
sock.listen(1)

conn,addr = sock.accept()
while True:
	data = conn.recv(1024)
	if not data: break
conn.close()
