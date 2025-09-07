
#!/bin/bash
echo "START----------$0"

sudo apt update

# Helper function
install_if_missing() {
    pkg="$1"
    if dpkg -s "$pkg" >/dev/null 2>&1; then
        echo "[OK] $pkg already installed"
    else
        echo "[INSTALL] $pkg"
        sudo apt-get install -y "$pkg"
    fi
}

# Development tools
for p in openssh-server screen git; do install_if_missing "$p"; done

# Build tools
for p in autoconf automake libtool build-essential cmake pkg-config zlib1g-dev; do install_if_missing "$p"; done

# DLT
for p in dlt-daemon libdlt-dev dlt-tools; do install_if_missing "$p"; done

# Boost
for p in libboost-system-dev libboost-thread-dev libboost-log-dev \
         libboost-program-options-dev libboost-regex-dev libboost-filesystem-dev; do install_if_missing "$p"; done

# Networking
for p in net-tools netcat socat tcpdump; do install_if_missing "$p"; done

echo "END----------$0"