import socket

s=socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

udp_host = socket.gethostname()
udp_port = 9991

s.sendto(b"", (udp_host, udp_port))

tm, addr = s.recvfrom(1024)
print('Current time from server:', tm.decode())
s.close()
