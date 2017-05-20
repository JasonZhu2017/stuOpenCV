#ifndef READER_H
#define READER_H
#include <QObject>
#include <QDebug>

class Reader : public QObject
{
    Q_OBJECT
public:
    Reader(){}

    void receiveNewspaper(const QString & name) const
    {
        qDebug() << "receive newspaper: " << name;
    }
};

#endif // READER_H
