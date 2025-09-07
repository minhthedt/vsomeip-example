#!/bin/bash
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
export VSOMEIP_CONFIGURATION=../config/vsomeip_receiver.json
export VSOMEIP_LOG=warn

# Get start time
START_TIME=$(date +%Y%m%d_%H%M%S)

# Start tcpdump in the background
tcpdump -i eth0 -w "tcpdump_${START_TIME}_to_END.pcap" &
TCPDUMP_PID=$!

# Run your application
 ./response-sample

# After sender exits, get end time
END_TIME=$(date +%Y%m%d_%H%M%S)

# Kill tcpdump
kill $TCPDUMP_PID

# Rename the file with end time
mv "tcpdump_${START_TIME}_to_END.pcap" "tcpdump_${START_TIME}_to_${END_TIME}.pcap"