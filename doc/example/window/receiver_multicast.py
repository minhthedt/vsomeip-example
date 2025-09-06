import socket
import struct

MCAST_GRP = '239.0.0.1'
MCAST_PORT = 12345
IFACE_IP   = '192.168.1.8'   # <-- replace with your Wi-Fi IPv4

# Create socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

# Bind to port (all interfaces)
sock.bind(('', MCAST_PORT))

# Explicitly join group on specific interface
mreq = socket.inet_aton(MCAST_GRP) + socket.inet_aton(IFACE_IP)
sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)

print(f"Listening for multicast on {MCAST_GRP}:{MCAST_PORT} via {IFACE_IP}")

while True:
    data, addr = sock.recvfrom(1024)
    print(f"Received from {addr}: {data.decode(errors='ignore')}")
