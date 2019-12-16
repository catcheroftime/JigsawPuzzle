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
    explicit CutImage(const QString &filepath, QWidget *parent = 0);
    ~CutImage();

private:
    void initView();

private:
    Ui::CutImage *ui;
    QString m_filepath;
};

#endif // CUTIMAGE_H
