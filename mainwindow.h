#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "camera/markermanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool init();

protected slots:
    void currentMousePosition(QPoint pos);

private:
    Ui::MainWindow *ui;

    MarkerManager *manager = NULL;
};

#endif // MAINWINDOW_H
