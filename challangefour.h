#ifndef CHALLANGEFOUR_H
#define CHALLANGEFOUR_H

#include <QDialog>
#include <QDebug>

#include <QSlider>
#include <QLineEdit>

#include <vector>
#include <iostream>

#include "imageelement.h"
#include "imageprocessing.h"

namespace Ui {
class ChallangeFour;
}

using namespace std;
using namespace cv;


class ChallangeFour : public QDialog
{
    Q_OBJECT

public:
    explicit ChallangeFour(string filename, string resultPath, bool isSumFilter, QWidget *parent = 0);
    ~ChallangeFour();

private:
    Ui::ChallangeFour *ui;
    string filename,resultPath;
    bool isSumFilter;
    Mat I, processedImage;
    QLineEdit* txt_filterSize;

    int spinFilterSizeValue;
private slots:
    void resetImage();

    void execMittelwertfilter();
    void execGaussfilter();

    void execXfrontGradient();
    void execYBackGradient();
    void execLaplace();
    void execSobelX();
    void execSobelY();
    void execSobelBetrag();
    void execCannyEdge();

    void spinValueChanged(int value);
};

#endif // CHALLANGEFOUR_H
