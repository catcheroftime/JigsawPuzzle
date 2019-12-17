#include "cropbox.h"

#include <QDebug>
#include <QPainterPath>
#include <QPainter>
#include <QtMath>

#define LINEWIDTH 1
#define SPACING   2
#define POINTSIZE 5

CropBox::CropBox(QWidget *parent)
    : MainWidget(parent)
    , m_widthCount(4)
    , m_heightCount(4)
{
    this->installEventFilter(this);
    this->setMouseTracking(true);
}

CropBox::~CropBox()
{

}

void CropBox::setCropBoxLine(const int &widthcount, const int &heightcount)
{
    m_widthCount = widthcount;
    m_heightCount = heightcount;
}

void CropBox::showEvent(QShowEvent *e)
{
    Q_UNUSED(e);
    qDebug() << "CropBox size:" << this->width() << "," << this->height() << ")";
}

void CropBox::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter painter(this);

    drawBackground(painter);
    drawInternalLines(painter);
    drawBorder(painter);
    drawPoints(painter);
}

void CropBox::drawBackground(QPainter &painter)
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(2, 2, this->width()-2, this->height()-2);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QColor(50, 50, 50, 0));
}

void CropBox::drawInternalLines(QPainter &painter)
{
    painter.setPen( QPen{QColor{255,255,255},LINEWIDTH,Qt::DashLine});
    for (int i=1; i<m_widthCount; i++) {
        int width = this->width() / m_widthCount;
        painter.drawLine( i*width,  SPACING , i*width , this->height()-SPACING);
    }

    for (int i=1; i<m_heightCount; i++) {
        int heigth = this->height()/ m_heightCount;
        painter.drawLine( SPACING ,i*heigth,   this->width()- SPACING, i*heigth);
    }

}

void CropBox::drawBorder(QPainter &painter)
{
    painter.setPen( QPen{QColor{3,125,203},SPACING});
    painter.drawLine( SPACING,  SPACING , this->width()-SPACING , SPACING);
    painter.drawLine( SPACING,  SPACING, SPACING , this->height()-SPACING);
    painter.drawLine( SPACING,  this->height()-SPACING ,this->width()-SPACING , this->height()-SPACING);
    painter.drawLine( this->width()-SPACING,  SPACING , this->width()-SPACING , this->height()-SPACING);

}

void CropBox::drawPoints(QPainter &painter)
{
    painter.setPen( QPen{QColor{3,125,203},POINTSIZE});
    painter.drawPoint(SPACING,SPACING);
    painter.drawPoint(this->width()/2, SPACING);
    painter.drawPoint(this->width()-SPACING, SPACING);
    painter.drawPoint(SPACING, this->height()/2);
    painter.drawPoint(SPACING, this->height()-SPACING);
    painter.drawPoint(this->width()-SPACING, this->height()/2);
    painter.drawPoint(this->width()-SPACING, this->height()-SPACING);
    painter.drawPoint(this->width()/2, this->height()-SPACING);
}
