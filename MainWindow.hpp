#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    explicit MainWindow(const MainWindow&)     = delete;
    explicit MainWindow(MainWindow&&) noexcept = delete;

    auto operator = (const MainWindow&)     -> MainWindow& = delete;
    auto operator = (MainWindow&&) noexcept -> MainWindow& = delete;
    ~MainWindow() override;


protected:


private slots:
    void on_action_eXit_triggered();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_HPP
