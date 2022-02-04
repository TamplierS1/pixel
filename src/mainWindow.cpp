#include <fstream>
#include <sstream>
#include <filesystem>

#include <QMenu>
#include <QMenuBar>
#include <QApplication>
#include <QTextEdit>
#include <QFileDialog>

#include "nlohmann/json.hpp"

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

    readCache();

    if (!mPathToCurrentFile.isEmpty())
        openFileForEditing(mPathToCurrentFile);
}

void MainWindow::createMenus()
{
    QMenu* fileMenu = menuBar()->addMenu("&File");

    QAction* open = new QAction{"&Open", this};
    fileMenu->addAction(open);
    connect(open, &QAction::triggered, this, &MainWindow::openFileDialog);

    QAction* save = new QAction{"&Save", this};
    fileMenu->addAction(save);
    connect(save, &QAction::triggered, this, &MainWindow::saveCache);
    connect(save, &QAction::triggered, this, &MainWindow::saveFileDialog);

    QAction* quit = new QAction{"&Quit", this};
    fileMenu->addAction(quit);
    connect(quit, &QAction::triggered, qApp, QApplication::quit);

    connect(qApp, &QApplication::aboutToQuit, this, &MainWindow::saveCache);
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

void MainWindow::readCache()
{
    std::string cache_path = std::filesystem::temp_directory_path().string().append(
        "/" + mCacheFileName.toStdString());

    if (!std::filesystem::exists(cache_path))
        return;

    std::fstream cache{cache_path};
    nlohmann::json jcache;
    cache >> jcache;

    mPathToCurrentFile = jcache["last_opened_file"].get<std::string>().c_str();
    if (!std::filesystem::exists(mPathToCurrentFile.toStdString()))
        mPathToCurrentFile.clear();
}

void MainWindow::saveCache() const
{
    std::string cache_path = std::filesystem::temp_directory_path().string().append(
        "/" + mCacheFileName.toStdString());

    std::ofstream cache{cache_path};

    nlohmann::json jcache;
    jcache["last_opened_file"] = mPathToCurrentFile.toStdString();

    cache << jcache;
}
