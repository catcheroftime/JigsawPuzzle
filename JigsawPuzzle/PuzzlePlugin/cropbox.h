#ifndef CROPBOX_H
#define CROPBOX_H

#include <QWidget>

class CropBox : public QWidget
{
    Q_OBJECT

    enum Direction { UP=0, DOWN, LEFT, RIGHT, LEFTTOP, LEFTBOTTOM, RIGHTBOTTOM, RIGHTTOP, NONE };
    enum {PADDING = 5, PADINGADD = 10*PADDING};

public:
    CropBox(QWidget *parent = 0);
    ~CropBox();

    enum CropBoxShape {
        Square = 0,
        Rectangle,
        Round
    };

     void setCropBoxLine(const int & widthcount,const int& heightcount);

     void setCropBoxShape(CropBoxShape shape = CropBoxShape::Rectangle);

protected:
    void showEvent(QShowEvent *event);
    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    void drawBackground(QPainter &painter);
    void drawInternalLines(QPainter &painter);
    void drawBorder(QPainter &painter);
    void drawPoints(QPainter &painter);

    void setDirection(QPoint point);
    void resizeWindow(QPoint global_point, QPoint local_point);

private:
    CropBoxShape m_shape;
    int m_widthCount;
    int m_heightCount;

    bool m_bMovingFlag;
    Direction m_curDirec;
    QPoint m_dragPosition;
};

#endif // CROPBOX_H
