import socket

host = socket.gethostname()
port = 12345
s = socket.socket()
s.bind((host,port))
s.listen(5)
conn, addr = s.accept()
print("got connection frm:",addr[0],'(',addr[1],')')
print("tq for connecting")
while True:
	data = conn.recv(1024)
	if not data: break
	conn.sendall(data)
conn.close()
