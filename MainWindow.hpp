#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "TableViewManager.hpp"
#include "TabWidgetManager.hpp"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QString& title, QWidget* parent = nullptr);

    explicit MainWindow(const MainWindow&)     = delete;
    explicit MainWindow(MainWindow&&) noexcept = delete;

    auto operator = (const MainWindow&)     -> MainWindow& = delete;
    auto operator = (MainWindow&&) noexcept -> MainWindow& = delete;
    ~MainWindow() override;


protected:


private slots:
    void on_action_eXit_triggered();


private:
    struct UIManager final
    {
        UIManager(Ui::MainWindow*& theUi, QMainWindow* pWnd);
    };


private:
    Ui::MainWindow* ui;

    UIManager m_UIMgr_;

    TableViewManager m_TableViewMgr_;
    // TableManager m_TableViewMgr2_;

    TabWidgetManager m_TabWidgetMgr_;
    // TabManager m_TabWidgetMgr2_;
};

#endif // MAINWINDOW_HPP
