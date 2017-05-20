#ifndef IMAGECORE_H
#define IMAGECORE_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <QString>
#include <QDebug>
#include <QImage>

using namespace cv;
class ImageCore
{
public:
    ImageCore();
    void setImg(const Mat& img, bool bDeepCopy = false);
    Mat getImg();
    void setImgBck(const Mat& img, bool bDeepCopy = false);
    Mat getImgBck();
    void applyChange();
    bool readImg(QString fileName);
    QImage cvtToQImage();
private:
    Mat m_imgBck;
    Mat m_img;

};

#endif // IMAGECORE_H
