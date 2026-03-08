#include "Task.h"

#include <iostream>
#include <string>
#include <vector>

class ToDoApp
{
public:
    //ToDoApp() : currentTasksIndex(0) {}
    ToDoApp() {}
    ~ToDoApp() {};

    void addTask()
    {
        std::cout << "Введите описание задачи: " << std::endl;
        std::string description;
        std::getline(std::cin, description);
        //
        std::cout << "Введите приоритет задачи\n"
        "[1] - Низкий\n"
        "[2] - Средний\n"
        "[3] - Высокий\n"
        "[0] - Отменить создание задачи и вернуться в главное меню\n";
        //
        int priority;
        std::cin >> priority;
        //
        if (priority >= 1 && priority <= 3) 
        {
            Task task(description, priority);
            tasks.push_back(task);
            std::cout << "Задача успешно добавлена в список задач" << std::endl;
        }
        else
        {
            return;
        }
    }

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