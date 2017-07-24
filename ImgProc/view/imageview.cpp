#include "imageview.h"

ImageView::ImageView(QWidget *parent, view_type vType):
    QScrollArea(parent),
    type(vType)
{
    setupUi();
}

void ImageView::setupUi()
{
//  this->setFrameStyle(QFrame::Panel | QFrame::Sunken);
//    this->setFrameStyle(QFrame::StyledPanel);
    imgLabel = new QLabel(this);
    imgLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imgLabel->setAlignment(Qt::AlignCenter);
//    imgLabel->setStyleSheet("background: white;");
    this->setWidget(imgLabel);
    this->setAlignment(Qt::AlignCenter);
    this->setBackgroundRole(QPalette::Dark);
    if (type == ScrollView){
        this->setWidgetResizable(true);
        qDebug() << "setupUi scroll view:" << this->size();
    }else{
        imgLabel->setScaledContents(true);
        qDebug() << "setupUi Thumbnail View:" << this->size();
    }
}

void ImageView::setImg(cv::Mat mat)
{
    img = mat;
}

cv::Mat ImageView::getImg()
{
    return img;
}

void ImageView::showImg()
{
    if (! img.data)
        return;
    cv::Mat rgbMat;
    QImage qImg;
    if (img.channels() == 3)
    {
        cvtColor(img, rgbMat, CV_BGR2RGB);
        qImg = QImage((const uchar*)(rgbMat.data),
                     rgbMat.cols,
                     rgbMat.rows,
                     rgbMat.step, //rgbMat.cols* rgbMat.channels()
                     QImage::Format_RGB888);
//        qDebug() << "format RGB888";
    }else{
        qImg = QImage((const uchar*)(img.data),
                     img.cols,
                     img.rows,
                     img.step,
                     QImage::Format_Indexed8);
//        qDebug() << "Format indexed8";
    }
    imgLabel->setPixmap(QPixmap::fromImage(qImg));
    if (this->type == ScrollView){
        this->widget()->resize(img.cols,img.rows);
//        this->imgLabel->resize(img.cols, img.rows);
        qDebug() << "showImg Scroll view resize:" << this->size();
    }else{
        QSize size = this->size();
        float wScale = img.cols * 1.0 / (size.width()-2);
        float hScale = img.rows * 1.0 / (size.height()-2);
        float scale = wScale > hScale ? wScale : hScale;
        scale = scale > 1.0 ? scale : 1.0;
        qDebug() << wScale << hScale << scale;
        this->imgLabel->resize(img.cols/scale, img.rows/scale);
        qDebug() << "showImg Thumbnail View resize:" << size;
//        this->widget()->resize(size);
    }
    imgLabel->show();
}
