#ifndef PUZZLE_H
#define PUZZLE_H

#include <QPixmap>
#include <QWidget>
#include <QtUiPlugin/QDesignerExportWidget>

class PiecesList;
class PuzzleWidget;

class QDESIGNER_WIDGET_EXPORT Puzzle : public QWidget
{
    Q_OBJECT

public:
    Puzzle(QWidget *parent = 0);

    void loadImage(const QString &fileName);

private slots:
    void setCompleted();

public slots:
    void openImage();
    void setupPuzzle();

private:
    void initView();

private:
    QPixmap puzzleImage;
    PiecesList *piecesList;
    PuzzleWidget *puzzleWidget;
};

#endif
