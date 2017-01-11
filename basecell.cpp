#include "basecell.h"

baseCell::baseCell(int row, int col, int sq)
{
    wasOG = false;
    this->setRow(row);
    this->setCol(col);
    this->setSquare(sq);
    for (int i=0; i<10; i++)
    {
        solArray[i] = true;
    }
    solArray[0] = false;
    this->value = 0;
    guess = false;
}
baseCell::baseCell()
{
    for (int i=0; i<10; i++)
    {
        solArray[i] = true;
    }
    solArray[0] = false;
    this->value = 0;
}

void baseCell::copy(baseCell cell)
{
    this->setRow(cell.getRow());
    this->setCol(cell.getCol());
    this->setSquare(cell.getSquare());
    this->setValue(cell.getValue());
    for( int i=0; i<10; i++)
    {
        this->modArray(i,cell.readArray(i));
    }
    this->setOG(cell.getOG());
}

int baseCell::getCol()
{
    return col;
}
int baseCell::getRow()
{
    return row;
}
int baseCell::getSquare()
{
    return square;
}

bool baseCell::isPeer(baseCell cell)
{
    if (cell.getRow() == this->getRow() && cell.getCol() == this->getCol() && cell.getSquare() == this->getSquare())
    {
        return false; // same Cell!
    }
    if (cell.getRow() == this->getRow())
    {
        return true;
    }
    if (cell.getCol() == this->getCol())
    {
        return true;
    }
    if (cell.getSquare() == this->getSquare())
    {
        return true;
    }
    return false;

}

bool baseCell::isPeer(baseCell* cell)
{
    if (cell->getRow() == this->getRow() && cell->getCol() == this->getCol() && cell->getSquare() == this->getSquare())
    {
        return false; // same Cell!
    }
    if (cell->getRow() == this->getRow())
    {
        return true;
    }
    if (cell->getCol() == this->getCol())
    {
        return true;
    }
    if (cell->getSquare() == this->getSquare())
    {
        return true;
    }
    return false;

}

int baseCell::modArray (int nIndex)  // changes the cell array at nIndex to false, then sweeps the bool array to see if the cell is solved, in which case its sets the value of that cell to nIndex
{
    solArray[nIndex] = false;
    int nTrueCounter = 0;
    nIndex = 1;
    while (nIndex <=9)
    {   if (solArray [nIndex] == true)
        {   nTrueCounter++;

        }
        nIndex++;
    }

    if (nTrueCounter == 1)
    {   nIndex = 1;
        solArray[0] = true;
        while (nIndex <=9)
        {
            if (solArray [nIndex] == true)
            {
                break;
            }
            nIndex++;
        }
        int nNumber = nIndex;

        setValue(nNumber);

    }
    if (nTrueCounter == 0)
    {
        return -1;
    }
    return 0;
}

int baseCell::modArray (int nIndex, bool TF)  // changes the cell array at nIndex to false, then sweeps the bool array to see if the cell is solved, in which case its sets the value of that cell to nIndex
{
    solArray[nIndex] = TF;
    int nTrueCounter = 0;
    nIndex = 1;
    while (nIndex <=9)
    {   if (solArray [nIndex] == true)
        {   nTrueCounter++;

        }
        nIndex++;
    }

    if (nTrueCounter == 1)
    {   nIndex = 1;
        solArray[0] = true;
        while (nIndex <=9)
        {
            if (solArray [nIndex] == true)
            {
                break;
            }
            nIndex++;
        }
        int nNumber = nIndex;

        setValue(nNumber);

    }
    if (nTrueCounter == 0)
    {
        return -1;
    }
    return 0;
}

int baseCell::getValue()
{
    return value;
}

bool baseCell::readArray(int index)
{
    return solArray[index];
}

void baseCell::setCol(int c)
{
    col = c;
}

void baseCell::setRow(int r)
{
    row = r;
}

void baseCell::setSquare(int sq)
{
    square = sq;
}

bool baseCell::isSolved()
{
    return this->readArray(0);
}

void baseCell::setValue(int i)
{
    value = i;
    guess=false;
}

void baseCell::init(int i)
{
    for (int r = 1; r<10; r++)
    {
        modArray(r,false);
    }
    modArray(i,true);
    modArray(0,true);
    setValue(i);
}

void baseCell::setGuess(int nGuess)
{
    this->init(nGuess);
    modArray(nGuess,true);
    modArray(0,true);
    this->guess = true;
}

bool baseCell::isGuess()
{
    return guess;
}

int baseCell::possibilities()
{
    if (readArray(0) == true)
    {
        return -1;
    }
    int counter = 0;
    for (int i = 1; i<10; i++)
    {
        if (readArray(i) == true)
        {
            counter++;
        }
    }
    return counter;
}

void baseCell::setOG(bool TF)
{
    wasOG = TF;
}

bool baseCell::getOG()
{
    return wasOG;
}
