#include "mainwindow.h"
#include <QApplication>
#include "newspaper.h"
#include "reader.h"
#include "eventlabel.h"
#include "custombutton.h"
#include "testevnetfilter.h"


void mainWindow()
{
    MainWindow w;
    w.show();
}

void testSignal()
{
   Newspaper newspaper("Newspaper A");
   Reader reader;
   QObject::connect(&newspaper, &Newspaper::newPaper, &reader, &Reader::receiveNewspaper);
   newspaper.send();
}

void testLabel()
{
    EventLabel *label = new EventLabel;
    label->setWindowTitle("MouseEvent Demo");
    label->resize(300, 200);
    label->setMouseTracking(true);
    label->show();
}

void testCustomButton()
{
    CustomButton *btn = new CustomButton();
    btn->setText("this is a Button !");
    btn->show();
}

void testEvent(QApplication & app)
{
    Label *label = new Label;
    app.installEventFilter(new EventFilter(label, label));
    label->show();

}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
//    mainwindow();
//    testSignal();
//    testLabel();
    testEvent(app);
    return app.exec();
}
