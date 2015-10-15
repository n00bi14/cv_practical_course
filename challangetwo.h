#ifndef CHALLANGETWO_H
#define CHALLANGETWO_H

#include <QDialog>
#include "imageelement.h"
#include "imageprocessing.h"



namespace Ui {
class ChallangeTwo;
}

using namespace std;

class ChallangeTwo : public QDialog
{
    Q_OBJECT

public:
    explicit ChallangeTwo(QWidget *parent = 0);
    ~ChallangeTwo();
    void startA(string filename, string resultPath);
    void startB(string filename, string resultPath);
    void startC(string filename, string resultPath);
    void startD(string filename, string resultPath);

private:
    Ui::ChallangeTwo *ui;
    void showImages(vector<ImageElement*> &images);

};

#endif // CHALLANGETWO_H
