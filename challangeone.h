#ifndef CHALLANGEONE_H
#define CHALLANGEONE_H

#include <QDialog>

namespace Ui {
class ChallangeOne;
}

class ChallangeOne : public QDialog
{
    Q_OBJECT

public:
    explicit ChallangeOne(QWidget *parent = 0);
    ~ChallangeOne();

private:
    Ui::ChallangeOne *ui;
};

#endif // CHALLANGEONE_H
