#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QMessageBox>

#include <string>
#include <queue>

#include "challangeone.h"
#include "challangetwo.h"
#include "challangethree.h"
#include "challangefour.h"
#include "challangefive.h"


#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "opencv2/stitching/stitcher.hpp"

namespace Ui {
class MainWindow;
}

using namespace std;

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
    void executeAufgabe5();
    void executeAufgabe6();
    void exit();
};

#endif // MAINWINDOW_H
