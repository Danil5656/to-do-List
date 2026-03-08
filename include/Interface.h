#include "ToDoApp.h"

#include <string>
#include <map>

class Interface
{
public:
    explicit Interface() : my_map({ {"0", 0}, {"1", 1}, {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5} }) {}
       
private:
    std::map<std::string, int> my_map;

public:
    void run()
    {
        std::string line;
        while(true)
        {
            std::cout << "Выберите действие:\n"
            "[1] - Добавить задачу\n"
            "[2] - Показать список задач\n"
            "[3] - Завершить задачу\n"
            "[4] - Удалить задачу\n"
            "[5] - Сохранить задачи в файл\n"
            "[0] - Завершить работу программы" << std::endl;
            //
            if (!std::getline(std::cin, line)) break;
            //
            auto it = my_map.find(line); 
            if (it == my_map.end())
            {
                std::cout << "Некорректный ввод, попробуйте снова" << std::endl;
                continue;
            }
            else
            {
                ToDoApp toDoApp;
                switch(it->second) {
                    case 1:
                        toDoApp.addTask();
                        break;
                    case 2:
                        std::cout << "2" << std::endl;
                        break;
                    case 3:
                        break;
                    case 4:
                        break;
                    case 5:
                        break;
                    case 0:
                        exit(0);
                    default:
                        break;
                }
            }
        }
    }
};
