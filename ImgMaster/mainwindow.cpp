#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QTabBar>
#include <QStatusBar>
#include <QAction>
#include <QKeySequence>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(800,500);
//    this->setWindowState(Qt::WindowMaximized);
//    imgView(ui->centralWidget);
//    imgView.setParent(this);
    QRect centRect = ui->centralWidget->geometry();
    qDebug() << centRect;
    ui->centralWidget->setGeometry(this->geometry());
    imgView.setParent(ui->centralWidget);
    imgView.adjustWindow();
//    QWidget* widget = ui->centralWidget;
//    imgView(widget);
//    this->setWindowState(Qt::WindowMaximized);
    QAction *pOpenAct = new QAction(QIcon(":/images/file-open"),tr("&Open..."),this);
    pOpenAct->setShortcut(QKeySequence::Open);
    pOpenAct->setStatusTip(tr("open a file"));
    connect(pOpenAct, &QAction::triggered, this, &MainWindow::fileOpen);
    QMenu* pFileMenu = ui->menuBar->addMenu(tr("&File"));
    ui->mainToolBar->setIconSize(QSize(36,36));
    pFileMenu->addAction(pOpenAct);
    ui->mainToolBar->addAction(pOpenAct);
    ui->statusBar->addAction(pOpenAct);


    QMenu * pProcMenu = ui->menuBar->addMenu(tr("&Process"));
    QToolBar* pProcToolBar = addToolBar("&Process");
    pProcToolBar->setIconSize(QSize(36,36));

    QAction * pInverseAct = new QAction(QIcon(":/images/proc-inverse"), tr("in&Verse"), this);
    pInverseAct->setStatusTip("inverse image");
    connect(pInverseAct, &QAction::triggered, this, &MainWindow::procInverse);
    pProcMenu->addAction(pInverseAct);
    pProcToolBar->addAction(pInverseAct);
    ui->statusBar->addAction(pInverseAct);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fileOpen()
{
    QFileDialog * pDlg = new QFileDialog();
    pDlg->setWindowTitle(tr("open"));
    pDlg->setDirectory(".");
    pDlg->setFilter(QDir(tr("Image Files(*.png *.jpg *.jepg *.bmp)")).filter());
//    pDlg->setAttribute(Qt::WA_DeleteOnClose);
    if (pDlg->exec() == QDialog::Accepted){
        QString pathName = pDlg->selectedFiles()[0];
//        QMessageBox::information(NULL, tr("path"), tr("you selected ")+ pathName );
        image.readImg(pathName);
        imgView.showQImage(image.cvtToQImage());
    }else{
//        QMessageBox::information(NULL, tr("path"), tr("you didn't selected any image file."));
        qDebug() << "you didn't selected any image file.";
    }

//      method 2
//    QString pathName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.png *.jpg *.jepg *.bmp)"));
//    if (pathName.length() == 0){
//        QMessageBox::information(NULL, tr("path"), tr("you didn't selected any image file."));
//        return;
//    }else{
//        QMessageBox::information(NULL, tr("path"), tr("you selected ") + pathName);
//    }
}

void MainWindow::procInverse()
{
    ;
}
