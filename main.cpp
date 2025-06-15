#include "MainWindow.hpp"

#include <QApplication>

// NOLINTBEGIN(readability-static-accessed-through-instance)
int main(int argc, char *argv[])
{
    const QApplication app(argc, argv);

    const MainWindow wnd{"File-Manager © fatpound 2025"};

    return app.exec();
}
// NOLINTEND(readability-static-accessed-through-instance)
