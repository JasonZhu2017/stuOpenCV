#ifndef VIEWPANELC2R2_H
#define VIEWPANELC2R2_H

#include <QWidget>
#include <QtWidgets/QGridLayout>
#include <view/imageview.h>

class ViewPanelC2R2: public QWidget
{
public:
    explicit ViewPanelC2R2(QWidget * parent=0);
    QGridLayout * viewLayout;
    ImageView * imgView1;
    ImageView * imgView2;
    ImageView * imgView3;
    ImageView * imgView4;

    int viewLoopCounter;

    void setupUi();
    void slot_viewSwitch();
    void set_viewShowStyle(int counter);
};

#endif // VIEWPANELC2R2_H
