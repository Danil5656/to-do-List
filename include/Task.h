#pragma once

#include <filesystem>
#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>
#include <ctime>
#include <map>

namespace fs = std::filesystem;
namespace
{
    std::map<uint16_t, std::string> m_priorityToString = { {1, "Низкий"}, {2, "Средний"}, {3, "Высокий"} };
}

class Task
{
public: 
    Task(){}
    //
    Task(const std::string &description, uint16_t priority):
    m_description(description), m_priority(priority) {}
    //
    Task(const std::string &description, uint16_t priority, uint64_t idTask):
    m_description(description), m_priority(priority), m_idTask(idTask) {}

    void markCompleted()
    {
        m_isCompleted = true;
        m_dateCompleted = getCurrentTime();
    }

    std::string getCurrentTime()
    {
        std::time_t now = std::time(nullptr);
        std::tm* ltm = std::localtime(&now);
        std::ostringstream oss;
        oss << std::put_time(ltm, "%d.%m.%Y %H:%M:%S");
        return oss.str();
    }

private:
    const std::string fileName = "/home/user/to-do-list/src/tasks.txt";

public:
    static uint64_t m_numberTask;
    uint64_t m_idTask;
    uint16_t m_priority;
    std::string m_dateAdded = getCurrentTime();
    bool m_isCompleted = false;
    std::string m_dateCompleted = "";
    std::string m_description;
};
