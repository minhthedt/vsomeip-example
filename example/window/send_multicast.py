import socket
import struct

#echo "Hello multicast" | socat - UDP4-DATAGRAM:239.0.0.1:12345
message = b'Hello multicast'
multicast_group = ('239.0.0.1', 12345)

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
ttl = struct.pack('b', 1)
sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, ttl)

sock.sendto(message, multicast_group)
print(f'Sent message: {message.decode()} to multicast group {multicast_group}')