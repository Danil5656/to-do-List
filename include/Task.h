#pragma once

#include <map>
#include <filesystem>

namespace fs = std::filesystem;
namespace
{
    std::map<uint16_t, std::string> m_priorityToString = 
    { 
        { 1, "Низкий"  },
        { 2, "Средний" },
        { 3, "Высокий" } 
    };
    
    /**
    * @brief Формирует строку с текущим временем системы
    * @return std::string - Дата и время в формате "ДД.ММ.ГГГГ ЧЧ:ММ:СС"
    */
    std::string getCurrentTime()
    {
        std::time_t now = std::time(nullptr);
        std::tm* ltm = std::localtime(&now);
        std::ostringstream oss;
        oss << std::put_time(ltm, "%d.%m.%Y %H:%M:%S");
        return oss.str();
    }
}

/**
 * @class Task
 * @brief Класс, представляющий отдельную задачу в списке
 */
class Task
{
public: 
    explicit Task(){ fileName = (std::filesystem::current_path() / "../tasks.txt").string(); }
    explicit Task(const std::string &description, const uint16_t priority);
    explicit Task(const std::string &description, const uint16_t priority, const uint64_t idTask);
    void markCompleted();

private:
    std::string fileName = "../tasks.txt"; ///< Путь к файлу базы данных

public:
    static uint64_t m_numberTask;          ///< Статический счетчик для генерации ID
    uint64_t m_idTask;                     ///< Идентификатор задачи
    uint16_t m_priority;                   ///< Приоритет (1-Низкий, 2-Средний, 3-Высокий)
    std::string m_dateAdded;               ///< Дата и время создания задачи
    bool m_isCompleted = false;            ///< Флаг состояния: выполнена/не выполнена
    std::string m_dateCompleted;           ///< Дата и время завершения задачи
    std::string m_description;             ///< Текстовое описание задачи
};
