#include <string_view>
#include <fstream>
#include <sstream>

#include <QMenu>
#include <QMenuBar>
#include <QApplication>
#include <QTextEdit>
#include <QFileDialog>

#include "mainWindow.h"

static QString getFileNameFromPath(const QString& path)
{
    if (path.isEmpty())
        return path;

    QString filename;
    for (int i = path.size() - 1; i < 0; i--)
    {
        if (path[i] == '/')
            break;
        filename.prepend(path[i]);
    }
    return filename;
}

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

    QAction* open = new QAction{"&Open", this};
    fileMenu->addAction(open);
    connect(open, &QAction::triggered, this, &MainWindow::openFileDialog);

    QAction* save = new QAction{"&Save", this};
    fileMenu->addAction(save);
    connect(save, &QAction::triggered, this, &MainWindow::saveFileDialog);

    QAction* quit = new QAction{"&Quit", this};
    fileMenu->addAction(quit);
    connect(quit, &QAction::triggered, qApp, QApplication::quit);
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

void MainWindow::saveFileDialog()
{
    QFileDialog::saveFileContent(mEditor->toPlainText().toLocal8Bit(),
                                 getFileNameFromPath(mPathToCurrentFile));
}

void MainWindow::openFileForEditing(const QString& name)
{
    std::fstream file{name.toStdString()};

    std::stringstream contents;
    contents << file.rdbuf();

    mEditor->setText(contents.str().c_str());
}
