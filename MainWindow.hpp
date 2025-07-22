#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "_macros.hpp"
#include "TabWidgetManager.hpp"

#include <QMainWindow>
#include <QWidget>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

FM_BEGIN_NAMESPACE

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
    virtual ~MainWindow() override;


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

FM_END_NAMESPACE

#endif // MAINWINDOW_HPP
