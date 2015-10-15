#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <core.hpp>
#include <highgui.hpp>
#include <imgproc.hpp>
#include <string>
#include <QDebug>

using namespace std;
using namespace cv;

#define  CV_CAST_8U(t)  (uchar)(!((t) & ~255) ? (t) : (t) > 0 ? 255 : 0)

class ImageProcessing
{
public:
    ImageProcessing();

    static void resizeImage(double cols, double rows, InputArray src, OutputArray dst);
    static void resizeMax512(InputArray src, OutputArray dst);
    static void convertToCMY(Mat& src);
    static vector<Mat> convertToYIQ(Mat& src);
    static void convertToLab(InputArray src, OutputArray dst);
    static void stretchImage(InputArray src, OutputArray dst, int saturation);
    static void correktGammaValue(InputArray src, OutputArray dst, double gammaValue, int saturation);

};

#endif // IMAGEPROCESSING_H
