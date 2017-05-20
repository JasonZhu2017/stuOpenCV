#include <QDebug>
#include <QMouseEvent>
#include "custombutton.h"

CustomButton::CustomButton(QWidget * parent):
    QPushButton(parent)
{
    connect(this, &CustomButton::clicked,
            this, &CustomButton::onButtonCliecked);
}

void CustomButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        qDebug() << "left";
    } else{
        QPushButton::mousePressEvent(event);
    }
}

void CustomButton::onButtonCliecked()
{
    qDebug() << "You Clicked this !";
}
