#include "imageelement.h"
//#include "ui_imageelement.h"

ImageElement::ImageElement(std::string heading, std::string filename, QWidget *parent) :
    QWidget(parent), heading(heading), filename(filename)
{
//    qDebug() << heading.c_str() << " @ " << filename.c_str();
    image = imread(filename, CV_LOAD_IMAGE_UNCHANGED);

}

ImageElement::ImageElement(std::string title, const Mat& I, QWidget *parent):
    QWidget(parent), heading(title),image(I)
{
}

ImageElement::ImageElement(QWidget *parent):
    QWidget(parent)
{

}

ImageElement::~ImageElement()
{

}

void ImageElement::showImageElement(Mat& I, std::string title)
{
    this->image = I;
    this->heading = title;
    this->showImageElement();
}

void ImageElement::showImageElement()
{
    switch (image.type()) {
        case CV_8UC1:
            cvtColor(image, _cvImage, CV_GRAY2RGB);
            break;
        case CV_8UC3:
            cvtColor(image, _cvImage, CV_BGR2RGB);
            break;
    }

    assert(_cvImage.isContinuous());
    _qimage = QImage(_cvImage.data, _cvImage.cols, _cvImage.rows, _cvImage.cols*3, QImage::Format_RGB888);


    int scaleTo = (this->size().width() < this->size().height()) ? this->size().width() : this->size().height();

    qDebug() << this->size().width() << "\t" << this->size().height();

    if(_qimage.width() < _qimage.height())
        _qimage = _qimage.scaledToHeight(scaleTo);
    else
        _qimage = _qimage.scaledToWidth(scaleTo);

    float cvScaleFactor = float(scaleTo) / ((_cvImage.cols < _cvImage.rows) ? _cvImage.rows : _cvImage.cols);
    cv::resize(_cvImage, _cvImage, cv::Size(int(_cvImage.cols * cvScaleFactor), int(_cvImage.rows * cvScaleFactor)));

//    qDebug() << this->heading.c_str() << " with: ";
//    qDebug() << &(this->_cvImage) << " @ " << this->filename.c_str();

    repaint();
}


void ImageElement::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);
    painter.drawText(QPoint(10,15), QString::fromStdString(heading));
    painter.drawImage(QPoint(0,25), _qimage);
    painter.end();
}
