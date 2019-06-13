#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->widget, SIGNAL(currentMousePosition(QPoint)),
            this, SLOT(currentMousePosition(QPoint)));

    init();
}

MainWindow::~MainWindow()
{
    manager->save("marker.json");
    manager->destroyManager();
    delete ui;
}

bool MainWindow::init()
{
    manager = MarkerManager::getInstance();
    manager->load("marker.json");


    return true;
}

void MainWindow::currentMousePosition(QPoint pos)
{
    ui->statusBar->showMessage(QString("(%1, %2)").arg(pos.x()).arg(pos.y()));
}
