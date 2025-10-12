import socket

def send_unicast_message(target_ip, target_port, message):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        if isinstance(message, str):
            data = message.encode()
        else:
            data = message
        sock.sendto(data, (target_ip, target_port))
        print(f"Sent message to {target_ip}:{target_port}")
    finally:
        sock.close()

if __name__ == "__main__":
    target_ip = "172.17.0.6"  # Replace with receiver's IP
    target_port = 33334          # Replace with receiver's port
    message = "vvthe, unicast receiver!"
    # Convert hexdump string to bytes
    hexdump = "12 34 04 21 00 00 00 12 13 14 00 01 01 00 00 00 00 01 02 03 04 05 09 09 09 09"
    buffer = bytes(int(b, 16) for b in hexdump.split())
    print("Buffer bytes:", buffer)

    send_unicast_message(target_ip, target_port, buffer)