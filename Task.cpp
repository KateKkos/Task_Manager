#include "Task.h"

Task::Task() : description("") {}

const std::string Task::getDescription() const
{
    return description;
}

void Task::setDescription(const std::string& desc)
{
    description = desc;
}

const std::string Task::toLine() const
{
    return description;
}

Task Task::fromLine(const std::string& line)
{
    Task task;
    task.setDescription(line);
    return task;
}
