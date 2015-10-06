#ifndef CHALLANGETWO_H
#define CHALLANGETWO_H

#include <QDialog>

namespace Ui {
class ChallangeTwo;
}

class ChallangeTwo : public QDialog
{
    Q_OBJECT

public:
    explicit ChallangeTwo(QWidget *parent = 0);
    ~ChallangeTwo();

private:
    Ui::ChallangeTwo *ui;
};

#endif // CHALLANGETWO_H
