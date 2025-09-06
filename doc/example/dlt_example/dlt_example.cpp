#include <dlt/dlt.h>

/*
- On Ubuntu (192.168.1.5)
1)install DLT with:
  sudo apt update && sudo apt install dlt-daemon libdlt-dev dlt-tools
2)verify dlt-daeon is running
  sudo systemctl status dlt-daemon
3)verify dlt-daemon listening on default tcp port 3490
    sudo ss -tlnp | grep 3490

- On Windows:
4) verify can connect to DLT daemon
  pkgmgr /iu:"TelnetClient"
  telnet 192.168.1.5 3490
5) download and run dlt-viwer
https://github.com/COVESA/dlt-viewer/releases
Ecu id: ECU1
Tcp IP: 192.168.1.5
Tcp port: 3490

- From Windows -> vbee(ubuntu)
1) because we can connect SSH from Windows to vbee(ubuntu) via port 41624
2) we need to forward the DLT port 3490 from vbee(ubuntu)
ssh -p 41624 -L 3490:localhost:3490 worker@thevu-unbuntu-1.vbee.lge.com

3) now we can connect to DLT daemon from Windows
Ecu id: ECU1
Tcp IP: 127.0.0.1
Tcp port: 3490
*/

DLT_DECLARE_CONTEXT(my_context);

int main() {
    DLT_REGISTER_APP("MYAPP", "My Example App");

    DLT_REGISTER_CONTEXT(my_context, "MAIN", "Main Context");

    while (true) {
        DLT_LOG(my_context, DLT_LOG_DEBUG, DLT_STRING("Debug level message"));
        DLT_LOG(my_context, DLT_LOG_INFO,  DLT_STRING("Info level message"));
        DLT_LOG(my_context, DLT_LOG_WARN,  DLT_STRING("Warning message"));
        DLT_LOG(my_context, DLT_LOG_ERROR, DLT_STRING("Error occurred"));
        DLT_LOG(my_context, DLT_LOG_FATAL, DLT_STRING("Fatal issue happened"));
        printf("Hello from DLT logging! was send via DLT\n");
        sleep(10); // Avoid busy-wait
    }

   


    DLT_UNREGISTER_CONTEXT(my_context);
    DLT_UNREGISTER_APP();

    return 0;
}