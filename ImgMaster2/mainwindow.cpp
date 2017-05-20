#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>
#include <QDebug>
#include <QColorDialog>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    openAction = new QAction(QIcon(":/images/file-open"), tr("&Open..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));
    connect(openAction, &QAction::triggered, this, &MainWindow::fileOpen);

    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QToolBar * toolBar = addToolBar(tr("&File"));
    QSize iconsize = QSize(32, 32);
    toolBar->setIconSize(iconsize);
    QStatusBar * statusbar = statusBar();
    mountAction(openAction, fileMenu, toolBar, statusbar);

    newAction = new QAction(QIcon(":/images/file-new"), tr("&New..."), this);
    newAction->setShortcuts(QKeySequence::New);
    newAction->setStatusTip(tr("make a new file"));
    connect(newAction, &QAction::triggered, this, &MainWindow::fileNew);
    mountAction(newAction, fileMenu, toolBar, statusbar);

    saveAction = new QAction(QIcon(":/images/file-save"), tr("&Save..."), this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("save file"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::fileSave);
    mountAction(saveAction, fileMenu, toolBar, statusbar);

    settingAction = new QAction(QIcon(":/images/setting"), tr("&Setting..."), this);
    settingAction->setStatusTip(tr("setting..."));
    QMenu * TOOLSMenu = menuBar()->addMenu(tr("&Tools"));
    QToolBar * TOOLSBar = addToolBar(tr("&Tools"));
    TOOLSBar->setIconSize(iconsize);
    connect(settingAction, &QAction::triggered, this, &MainWindow::settingSys);
    mountAction(settingAction, TOOLSMenu, TOOLSBar, statusbar);

    colorAction = new QAction(QIcon(":/images/set-color"), tr("set &color"), this);
    colorAction->setStatusTip(tr("set color"));
    connect(colorAction, &QAction::triggered, this, &MainWindow::setColor);
    mountAction(colorAction, TOOLSMenu, TOOLSBar, statusbar);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QAction *MainWindow::getSaveAction() const
{
    return saveAction;
}

void MainWindow::setSaveAction(QAction *value)
{
    saveAction = value;
}

void MainWindow::fileSave()
{
    QMessageBox::information(this, tr("information"), tr("file Save"));
}

void MainWindow::settingSys()
{
    QWidget * settingWindow = new QWidget();
    //settingWindow->deleteLater();//
    settingWindow->setAttribute(Qt::WA_DeleteOnClose);
    settingWindow->setWindowTitle(tr("setting"));

    QSpinBox *spinBox = new QSpinBox(settingWindow);
    QSlider * slider = new QSlider(Qt::Horizontal, settingWindow);
    spinBox->setRange(0, 130);
    slider->setRange(0, 130);
    QObject::connect(slider, &QSlider::valueChanged, spinBox, QSpinBox::setValue);
    void (QSpinBox:: * spinBoxSignal) (int) = &QSpinBox::valueChanged;
    QObject::connect(spinBox, spinBoxSignal, slider, QSlider::setValue);
    spinBox->setValue(35);

    QHBoxLayout * layout =  new QHBoxLayout();
    layout->addWidget(spinBox);
    layout->addWidget(slider);
    settingWindow->setLayout(layout);
    settingWindow->show();
}

void MainWindow::setColor()
{
    QColorDialog * colorDlg = new QColorDialog();
    colorDlg->setAttribute(Qt::WA_DeleteOnClose);
    colorDlg->show();
}

void MainWindow::mountAction(QAction *action, QMenu *menu, QToolBar *toolbar, QStatusBar *statusbar)
{
    menu->addAction(action);
    toolbar->addAction(action);
    statusbar->addAction(action);
}

void fileOpen()
{
    //QMessageBox::information(this, tr("information"),tr("Open"));
    //    QDialog openDialog(this);
    QFileDialog * fileDlg = new QFileDialog();
    fileDlg->setAttribute(Qt::WA_DeleteOnClose);
    fileDlg->show();
}

void MainWindow::fileNew()
{
    //QMessageBox::information(this, tr("make a new image"), tr("New file"));
    QDialog * newDialog =  new QDialog();
    newDialog->setAttribute(Qt::WA_DeleteOnClose);
    newDialog->setWindowTitle(tr("new file"));
    newDialog->show();
}
