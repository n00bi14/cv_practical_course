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
