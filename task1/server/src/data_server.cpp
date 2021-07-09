//
// Created by Kirill Diordiev on 07.07.2021.
//

#include "data_server.h"
#include <iostream>
#include <algorithm>
#include <boost/format.hpp>
#include <vector>
#include <thread>


ZMQPublisher::ZMQPublisher(std::string &socket_address, std::vector<Record> &&data) :
        endpoint(socket_address), data(std::move(data)) {
    socket.bind(endpoint);

}

void ZMQPublisher::notify() {
    usleep(100000);
    zmqpp::message msg;
    std::string msg_content;
    for (auto &i : data) {

        auto msg_temp = boost::format("%s %s\n") % i.fullname % i.bd;
        msg_content += msg_temp.str();
    }

    msg << msg_content;

    do {
        socket.send(msg);
    } while (0);

}

ZMQPublisher::~ZMQPublisher() {
    socket.disconnect(endpoint);
    ctx.terminate();
}

HTTPPublisher::HTTPPublisher(std::string &socket_address) :
        port(socket_address) {
    server.Get("/topic", [](const httplib::Request &, httplib::Response &res) {
        std::string msg_content;
        std::vector<std::string> files = {"student_file_1.txt", "student_file_2.txt"};
        auto data = LoadData(files);
        for (auto &i : data) {

            auto msg_temp = boost::format("%s %s\n") % i.fullname % i.bd;
            msg_content += msg_temp.str();
        }

        res.set_content(msg_content.c_str(), "text/plain");
    });

}

void HTTPPublisher::notify() {
    server.listen("localhost", atoi(port.c_str()));
}