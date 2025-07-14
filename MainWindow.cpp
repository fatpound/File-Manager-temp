#include "MainWindow.hpp"
#include "ui_mainwindow.h"

FM_BEGIN_NAMESPACE

MainWindow::UIManager::UIManager(Ui::MainWindow* theUi, QMainWindow* const pWnd)
{
    theUi->setupUi(pWnd);
}

MainWindow::MainWindow(const QString& title, QWidget* const parent)
    :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_UIMgr_(ui, this),
    m_tab_widget_mgr_left_(ui->tabWidget,    ui->tableView,   ui->label, this),
    m_tab_widget_mgr_right_(ui->tabWidget_2, ui->tableView_2, ui->label, this)
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

FM_END_NAMESPACE
