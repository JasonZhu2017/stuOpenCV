#include "basicpanel.h"

BasicPanel::BasicPanel(QWidget * parent) : QWidget(parent)
{
    setupUi();
}

void BasicPanel::setupUi()
{
    flipBtn = new QPushButton(tr("Flip"), this);
    colorReduceBtn = new QPushButton(tr("ColorReduce"), this);

    topLayout = new QGridLayout();
    topLayout->setMargin(0);
    topLayout->setSpacing(5);
    topLayout->addWidget(flipBtn, 0, 0);
    topLayout->addWidget(colorReduceBtn, 1, 0);
//  topLayout->addWidget(flipBtn, 0, 0, Qt::AlignHCenter | Qt::AlignTop);

    mainLayout = new QVBoxLayout();
    mainLayout->setMargin(5);
    mainLayout->setSpacing(0);
    mainLayout->addLayout(topLayout);
    mainLayout->addStretch();

    this->setLayout(mainLayout);
}
