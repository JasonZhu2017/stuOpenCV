#include "corecontroller.h"

CoreController* CoreController::pSingleton = 0;
CoreController::CoreController(int bufferSize):
    arraySize(bufferSize)
{
    imgsArray = new RingBuffer<cv::Mat>(arraySize);
    pColorDetector =  new ColorDetector;
}

CoreController::~CoreController()
{
    if (imgsArray != 0 ){
        delete imgsArray;
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

void CoreController::resetBuffer()
{
    imgsArray->reset();
}

void CoreController::addImg2Array(cv::Mat img)
{
    imgsArray->add(img);
}

void CoreController::setSrcImg(cv::Mat imgIn)
{
    imgSrc.create(imgIn.rows, imgIn.cols, imgIn.type());
    imgSrc = imgIn.clone();
}

cv::Mat CoreController::getSrcImg()
{
    return imgSrc;
}

cv::Mat CoreController::getCurImg()
{
    cv::Mat temp;
    imgsArray->getCursor(temp);
    return temp;
}

cv::Mat CoreController::getPrevImg(int steps)
{
    cv::Mat temp;
    imgsArray->getPrev(steps, temp);
//    qDebug() << "coreController get prev img type:" << temp.type();
//    qDebug() << "coreController get prev img channels" << temp.channels();
    return temp;
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
        resetBuffer();
//        qDebug() << "load image" << &image;
//        qDebug() << "load image channels" << image.channels();
        addImg2Array(image);
        setSrcImg(image);
        return true;
    }else
        return false;
}

void CoreController::flipImg()
{
    cv::Mat curImg;
    curImg = getCurImg();
    if (curImg.data){
        cv::Mat reslut;
        cv::flip(curImg, reslut, 1);
        addImg2Array(reslut);
    }
}

void CoreController::undo()
{
    imgsArray->cursorRecede(1);
}

void CoreController::redo()
{
    imgsArray->cursorForward(1);
}

void CoreController::colorReduceProc()
{
//    pColorDetector->c;
}
