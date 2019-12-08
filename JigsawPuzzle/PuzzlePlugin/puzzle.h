#ifndef PUZZLE_H
#define PUZZLE_H

#include <QWidget>
#include <QtUiPlugin/QDesignerExportWidget>

class QDESIGNER_WIDGET_EXPORT Puzzle : public QWidget
{
    Q_OBJECT

public:
    Puzzle(QWidget *parent = 0);
};

#endif
