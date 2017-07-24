#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
}

MainWindow::~MainWindow()
{

}
void MainWindow::closeEvent(QCloseEvent *event)
{
    CoreController::destroy();
}

void MainWindow::setupUi()
{
    initWidget();
    initAction();
    initMenu();
    initToolBar();
    initConnect();
}

void MainWindow::initWidget()
{
    //init main window
    this->resize(800, 600);
    this->setWindowState(Qt::WindowMaximized);
    centralWidget = new QWidget(this);
    //init process panel
    initProcPanelsStack();
    //init view panel
    initViewPanelsStack();
    //init main layout
    mainLayout = new QHBoxLayout();
    mainLayout->addWidget(viewPanelsStack);
    mainLayout->addWidget(procPanelsStack);
    mainLayout->setSpacing(5);
    mainLayout->setMargin(5);
    centralWidget->setLayout(mainLayout);
    this->setCentralWidget(centralWidget);
    //init status bar
    statusBar = new QStatusBar(this);
    this->setStatusBar(statusBar);
    //init dock widget
    dockWidget = new QDockWidget(this);
    dockWidgetContents = new QWidget();
    dockWidget->setWidget(dockWidgetContents);
//    dockWidget->setVisible(false);
    this->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget);
}
void MainWindow::initAction()
{
    fileOpenAction = new QAction(QIcon(":/icon/file_open"), QString("&Open..."), this);
    fileOpenAction->setShortcuts(QKeySequence::Open);
    fileOpenAction->setStatusTip(QString("Open an exiting image file"));
    fileSaveAction = new QAction(QIcon(":/icon/file_save"), QString("&Save File"), this);
    fileSaveAction->setShortcuts(QKeySequence::Save);
    fileSaveAction->setStatusTip(QString("Save an exiting image file"));
    firstPanelAction = new QAction(QIcon(":/icon/panel_1st"), QString("1st panel"), this);
    firstPanelAction->setObjectName(QString("firstPanelAction"));
    firstPanelAction->setStatusTip(QString("switch first panel"));
    secondPanelAction = new QAction(QIcon(":/icon/panel_2nd"), QString("2nd panel"), this);
    secondPanelAction->setObjectName(QString("secondPanelAction"));
    secondPanelAction->setStatusTip(QString("switch second panel"));
    thirdPanelAction = new QAction(QIcon(":/icon/panel_3rd"), QString("3rd panel"), this);
    thirdPanelAction->setObjectName(QString("thirdPanelAction"));
    thirdPanelAction->setStatusTip(QString("switch third panel"));
    fourthPanelAction = new QAction(QIcon(":/icon/panel_4th"), QString("4th panel"), this);
    fourthPanelAction->setObjectName(QString("fourthPanelAction"));
    fourthPanelAction->setStatusTip(QString("switch fourth panel"));
    viewSwitchAction = new QAction(QIcon(":/icon/view_switch"), QString("view switch"), this);
    viewSwitchAction->setStatusTip(QString("switch view style"));
}

void MainWindow::initMenu()
{
    mainMenuBar = new QMenuBar(this);
    mainMenuBar->setGeometry(QRect(0, 0, 400, 23));
    this->setMenuBar(mainMenuBar);
    fileMenu = new QMenu(QString("&File"),mainMenuBar);
    mainMenuBar->addMenu(fileMenu);
    fileMenu->addAction(fileOpenAction);
    fileMenu->addAction(fileSaveAction);
    panelMenu = new QMenu(QString("&Panel"), mainMenuBar);
    mainMenuBar->addMenu(panelMenu);
    panelMenu->addAction(firstPanelAction);
    panelMenu->addAction(secondPanelAction);
    panelMenu->addAction(thirdPanelAction);
    panelMenu->addAction(fourthPanelAction);
    panelMenu->addSeparator();
    panelMenu->addAction(viewSwitchAction);
}

void MainWindow::initToolBar()
{
    mainToolBar = new QToolBar(this);
    QSize iconSize(30,30);
    mainToolBar->setIconSize(iconSize);
    this->addToolBar(Qt::TopToolBarArea, mainToolBar);
    mainToolBar->addAction(fileOpenAction);
    mainToolBar->addAction(fileSaveAction);
    panelToolBar = new QToolBar(this);
    this->addToolBar(Qt::TopToolBarArea, panelToolBar);
    panelToolBar->setIconSize(iconSize);
    panelToolBar->addAction(firstPanelAction);
    panelToolBar->addAction(secondPanelAction);
    panelToolBar->addAction(thirdPanelAction);
    panelToolBar->addAction(fourthPanelAction);
    panelToolBar->addSeparator();
    panelToolBar->addAction(viewSwitchAction);
}

