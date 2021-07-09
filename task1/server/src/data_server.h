//
// Created by Kirill Diordiev on 07.07.2021.
//

#pragma once

#include <string>
#include <list>
#include <zmqpp/zmqpp.hpp>
#include "record.h"
#include <httplib.h>


class Publisher { // Abstract
public:
    Publisher() = default;
    virtual void notify() = 0;

};



class ZMQPublisher : public Publisher {
public:
    ZMQPublisher(std::string &socket_address, std::vector<Record> &&data);
    ~ZMQPublisher();

    void notify();
private:
    std::string endpoint;
    zmqpp::context ctx;
    zmqpp::socket_type type = zmqpp::socket_type::pub;
    zmqpp::socket socket = zmqpp::socket(ctx, type);
    std::vector<Record> data;
};

class HTTPPublisher : public Publisher {
public:

    HTTPPublisher(std::string &socket_address);
    ~HTTPPublisher() = default;
    void notify();

private:
    std::string port;
    httplib::Server server;
    std::vector<Record> data;
};