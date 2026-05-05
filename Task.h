#ifndef TASK_H
#define TASK_H

#include <string>
#include <QMetaType>
#include <chrono>

class Task
{
private:
    std::string description; //сам текст задачи
    std::chrono::system_clock::time_point creationTime; //время создания задачи
public:
    Task(); //конструктор

    const std::string getDescription() const; //получить переменную с текстом задачи
    void setDescription(const std::string& desc); //задать текст задачи
    std::chrono::system_clock::time_point getCreationTime() const; //получить время создани задачи

    const std::string toLine() const;   //получить строку с текстом задачи (планируется модифицировать)
    static Task fromLine(const std::string& line); //получить задачу с заданным текстом
};

//объявляем, какие типы можно передавать между потоками
Q_DECLARE_METATYPE(Task)
Q_DECLARE_METATYPE(std::vector<Task>)

#endif // TASK_H
