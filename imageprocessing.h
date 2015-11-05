#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>

#include <string>
#include <iostream>

#include <QDebug>

using namespace std;
using namespace cv;

#define  CV_CAST_8U(t)  (uchar)(!((t) & ~255) ? (t) : (t) > 0 ? 255 : 0)


class ImageProcessing
{
public:
    ImageProcessing();

    enum FILTER{MEDIAN, GAUSSIAN, XFRONTGRADIENT, YBACKGRADIENT, LAPLACE, SOBELX, SOBELY, SOBELBETRAG, CANNYEDGE} ;

    static void resizeImage(double cols, double rows, InputArray src, OutputArray dst);
    static void resizeMax512(InputArray src, OutputArray dst);
    static void convertToCMY(Mat& src);
    static vector<Mat> convertToYIQ(Mat& src);
    static void convertToLab(InputArray src, OutputArray dst);
    static void stretchImage(InputArray src, OutputArray dst, int saturation);
    static void correktGammaValue(InputArray src, OutputArray dst, double gammaValue, int saturation);
    static void filterFactory(InputArray src, OutputArray dst, int kernelSize, FILTER filterName, int cannyEdgeThreshold = 1);
    static void faltung(InputArray src, OutputArray dst, QString filtername);


private:
    static double faltePixel(Mat& I, int x_pos, int y_pos, Mat& kernel, int kernelSize);

};

#endif // IMAGEPROCESSING_H
