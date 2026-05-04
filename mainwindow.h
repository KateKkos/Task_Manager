#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TaskManager.h"
#include <QThread>
#include "Save.h"
#include <QTimer>
#include <string>
#include <fstream>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT //макрос, нужный классам, работающим с сигналами/слотами

signals:
    void requestSave(const std::vector<Task> tasks); //сигнал с копией списка задач на сохранение
    void requestSaveDraft(const std::string text); //сигнал для сохранения строки ввода

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onAddTask(); //добавление задачи в глобальном смысле
    void onDeleteTask(); //удаление задачи в глобальном смысле
    void onSaveDraftTimer(); //таймер, по истечению которого сохраняется строка ввода

private:
    void refreshTaskList(); //обновление списка задач, отображаемого в окне пользователя
    void loadDraft(); //загрузка строки ввода при старте программы
    Ui::MainWindow *ui;
    TaskManager m_taskManager;
    QThread* m_saveThread;
    Save* m_save;
    QTimer* m_draftTimer;
};
#endif // MAINWINDOW_H
