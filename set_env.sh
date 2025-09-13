#!/bin/bash
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
LOG_FILE="$SCRIPT_DIR/set_env.log"

if ! command -v ts &> /dev/null; then
    echo "'ts' not found, installing moreutils..."
    sudo apt update
    sudo apt install moreutils -y
fi
pushd tools
#install essential tools
./install_essential_tools.sh | tee $LOG_FILE
#install vsomeip and dependencies
if ! command -v ts &> /dev/null; then
    ./install_vsomeip.sh 2>&1 | tee -a $LOG_FILE
    ./install_capi_someip.sh 2>&1 | tee -a $LOG_FILE
    ./install_fidl_gen.sh 2>&1 | ts '[%Y-%m-%d %H:%M:%S]' | tee -a $LOG_FILE
else
    ./install_vsomeip.sh 2>&1 | ts '[%Y-%m-%d %H:%M:%S]' | tee -a $LOG_FILE
    ./install_capi_someip.sh 2>&1 | ts '[%Y-%m-%d %H:%M:%S]' | tee -a $LOG_FILE
    ./install_fidl_gen.sh 2>&1 | ts '[%Y-%m-%d %H:%M:%S]' | tee -a $LOG_FILE
fi
popd
