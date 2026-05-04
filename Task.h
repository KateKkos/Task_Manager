#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QMetaType>

class Task
{
private:
    QString description; //сам текст задачи
public:
    Task(); //конструктор

    QString getDescription() const; //получить переменную с текстом задачи
    void setDescription(const QString& desc); //задать текст задачи

    QString toLine() const;   //получить строку с текстом задачи (планируется модифицировать)
    static Task fromLine(const QString& line); //получить задачу с заданным текстом
};

//объявляем, какие типы можно передавать между потоками
Q_DECLARE_METATYPE(Task)
Q_DECLARE_METATYPE(std::vector<Task>)

#endif // TASK_H
