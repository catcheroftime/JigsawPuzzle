#include "puzzle.h"
#include "pieceslist.h"
#include "puzzlewidget.h"

#include <QtWidgets>
#include <stdlib.h>

Puzzle::Puzzle(QWidget *parent) :
    QWidget(parent)
{
    initView();
}

void Puzzle::loadImage(const QString &fileName)
{
    QPixmap newImage;
    if (!newImage.load(fileName)) {
        QMessageBox::warning(this, tr("Open Image"),
                             tr("The image file could not be loaded."),
                             QMessageBox::Close);
        return;
    }
    puzzleImage = newImage;
    setupPuzzle();
}

void Puzzle::setCompleted()
{
    QMessageBox::information(this, tr("Puzzle Completed"),
                             tr("Congratulations! You have completed the puzzle!\n"
                                "Click OK to start again."),
                             QMessageBox::Ok);

    setupPuzzle();
}

void Puzzle::openImage()
{
    const QString fileName =
        QFileDialog::getOpenFileName(this, tr("Open Image"), QString(),
                                     tr("Image Files (*.png *.jpg *.bmp)"));

    if (!fileName.isEmpty())
        loadImage(fileName);
}

void Puzzle::setupPuzzle()
{
    int size = qMin(puzzleImage.width(), puzzleImage.height());
    puzzleImage = puzzleImage.copy((puzzleImage.width() - size)/2,
        (puzzleImage.height() - size)/2, size, size).scaled(puzzleWidget->width(),
            puzzleWidget->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    piecesList->clear();

    for (int y = 0; y < 5; ++y) {
        for (int x = 0; x < 5; ++x) {
            int pieceSize = puzzleWidget->pieceSize();
            QPixmap pieceImage = puzzleImage.copy(x * pieceSize, y * pieceSize, pieceSize, pieceSize);
            piecesList->addPiece(pieceImage, QPoint(x, y));
        }
    }

    qsrand(QCursor::pos().x() ^ QCursor::pos().y());

    for (int i = 0; i < piecesList->count(); ++i) {
        if (int(2.0*qrand()/(RAND_MAX+1.0)) == 1) {
            QListWidgetItem *item = piecesList->takeItem(i);
            piecesList->insertItem(0, item);
        }
    }

    puzzleWidget->clear();
}

void Puzzle::initView()
{
    QHBoxLayout *widgetLayout = new QHBoxLayout(this);
    puzzleWidget = new PuzzleWidget(400);

    piecesList = new PiecesList(puzzleWidget->pieceSize(), this);


    connect(puzzleWidget, &PuzzleWidget::puzzleCompleted,
            this, &Puzzle::setCompleted, Qt::QueuedConnection);

    widgetLayout->addWidget(piecesList);
    widgetLayout->addWidget(puzzleWidget);
    widgetLayout->setStretch(0,1);
    widgetLayout->setStretch(1,2);
    this->setLayout(widgetLayout);
}
