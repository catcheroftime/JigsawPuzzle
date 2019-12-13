#include "cutimage.h"
#include "ui_cutimage.h"

CutImage::CutImage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CutImage)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::WindowCloseButtonHint | Qt::CustomizeWindowHint);
}

CutImage::~CutImage()
{
    delete ui;
}
