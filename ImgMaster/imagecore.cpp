#include "imagecore.h"
ImageCore::ImageCore()
{

}

void ImageCore::setImg(const Mat &img, bool bDeepCopy)
{
    this->m_img.create(img.rows, img.cols, img.type());
    if (bDeepCopy) {
        m_img = img.clone();
    }else{
        m_img = img;
    }
}

Mat ImageCore::getImg()
{
    return m_img;
}

void ImageCore::setImgBck(const Mat &img, bool bDeepCopy)
{
    this->m_imgBck.create(img.rows, img.cols, img.type());
    if (bDeepCopy) {
        img.copyTo(m_imgBck);
    }else{
        m_imgBck = img;
    }
}

Mat ImageCore::getImgBck()
{
    return m_imgBck;
}

void ImageCore::applyChange()
{
    this->setImgBck(m_img, true);
}

bool ImageCore::readImg(QString fileName)
{
    if (fileName.length() == 0){
        qDebug()<<"filename is empty";
        return false;
    }
    Mat tImg = imread(fileName.toLatin1().data());
    cvtColor(tImg, tImg, CV_BGR2RGB);
    this->setImg(tImg);
    this->setImgBck(tImg, true);
    return true;
}

QImage ImageCore::cvtToQImage()
{
    QImage img = QImage((const unsigned char*)(m_img.data),
                        m_img.cols,
                        m_img.rows,
                        QImage::Format_RGB888);
    return img;
}
