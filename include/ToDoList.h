#include <string>
#include <ctime>
#include <cstdint>
#include <vector>

class Task
{
public: 
    Task(const std::string &description, uint8_t priority, bool isCompleted = false):
    m_description(description), m_isCompleted(isCompleted) {
        m_priority = priority;
        m_dateAdded = getCurrentTime();
        m_dateAdded.pop_back(); //newline
    }
    ~Task();

    void markCompleted()
    {
        m_isCompleted = true;
        m_dateCompleted = getCurrentTime();
    }

    std::string &getCurrentTime()
    {
        time_t now = time(nullptr);
        std::string currentTime = std::ctime(&now);
        return currentTime;
    }

private:
    std::string m_description;
    std::string m_dateAdded;
    std::string m_dateCompleted;
    bool m_isCompleted;
    uint8_t m_priority;
    enum Priority {
        low    = 1,
        medium = 2,
        heigh  = 3
    }
};

class ToDoApp
{
public:
    ToDoApp() : currentTasksIndex(0) {}
    ~ToDoApp();

    void addTask();

    void deleteTask();

    void markTask();

    void getAllTasks();

    void saveTasks();

    void sortTasksByDate();

    void sortTasksByPriority();

    void findTask();

private:
    std::vector<Task> tasks;
    std::vector<Task> completedTasks;
    uint64_t currentTasksIndex;
};

// Общий проект: CLI To-Do List / Список задач в терминале
// Каждый реализует одинаковую функциональность на своём языке. Сравниваем код, производительность, удобство.
// Минимальный функционал (MVP):

// Добавить задачу
// Показать все задачи (с номерами)
// Отметить задачу выполненной (удалить / пометить)
// Удалить задачу
// Сохранить задачи в файл (простой txt или json)
// Загрузить задачи при запуске

// Опционально:

// Приоритет задач (low/medium/high)
// Сортировка по приоритету / дате
// Поиск по тексту
// Простые категории