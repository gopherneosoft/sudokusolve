#include "sudokucell.h"
#include <QtGui>

SudokuCell::SudokuCell() : QLineEdit()
{   v = new QIntValidator(1,9);
    setValidator(v);
    setMaximumWidth(25);
    row=0;
    col=0;
    nSquareNumber = 0;

};

int SudokuCell::getValue() //find the value of the current cell
{   QString str = text();
    int nValue = str.toInt();
    return nValue;
}

void SudokuCell::setValue (int nIndex)
{
    char digits [] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char a;
    a = digits [nIndex];

    QString str;
    str = a;
    setText(str);
    nValue = nIndex;

}

void SudokuCell::setSquareNumber(int nNumber)
{
    nSquareNumber = nNumber;

}

void SudokuCell::setCol(int i)
{
    col = i;
}

void SudokuCell::setRow(int r)
{
    row = r;
}

int SudokuCell::getCol()
{
    return col;
}

int SudokuCell::getRow()
{
    return row;
}
