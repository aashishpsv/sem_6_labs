import socket

sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

udp_host = socket.gethostname()
udp_port = 12345

msg = "udp prog 3rd time"
print('udp target ip:',udp_host)
print('udp target port:',udp_port)

sock.sendto(msg.encode(),(udp_host,udp_port))
sock.sendto(msg.encode(),(udp_host,udp_port))
sock.close()