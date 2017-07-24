#include "viewpanelc3.h"

ViewPanelC3::ViewPanelC3(QWidget *parent, int leftViewNum, int rightViewNum) :
    QWidget(parent),
    leftViewNum(leftViewNum),
    rightViewNum(rightViewNum)
{
    setupUi();
}

ViewPanelC3::~ViewPanelC3()
{
    if (leftViewArray != 0 )
    {
        for (int i=0; i<leftViewNum; i++){
           if (leftViewArray[i] != 0){
               delete leftViewArray[i];
               leftViewArray[i] = 0;
           }
        }
        delete [] leftViewArray;
        leftViewArray = 0;
    }
    if (rightLayout != 0){
        for (int i=0; i<rightViewNum; i++){
            if (rightViewArray[i] != 0){
                 delete rightViewArray[i];
                 rightViewArray[i]=0;
            }
        }
    }
}

void ViewPanelC3::setupUi()
{
    //leftlayout
    leftLayout = new QVBoxLayout();
    leftLayout->setSpacing(3);
    leftLayout->setMargin(0);
    //left views
    leftViewArray = new ImageView* [leftViewNum];
    for (int i = 0; i < leftViewNum; i++)
    {
        leftViewArray[i] = new ImageView(this, ThumbnailView);
        leftLayout->addWidget(leftViewArray[i]);
    }
    //rightlayout
    rightLayout = new QVBoxLayout();
    rightLayout->setSpacing(3);
    rightLayout->setMargin(0);
    //right views
    rightViewArray = new ImageView* [rightViewNum];
    for (int i=0; i<rightViewNum; i++){
        rightViewArray[i] = new ImageView(this, ThumbnailView);
        rightLayout->addWidget(rightViewArray[i]);
    }
    //central view
    centralView = new ImageView(this);
    //mainLayout
    mainLayout = new QHBoxLayout();
    mainLayout->setMargin(0);
    mainLayout->setSpacing(3);
    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(centralView);
    mainLayout->addLayout(rightLayout);
    mainLayout->setStretchFactor(leftLayout, 1);
    mainLayout->setStretchFactor(centralView, 4);
    mainLayout->setStretchFactor(rightLayout, 1);
    this->setLayout(mainLayout);
    focusView = centralView;
}

void ViewPanelC3::showImg()
{
    for (int i=0; i < leftViewNum; i++){
        cv::Mat  temp = CoreController::getInstance()->getPrevImg(i);
        leftViewArray[i]->setImg(temp);
        leftViewArray[i]->showImg();
    }
    if (centralView == focusView){
        cv::Mat curImg = CoreController::getInstance()->getCurImg();
        centralView->setImg(curImg);
    }else{
        centralView->setImg(focusView->getImg());
    }
    centralView->showImg();
    rightViewArray[0]->setImg(CoreController::getInstance()->getSrcImg());
    rightViewArray[0]->showImg();

}

