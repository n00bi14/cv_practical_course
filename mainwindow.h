#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QMessageBox>
#include <string>
#include "challangeone.h"
#include "challangetwo.h"
#include "challangethree.h"
#include "challangefour.h"

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

 private slots:
    void executeAufgabe1();
    void executeAufgabe2a();
    void executeAufgabe2b();
    void executeAufgabe2c();
    void executeAufgabe2d();
    void executeAufgabe3();
    void executeAufgabe4();
    void exit();
};

#endif // MAINWINDOW_H
