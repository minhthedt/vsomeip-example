# fake someip message
# run server: ./bin./run_request_sample.sh
# run_client: python ./doc/example/window/send_unicast.py
# Server log: UDP: SERVICE: Received message with Client/Session [1314/0001] 00 01 02 03 04 05 09 09 09 09
# client log : Response data (hex): 12 34 04 21 00 00 00 12 13 14 00 01 01 00 80 00 09 08 07 06 05 04 03 02 01 00
# test: pass


import socket

def send_unicast_message(target_ip, target_port, message, listen_response=True, timeout=5):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        if isinstance(message, str):
            data = message.encode()
        else:
            data = message
        sock.sendto(data, (target_ip, target_port))
        print("Sent message to {}:{}".format(target_ip, target_port))
        print("Actual data length sent: {} bytes".format(len(data)))
        print("Data as hex: {}".format(' '.join('{:02x}'.format(ord(b) if isinstance(b, str) else b) for b in data)))
        
        if listen_response:
            sock.settimeout(timeout)
            try:
                response, addr = sock.recvfrom(4096)
                print("Received response from {}:{}".format(addr[0], addr[1]))
                print("Response length: {} bytes".format(len(response)))
                # Fix for Python 2.x: convert string chars to ordinal values
                print("Response data (hex): {}".format(' '.join('{:02x}'.format(ord(c) if isinstance(c, str) else c) for c in response)))
            except socket.timeout:
                print("No response received within {} seconds.".format(timeout))
    finally:
        sock.close()

def create_buffer_from_hexdump(hexdump_str):
    """Create buffer from hex dump string with individual byte variables"""
    hex_bytes = hexdump_str.split()
    buffer = bytearray()
    
    print("Creating buffer from hex dump:")
    print("-" * 40)
    
    for i, hex_val in enumerate(hex_bytes):
        byte_value = int(hex_val, 16)
        buffer.append(byte_value)
        print("byte{} = 0x{} ({})".format(i, hex_val.upper(), byte_value))
    
    print("-" * 40)
    print("Total buffer size: {} bytes".format(len(buffer)))
    print("Buffer as hex: {}".format(' '.join('{:02x}'.format(b) for b in buffer)))
    
    return buffer

if __name__ == "__main__":
    target_ip = "172.17.0.5"  # Replace with receiver's IP
    target_port = 30510        # Replace with receiver's port
    
    # Convert hexdump string to bytes
    hexdump = "12 34 04 21 00 00 00 12 13 14 00 01 01 00 00 00 00 01 02 03 04 05 09 09 09 09"
    
    print("Original hexdump: {}".format(hexdump))
    print("Number of hex values: {}".format(len(hexdump.split())))
    
    # Method 1: Python 2.x compatible conversion
    hex_list = [int(b, 16) for b in hexdump.split()]
    buffer = bytearray(hex_list)
    print("Buffer bytes: {}".format(buffer))
    print("Buffer length: {} bytes".format(len(buffer)))
    
    # Method 2: With individual byte display
    buffer_with_details = create_buffer_from_hexdump(hexdump)
    
    print("\n=== SENDING DATA ===")
    # Send the buffer and listen for response
    send_unicast_message(target_ip, target_port, buffer, listen_response=True)