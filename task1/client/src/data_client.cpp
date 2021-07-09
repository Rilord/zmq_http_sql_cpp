//
// Created by Kirill Diordiev on 07.07.2021.
//

#include "data_client.h"
#include <sstream>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

#define HTTP_CLIENT_TIMEOUT 100

void PrintData(std::vector<Record> &result) {
    for (auto &row : result)
        std::cout << row.fullname << " " << row.bd << std::endl;
}

void DataUnpackAndSort(std::string &body) {
    std::vector<Record> result;
    std::istringstream f(body);
    std::string buffer;
    std::vector<std::string> temp_row;

    while (std::getline(f, buffer)) {
        boost::algorithm::split(temp_row, buffer, boost::is_any_of(" "));
        auto fullname = temp_row[0] + " " + temp_row[1];
        result.push_back(Record(fullname, temp_row[2]));
    }

    std::sort(result.begin(), result.end());

    PrintData(result);
}

ZMQSubscriber::ZMQSubscriber(std::string &socket_address) : endpoint(socket_address) {
    socket.subscribe("");
    socket.connect(endpoint);
}

void ZMQSubscriber::receive() {

    std::string msg;

    socket.receive(msg);

    temp = msg;
}

ZMQSubscriber::~ZMQSubscriber() {
    socket.disconnect(endpoint);
    ctx.terminate();
}

void ZMQSubscriber::sort() {
    DataUnpackAndSort(temp);
}


HTTPSubscriber::HTTPSubscriber(std::string &endpoint) :
        port(endpoint), client("localhost", atoi(endpoint.c_str())) {

}


void HTTPSubscriber::receive() {

    auto res = client.Get("/topic");

    if (res) {

        temp = res->body;


        return;

    }
}


void HTTPSubscriber::sort() {
    DataUnpackAndSort(temp);
}

void HTTPSubscriber::PrintData() {
    for (auto &row : data)
        std::cout << row.fullname << " " << row.bd << "\n";
}