#include "../include/ToDoApp.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

bool ToDoApp::init()
{
    if (!fs::exists(fileName))
    {
        return true;
    }
    //
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cerr << "Ошибка: невозможно открыть файл tasks.txt" << std::endl;
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
            std::cerr << "Ошибка: невозможно конвертировать строку в объект задачи" << std::endl;
            continue;
        }
        fileTasks.push_back(task);
    }
    std::copy(fileTasks.begin(), fileTasks.end(), std::back_inserter(allTasks));
    //показываем список задач при старте ПО если они присутствуют
    this->showAllTasks();
    return true;
}
//сериализовать строку из файла в объект задачи
bool ToDoApp::convertStrToTask(std::string &line, Task &task)
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
    if (parts.size() < 5) 
    {
        return false; // Минимум 5 полей
    }
    //TODO обернуть в блок try except std::stoi
    task.m_idTask      = static_cast<uint64_t>(std::stoi(parts[0]));
    task.m_description = parts[1];
    task.m_priority    = std::stoi(parts[2]);
    task.m_dateAdded   = parts[3];
    task.m_isCompleted = (parts[4] == "1");
    //
    if (task.m_isCompleted && parts.size() == 6) 
    {
        task.m_dateCompleted = parts[5];
    }
    //
    return true;
}
//добавить задачу в список
void ToDoApp::addTask()
{
    clearScreen();
    std::cout << "Введите описание задачи: " << std::endl;
    std::string description;
    std::getline(std::cin, description);
    //
    clearScreen();
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
        clearScreen();
        std::cerr << "Ошибка: неверный формат числа. Операция добавления задачи отменена" << std::endl;
        return;
    }
    //
    if (!priority)
    {
        clearScreen();
        std::cout << "Операция добавления задачи отменена" << std::endl;
        return;
    }
    //
    if (priority >= 1 && priority <= 3) 
    {
        clearScreen();
        allTasks.emplace_back(description, priority, Task::m_numberTask);
        ++Task::m_numberTask;
        std::cout << "Операция добавления задачи успешно выполнена" << std::endl;
    }
    else
    {
        clearScreen();
        std::cerr << "Ошибка: некорректное значение приоритета. Операция добавления задачи отменена" << std::endl;
        return;
    }
}
//показать список задач
void ToDoApp::showAllTasks()
{
    clearScreen();
    if (allTasks.empty()) 
    {
        std::cout << "Список задач пуст. Для добавление задачи в список выберите операцию [1]" << std::endl;
        return;
    }
    //
    std::cout << "Список задач:" << std::endl;
    for (const Task & task : allTasks)
    {
        std::string sz_isCompleted = !task.m_isCompleted ? "Не завершена" : "Завершена";
        std::cout <<
        "№"                   << task.m_idTask                          << " | " <<
        "Описание: "          << task.m_description                     << " | " <<
        "Приоритет: "         << m_priorityToString.at(task.m_priority) << " | " <<
        "Дата добавления: "   << task.m_dateAdded                       << " | " <<
        "Статус: "            << sz_isCompleted;
        if (task.m_isCompleted)
        {
            std::cout << " | " << "Дата завершения: " << task.m_dateCompleted;
        }
        std::cout << std::endl;
    }
}
//завершить задачу
void ToDoApp::completeTask()
{
    clearScreen();
    if (allTasks.empty()) 
    {
        std::cout << "Список задач пуст. Для добавление задачи в список выберите операцию [1]" << std::endl;
        return;
    }
    //
    this->showAllTasks();
    std::cout << "Введите номер задачи для завершения: ";
    std::string sz_idTask;
    std::getline(std::cin, sz_idTask);
    uint64_t idTask;
    try
    {
        idTask = std::stoi(sz_idTask);
    }
    catch(const std::exception& e)
    {
        clearScreen();
        std::cerr << "Ошибка: неверный формат числа. Операция завершения задачи отменена" << std::endl;
        return;
    }
    //ищем задачу с введеным номером пользователя в списке
    Task *findTask = nullptr;
    for (Task & task : allTasks)
    {
        if (task.m_idTask == idTask)
        {
            findTask = &task;
        }
    }
    //
    if (findTask == nullptr)
    {
        clearScreen();
        std::cout << "Задача с номером " << idTask << " не найдена. Операция завершения задачи отменена" << std::endl;
        return;
    }
    //
    clearScreen();
    findTask->markCompleted();
    std::cout << "Операция завершения задачи успешно выполнена" << std::endl;
}
//удалить задачу из списка
void ToDoApp::deleteTask()
{
    clearScreen();
    if (allTasks.empty()) 
    {
        std::cout << "Список задач пуст. Для добавление задачи в список выберите операцию [1]" << std::endl;
        return;
    }
    //
    this->showAllTasks();
    std::cout << "Введите номер задачи для удаления: ";
    std::string sz_findTask;
    std::getline(std::cin, sz_findTask);
    uint64_t findTask;
    try
    {
        findTask = std::stoi(sz_findTask);
    }
    catch(const std::exception& e)
    {
        clearScreen();
        std::cerr << "Ошибка: неверный формат числа. Операция удаления задачи отменена" << std::endl;
        return;
    }
    //находим индекс удаленной задачи
    int removedIndex = -1;
    for(int i = 0; i < allTasks.size(); ++i) 
    {
        if(allTasks[i].m_idTask == findTask) 
        {
            removedIndex = i;
            break;
        }
    }
    //
    if (removedIndex == -1) 
    {
        clearScreen();
        std::cout << "Задача с номером " << findTask << " не найдена. Операция завершения задачи отменена" << std::endl;
        return;
    }
    //удаляем задачу из списка
    allTasks.erase(allTasks.begin() + removedIndex);
    //обновляем id у хвоста после удаления
    for (int i = removedIndex; i < allTasks.size(); ++i) 
    {
        allTasks[i].m_idTask--;
    }
    clearScreen();
    --Task::m_numberTask;
    std::cout << "Операция завершения задачи успешно выполнена" << std::endl;
}
//сохранить задачи в файл
void ToDoApp::saveTasks()
{
    clearScreen();
    if (allTasks.empty()) 
    {
        std::cout << "Список задач пуст. Для добавление задачи в список выберите операцию [1]" << std::endl;
        return;
    }
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
    //
    file.close();
    std::cout << "Операция сохранения задач в файл успешно выполнена" << std::endl;
}

