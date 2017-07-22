#include "colordetectcontroller.h"

ColorDetectController * ColorDetectController::pSingleton = 0;

ColorDetectController::ColorDetectController()
{
    pColorDetector = new ColorDetector();
}

ColorDetectController::~ColorDetectController()
{
    delete pColorDetector;
}

ColorDetectController* ColorDetectController::getInstance()
{
    if(pSingleton == 0)
        pSingleton = new ColorDetectController;
    return pSingleton;
}

void ColorDetectController::destroy()
{
    if(pSingleton != 0){
        delete pSingleton;
        pSingleton = 0;
    }
}

void ColorDetectController::setTargetColor(unsigned char red, unsigned char green, unsigned char blue)
{
    pColorDetector->setTarget(red, green, blue);
}

void ColorDetectController::getTargetColor(unsigned char &red, unsigned char &green, unsigned char &blue) const
{
    cv::Vec3b target = pColorDetector->getTarget();
    red = target[2];
    green = target[1];
    blue = target[0];
}

void ColorDetectController::setMinDistance(int distance)
{
    pColorDetector->setMinDist(distance);
}

int ColorDetectController::getMinDistance() const
{
    return pColorDetector->getMinDist();
}

bool ColorDetectController::setInputImg(std::string filename)
{
    image = cv::imread(filename);
    if(image.data){
        setImageBak();
        return true;
    }else{
        return false;
    }
}

cv::Mat ColorDetectController::getImg() const
{
    return image;
}

cv::Mat ColorDetectController::getLastResult() const
{
    return result;
}

void ColorDetectController::process()
{
    result = pColorDetector->process(image);
}

void ColorDetectController::setImageBak()
{
    imgBak = image.clone();
}

void ColorDetectController::recoveryImg()
{
    image = imgBak.clone();
}

