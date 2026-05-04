#include "Save.h"
#include <QFile>
#include <QTextStream>
#include <fstream>

Save::Save(QObject *parent)
    : QObject(parent)
    , m_filename("tasks.txt") {}

Save::~Save() {}

void Save::saveTasks(const std::vector<Task> &tasks)
{
    QFile file(m_filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream out(&file);
    for (const Task &task : tasks)
    {
        out << task.toLine() << "\n";
    }
    file.close();
}

void Save::saveDraft(const std::string text)
{
    std::ofstream file("draft.txt", std::ios::trunc);
    if (file.is_open())
    {
        file << text;
    }
    file.close();
}
