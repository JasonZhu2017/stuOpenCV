#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QSize>
#include <QDebug>

//#include <opencv2/core.hpp>

class ImageView : public QLabel
{
    Q_OBJECT
public:
    ImageView(QWidget * parent = 0);
    ~ImageView();
    void showQImage(const QImage & img);
    void adjustWindow();
};

#endif // IMAGEVIEW_H
