#ifndef COLORDETECTCONTROLLER_H
#define COLORDETECTCONTROLLER_H
#include <colordetector.h>
#include <iostream>

class ColorDetectController
{
private:
    cv::Mat image;
    cv::Mat imgBak;
    cv::Mat result;
    ColorDetector * pColorDetector;
    static ColorDetectController *pSingleton;

    ColorDetectController();
    ~ColorDetectController();

public:
    static ColorDetectController * getInstance();
    static void destroy();

    void setTargetColor(unsigned char red, unsigned char green, unsigned char blue);
    void getTargetColor(unsigned char &red, unsigned char &green, unsigned char &blue) const;
    void setMinDistance(int distance);
    int getMinDistance() const;
    bool setInputImg(std::string filename);
    cv::Mat getImg() const;
    cv::Mat getLastResult() const;
    void process();
    void setImageBak();
    void recoveryImg();
};

#endif // COLORDETECTCONTROLLER_H
