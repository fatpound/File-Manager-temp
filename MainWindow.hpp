#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "TabWidgetManager.hpp"

#include <QMainWindow>
#include <QWidget>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QString& title, QWidget* parent = nullptr);

    explicit MainWindow()                      = delete;
    explicit MainWindow(const MainWindow&)     = delete;
    explicit MainWindow(MainWindow&&) noexcept = delete;

    auto operator = (const MainWindow&)     -> MainWindow& = delete;
    auto operator = (MainWindow&&) noexcept -> MainWindow& = delete;
    ~MainWindow() override;


protected:


private:
    struct UIManager final
    {
        UIManager(Ui::MainWindow* theUi, QMainWindow* pWnd);
    };


private:
    Ui::MainWindow*    ui;
    UIManager          m_UIMgr_;

    TabWidgetManager   m_tab_widget_mgr_left_;
    TabWidgetManager   m_tab_widget_mgr_right_;


private slots:
    void on_action_eXit_triggered();
};

#endif // MAINWINDOW_HPP
