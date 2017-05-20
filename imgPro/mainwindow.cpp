#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QString>
#include <QFileDialog>
#include <QImage>
#include <QDebug>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pBtn_open_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), tr("."), tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
    if (fileName.isEmpty())
    {
        cout << "filename is empty";
        return;
    }
    if (fileName.isNull())
    {
        cout << "filename is null";
        return;
    }

//    cout << fileName << endl;
    image=cv::imread(fileName.toLatin1().data());
//    cv::namedWindow("original Image");
//    cv::imshow("original Image", image);
    cv::cvtColor(image, image, CV_BGR2RGB);
    QImage img = QImage((const unsigned char*) (image.data), image.cols, image.rows, QImage::Format_RGB888);

    ui->label_img->setPixmap(QPixmap::fromImage(img));
    ui->label_img->resize(ui->label_img->pixmap()->size());
}

void MainWindow::on_pBtn_process_clicked()
{
    cv::flip(image, image, 1);
    QImage img = QImage((const unsigned char*)(image.data), image.cols, image.rows, QImage::Format_RGB888);
    ui->label_img->setPixmap(QPixmap::fromImage(img));
    ui->label_img->resize(ui->label_img->pixmap()->size());

}
