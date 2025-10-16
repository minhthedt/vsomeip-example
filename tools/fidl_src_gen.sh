#!/bin/bash
set -e
# Variables
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

CAPI_CORE_BIN="$SCRIPT_DIR/download/commonapi_core_generator/commonapi-core-generator-linux-x86_64"
CAPI_SOMEIP_BIN="$SCRIPT_DIR/download/commonapi_someip_generator/commonapi-someip-generator-linux-x86_64"

FIDL_FILE="$SCRIPT_DIR/../src/capi-example/fidl/HelloWorld.fidl"
FDEPL_FILE="$SCRIPT_DIR/../src/capi-example/fidl/HelloWorld.fdepl"
FIDL_CORE_SRC_GEN="$SCRIPT_DIR/../src/capi-example/fidl-src-gen/core"
FIDL_SOMEIP_SRC_GEN="$SCRIPT_DIR/../src/capi-example/fidl-src-gen/someip"

mkdir -p "$FIDL_CORE_SRC_GEN" "$FIDL_SOMEIP_SRC_GEN"

check_and_install_java() {
    if command -v java >/dev/null 2>&1; then
        echo "[OK] Java already installed: $(java -version 2>&1 | head -n 1)"
    else
        echo "[INFO] Java not found. Installing OpenJDK..."
        sudo apt update
        # You can change openjdk-11-jdk → openjdk-8-jdk if you need Java 8
        sudo apt install -y openjdk-11-jdk
        if command -v java >/dev/null 2>&1; then
            echo "[OK] Java installed successfully: $(java -version 2>&1 | head -n 1)"
        else
            echo "[ERROR] Failed to install Java. Please check manually."
            exit 1
        fi
    fi
}
check_and_install_java


if [ -f "$CAPI_CORE_BIN" ]; then
    $CAPI_CORE_BIN -d $FIDL_CORE_SRC_GEN -sk $FIDL_FILE
else 
    echo "Error: not found $CAPI_CORE_BIN"
fi

if [ -f "$CAPI_SOMEIP_BIN" ]; then
    $CAPI_SOMEIP_BIN -d $FIDL_SOMEIP_SRC_GEN  $FDEPL_FILE
else 
    echo "Error: not found $CAPI_CORE_BIN"
fi