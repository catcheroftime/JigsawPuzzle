#include "mainwidget.h"

#include <QPropertyAnimation>
#include <QTimer>
#include <QDebug>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , m_bMoveWndFlag(false)
    , m_curDirec(NONE)
{
    //    去掉控制器窗口的标题栏
//    this->setWindowFlags(Qt::FramelessWindowHint/*|Qt::SubWindow*/);
    //    设置响应鼠标移动事件
    //    this->setMouseTracking(true);
}

MainWidget::~MainWidget()
{

}


void MainWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(this->isMaximized())
    {
        QWidget::mouseMoveEvent(event);
        return;
    }
    QPoint IPoint = event->globalPos();

    if (!m_bMoveWndFlag)
    {
        setDirec(IPoint);//改变鼠标形状
    }
    else
    {
        IResize(IPoint);//鼠标点击之后，（关于移动）
    }
    QWidget::mouseMoveEvent(event);
}

void MainWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if(!this->isMaximized())
        {
            m_WndPoint = this->pos() - event->globalPos();
        }
        m_bMoveWndFlag = true;
    }
    QWidget::mousePressEvent(event);
}

void MainWidget::mouseReleaseEvent(QMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    m_bMoveWndFlag = false;

    QWidget::mouseReleaseEvent(event);
}

void MainWidget::setWndPoint(QPoint pos)
{
    m_WndPoint = this->pos()-pos;
}

bool MainWidget::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() == QEvent::MouseMove)
    {
        QWidget* pWdt = dynamic_cast<QWidget*>(object);
        QMouseEvent* pEvent = dynamic_cast<QMouseEvent*>(event);
        if(pWdt && pEvent)
        {
            mouseMoveEvent(pEvent);
        }
    }
    QWidget::eventFilter(object, event);
    return false;
}

void MainWidget::setDirec(QPoint IPoint)
{
    QRect rect = this->rect();
    QPoint TopLeftPos = this->mapToGlobal(rect.topLeft());
    QPoint BottomRightPos = this->mapToGlobal(rect.bottomRight());

    if(this->isFullScreen())
        return;
    if (TopLeftPos.x() + PADDING >= IPoint.x() && TopLeftPos.x() <= IPoint.x() && TopLeftPos.y() + PADDING  >= IPoint.y() && TopLeftPos.y() <= IPoint.y())
    {
        m_curDirec = LEFTTOP;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));  // 设置鼠标形状
    }
    else if(BottomRightPos.x() - PADDING <= IPoint.x() && BottomRightPos.x() >= IPoint.x() && BottomRightPos.y() - PADDING <= IPoint.y() && BottomRightPos.y() >= IPoint.y())
    {
        m_curDirec = RIGHTBOTTOM;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));  // 设置鼠标形状
    }
    else if(TopLeftPos.x() +PADDING >= IPoint.x() && TopLeftPos.x() <= IPoint.x() && BottomRightPos.y() - PADDING <= IPoint.y() && BottomRightPos.y() >= IPoint.y())
    {
        m_curDirec = LEFTBOTTOM;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    }
    else if(TopLeftPos.y() + PADDING >= IPoint.y() && TopLeftPos.y() <= IPoint.y() && BottomRightPos.x() - PADDING <= IPoint.x() && BottomRightPos.x() >= IPoint.x())
    {
        m_curDirec = RIGHTTOP;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    }
    else if(TopLeftPos.x() + PADDING >= IPoint.x() && TopLeftPos.x() <= IPoint.x())
    {
        m_curDirec = LEFT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if(TopLeftPos.y() + PADDING >= IPoint.y() && TopLeftPos.y() <= IPoint.y())
    {
        m_curDirec = UP;
        this->setCursor(QCursor(Qt::SizeVerCursor));

    }
    else if(BottomRightPos.x() - PADDING <= IPoint.x() && BottomRightPos.x() >= IPoint.x())
    {
        m_curDirec = RIGHT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if(BottomRightPos.y() - PADDING <= IPoint.y() && BottomRightPos.y() >= IPoint.y())
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

void MainWidget::IResize(QPoint IPoint)
{
    QRect rectMove = this->geometry();
    QPoint TopLeftPos = mapToGlobal(this->rect().topLeft());
    QPoint BottomRight = mapToGlobal(this->rect().bottomRight());

    if (m_bMoveWndFlag)
    {
        switch(m_curDirec)
        {
        case NONE:
           this->move(IPoint+ m_WndPoint);
            break;
        case LEFTTOP:
           if(BottomRight.x() - IPoint.x() <= this->minimumWidth())
                rectMove.setX(TopLeftPos.x());
           else
                 rectMove.setX(IPoint.x());
           if(BottomRight.y() - IPoint.y() <= this->minimumHeight())
                rectMove.setY(TopLeftPos.y());
           else
                rectMove.setY(IPoint.y());
            break;
        case RIGHTBOTTOM:
            rectMove.setWidth(IPoint.x()-TopLeftPos.x());
            rectMove.setHeight(IPoint.y()-TopLeftPos.y());
            break;
        case LEFTBOTTOM:
            rectMove.setX(IPoint.x());
            rectMove.setHeight(IPoint.y()-TopLeftPos.y());
            break;
        case RIGHTTOP:
            rectMove.setY(IPoint.y());
            rectMove.setWidth(IPoint.x()-TopLeftPos.x());
            break;
        case LEFT:
            if(BottomRight.x() - IPoint.x() <= this->minimumWidth())
                break;
            else{
                rectMove.setX(IPoint.x());
            }
            break;
        case UP:
            if(BottomRight.y() - IPoint.y() <= this->minimumHeight())
                 break;
            else{
                rectMove.setY(IPoint.y());
            }
            break;
        case RIGHT:

                rectMove.setWidth(IPoint.x() - TopLeftPos.x());

            break;
        case DOWN:
            rectMove.setHeight(IPoint.y() - TopLeftPos.y());
            break;
        default:
            break;

        }
    }
    if (m_curDirec != NONE)
        this->setGeometry(rectMove);
}

