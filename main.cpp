#include "mainwindow.h"
#include "Task.h"
#include <QApplication>
#include <QMetaType>
#include <vector>
#include <string>

Q_DECLARE_METATYPE(std::string);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<Task>();
    qRegisterMetaType<std::vector<Task>>();
    qRegisterMetaType<std::string>();

    MainWindow w;
    w.show();
    return a.exec();
}

