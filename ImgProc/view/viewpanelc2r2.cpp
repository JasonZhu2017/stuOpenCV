#include "viewpanelc2r2.h"

ViewPanelC2R2::ViewPanelC2R2(QWidget *parent): QWidget(parent)
{
    viewLoopCounter = 2;
    setupUi();
}

void ViewPanelC2R2::setupUi()
{
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
    this->setLayout(viewLayout);
}

void ViewPanelC2R2::slot_viewSwitch()
{
    viewLoopCounter += 1;
    viewLoopCounter %= 3;
    set_viewShowStyle(viewLoopCounter);
}

void ViewPanelC2R2::set_viewShowStyle(int counter)
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

