#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "updatedialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setVersion()
{
    QSettings conf(updateDialog::confName, QSettings::IniFormat);
    ui->versionLabel->setText(conf.value("cv").toString());
}
