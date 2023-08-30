#!/bin/sh

exe_name="bin/m2c-udp-process"

# First setup Python UDP packets sender
python3 tests/udp_sender.py 127.0.0.1 1234 -q -i1 &
python_pid=$!

# Then run the test
${exe_name} r tests/self.yml -V # verbose mode

# Kill the background Python script process
kill ${python_pid}

echo "Test finished."
