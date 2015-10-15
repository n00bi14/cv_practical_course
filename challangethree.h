#ifndef CHALLANGETHREE_H
#define CHALLANGETHREE_H

#include <QDialog>
#include <QDebug>

#include <QSlider>
#include <QLineEdit>
#include <QCheckBox>

#include <vector>

#include "imageelement.h"
#include "imageprocessing.h"

namespace Ui {
class ChallangeThree;
}

using namespace std;
using namespace cv;

class ChallangeThree : public QDialog
{
    Q_OBJECT

public:
    explicit ChallangeThree(string filename, string resultPath,QWidget *parent = 0);
    ~ChallangeThree();

private:
    Ui::ChallangeThree *ui;
    string filename,resultPath;
    Mat I, processedImage;

    ImageElement* processed;

    QSlider* slider_stretching;
    QSlider* slider_gammakorrektur;
    QLineEdit* txt_stretching;
    QLineEdit* txt_gammakorrektur;
    QCheckBox* chk_linearisierung;

    void calculateAllFilters();

private slots:
    void setStretchedValue(int value);
    void setGammakorrekturValue(int value);
    void linearisierungChecked(bool);
};

#endif // CHALLANGETHREE_H
