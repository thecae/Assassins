#include "../include/Log.h"
#include <chrono>
#include <iostream>

Log::Log()
{
    aLog.clear();
    pLog.clear();

    std::string logFile = "gamelog.txt";
    std::ifstream lFile(logFile);
    if (!lFile.is_open()) {
        std::cerr << "Unable to open log file [R]: " << logFile << std::endl;
        exit(1);
    }
    std::string aInfo;
    while (lFile >> aInfo)
        aLog << aInfo;
    lFile.close();

    std::string playerFile = "playerlog.txt";
    std::ifstream pFile(playerFile);
    if (!pFile.is_open()) {
        std::cerr << "Unable to open log file [R]: " << logFile << std::endl;
        exit(1);
    }
    std::string pInfo;
    while (pFile >> pInfo)
        pLog << pInfo;
    pFile.close();
}

Log::~Log()
{
    std::string logFile = "gamelog.txt";
    std::ofstream lFile(logFile);
    if (!lFile.is_open()) {
        std::cerr << "Unable to open log file [W]: " << logFile << std::endl;
        exit(1);
    }
    lFile << aLog.str();
    lFile.close();

    std::string playerFile = "playerlog.txt";
    std::ofstream pFile(playerFile);
    if (!pFile.is_open()) {
        std::cerr << "Unable to open log file [W]: " << logFile << std::endl;
        exit(1);
    }
    pFile << pLog.str();
    pFile.close();
}

void Log::playerLog(const std::string &info)
{
    pLog << info;
    pLog << std::endl;
}

void Log::activityLog(const std::string &category, const std::string &info)
{
    auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    aLog << "[" << strtok(ctime(&time), "\n") << "] ";
    aLog << "[ " << category << " ] ";
    aLog << info << std::endl;
}