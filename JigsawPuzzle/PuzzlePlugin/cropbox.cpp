#include "cropbox.h"

#include <QDebug>
#include <QPainterPath>
#include <QPainter>
#include <QMouseEvent>

#define LINEWIDTH 1
#define SPACING   2
#define POINTSIZE 5

CropBox::CropBox(QWidget *parent)
    : QWidget(parent)
    , m_widthCount(4)
    , m_heightCount(4)
    , m_bMovingFlag(false)
    , m_curDirec(NONE)
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

void CropBox::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "CropBox size:" << this->width() << "," << this->height() << ")";
}

void CropBox::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    drawBackground(painter);
    drawInternalLines(painter);
    drawBorder(painter);
    drawPoints(painter);
}

void CropBox::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bMovingFlag = true;
        m_dragPosition = event->globalPos() - this->pos();
    }
    event->accept();
}


void CropBox::mouseMoveEvent(QMouseEvent *event)
{
    QPoint point = event->pos();
    QPoint global_point = event->globalPos();

    if (!m_bMovingFlag)
        setDirection(point);//改变鼠标形状
    else
        resizeWindow(global_point, point);//鼠标点击之后，（关于移动）

    event->accept();
}


void CropBox::mouseReleaseEvent(QMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    if(event->button()==Qt::LeftButton) {
        m_bMovingFlag = false;
    }

    event->accept();
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

void CropBox::setDirection(QPoint point)
{
    int width = this->width();
    int heigth = this->height();

    if ( PADDING >= point.x() && 0 <= point.x() &&  PADDING  >= point.y() && 0 <= point.y())
    {
        m_curDirec = LEFTTOP;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));  // 设置鼠标形状
    }
    else if(width - PADDING <= point.x() && width >= point.x() && heigth - PADDING <= point.y() && heigth >= point.y())
    {
        m_curDirec = RIGHTBOTTOM;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));  // 设置鼠标形状
    }
    else if(PADDING >= point.x() && 0 <= point.x() && heigth - PADDING <= point.y() && heigth >= point.y())
    {
        m_curDirec = LEFTBOTTOM;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    }
    else if(PADDING >= point.y() && 0 <= point.y() && width - PADDING <= point.x() && width >= point.x())
    {
        m_curDirec = RIGHTTOP;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    }
    else if(PADDING >= point.x() && 0 <= point.x())
    {
        m_curDirec = LEFT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if(PADDING >= point.y() && 0 <= point.y())
    {
        m_curDirec = UP;
        this->setCursor(QCursor(Qt::SizeVerCursor));

    }
    else if(width - PADDING <= point.x() && width >= point.x())
    {
        m_curDirec = RIGHT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if(heigth - PADDING <= point.y() && heigth >= point.y())
    {
        m_curDirec = DOWN;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }
    else
    {
        m_curDirec = NONE;
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
}

void CropBox::resizeWindow(QPoint global_point, QPoint local_point)
{
    QRect rectMove = this->geometry();

    QPoint parent_point = mapToParent(local_point);

    if (m_bMovingFlag)
    {
        QWidget* parent_widget = (QWidget *)this->parent();
        switch(m_curDirec)
        {
        case NONE: {
            QPoint end_point = global_point - m_dragPosition ;
            if (parent_widget) {
                if (end_point.x() <= 0 || end_point.x() >= parent_widget->width()-this->width() ||
                        end_point.y() <= 0 || end_point.y() >= parent_widget->height()-this->height() )
                    return;
            }
            move( end_point );
            break;
        }
        case LEFTTOP:
            if (parent_widget) {
                if (parent_point.x() < 0 || parent_point.y() < 0)
                    return;
            }
            if ( rectMove.right() - parent_point.x()  < PADINGADD || rectMove.bottom() - parent_point.y() < PADINGADD)
                return;

            rectMove.setLeft(parent_point.x() );
            rectMove.setTop(parent_point.y());
            break;
        case RIGHTBOTTOM: {
            if (parent_widget) {
                if ( parent_point.x() > parent_widget->width() || parent_point.y() > parent_widget->height())
                    return;
            }
            if ( parent_point.x()  - rectMove.left() < PADINGADD || parent_point.y() - rectMove.top() < PADINGADD)
                return;

            rectMove.setRight(parent_point.x() );
            rectMove.setBottom(parent_point.y());
            break;
        }
        case LEFTBOTTOM:
            if (parent_widget) {
                if (parent_point.x() < 0 || parent_point.y() > parent_widget->height())
                    return;
            }
            if ( rectMove.right() - parent_point.x() < PADINGADD || parent_point.y() - rectMove.top() < PADINGADD)
                return;

            rectMove.setLeft(parent_point.x() );
            rectMove.setBottom(parent_point.y());
            break;
        case RIGHTTOP:
            if (parent_widget) {
                if (parent_point.y() < 0 || parent_point.x() > parent_widget->width())
                    return;
            }
            if ( parent_point.x()- rectMove.left() < PADINGADD || rectMove.bottom() - parent_point.y() < PADINGADD)
                return;
            rectMove.setRight(parent_point.x() );
            rectMove.setTop(parent_point.y());
            break;
        case LEFT: {
            if (parent_widget) {
                if ( parent_point.x() < PADINGADD )
                    return;
            }

            if ( rectMove.right() - parent_point.x() < PADINGADD )
                return;

            rectMove.setLeft(parent_point.x()  );
            break;
        }
        case UP:
            if (parent_widget) {
                if (parent_point.y() < 0)
                    return;
            }
            if ( rectMove.bottom() - parent_point.y() < PADINGADD)
                return;

            rectMove.setTop(parent_point.y());
            break;
        case RIGHT: {
            if (parent_widget) {
                if ( parent_point.x() > parent_widget->width())
                    return;
            }
            if ( parent_point.x() - rectMove.left() < PADINGADD)
                return;

            rectMove.setRight(parent_point.x() );
            break;
        }
        case DOWN: {
            if (parent_widget) {
                if ( parent_point.y() > parent_widget->height())
                    return;
            }
            if ( parent_point.y() - rectMove.top() < PADINGADD)
                return;

            rectMove.setBottom(parent_point.y());
            break;
        }
        default:
            break;

        }
    }
    if (m_curDirec != NONE)
        this->setGeometry(rectMove);
}
