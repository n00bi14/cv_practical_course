#ifndef IMAGEELEMENT_H
#define IMAGEELEMENT_H

#include <QDialog>

namespace Ui {
class ImageElement;
}

class ImageElement : public QDialog
{
    Q_OBJECT

public:
    explicit ImageElement(QWidget *parent = 0);
    ~ImageElement();

private:
    Ui::ImageElement *ui;
};

#endif // IMAGEELEMENT_H
