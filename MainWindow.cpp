#include "MainWindow.hpp"
#include "ui_mainwindow.h"

MainWindow::UIManager::UIManager(Ui::MainWindow*& theUi, QMainWindow* pWnd)
{
    theUi->setupUi(pWnd);
}

MainWindow::MainWindow(const QString& title, QWidget* parent)
    :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_UIMgr_(ui, this),
    m_TableViewMgr_(ui->tableView, this),
    m_TabWidgetMgr_(ui->tabWidget, this)
{
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    setWindowTitle(title);

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

