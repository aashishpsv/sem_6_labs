import socket
host = socket.gethostname()
port = 12345
s = socket.socket()
s.connect((host,port))
s.sendall(b'welcome user!')
data = s.recv(1024)
s.close()
print(repr(data))