#ifndef BASICPANEL_H
#define BASICPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>

class BasicPanel : public QWidget
{
    Q_OBJECT
public:
    explicit BasicPanel(QWidget* parent=0);

    QGridLayout * topLayout;
    QVBoxLayout * mainLayout;
    QPushButton * flipBtn;
    QPushButton * colorReduceBtn;

public:
    void setupUi();

signals:

public slots:

};


#endif // BASICPANEL_H
