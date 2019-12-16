#include "imageshowlabel.h"

#include <QPixmap>

ImageShowLabel::ImageShowLabel(QWidget *parent) :
    QLabel(parent)
  , m_shape(CropBoxShape::Square)
  , m_pCropBox( new CropBox() )
  , m_widthCount(3)
  , m_heightCount(3)
{
    m_pCropBox->setStyleSheet("background-color:rgb(255,0,0)");
}

void ImageShowLabel::setImage(const QString &filename)
{

}

QPixmap ImageShowLabel::getCroppedImage()
{

}

void ImageShowLabel::setCropBoxLine(const int& widthcount, const int& heightcount)
{
    m_widthCount = widthcount;
    m_heightCount = heightcount;
}

void ImageShowLabel::setCropBoxShape(ImageShowLabel::CropBoxShape shape)
{
    m_shape = shape;
}

void ImageShowLabel::mousePressEvent(QMouseEvent *ev)
{

}

void ImageShowLabel::mouseReleaseEvent(QMouseEvent *ev)
{

}

void ImageShowLabel::mouseMoveEvent(QMouseEvent *ev)
{

}
