#ifndef COLORREDUCEPANEL_H
#define COLORREDUCEPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class ColorReducePanel : public QWidget
{
    Q_OBJECT
public:
    explicit ColorReducePanel(QWidget *parent = 0);

    QPushButton * testBtn;
    QVBoxLayout * mainLayout;

    void setupUi();

signals:

public slots:
};

#endif // COLORREDUCEPANEL_H
