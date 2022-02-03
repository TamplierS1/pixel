#pragma once

#include <QMainWindow>

class MainWindow : public QMainWindow
{
public:
    MainWindow(int width = 800, int height = 600, std::string_view title = "Main Window",
               QWidget* parent = nullptr);
};
