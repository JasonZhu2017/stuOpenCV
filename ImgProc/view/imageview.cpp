#include "imageview.h"

ImageView::ImageView(QWidget *parent): QScrollArea(parent)
{
    img = NULL;
    setupUi();

}

void ImageView::setupUi()
{
//  this->setFrameStyle(QFrame::Panel | QFrame::Sunken);
//    this->setFrameStyle(QFrame::StyledPanel);
    imgLabel = new QLabel(this);
    imgLabel->setAlignment(Qt::AlignCenter);
//    imgLabel->setStyleSheet("background: white;");
    this->setWidget(imgLabel);
    this->setAlignment(Qt::AlignCenter);
    this->setBackgroundRole(QPalette::Dark);
    this->setWidgetResizable(true);
}

void ImageView::setImg(cv::Mat *mat)
{
    qDebug() << "set Img mat: " << mat;
    qDebug() << "set Img mat channels: " << mat->channels();
    img = mat;
}

cv::Mat* ImageView::getImg()
{
    return img;
}

void ImageView::showImg()
{
    if (img == NULL)
        return;
    if (! img->data)
        return;
    qDebug() << "img in ImageView: " << img;
    cv::Mat rgbMat;
    QImage qImg;
    qDebug() << "chanels: " << img->channels();
    if (img->channels() == 3)
    {
        cvtColor(*img, rgbMat, CV_BGR2RGB);
        qImg = QImage((const uchar*)(rgbMat.data),
                     rgbMat.cols,
                     rgbMat.rows,
                     rgbMat.step, //rgbMat.cols* rgbMat.channels()
                     QImage::Format_RGB888);
        qDebug() << "format RGB888";
    }else{
        qImg = QImage((const uchar*)(img->data),
                     img->cols,
                     img->rows,
                     img->step,
                     QImage::Format_Indexed8);
        qDebug() << "Format indexed8";
    }
    qDebug() << "setPixmap";
    imgLabel->setPixmap(QPixmap::fromImage(qImg));
    qDebug() << "show";
    imgLabel->show();
//    this->widget()->resize(img->cols,img->rows);
}
