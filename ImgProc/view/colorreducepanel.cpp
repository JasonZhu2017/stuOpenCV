#include "colorreducepanel.h"

ColorReducePanel::ColorReducePanel(QWidget *parent) : QWidget(parent)
{
    setupUi();
}

void ColorReducePanel::setupUi()
{
//    this->setMinimumWidth(180);
//    this->setMaximumWidth(180);
    testBtn = new QPushButton(tr("test"));
    mainLayout = new QVBoxLayout();
    mainLayout->setMargin(5);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(testBtn);
    mainLayout->addStretch();
    this->setLayout(mainLayout);
}
