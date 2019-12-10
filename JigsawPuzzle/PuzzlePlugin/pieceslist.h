#ifndef PIECESLIST_H
#define PIECESLIST_H

#include <QListWidget>

class PiecesList : public QListWidget
{
    Q_OBJECT

public:
    explicit PiecesList(int pieceSize, QWidget *parent = 0);
    void addPiece(QPixmap pixmap, QPoint location);

    static QString puzzleMimeType() { return QStringLiteral("image/x-puzzle-piece"); }

protected:
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
    void startDrag(Qt::DropActions supportedActions) Q_DECL_OVERRIDE;

    int m_PieceSize;
};

#endif // PIECESLIST_H
