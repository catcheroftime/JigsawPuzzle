#ifndef PUZZLEWIDGET_H
#define PUZZLEWIDGET_H

#include <QList>
#include <QPoint>
#include <QPixmap>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
class QMouseEvent;
QT_END_NAMESPACE

class PuzzleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PuzzleWidget(int imageSize, QWidget *parent = 0);
    void clear();

    int pieceSize() const;
    int imageSize() const;

signals:
    void puzzleCompleted();

protected:
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragLeaveEvent(QDragLeaveEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    const QRect targetSquare(const QPoint &position) const;

    QList<QPixmap> piecePixmaps;
    QList<QRect> pieceRects;
    QList<QPoint> pieceLocations;
    QRect highlightedRect;
    int inPlace;
    int m_ImageSize;
};

#endif // PUZZLEWIDGET_H
