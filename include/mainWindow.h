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
    void saveFileDialog();
    void readFile(const QString& name);
    void saveCurrentFile();

    void readCache();
    void saveCache() const;

    QString mDefaultStartDir = ".";
    QString mPathToCurrentFile;
    QString mCacheFileName = "pixel_cache.json";

    QTextEdit* mEditor = nullptr;
};
