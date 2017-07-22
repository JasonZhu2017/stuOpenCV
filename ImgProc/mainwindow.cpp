#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    viewLoopCounter = 1;
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
    this->resize(800, 600);
    this->setWindowState(Qt::WindowMaximized);
    centralWidget = new QWidget(this);
    imgView1 = new ImageView();
    imgView2 = new ImageView();
    imgView3 = new ImageView();
    imgView4 = new ImageView();
    viewLayout = new QGridLayout();
    viewLayout->addWidget(imgView1, 0, 0);
    viewLayout->addWidget(imgView2, 0, 1);
    viewLayout->addWidget(imgView3, 1, 0);
    viewLayout->addWidget(imgView4, 1, 1);
    viewLayout->setMargin(0);
    viewLayout->setSpacing(5);
    set_viewShowStyle(viewLoopCounter);
    panelsStack = new QStackedWidget(centralWidget);
    panelsStack->setFrameStyle(QFrame::StyledPanel);
    panelsStack->setMaximumWidth(180);
    panelsStack->setMinimumHeight(150);
    panelsStack->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);
    setupPanelsStack();
    mainLayout = new QHBoxLayout();
    mainLayout->addLayout(viewLayout);
    mainLayout->addWidget(panelsStack);
    mainLayout->setSpacing(5);
    mainLayout->setMargin(5);
    centralWidget->setLayout(mainLayout);
    this->setCentralWidget(centralWidget);

    statusBar = new QStatusBar(this);
    this->setStatusBar(statusBar);

    dockWidget = new QDockWidget(this);
    dockWidgetContents = new QWidget();
    dockWidget->setWidget(dockWidgetContents);
    dockWidget->setVisible(false);
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
    mainToolBar->setIconSize(QSize(36, 36));
    this->addToolBar(Qt::TopToolBarArea, mainToolBar);
    mainToolBar->addAction(fileOpenAction);
    mainToolBar->addAction(fileSaveAction);
    panelToolBar = new QToolBar(this);
    this->addToolBar(Qt::TopToolBarArea, panelToolBar);
    panelToolBar->setIconSize(QSize(36, 36));
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
    connect(firstPanelAction, &QAction::triggered, this, MainWindow::slot_panelSwitch);
    connect(secondPanelAction, &QAction::triggered, this, MainWindow::slot_panelSwitch);
    connect(thirdPanelAction, &QAction::triggered, this, MainWindow::slot_panelSwitch);
    connect(fourthPanelAction, &QAction::triggered, this, MainWindow::slot_panelSwitch);
    connect(viewSwitchAction, &QAction::triggered, this, MainWindow::slot_viewSwitch);
}

// setupUi

void MainWindow::setupPanelsStack(){
    cReducePanel = new ColorReducePanel();
    basicPanel = new BasicPanel();
    panelsStack->addWidget(basicPanel);//index 0
    panelsStack->addWidget(cReducePanel);//index 1
    panelsStack->setCurrentIndex(0);
    connect(basicPanel->flipBtn, &QPushButton::clicked, this, &MainWindow::slot_flip);
}

void MainWindow::slot_fileOpenAct(){
   QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image Files"),
                                                    tr("../"),
                                                    tr("Image Files(*.jpg *.png *.jpeg *.bmp)"));
   if (! fileName.isEmpty()) {
        bool succ = CoreController::getInstance()->loadImg(fileName.toLatin1().data());
//        qDebug() << succ;
        if (succ){
            imgView1->showImg(CoreController::getInstance()->getImg());
//            imgView2->showImg(CoreController::getInstance()->getImg());
//            imgView3->showImg(CoreController::getInstance()->getImg());
//            imgView4->showImg(CoreController::getInstance()->getImg());
        }
   }
}

void MainWindow::slot_fileSaveAct(){
    QDialog dlg;
    dlg.show();
}

void MainWindow::slot_panelSwitch()
{
    QString senderObj = this->sender()->objectName();
//    qDebug() << senderObj;
    if (senderObj == "firstPanelAction")
        this->panelsStack->setCurrentIndex(0);
    else if (senderObj == "secondPanelAction")
        this->panelsStack->setCurrentIndex(1);
    else if (senderObj == "thirdPanelAction")
        this->panelsStack->setCurrentIndex(2);
    else if (senderObj == "fourthPanelAction")
        this->panelsStack->setCurrentIndex(3);
    else
        this->panelsStack->setCurrentIndex(0);
}

void MainWindow::slot_viewSwitch()
{
    viewLoopCounter += 1;
    viewLoopCounter %= 3;
    set_viewShowStyle(viewLoopCounter);
}

void MainWindow::set_viewShowStyle(int counter)
{
    uchar showMask = 0;
    switch (counter)
    {
    case 0:
        showMask = 0x01; //00000001b
        break;
    case 1:
        showMask = 0x03; //00000011b
        break;
    case 2:
        showMask = 0x0F; //00001111b
        break;
    case 3:
        showMask = 0x0F; //00001111b
        break;
    default:
        showMask = 0x0F;
    }
    imgView1->setVisible(showMask & 0x01);
    imgView2->setVisible(showMask & 0x02);
    imgView3->setVisible(showMask & 0x04);
    imgView4->setVisible(showMask & 0x08);
}

void MainWindow::showImg()
{
//    switch (viewLoopCounter)
//    {
//    case 0:
//        imgView2->showImg(CoreController::getInstance()->getImg());
//        imgView2->
//        break;
//    }
}

void MainWindow::slot_flip()
{
    CoreController::getInstance()->flipImg();
    imgView2->showImg(CoreController::getInstance()->getLastResult());
}

void MainWindow::slot_colorReduce()
{
    CoreController::getInstance()->colorReduceProc();
    imgView2->showImg(CoreController::getInstance()->getLastResult());
}
