#ifndef CORECONTROLLER_H
#define CORECONTROLLER_H
#include <QDebug>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <model/colordetector.h>
#include <controller/ringbuffer.h>

class CoreController
{
private:
    CoreController(int bufferSize=10);
    ~CoreController();
    static CoreController * pSingleton;
    //data store
    int arraySize;
    RingBuffer <cv::Mat> * imgsArray;
    cv::Mat imgSrc;
    cv::Mat imgGray;
    cv::Mat imgChRed;
    cv::Mat imgChGreen;
    cv::Mat imgChBlue;
    cv::Mat imgHist;
    //data store

public:
    static CoreController *getInstance();
    static void destroy();

    void resetBuffer();
    void addImg2Array(cv::Mat img);
    cv::Mat getCurImg();
    cv::Mat getPrevImg(int steps);

    cv::Mat getSrcImg();
    void setSrcImg(cv::Mat imgIn);
    void recoveryImg();
    bool loadImg(std::string filename);
    void flipImg();

    void undo();
    void redo();

    //color reduce control begin
    ColorDetector *pColorDetector;
    void setTargetColor(unsigned char red, unsigned char green, unsigned char blue);
    void getTargetColor(unsigned char &red, unsigned char &green, unsigned char &blue) const;
    void setMinDistance(int distance);
    int getMinDistance() const;
    void colorReduceProc();
    //color reduce control end

};

#endif // CORECONTROLLER_H
