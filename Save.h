#ifndef SAVE_H
#define SAVE_H

#include <QObject>
#include "Task.h"
#include <vector>
#include <string>

class Save : public QObject
{
Q_OBJECT

public:
    explicit Save(QObject *parent = nullptr); //конструктор; запрет на неявное преобразование типов
    ~Save(); //деструктор

public slots:
    void saveTasks(const std::vector<Task> &tasks); //сохранение задач в файл, выполняется в отдельном потоке
    void saveDraft(const std::string text); //сохранение вводимой задачи

private:
    QString m_filename; //файл, куда происходит сохранение
};

#endif // SAVE_H
