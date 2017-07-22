#ifndef COLORDETECTOR_H
#define COLORDETECTOR_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class ColorDetector
{
public:
    ColorDetector();
    cv::Vec3b target;
    cv::Mat result;
    int minDist;
    cv::Mat process(const cv::Mat &image);
    cv::Mat getResult() const;
    int getDistance(cv::Vec3b elem);
    void setTarget(unsigned char red, unsigned char green, unsigned char blue);
    void setTarget(const cv::Vec3b color);
    cv::Vec3b getTarget() const;
    void setMinDist(const int distance);
    int getMinDist() const;

};

#endif // COLORDETECTOR_H
