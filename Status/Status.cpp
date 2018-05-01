#include <cstdio>
#include <unistd.h>

#include "./Status.h"

Status* Status::instance = 0;

Status* Status::getInstance() {
    if (instance == nullptr) {
        instance = new Status();
    }

    return instance;
}

void Status::AddFileDescriptor(int fileDescriptor) {
    Status::getInstance()->fileDescriptors.push_back(fileDescriptor);
}

void Status::CloseFileDescriptors() {
    for(auto &fileDescriptor : Status::getInstance()->fileDescriptors) {
        close(fileDescriptor);
    }
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);
}

Status::Status() = default;
Status::~Status() = default;