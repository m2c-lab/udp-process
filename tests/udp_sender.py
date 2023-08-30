# UDP packet sender for testing purposes
# Usage: python3 udp_sender.py <host> <port> [-q] [-i <interval>]
#
# Author: Wuqiong Zhao (me@wqzhao.org)
# Date: 2023-08-16

import socket
import time
import argparse

# message = b"\x31\xd4\x91\xb2\x34\x01\xd2\x04" + b"\x00" * 1032
message = \
    b"\x31\xd4\x91\xb2\x34\x01" \
    b"\xd2\x04\x31\xd4\x91\xb2\x34\x01\xd2\x04\x02\x00\xfa\xff\x02\x00" \
    b"\xfb\xff\xfc\xff\x09\x00\x05\x00\x0f\x00\xff\xff\x8e\xff\x07\x00" \
    b"\x08\x00\xfd\xff\xad\xff\x03\x00\x05\x00\xfe\xff\xcf\xff\x01\x00" \
    b"\xff\xff\xfc\xff\x73\x00\xfd\xff\x05\x00\xfa\xff\xf1\xff\x0d\x00" \
    b"\xff\xff\xfa\xff\xdd\xff\xf8\xff\xfa\xff\xff\xff\xca\xff\xfe\xff" \
    b"\xf8\xff\xfb\xff\xbf\xff\xf5\xff\xf1\xff\xfd\xff\x73\x00\x03\x00" \
    b"\xef\xff\xfd\xff\x7f\x00\xee\xff\x04\x00\xff\xff\x48\x00\xff\xff" \
    b"\x05\x00\xfa\xff\xf0\xff\x01\x00\xfa\xff\xff\xff\x3e\x00\x0a\x00" \
    b"\xfc\xff\xfb\xff\x24\x00\x01\x00\xfb\xff\xff\xff\xe1\xff\xfc\xff" \
    b"\x01\x00\xfe\xff\xc1\xff\xfe\xff\xfd\xff\xf8\xff\x30\x00\xfb\xff" \
    b"\xfc\xff\xfe\xff\x2b\x00\x04\x00\x03\x00\x01\x00\x38\x00\xfb\xff" \
    b"\x03\x00\xf9\xff\xf3\xff\xfa\xff\xff\xff\xfe\xff\x15\x00\x00\x00" \
    b"\xff\xff\xfc\xff\x22\x00\xff\xff\x00\x00\xf9\xff\x0f\x00\xfe\xff" \
    b"\x00\x00\xfa\xff\x00\x00\xfc\xff\x01\x00\xfd\xff\x03\x00\xfc\xff" \
    b"\xff\xff\xfc\xff\x00\x00\xfe\xff\x03\x00\xff\xff\x10\x00\xfd\xff" \
    b"\xff\xff\xfb\xff\xfe\xff\xfd\xff\xff\xff\x00\x00\x03\x00\xfc\xff" \
    b"\xfe\xff\xfa\xff\xff\xff\xfe\xff\xff\xff\xfe\xff\x03\x00\xfc\xff" \
    b"\xfe\xff\xfd\xff\xfe\xff\xfb\xff\xfd\xff\x00\x00\x02\x00\xfc\xff" \
    b"\xff\xff\xf8\xff\x00\x00\xfc\xff\x00\x00\xfc\xff\x00\x00\xfd\xff" \
    b"\x01\x00\xfa\xff\xfe\xff\xfd\xff\xfe\xff\xff\xff\xfe\xff\xff\xff" \
    b"\xfe\xff\xfd\xff\x00\x00\xfc\xff\xfe\xff\xfc\xff\x00\x00\xfc\xff" \
    b"\xfd\xff\xfd\xff\xfb\xff\xff\xff\x00\x00\x00\x00\xff\xff\x00\x00" \
    b"\xfd\xff\xf8\xff\x00\x00\xfb\xff\xfe\xff\xfe\xff\x03\x00\xfe\xff" \
    b"\xff\xff\xfb\xff\xfe\xff\xfb\xff\x01\x00\xfe\xff\xff\xff\xfd\xff" \
    b"\x01\x00\xfb\xff\xff\xff\xfb\xff\xfe\xff\xfd\xff\x02\x00\xfe\xff" \
    b"\xfb\xff\xfa\xff\xfd\xff\xfa\xff\xfe\xff\xfe\xff\x00\x00\xfd\xff" \
    b"\x01\x00\xf6\xff\x09\x00\xf6\xff\xfc\xff\xfc\xff\x00\x00\xfe\xff" \
    b"\xfd\xff\xff\xff\xf4\xff\x04\x00\xff\xff\x02\x00\xff\xff\xf5\xff" \
    b"\xfc\xff\x16\x00\xec\xff\xc0\xff\xfc\xff\xfd\xff\x02\x00\x01\x00" \
    b"\xf9\xff\xf2\xff\xe6\xff\xc2\xff\xfe\xff\x17\x00\x04\x00\xf3\xff" \
    b"\xfd\xff\x02\x00\x08\x00\xff\xff\xff\xff\xdf\x00\x00\x00\x09\xf7" \
    b"\xfe\xff\xf5\xff\xf8\xff\xe8\xff\x03\x00\xff\xff\x02\x00\xf8\xff" \
    b"\xfd\xff\xef\xff\x01\x00\x07\x00\x00\x00\xf3\xff\x02\x00\xfb\xff" \
    b"\xfe\xff\xf6\xff\xff\xff\xf7\xff\xff\xff\xf6\xff\xff\xff\xfc\xff" \
    b"\xfd\xff\xf8\xff\x00\x00\xf9\xff\x04\x00\xe2\xff\x01\x00\xf8\xff" \
    b"\x03\x00\xfa\xff\xfc\xff\xfd\xff\xff\xff\xfc\xff\x03\x00\xff\xff" \
    b"\xff\xff\xfa\xff\x01\x00\xfb\xff\x00\x00\xf9\xff\x04\x00\xf9\xff" \
    b"\xfe\xff\xfd\xff\xfc\xff\xfe\xff\x02\x00\xff\xff\x01\x00\x00\x00" \
    b"\xff\xff\xfa\xff\xff\xff\xfe\xff\x02\x00\x00\x00\x00\x00\xfc\xff" \
    b"\xfd\xff\xfd\xff\xff\xff\xff\xff\x01\x00\xff\xff\x01\x00\xff\xff" \
    b"\xfe\xff\xfb\xff\xfe\xff\xff\xff\x01\x00\x03\x00\xff\xff\xfd\xff" \
    b"\x02\x00\xff\xff\x01\x00\xfe\xff\x01\x00\x01\x00\x02\x00\x01\x00" \
    b"\xff\xff\xfe\xff\x00\x00\xfe\xff\x01\x00\x02\x00\x00\x00\x00\x00" \
    b"\x00\x00\x02\x00\xfe\xff\xfd\xff\x00\x00\x02\x00\xfd\xff\x03\x00" \
    b"\x00\x00\x01\x00\x00\x00\x02\x00\x04\x00\x02\x00\x05\x00\x03\x00" \
    b"\x00\x00\x02\x00\xed\xff\x04\x00\x04\x00\x02\x00\xd9\xff\x09\x00" \
    b"\xfd\xff\x03\x00\xf3\xff\xfc\xff\xfe\xff\x03\x00\x00\x00\x03\x00" \
    b"\xff\xff\xfc\xff\xef\xff\x06\x00\x02\x00\x01\x00\xe2\xff\xfc\xff" \
    b"\x05\x00\x04\x00\xb8\xff\x03\x00\xfb\xff\xfd\xff\x0c\x00\x02\x00" \
    b"\xff\xff\xff\xff\xb9\xff\x03\x00\x03\x00\x03\x00\xd7\xff\x15\x00" \
    b"\x02\x00\x00\x00\xc1\xff\x09\x00\xff\xff\x02\x00\x31\x00\xfe\xff" \
    b"\x04\x00\xfe\xff\x23\x00\xf2\xff\x10\x00\xff\xff\x7a\xff\x06\x00" \
    b"\x07\x00\xfe\xff\x94\xff\xfa\xff\xfc\xff\x03\x00\x09\x00\x00\x00" \
    b"\xfb\xff\xff\xff\xa5\xff\xf9\xff\xfe\xff\x01\x00\x25\x00\x12\x00" \
    b"\xfe\xff\x01\x00\xff\xff\x03\x00\x0a\x00\x03\x00\x32\x00\x02\x00" \
    b"\x07\x00\xff\xff\x44\x00\xfe\xff\xf9\xff\xfc\xff\x5d\x00\x08\x00" \
    b"\xf3\xff\xfd\xff\x6b\x00\x08\x00\xfe\xff\xff\xff\xa1\xff\x03\x00" \
    b"\xf6\xff\xfd\xff\x3e\x00\xfe\xff\x08\x00\x03\x00\xd2\xff\x07\x00" \
    b"\x03\x00\x00\x00\xd4\xff\xf8\xff\x03\x00\xff\xff\xfc\xff\x05\x00" \
    b"\xf2\xff\xff\xff\x09\x00\x02\x00\x07\x00\x01\x00\xf0\xff\xfc\xff" \
    b"\x03\x00\xfd\xff\xdb\xff\xff\xff\x02\x00\x03\x00\xfa\xff\x00\x00" \
    b"\x01\x00\xff\xff\x02\x00\xfa\xff\xfe\xff\x00\x00\x17\x00\xfd\xff" \
    b"\xff\xff\xfd\xff\x07\x00\x01\x00\xff\xff\x00\x00\xf6\xff\x01\x00" \
    b"\xfd\xff\xff\xff\x05\x00\xfa\xff\xff\xff\xff\xff\x12\x00\x05\x00" \
    b"\x00\x00\xfe\xff\x25\x00\xfc\xff\x06\x00"

def send_udp_packet(host, port, data, quiet=False):
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.sendto(data, (host, port))
        if not quiet:
            print(f"Sent packet with length {len(data)} to {host}:{port}")
    except Exception as e:
        print(f"Error sending UDP packet: {e}")
    finally:
        sock.close()

def main():
    parser = argparse.ArgumentParser(description="Send UDP packets at regular intervals")
    parser.add_argument("host", help="Destination host IP address")
    parser.add_argument("port", type=int, help="Destination port number")
    parser.add_argument("-q", "--quiet", action="store_true", help="Suppress packet information printing")
    parser.add_argument("-i", "--interval", type=float, default=0.1, help="Packet sending interval in seconds")
    args = parser.parse_args()

    print(len(message))

    try:
        while True:
            send_udp_packet(args.host, args.port, message, args.quiet)
            time.sleep(args.interval)
    except KeyboardInterrupt:
        print("\nUDP packet sending stopped.")

if __name__ == "__main__":
    main()
