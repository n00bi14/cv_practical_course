#include "imageprocessing.h"

ImageProcessing::ImageProcessing()
{}


void ImageProcessing::resizeImage(double cols, double rows, InputArray src, OutputArray dst)
{
    cv::resize(src,dst, Size(), cols, rows);
}

void ImageProcessing::resizeMax512(InputArray src, OutputArray dst)
{
    double fx_nenner=512,fy_nenner=512;
    if(src.cols() > src.rows())
    {
        fx_nenner = src.cols() - (src.cols() - 512);
        fy_nenner = src.rows() - (src.cols() - 512);
    }else if(src.cols() < src.rows()){
        fy_nenner = src.rows() - (src.rows() - 512);
        fx_nenner = src.cols() - (src.rows() - 512);
    }

    double fx = (1. / (src.cols() / fx_nenner));
    double fy = (1. / (src.rows() / fy_nenner));

    //TODO: Formel klappt nicht... Nachbessern
    if(fx < 0) fx *= -1;
    if(fy < 0) fy *= -1;

    return resizeImage(fx, fy, src, dst);
}

void ImageProcessing::convertToCMY(Mat& src){

    for(int i = 0; i < src.rows; i++)
    {
        for(int j = 0; j < src.cols; j++)
        {
            Vec3b &bgrPixel = src.at<Vec3b>(i, j);
            uchar r = bgrPixel[2];
            uchar g = bgrPixel[1];
            uchar b = bgrPixel[1];
            bgrPixel[0] = 0xff - r;
            bgrPixel[1] = 0xff - g;
            bgrPixel[2] = 0xff - b;
        }
    }
}


vector<Mat> ImageProcessing::convertToYIQ(Mat& src){
    uchar r, g, b;
    double y, i, q;

    Mat out_y(src.rows, src.cols, CV_8UC1);
    Mat out_i(src.rows, src.cols, CV_8UC1);
    Mat out_q(src.rows, src.cols, CV_8UC1);
    Mat out(src.rows, src.cols, CV_8UC3);

    /* convert image from RGB to YIQ */

    int m=0, n=0;
    for(m=0; m<src.rows; m++)
    {
        for(n=0; n<src.cols; n++)
        {
            r = src.data[m*src.step + n*3 + 2];
            g = src.data[m*src.step + n*3 + 1];
            b = src.data[m*src.step + n*3 ];
            y = 0.299*r + 0.587*g + 0.114*b;
            i = 0.595*r - 0.274*g - 0.321*b;
            q = 0.211*r - 0.522*g + 0.311*b;

            out_y.data[m*out_y.step+n] = CV_CAST_8U((int)(y));
            out_i.data[m*out_i.step+n] = CV_CAST_8U((int)(i));
            out_q.data[m*out_q.step+n] = CV_CAST_8U((int)(q));
            out.data[m*src.step+n*3 +2] = CV_CAST_8U((int)(y));
            out.data[m*src.step+n*3 +1] = CV_CAST_8U((int)(i));
            out.data[m*src.step+n*3 ] = CV_CAST_8U((int)(q));

        }
    }

    vector<Mat> result;

    result.push_back(out);
    result.push_back(out_y);
    result.push_back(out_i);
    result.push_back(out_q);

    return result;

}

void ImageProcessing::convertToLab(InputArray src, OutputArray dst){
    cvtColor(src, dst, CV_BGR2Lab);
}

void ImageProcessing::stretchImage(InputArray src, OutputArray dst, int saturation){
    Mat I;

    src.getMat().copyTo(I);

    int histSize = 255;
    float range[] = {0, 255};
    const float* histRange = {range};

    cv::Mat histogram;
    cv::calcHist(&I, 1, 0, cv::Mat(), histogram, 1, &histSize, &histRange, true, false);

    int size = (I.cols * I.rows);
    int threshold = int((size / 100) * saturation);
    int tmp  = 0;
    int gmin = 0;
    int gmax = 0;

    for(gmin = 0; gmin < histogram.rows * histogram.cols; gmin++)
        if(tmp < threshold)
            tmp += histogram.data[gmin];
        else
            break;

    for(gmax = histogram.rows * histogram.cols; gmax >= 0 ; gmax--)
        if(tmp < threshold)
            tmp += histogram.data[gmax];
        else
            break;

    double d = 255 / (gmax - gmin);


    for(int i = 0; i < size; i++){
        uchar pixel = (I.data[i]);
        I.data[i] = CV_CAST_8U((int)((pixel - gmin) * d));
    }

    I.copyTo(dst);
}


void ImageProcessing::correktGammaValue(InputArray src, OutputArray dst, double gammaValue, int saturation){
    Mat I;

    src.getMat().copyTo(I);

    int histSize = 255;
    float range[] = {0, 255};
    const float* histRange = {range};

    cv::Mat histogram;
    cv::calcHist(&I, 1, 0, cv::Mat(), histogram, 1, &histSize, &histRange, true, false);

    int size = (I.cols * I.rows);
    int threshold = int((size / 100) * saturation);
    int tmp  = 0;
    int gmin = 0;
    int gmax = 0;

    for(gmin = 0; gmin < histogram.rows * histogram.cols; gmin++)
        if(tmp < threshold)
            tmp += histogram.data[gmin];
        else
            break;

    for(gmax = histogram.rows * histogram.cols; gmax >= 0 ; gmax--)
        if(tmp < threshold)
            tmp += histogram.data[gmax];
        else
            break;

    double g = gmax - gmin;

//    qDebug() << d << "\t" << g;

    for(int i = 0; i < I.rows * I.cols; i++)
    {
        I.data[i] = CV_CAST_8U((int)(255 * std::pow(((I.data[i] - gmin) / g), gammaValue)));
    }

    I.copyTo(dst);
}

