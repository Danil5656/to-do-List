#include "../include/Task.h"


uint64_t Task::m_numberTask = 1;

Task::Task(const std::string &description, const uint16_t priority):
    m_description(description), m_priority(priority) {}

Task::Task(const std::string &description, const uint16_t priority, const uint64_t idTask):
    m_description(description), m_priority(priority), m_idTask(idTask) {}

void Task::markCompleted()
{
    m_isCompleted = true;
    m_dateCompleted = getCurrentTime();
}