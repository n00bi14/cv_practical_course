#include "imageelement.h"
#include "ui_imageelement.h"

ImageElement::ImageElement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageElement)
{
    ui->setupUi(this);
}

ImageElement::~ImageElement()
{
    delete ui;
}
