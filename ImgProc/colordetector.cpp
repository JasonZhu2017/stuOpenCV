#include "colordetector.h"

ColorDetector::ColorDetector()
{
    minDist = 10;
    target[0]=target[1]=target[2]=0;
}

cv::Mat ColorDetector::process(const cv::Mat &image)
{
    result.create(image.rows, image.cols, CV_8U);
    cv::Mat_<cv::Vec3b>::const_iterator it=image.begin<cv::Vec3b>();
    cv::Mat_<cv::Vec3b>::const_iterator itend=image.end<cv::Vec3b>();
    cv::Mat_<uchar>::iterator itout = result.begin<uchar>();
    for(; it!=itend; ++it, ++itout){
        if(getDistance(*it) <= minDist)
        {
            *itout = 255;
        }else{
            *itout = 0;
        }
    }
    return result;
}

cv::Mat ColorDetector::getResult() const
{
    return result;
}


int ColorDetector::getDistance(cv::Vec3b elem){
    return abs(elem[0] - target[0]) +
            abs(elem[1] - target[1]) +
            abs(elem[2] - target[2]);
}

void ColorDetector::setTarget(unsigned char red, unsigned char green, unsigned char blue)
{
    target[0] = blue;
    target[1] = green;
    target[2] = red;
}

void ColorDetector::setTarget(const cv::Vec3b color)
{
    target = color;
}

cv::Vec3b ColorDetector::getTarget() const
{
    return target;
}

void ColorDetector::setMinDist(const int distance)
{
    minDist = distance;
}

int ColorDetector::getMinDist() const
{
    return minDist;
}
