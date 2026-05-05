#ifndef TASK_H
#define TASK_H

#include <string>
#include <QMetaType>

class Task
{
private:
    std::string description; //сам текст задачи
public:
    Task(); //конструктор

    const std::string getDescription() const; //получить переменную с текстом задачи
    void setDescription(const std::string& desc); //задать текст задачи

    const std::string toLine() const;   //получить строку с текстом задачи (планируется модифицировать)
    static Task fromLine(const std::string& line); //получить задачу с заданным текстом
};

//объявляем, какие типы можно передавать между потоками
Q_DECLARE_METATYPE(Task)
Q_DECLARE_METATYPE(std::vector<Task>)

#endif // TASK_H
