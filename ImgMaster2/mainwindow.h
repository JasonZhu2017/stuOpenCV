#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QAction *getSaveAction() const;
    void setSaveAction(QAction *value);

private:
    Ui::MainWindow *ui;
    void fileOpen();
    void fileNew();
    void fileSave();
    void settingSys();
    void setColor();
    void mountAction(QAction * action, QMenu *menu, QToolBar *toolbar, QStatusBar *statusbar);



    QAction * openAction;
    QAction * newAction;
    QAction * saveAction;
    QAction * settingAction;
    QAction * colorAction;

};

#endif // MAINWINDOW_H
