//
// Created by Kirill Diordiev on 08.07.2021.
//

#include "record.h"

bool operator < (const Record &a, const Record &b) {
    return a.fullname < b.fullname || (
            !(b.fullname < a.fullname) && a.bd < b.bd
    );}

bool operator == (const Record &a, const Record &b) {
    return a.fullname == b.fullname && a.bd == b.bd;
}
std::vector<Record> LoadData(std::vector<std::string> &files) {
    std::vector<Record> records;

    for (auto i = 0; i < files.size(); ++i) {
        std::ifstream file(files[i]);
        int32_t num;
        std::string str;

        while(getline(file, str)) {
            std::istringstream iss(str);
            std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                             std::istream_iterator<std::string>());
            std::string fullname = results[1] + " " + results[2];
            records.push_back(Record(fullname, results[3]));
        }

    }

    std::sort(records.begin(), records.end());
    records.erase(std::unique(records.begin(), records.end()), records.end());


    return records;
}
