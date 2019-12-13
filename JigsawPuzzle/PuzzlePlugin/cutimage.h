#ifndef CUTIMAGE_H
#define CUTIMAGE_H

#include <QDialog>

namespace Ui {
class CutImage;
}

class CutImage : public QDialog
{
    Q_OBJECT

public:
    explicit CutImage(QWidget *parent = 0);
    ~CutImage();

private:
    Ui::CutImage *ui;
};

#endif // CUTIMAGE_H
