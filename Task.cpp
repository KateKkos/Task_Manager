#include "Task.h"

Task::Task() : description("") {}

QString Task::getDescription() const
{
    return description;
}

void Task::setDescription(const QString& desc)
{
    description = desc;
}

QString Task::toLine() const
{
    return description;
}

Task Task::fromLine(const QString& line)
{
    Task task;
    task.setDescription(line);
    return task;
}
