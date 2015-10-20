#ifndef IMAGEELEMENT_H
#define IMAGEELEMENT_H

#include <QWidget>


#include <core.hpp>
#include <highgui.hpp>
#include <imgproc.hpp>

#include <string>

#include <QDebug>

using namespace cv;

class ImageElement : public QWidget
{
    Q_OBJECT

public:
    explicit ImageElement(std::string title, std::string path, QWidget *parent = 0);
    ImageElement(std::string title, const Mat& I, QWidget *parent = 0);
    ~ImageElement();
    void showImageElement();

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    std::string heading, filename;
    QImage _qimage;
    Mat _cvImage;
    Mat image;
};

#endif // IMAGEELEMENT_H
