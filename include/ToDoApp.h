#pragma once

#include "Task.h"

#include <vector>

namespace
{
    namespace fs = std::filesystem;
    //
    void clearScreen()
    {
        #ifdef _WIN32
            std::system("cls");
        #else
            std::system("clear");
        #endif
    }
}
/**
 * @class ToDoApp
 * @brief Класс управления списком задач
 */
class ToDoApp
{
public:
    explicit ToDoApp() { fileName = (std::filesystem::current_path() / "../tasks.txt").string(); }
    bool init();
    bool convertStrToTask(std::string &line, Task &task);
    void addTask();
    void showAllTasks();
    void completeTask();
    void deleteTask();
    void saveTasks();
    void sortTaskByDefault();
    void sortTasksByPriority();
    void sortTasksByDate();

private:
    std::vector<Task> fileTasks;            ///< Список задач, считанных из файла
    std::vector<Task> allTasks;             ///< Общий рабочий список задач
    std::string fileName = "../tasks.txt";  ///< Путь к файлу базы данных
};