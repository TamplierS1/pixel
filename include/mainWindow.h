#pragma once

#include <QMainWindow>
#include <QTextEdit>

class MainWindow : public QMainWindow
{
public:
    MainWindow(int width = 800, int height = 600, std::string_view title = "Main Window",
               QWidget* parent = nullptr);

private:
    void createMenus();
    void createEditor();

    void openFileDialog();
    void openFileForEditing(const QString& name);

    QString mDefaultStartDir = ".";
    QString mPathToCurrentFile;

    QTextEdit* mEditor = nullptr;
};
