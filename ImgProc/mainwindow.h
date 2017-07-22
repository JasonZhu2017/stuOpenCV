#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//#include <QObject>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMenu>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QAction>
#include <QtWidgets/QFileDialog>
#include <QDebug>
#include <iostream>
#include <view/imageview.h>
#include <view/colorreducepanel.h>
#include <view/basicpanel.h>
#include <view/viewpanelc2r2.h>
#include <view/viewpanelc3.h>
#include <controller/corecontroller.h>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public:  //for ui
    QWidget * centralWidget;
    //menu
    QMenuBar * mainMenuBar;
    QMenu * fileMenu;
    QMenu * panelMenu;
    //toolbar
    QToolBar * mainToolBar;
    QToolBar * panelToolBar;
    QStatusBar *statusBar;
    //dockwidget
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    //for process panel
    QStackedWidget* procPanelsStack;
    ColorReducePanel* cReducePanel;
    BasicPanel * basicPanel;
    QWidget* generalPanel;
    //for view show pannel
    QStackedWidget * viewPanelsStack;
    ViewPanelC2R2 * pViewPanelC2R2;
    ViewPanelC3 * pViewPanelC3;
    //layout
    QHBoxLayout * mainLayout;
    //file operate action
    QAction * fileOpenAction;
    QAction * fileSaveAction;
    //panel switch action
    QAction * firstPanelAction;
    QAction * secondPanelAction;
    QAction * thirdPanelAction;
    QAction * fourthPanelAction;
    //view switch action
    QAction * viewSwitchAction;
    //for ui

public:
    void closeEvent(QCloseEvent *event);

private:
    void setupUi();
    void initWidget();
    void initAction();
    void initMenu();
    void initToolBar();
    void initConnect();
    void initProcPanelsStack();
    void initViewPanelsStack();

private slots:
    void slot_fileOpenAct();
    void slot_fileSaveAct();
    void slot_procPanelSwitch();
    void showImg();
    void slot_flip();
    void slot_colorReduce();

};

#endif // MAINWINDOW_H
