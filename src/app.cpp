#include <QFont>
#include <QWindow>

#include "app.h"

App::App(int argc, char** argv)
{
    mApp = new QApplication{argc, argv};

    mMainWindow = new MainWindow{800, 600, "Pixel"};
    mMainWindow->show();
}

App::~App()
{
    delete mMainWindow;
    delete mApp;
}

int App::exec()
{
    return mApp->exec();
}
