//
// Created by Kirill Diordiev on 07.07.2021.
//

#pragma once

#include <zmq.h>
#include <zmqpp/zmqpp.hpp>
#include "record.h"
#include <httplib.h>


void PrintData(std::vector<Record> &result);
void DataUnpackAndSort(std::string &body);

class Subscriber {
public:
    virtual void receive() = 0;
    Subscriber() = default;
};


class ZMQSubscriber : public Subscriber {
public:
    ZMQSubscriber(std::string &socket_address);
    ~ZMQSubscriber();

    void receive() override;
    void sort();
    void PrintData();

private:
    std::string endpoint;
    std::string temp;
    zmqpp::context ctx;
    zmqpp::socket_type type = zmqpp::socket_type::sub;
    zmqpp::socket socket = zmqpp::socket(ctx, type);
    std::vector<Record> data;
};

class HTTPSubscriber : public Subscriber {
public:
    HTTPSubscriber(std::string &endpoint);
    void receive() override;
    void sort();
    void PrintData();
private:
    std::string port;
    httplib::Client client;
    std::vector<Record> data;
    std::string temp;
};
