#include "challangeone.h"
#include "ui_challangeone.h"

ChallangeOne::ChallangeOne(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChallangeOne)
{
    ui->setupUi(this);
}

ChallangeOne::~ChallangeOne()
{
    delete ui;
}

void ChallangeOne::start(string filename, string resultPath)
{
//    qDebug() << "ChallangeOne.exec() : " << "Start execute Aufgabe 1";
//    qDebug() << "Filename: " << filename.c_str();

    Mat image = imread(filename);
    Mat resizedImage;

    ImageProcessing::resizeMax512(image,resizedImage);


    //Erstelle drei Graubilder aus dem Farbbild
    vector<Mat> bgr_planes;
    split(resizedImage, bgr_planes);

    imwrite(resultPath + "aufgabe_1_B.jpg", bgr_planes.at(0));
    imwrite(resultPath + "aufgabe_1_G.jpg", bgr_planes.at(1));
    imwrite(resultPath + "aufgabe_1_R.jpg", bgr_planes.at(2));

    //Färbe die Graubilder wieder ein
    //Lade Graubilder
    Mat saved_gray_B = imread(resultPath + "aufgabe_1_B.jpg");
    Mat saved_gray_G = imread(resultPath + "aufgabe_1_G.jpg");
    Mat saved_gray_R = imread(resultPath + "aufgabe_1_R.jpg");

    //Färbe Grafiken

    Mat blueFilledMat = createIndexImage(saved_gray_B, 0);
    Mat greenFilledMat = createIndexImage(saved_gray_G, 1);
    Mat redFilledMat = createIndexImage(saved_gray_R, 2);


//    qDebug() << "emptyMat.depth() = " << emptyMat.depth();
//    qDebug() << "blueFilledMat.depth() = " << blueFilledMat.depth();
//    qDebug() << "saved_gray_B.depth() = " << saved_gray_B.depth() << endl;

//    qDebug() << "emptyMat.size() = " << emptyMat.size().width << "," << emptyMat.size().height;
//    qDebug() << "blueFilledMat.size() = " << blueFilledMat.size().width << "," << blueFilledMat.size().height;
//    qDebug() << "saved_gray_B.size() = " << saved_gray_B.size().width << "," << saved_gray_B.size().height << endl;


    //Schreibe eingefärbte Grafiken

    imwrite(resultPath + "aufgabe_1_B_filled.jpg", blueFilledMat);
    imwrite(resultPath + "aufgabe_1_G_filled.jpg", greenFilledMat);
    imwrite(resultPath + "aufgabe_1_R_filled.jpg", redFilledMat);

    vector<ImageElement*> imageElements;
    imageElements.push_back(new ImageElement("Blue Channel", resultPath + "aufgabe_1_B.jpg"));
    imageElements.push_back(new ImageElement("Green Channel", resultPath + "aufgabe_1_G.jpg"));
    imageElements.push_back(new ImageElement("Red Channel", resultPath + "aufgabe_1_R.jpg"));

    imageElements.push_back(new ImageElement("Blue Channel filled", resultPath + "aufgabe_1_B_filled.jpg"));
    imageElements.push_back(new ImageElement("Blue Channel filled", resultPath + "aufgabe_1_G_filled.jpg"));
    imageElements.push_back(new ImageElement("Blue Channel filled", resultPath + "aufgabe_1_R_filled.jpg"));

    qDebug() << "imageElements.size = " << imageElements.size();

    showImages(imageElements);
}

void ChallangeOne::showImages(vector<ImageElement*> &images)
{
    for(int i = 0; i < images.size(); i++){
        ImageElement* element = images.at(i);
        element->showImageElement();
        element->repaint();
    }

    // QGridLayout *
    QHBoxLayout *layoutTop = findChild<QHBoxLayout*>("layoutHTop");
    QHBoxLayout *layoutBottom = findChild<QHBoxLayout*>("layoutHBottom");

    qDebug() << layoutTop << "\t" << layoutBottom;

    layoutTop->addWidget(images.at(0));
    layoutTop->addWidget(images.at(1));
    layoutTop->addWidget(images.at(2));

    layoutBottom->addWidget(images.at(3));
    layoutBottom->addWidget(images.at(4));
    layoutBottom->addWidget(images.at(5));

    this->repaint();
}

Mat ChallangeOne::createIndexImage(Mat image, int color){
    //build columns for lookup table
    vector<Mat> lookupCols;
    Mat lookUpColColored(256, 1, CV_8U);
    for(int i = 0; i < 256; i++)
       lookUpColColored.data[i] = i;
    Mat lookUpColBlack(256, 1, CV_8U, Scalar(0));

    //compose lookup table for the specified color
    for(int i = 0; i < 3; i++)
        if(i == color)
            lookupCols.push_back(lookUpColColored);
        else
            lookupCols.push_back(lookUpColBlack);

    Mat lookupTable, pigmentContent;
    merge(lookupCols, lookupTable);
    LUT(image, lookupTable, pigmentContent);

    return pigmentContent;
}
