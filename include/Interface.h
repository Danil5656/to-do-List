#pragma once

#include "ToDoApp.h"

#include <map>

class Interface
{
public:
    explicit Interface() {}
       
public:
    void run()
    {
        ToDoApp toDoApp;
        if (!toDoApp.init()) return;
        //
        while(true)
        {
            std::cout << "Выберите операцию:\n"
            "[1] - Добавить задачу\n"
            "[2] - Показать список задач\n"
            "[3] - Завершить задачу\n"
            "[4] - Удалить задачу\n"
            "[5] - Отсортировать задачи по умолчанию\n"
            "[6] - Отсортировать задачи по приоритету\n"
            "[7] - Отсортировать задачи по дате добавления\n"
            "[8] - Сохранить задачи в файл\n"
            "[0] - Завершить работу программы" << std::endl;
            //
            std::string sz_input;
            if (!std::getline(std::cin, sz_input) || sz_input.empty()) continue;
            if (sz_input.size() > 1)
            {
                clearScreen();
                std::cerr << "Ошибка: неверный формат числа" << std::endl;
                continue;
            }
            uint8_t choice;
            try
            {
                choice = std::stoi(sz_input);
            }
            catch (const std::invalid_argument& e) 
            {
                clearScreen();
                std::cerr << "Ошибка: неверный формат числа" << std::endl;
                continue;
            }
            //
            switch (choice) {
            case 1:
                toDoApp.addTask();
                break;
            case 2:
                toDoApp.showAllTasks();
                break;
            case 3:
                toDoApp.completeTask();
                break;
            case 4:
                toDoApp.deleteTask();
                break;
            case 5:
                toDoApp.sortTaskByDefault();
                break;
            case 6:
                toDoApp.sortTasksByPriority();
                break;
            case 7:
                toDoApp.sortTasksByDate();
                break;
            case 8:
                toDoApp.saveTasks();
                break;
            case 0:
                clearScreen();
                std::cout << "Успешное завершение работы программы" << std::endl;
                exit(0);
            default:
                clearScreen();
                std::cout << "Ошибка: некорректный ввод, попробуйте снова" << std::endl;
                break;
            }
        }
    }
};
