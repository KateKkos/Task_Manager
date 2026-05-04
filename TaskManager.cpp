#include "TaskManager.h"

#include <QFile>
#include <QTextStream>

TaskManager::TaskManager(const QString& file) : filename(file){}

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
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream in(&file);
    tasks.clear();
    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (!line.isEmpty())
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
