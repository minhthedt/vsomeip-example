#!/bin/bash
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
export VSOMEIP_APPLICATION_NAME=notify-sample
export VSOMEIP_CONFIGURATION=/home/worker/TRAINING/VSOMEIP-example/vsomeip_notifier.json

# Get start time
START_TIME=$(date +%Y%m%d_%H%M%S)

# Start tcpdump in the background
tcpdump -i enp0s3 -w "dump_${START_TIME}_to_END.pcap" &
TCPDUMP_PID=$!

# Run your application
./notify-sample

# After sender exits, get end time
END_TIME=$(date +%Y%m%d_%H%M%S)

# Kill tcpdump
kill $TCPDUMP_PID

# Rename the file with end time
mv "dump_${START_TIME}_to_END.pcap" "dump_${START_TIME}_to_${END_TIME}.pcap"