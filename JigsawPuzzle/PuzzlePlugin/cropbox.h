#ifndef CROPBOX_H
#define CROPBOX_H

#include "mainwidget.h"

class CropBox : public MainWidget
{
    Q_OBJECT
public:
    CropBox(QWidget *parent = 0);
    ~CropBox();

     void setCropBoxLine(const int & widthcount,const int& heightcount);

protected:
    void showEvent(QShowEvent * e);
    void paintEvent(QPaintEvent * e);

signals:

private:
    void drawBackground(QPainter &painter);
    void drawInternalLines(QPainter &painter);
    void drawBorder(QPainter &painter);
    void drawPoints(QPainter &painter);


private:
    int m_widthCount;
    int m_heightCount;
};

#endif // CROPBOX_H
