#!/bin/bash
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
export VSOMEIP_APPLICATION_NAME=notify-sample
export VSOMEIP_CONFIGURATION=/home/worker/TRAINING/VSOMEIP-example/vsomeip_notifier.json
 ./notify-sample