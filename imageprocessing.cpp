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
    Mat I = src.getMat();
    if(I.cols > I.rows)
    {
        fx_nenner = I.cols - (I.cols - 512);
        fy_nenner = I.rows - (I.cols - 512);
    }else if(I.cols < I.rows){
        fy_nenner = I.rows - (I.rows - 512);
        fx_nenner = I.cols - (I.rows - 512);
    }

    double fx = (1. / (I.cols / fx_nenner));
    double fy = (1. / (I.rows / fy_nenner));

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
    {
        Mat kernelx = (Mat_<float>(1,3)<<-0.5, 0, 0.5);
        filter2D(src, dst, -1, kernelx);
    }
        break;
    case YBACKGRADIENT:
    {
        Mat kernely = (Mat_<float>(3,1)<<-0.5, 0, 0.5);
        filter2D(src, dst, -1, kernely);
    }
        break;
    case LAPLACE:
    {
        Mat afterLaplacian, afterGaussian;
        afterLaplacian = afterGaussian = src.getMat().clone();

        ImageProcessing::filterFactory(src, afterGaussian, kernelSize, ImageProcessing::GAUSSIAN);
        Laplacian( afterGaussian, afterLaplacian, CV_64F, kernelSize);
        convertScaleAbs( afterLaplacian, dst );
    }
        break;
    case SOBELX:
    {
        Mat afterSobel, afterGaussian;
        afterSobel = afterGaussian = src.getMat().clone();

        ImageProcessing::filterFactory(src, afterGaussian, kernelSize, ImageProcessing::GAUSSIAN);
        Sobel(afterGaussian,afterSobel,CV_64F,1,0,kernelSize);
        convertScaleAbs( afterSobel, dst );
    }
        break;
    case SOBELY:
    {
        Mat afterSobel, afterGaussian;
        afterSobel = afterGaussian = src.getMat().clone();

        ImageProcessing::filterFactory(src, afterGaussian, kernelSize, ImageProcessing::GAUSSIAN);
        Sobel(afterGaussian,afterSobel,CV_64F,0,1,kernelSize);
        convertScaleAbs( afterSobel, dst );
    }
        break;
    case SOBELBETRAG:
    {
        Mat X, Y;
        ImageProcessing::filterFactory(src, X, kernelSize, ImageProcessing::SOBELX);
        ImageProcessing::filterFactory(src, Y, kernelSize, ImageProcessing::SOBELY);

        Mat tmp(src.getMat().rows, src.getMat().cols, 0.);
        for(int i = 0; i < tmp.rows; i++){
            for(int j = 0; j < tmp.cols; j++){
                double x = X.at<double>(i,j);
                double y = Y.at<double>(i,j);
                double s = sqrt((x*x + y*y));
                tmp.at<double>(i,j) = s;
            }
        }
        X.copyTo(dst);
    }
        break;
    case CANNYEDGE:
    {
        Mat detected_edges, dst_gray;
        Mat src_gray = src.getMat();
        int k = kernelSize<3?3:kernelSize;

        blur( src_gray, detected_edges, Size(k,k) );
        Canny( detected_edges, detected_edges, cannyEdgeThreshold, cannyEdgeThreshold*3, k );
        dst_gray = Scalar::all(0);
        src.getMat().copyTo( dst_gray, detected_edges);
        dst_gray.copyTo(dst);
    }
        break;
    }
}

void ImageProcessing::faltung(InputArray src, OutputArray dst, QString filtername){
    int k = 3;
    Mat kernel(3,3,1.);

    if(QString::compare(filtername, QString("Filter 1"), Qt::CaseInsensitive) == 0)
    {
        std::cout << "Filter 1" << std::endl;
        kernel.at<double>(1, 1) = -8;

    }else if(QString::compare(filtername, QString("Filter 2"), Qt::CaseInsensitive) == 0){

        std::cout << "Filter 2" << std::endl;

        kernel.at<double>(0, 1) = 2;
        kernel.at<double>(1, 0) = 2;
        kernel.at<double>(1, 1) = 4;
        kernel.at<double>(1, 2) = 2;
        kernel.at<double>(2, 1) = 2;

        kernel = kernel / (float)16.;

    }else if(QString::compare(filtername, QString("Filter 3"), Qt::CaseInsensitive) == 0){

        std::cout << "Filter 3" << std::endl;
        kernel.at<double>(0, 1) = 2;
        kernel.at<double>(1, 0) = 0;
        kernel.at<double>(1, 1) = 0;
        kernel.at<double>(1, 2) = 0;
        kernel.at<double>(2, 0) = -1;
        kernel.at<double>(2, 1) = -2;
        kernel.at<double>(2, 2) = -1;
    }else if(QString::compare(filtername, QString("SOBEL_X"), Qt::CaseInsensitive) == 0){

        std::cout << "Filter SOBEL X" << std::endl;
        kernel.at<double>(0, 1) = 2;
        kernel.at<double>(1, 0) = 0;
        kernel.at<double>(1, 1) = 0;
        kernel.at<double>(1, 2) = 0;
        kernel.at<double>(2, 0) = -1;
        kernel.at<double>(2, 1) = -2;
        kernel.at<double>(2, 2) = -1;
    }else if(QString::compare(filtername, QString("SOBEL_Y"), Qt::CaseInsensitive) == 0){

        std::cout << "Filter SOBEL Y" << std::endl;
        kernel.at<double>(0, 1) = 0;
        kernel.at<double>(0, 2) = -1;
        kernel.at<double>(1, 0) = 2;
        kernel.at<double>(1, 1) = 0;
        kernel.at<double>(1, 2) = -2;
        kernel.at<double>(2, 1) = 0;
        kernel.at<double>(2, 2) = -1;
    }

    std::cout << kernel << std::endl;
//    filter2D(src, dst, -1, kernel);

    Mat dstMat = src.getMat();
    Mat kopie = src.getMat();


//    cout << kopie << endl << endl;
    cout << dstMat.cols << "x" << dstMat.rows << endl;

    int i = 0;
    for(; i < dstMat.rows; i++){
        int j = 0;
        for(; j < dstMat.cols; j++){
            dstMat.at<double>(i,j) = faltePixel(kopie, i, j, kernel, k);
        }
        if(i == 0) cout << "j=" << j << endl;
    }
    cout << "i=" << i << endl;

//    std::cout << dstMat << std::endl << std::endl;
    dstMat.copyTo(dst);
}

