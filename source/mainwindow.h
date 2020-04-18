#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stdafx.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private:
    Ui::MainWindow *ui;

public slots:
    void on_Generate_Key_Button_clicked();
    void on_Enctypt_Button_clicked();
    void on_Dectypt_Button_clicked();
};

#endif // MAINWINDOW_H
