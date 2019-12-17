#ifndef IMAGESHOWLABEL_H
#define IMAGESHOWLABEL_H

#include <QLabel>

class QPixmap;
class CropBox;

class ImageShowLabel : public QLabel
{
public:
    ImageShowLabel(QWidget *parent = 0);

    enum CropBoxShape {
        Square = 0,
        Rectangle,
        Round
    };

    void setImage(const QString & filename);
    QPixmap getCroppedImage();

    void setCropBoxLine(const int & widthcount,const int& heightcount);
    void setCropBoxShape(CropBoxShape shape = CropBoxShape::Square);

protected:
    void paintEvent(QPaintEvent *event);
    void showEvent(QShowEvent *event);

private:


private:
    CropBoxShape m_shape;
    CropBox * m_pCropBox;
    int m_widthCount;
    int m_heightCount;
};

#endif // IMAGESHOWLABEL_H
