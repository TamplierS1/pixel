#pragma once

#include <QApplication>
#include <QMainWindow>

#include "mainWindow.h"

class App
{
public:
    App(int argc, char** argv);
    ~App();

    int exec();

private:
    QApplication* mApp;
    MainWindow* mMainWindow;
};
