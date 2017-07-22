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
#include <imageview.h>
#include <colorreducepanel.h>
#include <corecontroller.h>
#include <basicpanel.h>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public:  //for ui
    QWidget * centralWidget;
    QMenuBar * mainMenuBar;
    QMenu * fileMenu;
    QMenu * panelMenu;
    QToolBar * mainToolBar;
    QToolBar * panelToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QHBoxLayout * mainLayout;
    QGridLayout * viewLayout;
    QStackedWidget* panelsStack;
    ImageView * imgView1, srcView;
    ImageView * imgView2, firstResultView;
    ImageView * imgView3, secondResultView;
    ImageView * imgView4, histView;
    QAction * fileOpenAction;
    QAction * fileSaveAction;
    //panel switch
    QAction * firstPanelAction;
    QAction * secondPanelAction;
    QAction * thirdPanelAction;
    QAction * fourthPanelAction;
    //view switch
    QAction * viewSwitchAction;
    int viewLoopCounter;



    //for operation stack
    ColorReducePanel* cReducePanel;
    BasicPanel * basicPanel;
    QWidget* generalPanel;

    //for operation stack
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
    void setupPanelsStack();

private slots:
    void slot_fileOpenAct();
    void slot_fileSaveAct();
    void slot_panelSwitch();
    void slot_viewSwitch();
    void set_viewShowStyle(int counter);
    void showImg();
    void slot_flip();
    void slot_colorReduce();

};

#endif // MAINWINDOW_H
