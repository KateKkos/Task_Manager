#include "Task.h"
#include <iomanip>
#include <ctime>
#include <sstream>

static std::string timeToString(const std::chrono::system_clock::time_point& tp)
{
    std::time_t time = std::chrono::system_clock::to_time_t(tp);
    std::tm* tm = std::localtime(&time);

    std::stringstream ss;
    ss << std::put_time(tm, "%d.%m.%Y %H:%M:%S");

    return ss.str();
}

static std::chrono::system_clock::time_point stringToTime(const std::string& str)
{
    std::tm tm = {};
    std::stringstream ss(str);
    ss >> std::get_time(&tm, "%d.%m.%Y %H:%M:%S");

    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

Task::Task()
    : description("")
    , creationTime(std::chrono::system_clock::now()) {}

const std::string Task::getDescription() const
{
    return description;
}

void Task::setDescription(const std::string& desc)
{
    description = desc;
}

std::chrono::system_clock::time_point Task::getCreationTime() const
{
    return creationTime;
}

const std::string Task::toLine() const
{
    return timeToString(creationTime) + " | " + description;
}

Task Task::fromLine(const std::string& line)
{
    Task task;

    size_t separatorPos = line.find(" | ");
    if (separatorPos != std::string::npos)
    {
        std::string timeStr = line.substr(0, separatorPos);
        task.description = line.substr(separatorPos + 3);
        task.creationTime = stringToTime(timeStr);
    }
    else
    {
        task.description = line;
        task.creationTime = std::chrono::system_clock::now();
    }

    return task;
}

void Task::updateDescription(const std::string& newDesc)
{
    description = newDesc;
}
