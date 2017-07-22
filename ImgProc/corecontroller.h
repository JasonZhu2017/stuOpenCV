#ifndef CORECONTROLLER_H
#define CORECONTROLLER_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <QDebug>
#include <colordetector.h>

class CoreController
{
private:
    CoreController();
    ~CoreController();
    static CoreController * pSingleton;
    //data store
    cv::Mat image;
    cv::Mat imgBak;
    cv::Mat imgGray;
    cv::Mat result;
    cv::Mat hist;
    //data store


public:
    static CoreController * getInstance();
    static void destroy();

    cv::Mat  getImg();
    cv::Mat  getImgBak();
    void setBackImg(cv::Mat & imgIn);
    cv::Mat  getLastResult();
    void recoveryImg();
    bool loadImg(std::string filename);
    void flipImg();


    //color reduce control begin
    ColorDetector * pColorDetector;
    void setTargetColor(unsigned char red, unsigned char green, unsigned char blue);
    void getTargetColor(unsigned char &red, unsigned char &green, unsigned char &blue) const;
    void setMinDistance(int distance);
    int getMinDistance() const;
    void colorReduceProc();
    //color reduce control end

};

#endif // CORECONTROLLER_H
