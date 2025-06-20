g++ -std=c++11 client-example.cpp -o client-example -I /usr/local/include -L /usr/local/lib -lvsomeip3 -lpthread
g++ -std=c++11 service-example.cpp -o service-example -I /usr/local/include -L /usr/local/lib -lvsomeip3 -lpthread
g++ -std=c++11 routingmanagerd.cpp -o routingmanagerd -I /usr/local/include -L /usr/local/lib -lvsomeip3 -lpthread
g++ -std=c++11 notify-sample.cpp -o notify-sample -I /usr/local/include -L /usr/local/lib -lvsomeip3 -lpthread
g++ -std=c++11 subscribe-sample.cpp -o subscribe-sample -I /usr/local/include -L /usr/local/lib -lvsomeip3 -lpthread