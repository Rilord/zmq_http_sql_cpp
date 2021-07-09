#include <zmqpp/zmqpp.hpp>
#include <string>
#include "data_server.h"
#include <thread>

using namespace std;

int main(int argc, char *argv[]) {
    string endpoint = "tcp://*:5555";
    string port = "8080";

    vector<string> data = {"data/student_file_1.txt", "data/student_file_2.txt"};

    HTTPPublisher http_publisher(port);

    ZMQPublisher zmq_publisher(endpoint, LoadData(data));


    std::thread http_thread(&HTTPPublisher::notify, &http_publisher);
    std::thread zmq_thread(&ZMQPublisher::notify, &zmq_publisher);

    zmq_thread.join();
    http_thread.join();

    return 0;
}
