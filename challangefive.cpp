#include "challangefive.h"
#include "ui_challangefive.h"

ChallangeFive::ChallangeFive(string filename_orig, string filename_proc, string resultPath, QWidget *parent) :
    filename_orig(filename_orig), filename_proc(filename_proc), resultPath(resultPath), QDialog(parent),
    ui(new Ui::ChallangeFive)
{
    ui->setupUi(this);

    QPushButton* btn_start = findChild<QPushButton*>("btn_start");
    QPushButton* btn_reset = findChild<QPushButton*>("btn_reset");
    QPushButton* btn_close = findChild<QPushButton*>("btn_close");

    connect(btn_start, SIGNAL(clicked()), this, SLOT(start()));
    connect(btn_reset, SIGNAL(clicked()), this, SLOT(reset()));
    connect(btn_close, SIGNAL(clicked()), this, SLOT(close()));

    this->I = imread(this->filename_orig, IMREAD_GRAYSCALE);
    ui->img_original->showImageElement(this->I, "Original");
    this->reset();
}

ChallangeFive::~ChallangeFive()
{
    delete ui;
}

void ChallangeFive::start()
{
    vector<KeyPoint> keypoints_orig, keypoints_processed;
    vector<DMatch> matches;
    Mat descriptors_orig, descriptors_processed;
    Mat img_matches;


    ImageProcessing::detectSURFMatches(this->I, keypoints_orig, descriptors_orig);
    ImageProcessing::detectSURFMatches(this->processedImage, keypoints_processed, descriptors_processed);
    ImageProcessing::matchDescriptors(this->I, this->processedImage, img_matches, matches, QString("BF"), keypoints_orig, keypoints_processed, descriptors_orig, descriptors_processed);


    vector<Point2f> obj;
    vector<Point2f> scene;
    vector<DMatch> good_matches;

    ImageProcessing::findGoodMatches(this->processedImage, matches, keypoints_orig, keypoints_processed, obj, scene, good_matches);

    drawMatches( this->I, keypoints_orig, this->processedImage, keypoints_processed,
                good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
                vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

    Mat H = findHomography( obj, scene, CV_RANSAC);

    //-- Get the corners from the image_1 ( the object to be "detected" )
    vector<Point2f> obj_corners(4);
    obj_corners[0] = cvPoint(0,0);
    obj_corners[1] = cvPoint( this->I.cols, 0 );
    obj_corners[2] = cvPoint( this->I.cols, this->I.rows );
    obj_corners[3] = cvPoint( 0, this->I.rows );
    vector<Point2f> scene_corners(4);


    perspectiveTransform( obj_corners, scene_corners, H);

    //-- Draw lines between the corners (the mapped object in the scene - image_2 )
    //0 = Unten-Links ; 1 = Unten-Rechts
    line( img_matches, scene_corners[0] + Point2f( this->I.cols, 0), scene_corners[1] + Point2f( this->I.cols, 0), Scalar(255, 0, 0), 4 );
    line( img_matches, scene_corners[1] + Point2f( this->I.cols, 0), scene_corners[2] + Point2f( this->I.cols, 0), Scalar( 0, 255, 0), 4 );
    line( img_matches, scene_corners[2] + Point2f( this->I.cols, 0), scene_corners[3] + Point2f( this->I.cols, 0), Scalar( 0, 0, 255), 4 );
    line( img_matches, scene_corners[3] + Point2f( this->I.cols, 0), scene_corners[0] + Point2f( this->I.cols, 0), Scalar( 255, 0, 255), 4 );

    vector<Point2f> obj_corners2(3);
    vector<Point2f> scene_corners2(3);

    obj_corners2[0] = keypoints_orig[good_matches[0].queryIdx].pt;
    obj_corners2[1] = keypoints_orig[good_matches[5].queryIdx].pt;
    obj_corners2[2] = keypoints_orig[good_matches[10].queryIdx].pt;

    scene_corners2[0] = keypoints_processed[good_matches[0].trainIdx].pt;
    scene_corners2[1] = keypoints_processed[good_matches[5].trainIdx].pt;
    scene_corners2[2] = keypoints_processed[good_matches[10].trainIdx].pt;


    cout << obj_corners2 << endl << endl << scene_corners2 << endl;
    Mat warp_mat = getAffineTransform(scene_corners2, obj_corners2);


    Mat warp_dst = Mat::zeros( this->processedImage.rows, this->processedImage.cols, this->processedImage.type() );
    warpAffine( this->processedImage, warp_dst, warp_mat, warp_dst.size() );


    this->ui->img_matched->showImageElement(img_matches, "Matches");
    this->ui->img_rotated->showImageElement(warp_dst, "Rotiert");

    repaint();
}

void ChallangeFive::reset()
{
    this->processedImage = imread(this->filename_proc, IMREAD_GRAYSCALE);
    ui->img_processed->showImageElement(this->processedImage, "Bearbeitet");
    repaint();
}
