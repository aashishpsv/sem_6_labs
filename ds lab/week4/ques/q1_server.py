import socket
import time

serversocket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

udp_host = socket.gethostname()
udp_port = 9991

serversocket.bind((udp_host,udp_port))

while True:
    data, addr = serversocket.recvfrom(1024)
    print("Got connection request from %s" % str(addr))
    currenttime = time.ctime(time.time()) + "\r"
    serversocket.sendto(currenttime.encode('ascii'), addr)
