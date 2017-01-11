#ifndef SUDOKUWIDGET_H
#define SUDOKUWIDGET_H

#include <QLineEdit>
#include <QIntValidator>
#include <QtWidgets>
#include "sudokucell.h"
#include "basecell.h"
#include <QElapsedTimer>

class SudokuWidget : public QWidget
{   Q_OBJECT
public:
    SudokuWidget();
    void checkEnteredNumbers();
    void initializeSquareNumbers();
    void setInitialValues();
    bool isGridSolved(baseCell jGrid[10][10]);
    void sweep();
    void updateDisplay(baseCell [10][10]);
    void search();
    void search(baseCell [10][10], int, int, int);
    bool hasConflict(baseCell[10][10]);
    void finished(QElapsedTimer*);
    void setpBar(QProgressBar*);
    void complete();
    void working();

    QGridLayout* gLayout;


public slots:
    void solveGrid();

protected:
    int squareNumberGrid [10] [10];
    SudokuCell* grid [10][10];
    baseCell  bGrid [10][10];
    QElapsedTimer* timer;
    bool bMarker;
    QPalette* palette;
    QProgressBar* pBar;


};


#endif // SUDOKUCELL_H
