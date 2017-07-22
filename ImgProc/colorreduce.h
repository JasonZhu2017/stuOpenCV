#ifndef COLORREDUCE_H
#define COLORREDUCE_H
#include <opencv2/core/core.hpp>

class ColorReduce
{
public:
    ColorReduce();
    ColorReduce(int div);
    int div; //reduce factor
    void process(cv::Mat & inImg, cv::Mat result);

};

#endif // COLORREDUCE_H
