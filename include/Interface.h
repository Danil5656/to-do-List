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
        //показать список задач при запуске, без вывода сообщений если файл отсутствует
        //getAllTasks(false);
        //
        while(true)
        {
            std::cout << "Выберите действие:\n"
            "[1] - Добавить задачу\n"
            "[2] - Показать список задач\n"
            "[3] - Пометить задачу выполненной\n"
            "[4] - Удалить задачу\n"
            "[5] - Сохранить задачи в файл\n"
            "[0] - Завершить работу программы" << std::endl;
            //
            std::string sz_input;
            if (!std::getline(std::cin, sz_input) || sz_input.empty()) continue;
            uint8_t choice;
            try
            {
                choice = std::stoi(sz_input);
            }
            catch (const std::invalid_argument& e) 
            {
                std::cerr << "Ошибка: неверный формат числа" << std::endl;
                continue;
            }
            //
            switch(choice) {
                case 1:
                    toDoApp.addTask();
                    break;
                case 2:
                    toDoApp.showAllTasks();
                    break;
                case 3:
                    toDoApp.showAllTasks();
                    toDoApp.markTask();
                    break;
                case 4:
                    toDoApp.showAllTasks();
                    toDoApp.deleteTask();
                    break;
                case 5:
                    toDoApp.saveTasks();
                    break;
                case 0:
                    exit(0);
                default:
                    std::cout << "Ошибка: некорректный ввод, попробуйте снова" << std::endl;
                    break;
            }
        }
    }
};
