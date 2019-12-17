#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>

class MainWidget : public QWidget
{
    Q_OBJECT

    // 标记鼠标是否在边框位置
    enum Direction { UP=0, DOWN=1, LEFT, RIGHT, LEFTTOP, LEFTBOTTOM, RIGHTBOTTOM, RIGHTTOP, NONE };
    enum {PADDING = 2, PADINGADD = 2*PADDING};
    enum {SPEED = 300};

public:
    MainWidget(QWidget *parent = 0);
    virtual ~MainWidget();

protected:
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);

    void setWndPoint(QPoint pos);
    bool eventFilter(QObject *object, QEvent *event);

private:
    bool m_bMoveWndFlag;
    bool m_bContralState;
    Direction m_curDirec;// 鼠标在边框上的标记
    QPoint m_WndPoint;// 记录鼠标移动前窗口位置

    /**
     * @brief setDirec 设置鼠标是否在窗口边框上
     * @param pos 鼠标位置
     */
    void setDirec(QPoint IPoint);

    /**
     * @brief IResize 调整窗口大小
     * @param IPoint 当前鼠标位置
     */
    void IResize(QPoint IPoint);

signals:
    void sigSetContra();
};

#endif // MAINWIDGET_H
