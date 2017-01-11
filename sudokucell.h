#ifndef SUDOKUCELL_H
#define SUDOKUCELL_H

#include <QLineEdit>
#include <QIntValidator>
#include <QtGui>
class SudokuCell : public QLineEdit
{   Q_OBJECT
public:
    SudokuCell();
    void setSquareNumber(int);
    QIntValidator* v;
    int getValue();
    void setValue(int);
    void setCol(int);
    void setRow(int);
    int getCol();
    int getRow();

protected:
    int nValue;
    int nSquareNumber;
    int row;
    int col;


};


#endif // SUDOKUCELL_H
