#include "challangefour.h"
#include "ui_challangefour.h"

ChallangeFour::ChallangeFour(string filename, string resultPath, bool isSumFilter, QWidget *parent) :
    QDialog(parent),filename(filename),resultPath(resultPath),isSumFilter(isSumFilter),
    ui(new Ui::ChallangeFour)
{
    ui->setupUi(this);

    I = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);

    I.copyTo(processedImage);
    ui->img_original->showImageElement(I, "Original");
    ui->img_bearbeitet->showImageElement(processedImage, "Bearbeitet");


    QSpinBox* spin_filterSize = findChild<QSpinBox*>("spin_filterSize");
    QPushButton* btn_original = findChild<QPushButton*>("btn_original");

    //Summenfilter:
    QPushButton* btn_mittelwertfilter = findChild<QPushButton*>("btn_mittelwertfilter");
    QPushButton* btn_gaussfilter = findChild<QPushButton*>("btn_gaussfilter");
    QPushButton* btn_close = findChild<QPushButton*>("btn_close");

    //Differenzenfilter:
    QPushButton* btn_x_frontGradient = findChild<QPushButton*>("btn_x_frontGradient");
    QPushButton* btn_y_backGradient = findChild<QPushButton*>("btn_y_backGradient");
    QPushButton* btn_laplace = findChild<QPushButton*>("btn_laplace");
    QPushButton* btn_sobelX = findChild<QPushButton*>("btn_sobelX");
    QPushButton* btn_sobelY = findChild<QPushButton*>("btn_sobelY");
    QPushButton* btn_sobelBetrag = findChild<QPushButton*>("btn_sobelBetrag");
    QPushButton* btn_cannyEdge = findChild<QPushButton*>("btn_cannyEdge");
//    QSpinBox* spin_cannyEdgeThreshold = findChild<QSpinBox*>("spin_cannyEdgeThreshold");

    QPushButton* btn_faltung = findChild<QPushButton*>("btn_faltung");
    combo_filter = findChild<QComboBox*>("combo_filter");
    combo_filter->addItem("Filter 1");
    combo_filter->addItem("Filter 2");
    combo_filter->addItem("Filter 3");


    //TODO: Slot erstellen, Faltung ausführen.

    connect(spin_filterSize, SIGNAL(valueChanged(int)), this, SLOT(spinValueChanged(int)));
    connect(btn_original, SIGNAL(clicked()), this, SLOT(resetImage()));

    connect(btn_mittelwertfilter, SIGNAL(clicked()), this, SLOT(execMittelwertfilter()));
    connect(btn_gaussfilter, SIGNAL(clicked()), this, SLOT(execGaussfilter()));
    connect(btn_close, SIGNAL(clicked()), this, SLOT(close()));

    connect(btn_x_frontGradient, SIGNAL(clicked()), this, SLOT(execXfrontGradient()));
    connect(btn_y_backGradient, SIGNAL(clicked()), this, SLOT(execYBackGradient()));
    connect(btn_laplace, SIGNAL(clicked()), this, SLOT(execLaplace()));
    connect(btn_sobelX, SIGNAL(clicked()), this, SLOT(execSobelX()));
    connect(btn_sobelY, SIGNAL(clicked()), this, SLOT(execSobelY()));
    connect(btn_sobelBetrag, SIGNAL(clicked()), this, SLOT(execSobelBetrag()));
    connect(btn_cannyEdge, SIGNAL(clicked()), this, SLOT(execCannyEdge()));

    connect(btn_faltung, SIGNAL(clicked()), this, SLOT(execFaltung()));
//    connect(combo_filter, SIGNAL(editTextChanged(QString)), this, SLOT(comboChange(QString));


    this->spinFilterSizeValue = spin_filterSize->value();
    this->repaint();

}

ChallangeFour::~ChallangeFour()
{
    delete ui;
}


void ChallangeFour::resetImage()
{
    I.copyTo(processedImage);
    ui->img_bearbeitet->showImageElement(processedImage, "Bearbeitet");
    this->repaint();
}

void ChallangeFour::execMittelwertfilter()
{
    std::cout << "execMittelwertsfilter" << std::endl;
    ImageProcessing::filterFactory(this->processedImage, this->processedImage, this->spinFilterSizeValue,  ImageProcessing::MEDIAN);
    ui->img_bearbeitet->showImageElement(processedImage, "Bearbeitet");
    this->repaint();
}

void ChallangeFour::execGaussfilter()
{
    std::cout << "execGaussfilter" << std::endl;
    ImageProcessing::filterFactory(this->processedImage, this->processedImage, this->spinFilterSizeValue, ImageProcessing::GAUSSIAN);
    ui->img_bearbeitet->showImageElement(processedImage, "Bearbeitet");
    this->repaint();
}

void ChallangeFour::spinValueChanged(int value)
{
    this->spinFilterSizeValue = value;
    std::cout << "new Value: " << value << std::endl;
}


void ChallangeFour::execXfrontGradient()
{

}

void ChallangeFour::execYBackGradient()
{

}

void ChallangeFour::execLaplace()
{
    std::cout << "execLaplace" << std::endl;
    ImageProcessing::filterFactory(this->processedImage, this->processedImage, this->spinFilterSizeValue, ImageProcessing::LAPLACE);
    ui->img_bearbeitet->showImageElement(processedImage, "Bearbeitet");
    this->repaint();
}

void ChallangeFour::execSobelX()
{
    std::cout << "execSobelX" << std::endl;
    ImageProcessing::filterFactory(this->processedImage, this->processedImage, this->spinFilterSizeValue, ImageProcessing::SOBELX);
    ui->img_bearbeitet->showImageElement(processedImage, "Bearbeitet");
    this->repaint();
}

void ChallangeFour::execSobelY()
{
    std::cout << "execSobelY" << std::endl;
    ImageProcessing::filterFactory(this->processedImage, this->processedImage, this->spinFilterSizeValue, ImageProcessing::SOBELY);
    ui->img_bearbeitet->showImageElement(processedImage, "Bearbeitet");
    this->repaint();
}

void ChallangeFour::execSobelBetrag()
{

}

void ChallangeFour::execCannyEdge()
{
    std::cout << "execCannyEdge" << std::endl;
    QSpinBox* spin_cannyEdgeThreshold = findChild<QSpinBox*>("spin_cannyEdgeThreshold");
    ImageProcessing::filterFactory(this->processedImage, this->processedImage, this->spinFilterSizeValue, ImageProcessing::CANNYEDGE, spin_cannyEdgeThreshold->value());
    ui->img_bearbeitet->showImageElement(processedImage, "Bearbeitet");
    this->repaint();
}

void ChallangeFour::execFaltung()
{
    std::cout << "execFaltung() - Start" << std::endl;
    ImageProcessing::faltung(this->processedImage, this->processedImage, this->combo_filter->currentText());
    this->repaint();
    std::cout << "execFaltung() - Ende" << std::endl;
}
