#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <imagecore.h>
#include <imageview.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void fileOpen();
    void procInverse();

private:
    Ui::MainWindow *ui;
    ImageCore image;
    ImageView imgView;
};

#endif // MAINWINDOW_H
