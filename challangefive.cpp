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
    int hessian = 400;


//    SurfFeatureDetector detector( minHessian );
//    std::vector<KeyPoint> keypoints;
//    detector.detect( this->processedImage, keypoints);

//    Mat img_keypoints;
//    drawKeypoints( this->processedImage, keypoints, img_keypoints, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
//    repaint();
}

void ChallangeFive::reset()
{
    this->processedImage = imread(this->filename_proc, IMREAD_GRAYSCALE);
    ui->img_processed->showImageElement(this->processedImage, "Bearbeitet");
    repaint();
}
