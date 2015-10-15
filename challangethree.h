#ifndef CHALLANGETHREE_H
#define CHALLANGETHREE_H

#include <QDialog>

namespace Ui {
class ChallangeThree;
}

class ChallangeThree : public QDialog
{
    Q_OBJECT

public:
    explicit ChallangeThree(QWidget *parent = 0);
    ~ChallangeThree();

private:
    Ui::ChallangeThree *ui;
};

#endif // CHALLANGETHREE_H
