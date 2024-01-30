import socket 

sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

udp_host=socket.gethostname()
udp_port = 12345

sock.bind((udp_host,udp_port))

while True:
	print ("waiting for client")
	data,addr = sock.recvfrom(1024)
	print("recived msg:",data.decode(),"from",addr)
sock.close()