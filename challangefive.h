#ifndef CHALLANGEFIVE_H
#define CHALLANGEFIVE_H

#include <QDialog>
#include <QDebug>

#include <vector>
#include <math.h>

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>

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
