#include "cutimage.h"
#include "ui_cutimage.h"

#include <QPixmap>

CutImage::CutImage(const QString &filepath, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CutImage)
  , m_filepath(filepath)
{
    ui->setupUi(this);

    initView();


//    QImage* img=new QImage;

//    img->load(filepath);
//    ui->lb_showimage->setPixmap(QPixmap::fromImage(*img));

    ui->lb_showimage->setImage(filepath);
}

CutImage::~CutImage()
{
    delete ui;
}

void CutImage::initView()
{
    this->setWindowTitle(tr("自定义游戏"));
    this->setWindowFlags(Qt::WindowCloseButtonHint | Qt::CustomizeWindowHint);

    ui->rb_square->setChecked(true);
}
