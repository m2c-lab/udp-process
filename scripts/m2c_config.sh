#!/bin/sh
sudo ip a add 192.168.1.199/24 dev enp1s0f0
 
# Use the following to check the connection with netcat.
# $ nc -u -v -p 1234 192.168.1.128 1234
