#include "imageview.h"

ImageView::ImageView(QWidget *parent): QScrollArea(parent)
{

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

void ImageView::showImg(cv::Mat mat)
{
    if (! mat.data)
        return;
    cv::Mat rgbMat;
    QImage img;
    if (mat.channels() == 3)
    {
        cvtColor(mat, rgbMat, CV_BGR2RGB);
        img = QImage((const uchar*)(rgbMat.data),
                     rgbMat.cols,
                     rgbMat.rows,
                     rgbMat.step, //rgbMat.cols* rgbMat.channels()
                     QImage::Format_RGB888);
    }else{
        img = QImage((const uchar*)(mat.data),
                     mat.cols,
                     mat.rows,
                     rgbMat.step,
                     QImage::Format_Indexed8);
    }
    imgLabel->setPixmap(QPixmap::fromImage(img));
//    imgLabel->show();
//    this->widget()->resize(img.width(),img.height());

}
