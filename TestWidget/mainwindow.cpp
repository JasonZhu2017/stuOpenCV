#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets/QFileDialog>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRect centerRect = ui->centralWidget->geometry();
    int x = centerRect.x();
    int y = centerRect.y();
    int w = centerRect.width();
    int h = centerRect.height();
    std::cout << x <<"\t" << y << "\t" << w << "\t" << h << std::endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionFileOpen_triggered()
{
   QFileDialog *fileDlg = new QFileDialog(this,
                                          tr("open file"),
                                          tr("./"),
                                          QString("image file (.jpg .png .jpeg .bmp)"));
   QString fileName = fileDlg->getOpenFileName();
//   if (! fileName.isEmpty()) {

//   }
}

void MainWindow::on_pushButton_clicked()
{

}
