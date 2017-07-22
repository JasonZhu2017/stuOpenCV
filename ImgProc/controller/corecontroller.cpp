#include "corecontroller.h"

CoreController* CoreController::pSingleton = 0;
CoreController::CoreController(int bufferSize):
    bufferSize(bufferSize),
    curIndex(-1),
    prevValidNum(-1),
    nextValidNum(0)
{
    if (bufferSize < 1)
        bufferSize = 1;
    imgsArray = new cv::Mat *[bufferSize];
    for (int i=0; i<bufferSize; i++)
        imgsArray[i] = 0;
    pColorDetector =  new ColorDetector;
}

CoreController::~CoreController()
{
    if (imgsArray != 0 ){
        for (int i=0; i< bufferSize; i++)
            if (imgsArray[i] != 0)
                imgsArray[i] = 0;
        delete [] imgsArray;
        imgsArray = 0;
    }
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

void CoreController::addImg2Array(cv::Mat img)
{
    curIndex = (++curIndex) % bufferSize;
    prevValidNum = ++prevValidNum < bufferSize-1 ? prevValidNum : bufferSize - 1;
    nextValidNum = 0;
    imgsArray[curIndex] = &img;
}

void CoreController::insertImg2Array(cv::Mat img, int index)
{
    imgsArray[index] = &img;
}

//cv::Mat CoreController::getImg()
//{
//    return image;
//}

void CoreController::setImgSrc(cv::Mat & imgIn)
{
    imgSrc.create(imgIn.rows, imgIn.cols, imgIn.type());
    imgSrc = imgIn.clone();
}

cv::Mat CoreController::getImgSrc()
{
    return imgSrc;
}

cv::Mat CoreController::getCurImg()
{
    if (curIndex != -1)
        return *imgsArray[curIndex];
    else
        return cv::Mat();
}

cv::Mat CoreController::getLastResult()
{
    int lastIndex = (curIndex+nextValidNum)%bufferSize;
    return * imgsArray[lastIndex];
}

void CoreController::recoveryImg()
{
    cv::Mat newImg;
    newImg.create(imgSrc.rows, imgSrc.cols, imgSrc.type());
    newImg = imgSrc.clone();
    addImg2Array(newImg);
}

bool CoreController::loadImg(std::string filename)
{
    if (filename.empty())
        return false;
    cv::Mat image = cv::imread(filename);
    if (image.data){
        addImg2Array(image);
        setImgSrc(image);
        return true;
    }else{
        return false;
    }
}

void CoreController::flipImg()
{
//    if (image.data)
//        cv::flip(image, result, 1);
}

void CoreController::colorReduceProc()
{
//    pColorDetector->c;
}
