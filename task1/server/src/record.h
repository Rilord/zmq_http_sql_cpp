//
// Created by Kirill Diordiev on 08.07.2021.
//

#pragma once

#include <fstream>
#include <sstream>
#include <vector>


struct Record {
    Record() = delete;
    Record(std::string &fullname, std::string &bd) : fullname(fullname), bd(bd) {}
    std::string fullname;
    std::string bd;
};

bool operator < (const Record &a, const Record &b);
bool operator == (const Record &a, const Record &b);


std::vector<Record> LoadData(std::vector<std::string> &files);
