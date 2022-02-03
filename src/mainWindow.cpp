#include <string_view>
#include <fstream>
#include <sstream>

#include <QMenu>
#include <QMenuBar>
#include <QApplication>
#include <QTextEdit>
#include <QFileDialog>

#include "mainWindow.h"

MainWindow::MainWindow(int width, int height, std::string_view title, QWidget* parent)
    : QMainWindow(parent)
{
    this->resize(width, height);
    this->setWindowTitle(QString{title.data()});

    createMenus();
    createEditor();
}

void MainWindow::createMenus()
{
    QMenu* fileMenu = menuBar()->addMenu("&File");

    QAction* quit = new QAction{"&Quit", this};
    fileMenu->addAction(quit);
    connect(quit, &QAction::triggered, qApp, QApplication::quit);

    QAction* open = new QAction{"&Open", this};
    fileMenu->addAction(open);
    connect(open, &QAction::triggered, this, &MainWindow::openFileDialog);
}

void MainWindow::createEditor()
{
    mEditor = new QTextEdit{this};
    setCentralWidget(mEditor);
}

void MainWindow::openFileDialog()
{
    mPathToCurrentFile =
        QFileDialog::getOpenFileName(this, "Open File to Edit", mDefaultStartDir);

    openFileForEditing(mPathToCurrentFile);
}

void MainWindow::openFileForEditing(const QString& name)
{
    std::fstream file{name.toStdString()};

    std::stringstream contents;
    contents << file.rdbuf();

    mEditor->setText(contents.str().c_str());
}
