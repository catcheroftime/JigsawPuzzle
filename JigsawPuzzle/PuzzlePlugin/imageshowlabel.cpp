#include "imageshowlabel.h"

#include <QPixmap>
#include <QDebug>
#include <QPainter>
#include <QPainterPath>

#include "cropbox.h"

ImageShowLabel::ImageShowLabel(QWidget *parent) :
    QLabel(parent)
  , m_shape(CropBoxShape::Square)
  , m_pCropBox(new CropBox(this))
  , m_widthCount(3)
  , m_heightCount(3)
{
    m_pCropBox->resize(100, 100);
    m_pCropBox->move(0, 0);
    m_pCropBox->show();
}

void ImageShowLabel::setImage(const QString &filename)
{
    QImage* img = new QImage;

    img->load(filename);
    this->setPixmap(QPixmap::fromImage(*img));

    qDebug() <<"Image Size:("<< img->width()<< "," << img->height()<< ")";
}

QPixmap ImageShowLabel::getCroppedImage()
{

}

void ImageShowLabel::setCropBoxLine(const int& widthcount, const int& heightcount)
{
    m_pCropBox->setCropBoxLine(widthcount, heightcount );

}

void ImageShowLabel::setCropBoxShape(ImageShowLabel::CropBoxShape shape)
{
    m_shape = shape;
}

void ImageShowLabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);

    QPainterPath path1;
    path1.setFillRule(Qt::WindingFill);
    path1.addRect(0, 0, this->width(), this->height());

    QPainterPath path2;
    path2.setFillRule(Qt::WindingFill);
    path2.addRect(m_pCropBox->pos().x()+1,m_pCropBox->pos().y()+1, m_pCropBox->width()-2, m_pCropBox->height()-2);

    QPainterPath end_path = path1.subtracted(path2);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(end_path, QColor(0, 0, 0, 80));

}

void ImageShowLabel::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    qDebug() <<"Label Size:("<< this->width()<< "," << this->height()<< ")";
}
