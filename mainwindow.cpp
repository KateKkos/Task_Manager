#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <string>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_taskManager("tasks.txt")
    , m_draftTimer(new QTimer(this))
{
    ui->setupUi(this);
    connect(ui->pushButtonAdd, &QPushButton::clicked,
            this, &MainWindow::onAddTask);
    connect(ui->pushButtonDelete, &QPushButton::clicked,
            this, &MainWindow::onDeleteTask);

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

    Task newTask;
    newTask.setDescription(text);
    m_taskManager.addTask(newTask);
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

void MainWindow::refreshTaskList()
{
    ui->listWidget->clear();
    for (int i = 0; i < m_taskManager.getSize(); i++)
    {
        const Task& task = m_taskManager.getTaskAt(i);
        ui->listWidget->addItem(QString::fromStdString(task.getDescription()));
    }
}
