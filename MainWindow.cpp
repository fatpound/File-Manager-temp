#include "MainWindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    show();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_eXit_triggered()
{
    close();
}

