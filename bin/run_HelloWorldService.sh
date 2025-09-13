#!/bin/bash
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
export VSOMEIP_APPLICATION_NAME=xxxx-sample
export VSOMEIP_CONFIGURATION=$SCRIPT_DIR/../config/HelloWorldService.json
export COMMONAPI_CONFIG=$SCRIPT_DIR/../config/commonapi.ini
pushd "$SCRIPT_DIR"
# Get start time
START_TIME=$(date +%Y%m%d_%H%M%S)

# Start tcpdump in the background
tcpdump -i eth0 -w "tcpdump_${START_TIME}_to_END.pcap" &
TCPDUMP_PID=$!

# Run your application
./HelloWorldService

# After sender exits, get end time
END_TIME=$(date +%Y%m%d_%H%M%S)

# Kill tcpdump
kill $TCPDUMP_PID

# Rename the file with end time
mv "tcpdump_${START_TIME}_to_END.pcap" "tcpdump_${START_TIME}_to_${END_TIME}.pcap"
popd