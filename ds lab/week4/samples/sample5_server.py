import socket

HOST = socket.gethostname()
PORT = 31621

s = socket.socket()
s.bind((HOST,PORT))
s.listen()
print("waiting fr incoming connections:")
conn,addr=s.accept()
print("recived connection frm:",addr[0],'(',addr[1],")\n")
name = input(str("enter ur name:"))
conn.send(name.encode())

while True:
	message = input(str("Me : "))
	if message =="[e]":
		message="Left chat room!"
		conn.send(message.encode())
		print("\n")
		break
	conn.send(message.encode())
	message = conn.recv(1024)
	message = message.decode()
	print(name, ":", message)