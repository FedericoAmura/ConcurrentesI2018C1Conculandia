#ifndef ADUANACONCULANDIA_STATUS_H
#define ADUANACONCULANDIA_STATUS_H

#include <vector>

using namespace std;

class Status final {
public:
    static void AddFileDescriptor(int fileDescriptor);
    static void CloseFileDescriptors();

    ~Status();

private:
    static Status* instance;
    vector<int> fileDescriptors;

    Status();
    static Status* getInstance();
};


#endif //ADUANACONCULANDIA_STATUS_H
