#include "imageview.h"


ImageView::ImageView(QWidget * parent):
    QLabel(parent)
{
//    if (parent != 0)
//        this->setParent(parent);
    if (parent != 0)
    {
        QSize size = parent->size();
        this->resize(size);
    }
}

ImageView::~ImageView()
{

}

void ImageView::showQImage(const QImage &img)
{
    this->setPixmap(QPixmap::fromImage(img));
}

void ImageView::adjustWindow()
{
    QWidget * parent = (QWidget *)(this->parent());
    QSize size = parent->size();
    qDebug() << size;
    QRect rect = parent->geometry();
    qDebug() << rect;
    this->setGeometry(0,0,size.width(),size.height());
//    this->resize(size);
}

