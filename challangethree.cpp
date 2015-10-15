#include "challangethree.h"
#include "ui_challangethree.h"

ChallangeThree::ChallangeThree(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChallangeThree)
{
    ui->setupUi(this);
}

ChallangeThree::~ChallangeThree()
{
    delete ui;
}
