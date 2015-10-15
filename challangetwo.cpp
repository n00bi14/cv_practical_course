#include "challangetwo.h"
#include "ui_challangetwo.h"

ChallangeTwo::ChallangeTwo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChallangeTwo)
{
    ui->setupUi(this);
}

ChallangeTwo::~ChallangeTwo()
{
    delete ui;
}

void ChallangeTwo::showImages(vector<ImageElement*> &images)
{
    for(int i = 0; i < images.size(); i++){
        ImageElement* element = images.at(i);
        element->showImageElement();
        element->repaint();
    }

    // QGridLayout *
    QHBoxLayout *layoutHTop = findChild<QHBoxLayout*>("layoutHTop");
    QHBoxLayout *layoutHBottom = findChild<QHBoxLayout*>("layoutHBottom");


    layoutHTop->addWidget(images.at(0));
    layoutHTop->addWidget(images.at(1));

    layoutHBottom->addWidget(images.at(2));
    layoutHBottom->addWidget(images.at(3));

    this->repaint();
}

void ChallangeTwo::startA(string filename, string resultPath)
{
    Mat image = imread(filename);
    Mat M,I;

    ImageProcessing::resizeMax512(image,M);
    cvtColor(M,I,CV_BGR2HSV);

    imwrite(resultPath + "aufgabe_2_hsv.jpg", I);

    vector<Mat> bgr_planes;
    split(I, bgr_planes);

    imwrite(resultPath + "aufgabe_2_hsv_H.jpg", bgr_planes.at(0));
    imwrite(resultPath + "aufgabe_2_hsv_S.jpg", bgr_planes.at(1));
    imwrite(resultPath + "aufgabe_2_hsv_V.jpg", bgr_planes.at(2));

    vector<ImageElement*> imageElements;
    imageElements.push_back(new ImageElement("HSV", resultPath + "aufgabe_2_hsv.jpg"));
    imageElements.push_back(new ImageElement("H Channel", resultPath + "aufgabe_2_hsv_H.jpg"));
    imageElements.push_back(new ImageElement("S Channel", resultPath + "aufgabe_2_hsv_S.jpg"));
    imageElements.push_back(new ImageElement("V Channel", resultPath + "aufgabe_2_hsv_V.jpg"));
    showImages(imageElements);
}

void ChallangeTwo::startB(string filename, string resultPath)
{
    Mat image = imread(filename);
    Mat M;

    ImageProcessing::resizeMax512(image,M);
    ImageProcessing::convertToCMY(M);

    imwrite(resultPath + "aufgabe_2_cmy.jpg", M);

    vector<Mat> bgr_planes;
    split(M, bgr_planes);

    imwrite(resultPath + "aufgabe_2_cmy_C.jpg", bgr_planes.at(0));
    imwrite(resultPath + "aufgabe_2_cmy_M.jpg", bgr_planes.at(1));
    imwrite(resultPath + "aufgabe_2_cmy_Y.jpg", bgr_planes.at(2));

    vector<ImageElement*> imageElements;
    imageElements.push_back(new ImageElement("CMY", resultPath + "aufgabe_2_cmy.jpg"));
    imageElements.push_back(new ImageElement("C Channel", resultPath + "aufgabe_2_cmy_C.jpg"));
    imageElements.push_back(new ImageElement("M Channel", resultPath + "aufgabe_2_cmy_M.jpg"));
    imageElements.push_back(new ImageElement("Y Channel", resultPath + "aufgabe_2_cmy_Y.jpg"));
    showImages(imageElements);

}


void ChallangeTwo::startC(string filename, string resultPath)
{
    Mat image = imread(filename);
    Mat M;

    ImageProcessing::resizeMax512(image,M);

    qDebug() << "Processing images ...";

    vector<Mat> result = ImageProcessing::convertToYIQ(M);

    qDebug() << "Write images ...";

    imwrite(resultPath + "aufgabe_2_yiq.jpg", result.at(0));
    imwrite(resultPath + "aufgabe_2_yiq_Y.jpg", result.at(1));
    imwrite(resultPath + "aufgabe_2_yiq_I.jpg", result.at(2));
    imwrite(resultPath + "aufgabe_2_yiq_Q.jpg", result.at(3));

    qDebug() << "Load images to show ...";

    vector<ImageElement*> imageElements;
    imageElements.push_back(new ImageElement("YIQ",       resultPath + "aufgabe_2_yiq.jpg"));
    imageElements.push_back(new ImageElement("Y Channel", resultPath + "aufgabe_2_yiq_Y.jpg"));
    imageElements.push_back(new ImageElement("I Channel", resultPath + "aufgabe_2_yiq_I.jpg"));
    imageElements.push_back(new ImageElement("Q Channel", resultPath + "aufgabe_2_yiq_Q.jpg"));
    showImages(imageElements);

}

void ChallangeTwo::startD(string filename, string resultPath)
{
    Mat image = imread(filename);
    Mat M,I;
    ImageProcessing::resizeMax512(image,M);
    ImageProcessing::convertToLab(M,I);

    vector<Mat> planes;
    split(I, planes);


    imwrite(resultPath + "aufgabe_2_lab.jpg", I);
    imwrite(resultPath + "aufgabe_2_lab_L.jpg", planes.at(0));
    imwrite(resultPath + "aufgabe_2_lab_A.jpg", planes.at(1));
    imwrite(resultPath + "aufgabe_2_lab_B.jpg", planes.at(2));

    vector<ImageElement*> imageElements;
    imageElements.push_back(new ImageElement("Lab",       resultPath + "aufgabe_2_lab.jpg"));
    imageElements.push_back(new ImageElement("L Channel", resultPath + "aufgabe_2_lab_L.jpg"));
    imageElements.push_back(new ImageElement("A Channel", resultPath + "aufgabe_2_lab_A.jpg"));
    imageElements.push_back(new ImageElement("B Channel", resultPath + "aufgabe_2_lab_B.jpg"));
    showImages(imageElements);
}
