#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <string>
#include <QTimer>
#include <sstream>
#include <ctime>
#include <iomanip>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_taskManager("tasks.txt")
    , m_draftTimer(new QTimer(this))
    , m_editingIndex(-1)
{
    ui->setupUi(this);
    connect(ui->pushButtonAdd, &QPushButton::clicked,
            this, &MainWindow::onAddTask);
    connect(ui->pushButtonDelete, &QPushButton::clicked,
            this, &MainWindow::onDeleteTask);
    connect(ui->pushButtonEdit, &QPushButton::clicked,
            this, &MainWindow::onEditTask);

    m_saveThread = new QThread(this);
    m_save = new Save();
    m_save->moveToThread(m_saveThread);

    connect(this, &MainWindow::requestSave, m_save, &Save::saveTasks);
    m_saveThread->start();

    connect(this, &MainWindow::requestSaveDraft, m_save, &Save::saveDraft);

    m_draftTimer->setInterval(2000);
    connect(m_draftTimer, &QTimer::timeout, this, &MainWindow::onSaveDraftTimer);
    m_draftTimer->start();

    m_taskManager.loadFromFile();
    refreshTaskList();
    loadDraft();
}

MainWindow::~MainWindow()
{
    m_draftTimer->stop();
    m_saveThread->quit();
    m_saveThread->wait();
    delete m_save;
    delete ui;
}

void MainWindow::onSaveDraftTimer()
{
    std::string draftText = ui->lineEditTask->text().toStdString();
    emit requestSaveDraft(draftText);
}

void MainWindow::loadDraft()
{
    std::ifstream file("draft.txt");
    if (file.is_open())
    {
        std::string content;
        std::getline(file, content);
        file.close();
        ui->lineEditTask->setText(QString::fromStdString(content));
    }
}

void MainWindow::onAddTask()
{
    std::string text = ui->lineEditTask->text().toStdString();
    if (text.empty())
    {
        return;
    }

    if (m_editingIndex >= 0)
    {
        m_taskManager.editTask(m_editingIndex, text);
        m_editingIndex = -1;
        ui->pushButtonAdd->setText("Add task");

        ui->pushButtonEdit->setText("Edit task");
        ui->pushButtonEdit->setEnabled(true);
        ui->pushButtonDelete->setText("Delete task");
        ui->pushButtonDelete->setEnabled(true);
    }
    else
    {
        Task newTask;
        newTask.setDescription(text);
        m_taskManager.addTask(newTask);
    }

    ui->lineEditTask->clear();
    refreshTaskList();
    emit requestSave(m_taskManager.getTasks());
    emit requestSaveDraft("");
}

void MainWindow::onDeleteTask()
{
    int currentRow = ui->listWidget->currentRow();
    if (currentRow < 0)
    {
        return;
    }

    m_taskManager.removeTask(currentRow);
    refreshTaskList();

    emit requestSave(m_taskManager.getTasks());
}

void MainWindow::onEditTask()
{
    int currentRow = ui->listWidget->currentRow();
    if (currentRow < 0)
    {
        return;
    }

    const Task& task = m_taskManager.getTaskAt(currentRow);
    ui->lineEditTask->setText(QString::fromStdString(task.getDescription()));
    ui->lineEditTask->setFocus();
    m_editingIndex = currentRow;
    ui->pushButtonAdd->setText("Save changes");

    ui->pushButtonEdit->setText("");
    ui->pushButtonEdit->setEnabled(false);
    ui->pushButtonDelete->setText("");
    ui->pushButtonDelete->setEnabled(false);

}

void MainWindow::refreshTaskList()
{
    ui->listWidget->clear();
    for (int i = 0; i < m_taskManager.getSize(); i++)
    {
        const Task& task = m_taskManager.getTaskAt(i);
        std::time_t time = std::chrono::system_clock::to_time_t(task.getTimeStamp());
        std::tm* tm = std::localtime(&time);

        std::stringstream ss;
        ss << std::put_time(tm, "%d.%m.%Y %H:%M");
        std::string dateTimeStr = ss.str();

        QString displayText = QString::fromStdString(
            "(" + dateTimeStr + ") " + task.getDescription()
            );

        ui->listWidget->addItem(displayText);
    }
}
