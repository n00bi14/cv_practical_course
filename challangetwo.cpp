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
