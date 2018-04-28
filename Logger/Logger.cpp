#include <ctime>

#include "Logger.h"

void Logger::log(string message) {
    if (!debug) return;

    time_t timestamp = std::time(nullptr);
    string timeString = asctime(localtime(&timestamp));
    timeString.pop_back();
    string pid = to_string(getpid());
    string logMessage = "pid: " + pid + " (" + timeString + ") " + message + "\n";


    lock.tomarLock();
    lock.escribir(logMessage.c_str(), logMessage.length());
    lock.liberarLock();
}

Logger::Logger(string output, bool debug) :
    lock(LockFile(output)),
    debug(debug) {}

Logger::~Logger() = default;