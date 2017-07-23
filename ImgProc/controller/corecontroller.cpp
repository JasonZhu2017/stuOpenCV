#include "corecontroller.h"

CoreController* CoreController::pSingleton = 0;
CoreController::CoreController(int bufferSize):
    arraySize(bufferSize)
{
    imgsArray = new RingBuffer<cv::Mat*>(arraySize);
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

void CoreController::addImg2Array(cv::Mat *img)
{
    qDebug() << "add img: " << img;
    qDebug() << "add img channel: " << img->channels();
    imgsArray->add(img);
    cv::Mat * temp;
    if (imgsArray->getCursor(temp))
    {
        qDebug() << "get Cursor:" << temp;
        qDebug() << "get Cursor channels:" << temp->channels();
    }
    cv::Mat * previmg;
    if (imgsArray->getPrev(0, previmg))
    {
        qDebug() << "get prev:" << previmg;
        qDebug() << "get preve channels:" << previmg->channels();
    }

}

void CoreController::setSrcImg(cv::Mat *imgIn)
{
    imgSrc.create(imgIn->rows, imgIn->cols, imgIn->type());
    imgSrc = imgIn->clone();
}

cv::Mat* CoreController::getSrcImg()
{
    return &imgSrc;
}

cv::Mat* CoreController::getCurImg()
{
    cv::Mat * temp;
    if (imgsArray->getCursor(temp))
        return temp;
    else
        return NULL;
}

cv::Mat* CoreController::getPrevImg(int steps)
{
    cv::Mat * temp;
    if (imgsArray->getPrev(steps, temp)){
        qDebug() << "coreController get prev img:" << temp;
        qDebug() << "coreController get prev img channels" << temp->channels();
        return temp;
    }
    else
        return NULL;
}

void CoreController::recoveryImg()
{
    cv::Mat newImg;
    newImg.create(imgSrc.rows, imgSrc.cols, imgSrc.type());
    newImg = imgSrc.clone();
    addImg2Array(& newImg);
}

bool CoreController::loadImg(std::string filename)
{
    if (filename.empty())
        return false;
    cv::Mat image = cv::imread(filename);
    if (image.data){
        resetBuffer();
        qDebug() << "load image" << &image;
        qDebug() << "load image channels" << image.channels();
        addImg2Array(&image);
        setSrcImg(&image);
        return true;
    }else
        return false;
}

void CoreController::flipImg()
{
//    if (image.data)
//        cv::flip(image, result, 1);
    cv::Mat* curImg;
    curImg = getCurImg();
    if (curImg){
        if (curImg->data){
            cv::Mat reslut;
            cv::flip(*curImg, reslut, 1);
            addImg2Array(&reslut);
        }
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