void ToDoApp::sortTaskByDefault()
{
    clearScreen();
    if (allTasks.empty()) 
    {
        std::cout << "Список задач пуст. Нечего фильтровать" << std::endl;
        return;
    }
    //
    std::sort(allTasks.begin(), allTasks.end(), [](const Task& a, const Task& b) 
    {
        return a.m_idTask < b.m_idTask;
    });
    std::cout << "Задачи успешно отсортированы по умолчанию" << std::endl;
}

void ToDoApp::sortTasksByPriority()
{
    clearScreen();
    if (allTasks.empty()) 
    {
        std::cout << "Список задач пуст. Нечего фильтровать" << std::endl;
        return;
    }
    //
    std::sort(allTasks.begin(), allTasks.end(), [](const Task& a, const Task& b) 
    {
        return a.m_priority < b.m_priority; 
    });
    std::cout << "Задачи успешно отсортированы по приоритету" << std::endl;
}

void ToDoApp::sortTasksByDate()
{
    clearScreen();
    if (allTasks.empty()) 
    {
        std::cout << "Список задач пуст. Нечего фильтровать" << std::endl;
        return;
    }
    //
    std::sort(allTasks.begin(), allTasks.end(), [](const Task& a, const Task& b) 
    {
        return a.m_dateAdded < b.m_dateAdded;
    });
    std::cout << "Задачи успешно отсортированы по дате добавления" << std::endl;
}