void MainWindow::initConnect()
{
    connect(fileOpenAction, &QAction::triggered, this, MainWindow::slot_fileOpenAct);
    connect(fileSaveAction, &QAction::triggered, this, MainWindow::slot_fileSaveAct);
    connect(firstPanelAction, &QAction::triggered, this, MainWindow::slot_procPanelSwitch);
    connect(secondPanelAction, &QAction::triggered, this, MainWindow::slot_procPanelSwitch);
    connect(thirdPanelAction, &QAction::triggered, this, MainWindow::slot_procPanelSwitch);
    connect(fourthPanelAction, &QAction::triggered, this, MainWindow::slot_procPanelSwitch);
//    connect(viewSwitchAction, &QAction::triggered, this, MainWindow::slot_viewSwitch);
    //process panel signal slot connect
    connect(basicPanel->flipBtn, &QPushButton::clicked, this, &MainWindow::slot_flip);
}

// setupUi

void MainWindow::initProcPanelsStack(){
    procPanelsStack = new QStackedWidget(centralWidget);
    procPanelsStack->setFrameStyle(QFrame::StyledPanel);
    procPanelsStack->setMaximumWidth(180);
    procPanelsStack->setMinimumHeight(150);
    procPanelsStack->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);
    cReducePanel = new ColorReducePanel();
    basicPanel = new BasicPanel();
    procPanelsStack->addWidget(basicPanel);//index 0
    procPanelsStack->addWidget(cReducePanel);//index 1
    procPanelsStack->setCurrentIndex(0);
}

void MainWindow::initViewPanelsStack()
{
    viewPanelsStack = new QStackedWidget(centralWidget);
//    viewPanelsStack->setFrameStyle(QFrame::StyledPanel);
    pViewPanelC2R2 = new ViewPanelC2R2();
    pViewPanelC3 = new ViewPanelC3();
    viewPanelsStack->addWidget(pViewPanelC2R2); //index 0
    viewPanelsStack->addWidget(pViewPanelC3); //index 1
    viewPanelsStack->setCurrentIndex(1);
}

void MainWindow::slot_fileOpenAct(){
   QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image Files"),
                                                    tr("../"),
                                                    tr("Image Files(*.jpg *.png *.jpeg *.bmp)"));
   if (! fileName.isEmpty()) {
        bool succ = CoreController::getInstance()->loadImg(fileName.toLatin1().data());
//        qDebug() << "load result:\t" << succ;
        if (succ){
            showImg();
        }
   }
}

void MainWindow::slot_fileSaveAct(){
    QDialog dlg;
    dlg.show();
}

void MainWindow::slot_procPanelSwitch()
{
    QString senderObj = this->sender()->objectName();
//    qDebug() << senderObj;
    if (senderObj == "firstPanelAction")
        this->procPanelsStack->setCurrentIndex(0);
    else if (senderObj == "secondPanelAction")
        this->procPanelsStack->setCurrentIndex(1);
    else if (senderObj == "thirdPanelAction")
        this->procPanelsStack->setCurrentIndex(2);
    else if (senderObj == "fourthPanelAction")
        this->procPanelsStack->setCurrentIndex(3);
    else
        this->procPanelsStack->setCurrentIndex(0);
}


void MainWindow::showImg()
{
    int viewIndex = viewPanelsStack->currentIndex();
//    qDebug() << "view index: " << viewIndex;
    switch (viewIndex)
    {
    case 0:
//        pViewPanelC2R2->showImg();
        break;
    case 1:
        pViewPanelC3->showImg();
        break;
    default:
//        pViewPanelC2R2->showImg();
        break;
    }
}

void MainWindow::slot_flip()
{
    CoreController::getInstance()->flipImg();
//    imgView2->showImg(CoreController::getInstance()->getLastResult());
}

void MainWindow::slot_colorReduce()
{
    CoreController::getInstance()->colorReduceProc();
//    imgView2->showImg(CoreController::getInstance()->getLastResult());
}
