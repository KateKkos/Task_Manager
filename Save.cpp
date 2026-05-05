#include "Save.h"
#include <fstream>

Save::Save(QObject *parent)
    : QObject(parent)
    , m_filename("tasks.txt") {}

Save::~Save() {}

void Save::saveTasks(const std::vector<Task> &tasks)
{
    std::ofstream file(m_filename);
    if (!file.is_open())
    {
        return;
    }

    for(const Task &task : tasks)
    {
        file << task.toLine() << "\n";
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
