#ifndef CHALLANGEFIVE_H
#define CHALLANGEFIVE_H

#include <QDialog>
#include <QDebug>

#include <vector>

#include <opencv2/features2d/features2d.hpp>


#include "imageelement.h"
#include "imageprocessing.h"

namespace Ui {
class ChallangeFive;
}

using namespace std;
using namespace cv;

class ChallangeFive : public QDialog
{
    Q_OBJECT

public:
    explicit ChallangeFive(string filename, string filename_proc, string resultPath, QWidget *parent = 0);
    ~ChallangeFive();

private:
    Ui::ChallangeFive *ui;
    Mat I, processedImage;
    string filename_orig, filename_proc, resultPath;

private slots:
    void start();
    void reset();
};

#endif // CHALLANGEFIVE_H