void ImageProcessing::filterFactory(InputArray src, OutputArray dst, int kernelSize, FILTER filterName, int cannyEdgeThreshold)
{
    switch(filterName)
    {
    case MEDIAN:
        medianBlur(src,dst, kernelSize);
        break;
    case GAUSSIAN:
    {
        double sigmaX = (kernelSize / 6) + 1;
        GaussianBlur(src,dst, Size(kernelSize,kernelSize), sigmaX);
    }
        break;
    case XFRONTGRADIENT:
        //TODO
        break;
    case YBACKGRADIENT:
        //TODO
        break;
    case LAPLACE:
    {
        Mat afterLaplacian, afterGaussian;
        src.copyTo(afterGaussian);
        src.copyTo(afterLaplacian);
        ImageProcessing::filterFactory(src, afterGaussian, kernelSize, ImageProcessing::GAUSSIAN);
        Laplacian( afterGaussian, afterLaplacian, CV_64F, kernelSize);
        convertScaleAbs( afterLaplacian, dst );
    }
        break;
    case SOBELX:
    {
        Mat afterSobel, afterGaussian;
        src.copyTo(afterGaussian);
        src.copyTo(afterSobel);
        ImageProcessing::filterFactory(src, afterGaussian, kernelSize, ImageProcessing::GAUSSIAN);
        Sobel(afterGaussian,afterSobel,CV_64F,1,0,kernelSize);
        convertScaleAbs( afterSobel, dst );
    }
        break;
    case SOBELY:
    {
        Mat afterSobel, afterGaussian;
        src.copyTo(afterGaussian);
        src.copyTo(afterSobel);
        ImageProcessing::filterFactory(src, afterGaussian, kernelSize, ImageProcessing::GAUSSIAN);
        Sobel(afterGaussian,afterSobel,CV_64F,0,1,kernelSize);
        convertScaleAbs( afterSobel, dst );
    }
        break;
    case SOBELBETRAG:
        //TODO
        break;
    case CANNYEDGE:
        //Has a big big bug!!!!
    {
        Mat detected_edges;
        int k = kernelSize<3?3:kernelSize;

        detected_edges.create(src.size(), src.type());
        blur( src, detected_edges, Size(k,k) );
        Canny( detected_edges, dst, cannyEdgeThreshold, cannyEdgeThreshold*3, k );
//        dst = Scalar::all(0);
        src.copyTo(dst,detected_edges);
    }
        break;
    }
}

void ImageProcessing::faltung(InputArray src, OutputArray dst, QString filtername){
    int k = 3;
    Mat_<double> kernel(3,3,1.);

    if(QString::compare(filtername, QString("Filter 1"), Qt::CaseInsensitive) == 0)
    {
        std::cout << "Filter 1" << std::endl;
        double &p = kernel.at<double>(1, 1);
        p = -8;

    }else if(QString::compare(filtername, QString("Filter 2"), Qt::CaseInsensitive) == 0){

        std::cout << "Filter 2" << std::endl;

        double& p1 = kernel.at<double>(0, 1);
        p1 = 2;
        double& p2 = kernel.at<double>(1, 0);
        p2 = 2;
        double& p3 = kernel.at<double>(1, 1);
        p3 = 4;
        double& p4 = kernel.at<double>(1, 2);
        p4 = 2;
        double& p5 = kernel.at<double>(2, 1);
        p5 = 2;

        kernel = kernel / (float)16.;

    }else if(QString::compare(filtername, QString("Filter 3"), Qt::CaseInsensitive) == 0){

        std::cout << "Filter 3" << std::endl;
        double& p1 = kernel.at<double>(0, 1);
        p1 = 2;
        double& p2 = kernel.at<double>(1, 0);
        p2 = 0;
        double& p3 = kernel.at<double>(1, 1);
        p3 = 0;
        double& p4 = kernel.at<double>(1, 2);
        p4 = 0;
        double& p5 = kernel.at<double>(2, 0);
        p5 = -1;
        double& p6 = kernel.at<double>(2, 1);
        p6 = -2;
        double& p7 = kernel.at<double>(2, 2);
        p7 = -1;
    }

    std::cout << kernel << std::endl;
//    filter2D(src, dst, -1, kernel, Point(-1,-1), 0, BORDER_DEFAULT );

    Mat_<double> dstMat = src.getMat_();

    std::cout << dstMat << std::endl << std::endl;
    cout << dstMat.cols << "x" << dstMat.rows << endl;
    int i = 0;
    for(; i < dstMat.rows; i++){
        int j = 0;
        for(; j < dstMat.cols; j++){
            double &f = dstMat.at<double>(i,j);
            f = faltePixel(dstMat, i, j, kernel, k);
        }
        if(i == 0) cout << "j=" << j << endl;
    }
    cout << "i=" << i << endl;

//    std::cout << dstMat << std::endl << std::endl;
    dstMat.copyTo(dst);
}

double ImageProcessing::faltePixel(Mat_<double> &I, int y_pos, int x_pos, Mat_<double>& kernel, int k){
    double result = 0.;

    for(int v = (-1)*(k/2) ; v <= k/2; v++){
        for(int u = (-1)*(k/2); u <= k/2; u++){
            if(x_pos + u >= 0 && y_pos + v >= 0)
            {
                result += I.at<double>(y_pos + v, x_pos + u) * kernel.at<double>((k/2) + v, (k/2) + u);
            }
        }
    }

    return result;
}
