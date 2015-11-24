#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/calib3d/calib3d.hpp>

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

    static void detectSURFMatches(Mat& src, vector<KeyPoint>& keypoints, Mat& descriptor);
    static void matchDescriptors(Mat& src1, Mat& src2, Mat& dst, vector<DMatch>& matches, QString matcher,
                                 vector<KeyPoint>& keypoints_1, vector<KeyPoint>& keypoints_2, Mat& descriptor_1, Mat& descriptor_2);
    static void findGoodMatches(Mat& I, vector<DMatch>& matches, vector<KeyPoint>& keypoints_obj, vector<KeyPoint>& keypoints_scene,
                                vector<Point2f>& obj, vector<Point2f>& scene, vector<DMatch>& good_matches);
    static void stitchTwoImages(Mat& L, Mat& R, Mat& dst);



private:
    static double faltePixel(Mat& I, int x_pos, int y_pos, Mat& kernel, int kernelSize);

};

#endif // IMAGEPROCESSING_H
