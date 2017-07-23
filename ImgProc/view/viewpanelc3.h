#ifndef VIEWPANELC3_H
#define VIEWPANELC3_H

#include <QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QDebug>
#include <view/imageview.h>
#include <controller/corecontroller.h>

class ViewPanelC3: public QWidget
{
public:
    explicit ViewPanelC3(QWidget* parent =0, int leftViewNum=4, int rightViewNum=4);
    ~ViewPanelC3();
    int leftViewNum;
    int rightViewNum;
    ImageView ** leftViewArray;
    ImageView ** rightViewArray;
    ImageView * centralView;
    QHBoxLayout * mainLayout;
    QVBoxLayout * leftLayout;
    QVBoxLayout * rightLayout;

    ImageView * focusView;

    void setupUi();

    void showImg();
};

#endif // VIEWPANELC3_H
