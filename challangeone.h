#ifndef CHALLANGEONE_H
#define CHALLANGEONE_H

#include <QDebug>
#include <QDialog>
#include "imageelement.h"
#include "imageprocessing.h"

namespace Ui {
class ChallangeOne;
}

using namespace std;

class ChallangeOne : public QDialog
{
    Q_OBJECT

public:
    explicit ChallangeOne(QWidget *parent = 0);
    ~ChallangeOne();
    void start(string filename, string resultPath);

private:
    Ui::ChallangeOne *ui;
    void showImages(vector<ImageElement*> &images);
    Mat createIndexImage(Mat image, int color);
};

#endif // CHALLANGEONE_H
