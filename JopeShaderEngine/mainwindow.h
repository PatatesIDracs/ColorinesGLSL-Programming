#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class OpenGLWidget;

namespace Ui {
class MainWindow;
}

class Hierarchy;
class Inspector;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void resizeEvent(QResizeEvent* event) override;

private:
    Ui::MainWindow  *ui;

    Hierarchy   *hierarchy;
    Inspector   *inspector;
};

#endif // MAINWINDOW_H
