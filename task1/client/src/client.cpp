#include <zmqpp/zmqpp.hpp>
#include <string>
#include <iostream>
#include "data_client.h"


int main(int argc, char *argv[]) {
    std::string endpoint = "tcp://localhost:5555";
    std::string port = "8080";


    HTTPSubscriber http_subscriber(port);

    ZMQSubscriber zmq_subscriber(endpoint);

    std::thread http_thread(&HTTPSubscriber::receive, &http_subscriber);
    std::thread zmq_thread(&ZMQSubscriber::receive, &zmq_subscriber);

    http_thread.join();
    zmq_thread.join();

    std::thread http_thread_sort(&HTTPSubscriber::sort, &http_subscriber);
    std::thread zmq_thread_sort(&ZMQSubscriber::sort, &zmq_subscriber);


    http_thread_sort.join();
    zmq_thread_sort.join();

    return 0;
}
