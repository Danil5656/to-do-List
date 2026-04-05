#include "../include/Task.h"


uint64_t Task::m_numberTask = 1;

/**
 * @brief Конструктор создания новой задачи
 * @param description текстовое описание задачи
 * @param priority числовой приоритет (1-3)
 */
Task::Task(const std::string &description, const uint16_t priority):
    m_description(description), m_priority(priority) 
{
    fileName = (std::filesystem::current_path() / "../tasks.txt").string();
}

/**
 * @brief Конструктор для восстановления задачи из файла
 * @param description текстовое описание задачи
 * @param priority числовой приоритет (1-3)
 * @param idTask Идентификатор задачи, прочитанный из файла
 */
Task::Task(const std::string &description, const uint16_t priority, const uint64_t idTask):
    m_description(description), m_priority(priority), m_idTask(idTask) 
{
    fileName = (std::filesystem::current_path() / "../tasks.txt").string();
}

/**
 * @brief Переводит задачу в состояние "Выполнено"
 */
void Task::markCompleted()
{
    m_isCompleted = true;
    m_dateCompleted = getCurrentTime();
}