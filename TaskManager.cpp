#include "TaskManager.h"
#include <fstream>

TaskManager::TaskManager(const std::string& file) : filename(file){}

void TaskManager::addTask(const Task& task)
{
    tasks.push_back(task);
}

void TaskManager::removeTask(int index)
{
    if (index >= 0 && index < static_cast<int>(tasks.size()))
    {
        tasks.erase(tasks.begin() + index);
    }
}

void TaskManager::loadFromFile()
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (!line.empty())
        {
            tasks.push_back(Task::fromLine(line));
        }
    }
    file.close();
}

const Task& TaskManager::getTaskAt(int index) const
{
    if (index < 0 || index >= static_cast<int>(tasks.size()))
    {
        static Task emptyTask;
        return emptyTask;
    }
    return tasks.at(index);
}

int TaskManager::getSize() const
{
    return static_cast<int>(tasks.size());
}

void TaskManager::clear()
{
    tasks.clear();
}

std::vector<Task> TaskManager::getTasks() const
{
    return tasks;
}
