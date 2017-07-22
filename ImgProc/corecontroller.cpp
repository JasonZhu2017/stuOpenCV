#include "corecontroller.h"

CoreController* CoreController::pSingleton = 0;
CoreController::CoreController()
{
    pColorDetector =  new ColorDetector;
}

CoreController::~CoreController()
{
    delete pColorDetector;
    pColorDetector = 0;
}

CoreController *CoreController::getInstance()
{
    if (pSingleton == 0) {
        pSingleton = new CoreController();
    }
    return pSingleton;
}

void CoreController::destroy()
{
    if (pSingleton) {
        delete pSingleton;
        pSingleton = 0;
    }
}

cv::Mat CoreController::getImg()
{
    return image;
}

void CoreController::setBackImg(cv::Mat & imgIn)
{
    imgBak.create(imgIn.rows, imgIn.cols, imgIn.type());
    imgBak = imgIn.clone();
}

cv::Mat CoreController::getImgBak()
{
    return imgBak;
}

cv::Mat CoreController::getLastResult()
{
    return result;
}

void CoreController::recoveryImg()
{
    image.create(imgBak.rows, imgBak.cols, imgBak.type());
    image = imgBak.clone();
}

bool CoreController::loadImg(std::string filename)
{
    if (filename.empty())
        return false;
    image = cv::imread(filename);
    if (image.data){
        setBackImg(image);
        return true;
    }else{
        return false;
    }
}

void CoreController::flipImg()
{
    if (image.data)
        cv::flip(image, result, 1);
}

void CoreController::colorReduceProc()
{
//    pColorDetector->c;
}
