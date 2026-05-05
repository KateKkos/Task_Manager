#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <vector>
#include <string>
#include "Task.h"

class TaskManager
{
private:
    std::vector<Task> tasks; //контейнер для хранения задач
    std::string filename; //хранилище задач, "база данных"

public:
    TaskManager(const std::string& file); //конструктор

    void addTask(const Task& task); //добавить задачу в вектор
    void removeTask(int index); //удалить задачу из вектора
    void loadFromFile(); //загрузить в вектор задачи из файла при запуске программы
    const Task& getTaskAt(int index) const; //получить ссылку на задачу по индексу
    std::vector<Task> getTasks() const; //получить копию списка задач
    int getSize() const; //длина списка задач
    void clear(); //очистить вектор
};

#endif // TASKMANAGER_H
