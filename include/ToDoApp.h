#pragma once

#include "Task.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

class ToDoApp
{
public:
    ToDoApp() {}

    bool init()
    {
        if (!fs::exists(fileName)) 
        {
            return true;
        }
        //
        std::ifstream file(fileName);
        if (!file.is_open())
        {
            std::cerr << "Ошибка открытия файла tasks.txt" << std::endl;
            return false;
        }
        //
        std::string line;
        while(std::getline(file, line))
        {
            ++Task::m_numberTask;
            Task task;
            if (!convertStrToTask(line, task))
            {
                std::cerr << "Ошибка конвертации" << std::endl;
                continue;
            }
            fileTasks.push_back(task);
        }
        std::copy(fileTasks.begin(), fileTasks.end(), std::back_inserter(allTasks));
        return true;
    }
    //
    bool convertStrToTask(std::string &line, Task &task)
    {
        std::vector<std::string> parts;
        std::stringstream ss(line);
        std::string field;
        //разбиваем строку по '|'
        while (std::getline(ss, field, '|')) 
        {
            parts.push_back(field);
        }
        //
        if (parts.size() < 5) return false; // Минимум 5 полей
        //
        task.m_idTask      = static_cast<uint64_t>(std::stoi(parts[0]));
        task.m_description = parts[1];
        task.m_priority    = std::stoi(parts[2]);
        task.m_dateAdded   = parts[3];
        task.m_isCompleted = (parts[4] == "1");
        //
        if (task.m_isCompleted && parts.size() > 5) 
        {
            task.m_dateCompleted = parts[5];
        }
        //
        return true;
    }

    void addTask()
    {
        std::cout << "Введите описание задачи: " << std::endl;
        std::string description;
        std::getline(std::cin, description);
        //
        std::cout << "Введите приоритет задачи:\n"
        "[1] - Низкий\n"
        "[2] - Средний\n"
        "[3] - Высокий\n"
        "[0] - Отменить создание задачи и вернуться в главное меню\n";
        //
        std::string sz_priority;
        std::getline(std::cin, sz_priority);
        uint8_t priority;
        try 
        {
            priority = std::stoi(sz_priority);
        } 
        catch (const std::invalid_argument& e)
        {
            std::cerr << "Ошибка: неверный формат числа! " << std::endl;
            return;
        }
        //
        if (priority >= 1 && priority <= 3) 
        {
            allTasks.emplace_back(description, priority, Task::m_numberTask);
            ++Task::m_numberTask;
            std::cout << "Задача успешно добавлена в список" << std::endl;
        }
    }

    void showAllTasks(bool isShowError = true)
    {
        for (const Task & task : allTasks)
        {
            std::string sz_isCompleted = !task.m_isCompleted ? "Не завершена" : "Завершена";
            std::cout << "№ задачи: " << task.m_idTask << " | " << "Описание: " << task.m_description << " | " <<
            "Приоритет: " << m_priorityToString.at(task.m_priority) << " | " << "Дата добавления: " << task.m_dateAdded << 
            " | " << "Статус завершения: " << sz_isCompleted << "\n";
        }
    }
    //
    void deleteTask()
    {
        std::cout << "Введите номер задачи для удаления" << std::endl;
        std::string sz_numberTask;
        std::getline(std::cin, sz_numberTask);
        uint64_t numberTask;
        try
        {
            numberTask = std::stoi(sz_numberTask);
        }
        catch (const std::invalid_argument& e) 
        {
            std::cerr << "Ошибка: неверный формат числа" << std::endl;
            return;
        }
        //
        std::ifstream file(fileName);
        std::string line;
        uint64_t numberLine = 0;
        //
        while(std::getline(file, line))
        {
            ++numberLine;
            // if (line[1] == numberTasks)
            // {

            // }
        }
    }

    void markTask()
    {
        std::cout << "Hello World";
    }

    void saveTasks()
    {
        //реализовать сохранении копии файла с задачами перед удалением
        //
        fs::remove(fileName);
        //
        std::ofstream file(fileName, std::ios::app);
        if(!file.is_open())
        {
            std::cerr << "Ошибка: не удалось открыть файл tasks.txt" << std::endl;
            return;
        }
        //
        for (const Task & task : allTasks)
        {
            file << task.m_idTask << "|" << task.m_description << "|" << task.m_priority << "|" << 
            task.m_dateAdded << "|" << task.m_isCompleted;
            if (task.m_isCompleted)
            {
                file << "|" << task.m_dateCompleted;
            }
            file << "\n";
        }
        file.close();
        std::cout << "Задачи успешно сохранены в файл" << std::endl;
    }

    void sortTasksByDate();

    void sortTasksByPriority();

    void findTask();

private:
    std::vector<Task> fileTasks;
    std::vector<Task> allTasks;
    const std::string fileName = "/home/user/to-do-list/src/tasks.txt";
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