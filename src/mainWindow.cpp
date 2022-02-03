#include <string_view>

#include <QMenu>
#include <QMenuBar>
#include <QApplication>

#include "mainWindow.h"

MainWindow::MainWindow(int width, int height, std::string_view title, QWidget* parent)
    : QMainWindow(parent)
{
    this->resize(width, height);
    this->setWindowTitle(QString{title.data()});

    QAction* quit = new QAction{"&Quit", this};

    QMenu* fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(quit);

    connect(quit, &QAction::triggered, qApp, QApplication::quit);
}
