#!/bin/bash
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
export VSOMEIP_CONFIGURATION=$SCRIPT_DIR/../config/routingmanagerd.json
export VSOMEIP_LOG=warn

pushd "$SCRIPT_DIR"
# Run your application
 ./routingmanagerd
popd