double ImageProcessing::faltePixel(Mat &I, int y_pos, int x_pos, Mat& kernel, int k){
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


void ImageProcessing::detectSURFMatches(Mat& src, vector<KeyPoint>& keypoints, Mat& descriptor){
    int minHessian = 400;
    SURF surf( minHessian );
    surf( src, Mat(), keypoints, descriptor);

}

void ImageProcessing::matchDescriptors(Mat& src1, Mat& src2, Mat& dst, vector<DMatch>& matches, QString matcher,
                                       vector<KeyPoint>& keypoints_1, vector<KeyPoint>& keypoints_2, Mat& descriptor_1, Mat& descriptor_2){

    if(QString::compare(matcher, QString("BF"), Qt::CaseInsensitive) == 0)
    {
        BFMatcher matcher(NORM_L2, false );
        matcher.match( descriptor_1, descriptor_2, matches );
        drawMatches( src1, keypoints_1, src2, keypoints_2, matches, dst );
    }else if (QString::compare(matcher, QString("FB"), Qt::CaseInsensitive) == 0){
//        FlannBasedMatcher matcher;
//        matcher.match( descriptor_1, descriptor_2, matches );
//        drawMatches( src1, keypoints_1, src2, keypoints_2, matches, dst );
    }
}

void ImageProcessing::findGoodMatches(Mat& I, vector<DMatch>& matches, vector<KeyPoint>& keypoints_obj, vector<KeyPoint>& keypoints_scene,
                                      vector<Point2f>& obj, vector<Point2f>& scene, vector<DMatch>& good_matches){
    double max_dist = 0; double min_dist = 100;

    //-- Quick calculation of max and min distances between keypoints
    for( int i = 0; i < I.rows; i++ )
    { double dist = matches[i].distance;
     if( dist < min_dist ) min_dist = dist;
     if( dist > max_dist ) max_dist = dist;
    }

    printf("-- Max dist : %f \n", max_dist );
    printf("-- Min dist : %f \n", min_dist );


    for( int i = 0; i < I.rows; i++ )
    { if( matches[i].distance < 3*min_dist )
      { good_matches.push_back( matches[i]); }
    }


    for( int i = 0; i < good_matches.size(); i++ )
    {
        //-- Get the keypoints from the good matches
        obj.push_back( keypoints_obj[ good_matches[i].queryIdx ].pt );
        scene.push_back( keypoints_scene[ good_matches[i].trainIdx ].pt );
    }
}

void ImageProcessing::stitchTwoImages(Mat& L, Mat& R, Mat& dst){
    Mat img1, img2;
    cvtColor(L, img1, CV_RGB2GRAY);
    cvtColor(R, img2, CV_RGB2GRAY);


    vector<KeyPoint> keypoints_orig, keypoints_processed;
    vector<DMatch> matches;
    Mat descriptors_orig, descriptors_processed;
    Mat img_matches;


    ImageProcessing::detectSURFMatches(img1, keypoints_orig, descriptors_orig);
    ImageProcessing::detectSURFMatches(img2, keypoints_processed, descriptors_processed);
    ImageProcessing::matchDescriptors(img1, img2, img_matches, matches, QString("BF"), keypoints_orig, keypoints_processed, descriptors_orig, descriptors_processed);


    vector<Point2f> obj;
    vector<Point2f> scene;
    vector<DMatch> good_matches;

    ImageProcessing::findGoodMatches(img2, matches, keypoints_orig, keypoints_processed, obj, scene, good_matches);

    drawMatches( img1, keypoints_orig, img2, keypoints_processed,
                good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
                vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );


    Mat H = findHomography( obj, scene, CV_RANSAC);

    //warpPerspective( img_matches, warp_dst, H, warp_dst.size() );
    warpPerspective(R,dst,H,cv::Size(L.cols+R.cols,L.rows));
//    dst = getPerspectiveTransform(L,R);


    Mat left(dst, Rect(0,0,L.cols,L.rows));
    L.copyTo(left);

    KeyPoint pointL = keypoints_orig[good_matches[0].queryIdx];
    KeyPoint pointR = keypoints_processed[good_matches[0].trainIdx];

    Mat right(dst, Rect(pointL.pt.x-pointR.pt.x, 0, R.cols, R.rows));
    R.copyTo(right);
}
