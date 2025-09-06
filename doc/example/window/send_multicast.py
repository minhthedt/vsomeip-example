import socket
import struct
import time

message = b'Hello multicast'
multicast_group = ('239.0.0.1', 12345)
IFACE_IP   = '192.168.1.8'   # <-- replace with your Wi-Fi IPv4

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
ttl = struct.pack('b', 1)
sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, ttl)

# Set outgoing interface (replace with your interface IP)
sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_IF, socket.inet_aton(IFACE_IP))
print(f'Using interface: {IFACE_IP}')

for i in range(50):
    sock.sendto(message, multicast_group)
    print(f'Sent message: {message.decode()} to multicast group {multicast_group} ({i+1}/50)')
    time.sleep(1)
sock.close()