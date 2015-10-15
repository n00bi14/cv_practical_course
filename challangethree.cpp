#include "challangethree.h"
#include "ui_challangethree.h"

ChallangeThree::ChallangeThree(string filename, string resultPath, QWidget *parent) :
    QDialog(parent),filename(filename),resultPath(resultPath),
    ui(new Ui::ChallangeThree)
{
    ui->setupUi(this);

    slider_stretching = findChild<QSlider*>("slider_stretching");
    slider_gammakorrektur = findChild<QSlider*>("slider_gammakorrektur");

    txt_stretching = findChild<QLineEdit*>("txt_stretching");
    txt_gammakorrektur = findChild<QLineEdit*>("txt_gammakorrektur");

    chk_linearisierung = findChild<QCheckBox*>("chk_linearisierung");

    connect(slider_stretching, SIGNAL(valueChanged(int)), this, SLOT(setStretchedValue(int)));
    connect(slider_gammakorrektur, SIGNAL(valueChanged(int)), this, SLOT(setGammakorrekturValue(int)));
    connect(chk_linearisierung, SIGNAL(clicked(bool)), this, SLOT(linearisierungChecked(bool)));

    txt_stretching->setText(QString::number(slider_stretching->value()));
    txt_gammakorrektur->setText(QString::number(slider_gammakorrektur->value()));

    Mat image = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
    ImageProcessing::resizeMax512(image, this->I);
    this->I.copyTo(this->processedImage);


    ImageElement* original = new ImageElement("Originalbild", filename);
    processed = new ImageElement("Bearbeites Bild", this->processedImage);

    QHBoxLayout *hLayout = findChild<QHBoxLayout*>("hLayout");
    hLayout->addWidget(original);
    hLayout->addWidget(processed);

    original->showImageElement();
    processed->showImageElement();

    this->repaint();
}

ChallangeThree::~ChallangeThree()
{
    delete ui;
}

void ChallangeThree::setStretchedValue(int value)
{
    this->txt_stretching->setText(QString::number(value));
    this->slider_stretching->setValue(value);

    this->calculateAllFilters();
}

void ChallangeThree::setGammakorrekturValue(int value)
{
    //value * 0.1, damit Werte zwischen 0.1 und 3.0 raus kommen
    double newValue = value * 0.1;

    this->txt_gammakorrektur->setText(QString::number(newValue));
    this->slider_gammakorrektur->setValue(value);

    this->calculateAllFilters();
}

void ChallangeThree::linearisierungChecked(bool b)
{
    this->calculateAllFilters();
}

void ChallangeThree::calculateAllFilters()
{
    QHBoxLayout *hLayout = findChild<QHBoxLayout*>("hLayout");


    this->processed->hide();
    hLayout->removeWidget(this->processed);

    if(this->txt_stretching->text().toInt() != 0)
        ImageProcessing::stretchImage(this->I, this->processedImage, this->txt_stretching->text().toInt());
    else
        this->I.copyTo(this->processedImage);

    if(this->txt_gammakorrektur->text().toDouble() != 0)
        ImageProcessing::correktGammaValue(this->processedImage, this->processedImage, this->txt_gammakorrektur->text().toDouble(), this->txt_stretching->text().toInt());

    if(chk_linearisierung->isChecked())
        equalizeHist(this->processedImage, this->processedImage);

//    imshow("test", this->I);

    processed = new ImageElement("Bearbeites Bild", this->processedImage);
    processed->showImageElement();

    hLayout->addWidget(this->processed);

    this->repaint();
}
