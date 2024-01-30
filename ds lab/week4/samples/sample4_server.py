#time server

import socket
import time

serversocket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

host = socket.gethostname()
port = 9991

serversocket.bind((host,port))
serversocket.listen(5)

while True:
	clientsocket,addr=serversocket.accept()
	print("got connection req from %s "%str(addr))
	currenttime = time.ctime(time.time())+"\r\n"
	clientsocket.send(currentTime.encode('ascii'))
	clientsocket.close()
