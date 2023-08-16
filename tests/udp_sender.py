# UDP packet sender for testing purposes
# Usage: python3 udp_sender.py <host> <port> [-q] [-i <interval>]
#
# Author: Wuqiong Zhao (me@wqzhao.org)
# Date: 2023-08-16

import socket
import time
import argparse

message = "#" + "0" * 1039 # 1040 bytes

def send_udp_packet(host, port, data, quiet=False):
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.sendto(data.encode(), (host, port))
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

    try:
        while True:
            send_udp_packet(args.host, args.port, message, args.quiet)
            time.sleep(args.interval)
    except KeyboardInterrupt:
        print("\nUDP packet sending stopped.")

if __name__ == "__main__":
    main()
