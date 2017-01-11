#include "sudokuwidget.h"
#include <QtWidgets>
#include <basecell.h>
#include <QtGui>

SudokuWidget::SudokuWidget() : QWidget()
{
    bMarker = false;
    palette = new QPalette();
    QColor color1 (244,104,66);
    palette->setColor(QPalette::Text, color1);

    int nRow = 1;     // creates empty grid
    while (nRow <=9)
    {
        int nColumn = 1;
        while (nColumn <= 9)
        {
            grid [nRow][nColumn] = new SudokuCell();
            QFont font("Helvetica",15,QFont::Bold);
            grid[nRow][nColumn]->setFont(font);
            bGrid[nRow][nColumn].setCol(nColumn);
            bGrid[nRow][nColumn].setRow(nRow); // row and col, square nums init later.
            nColumn++;
        }
        nRow++;
    }
    timer = new QElapsedTimer();


    gLayout = new QGridLayout();
    nRow = 1;
    int nArrayRow = 1;   //space cells in grid correctly, to display correctly with a space after 3 cells in row and 3 cells in column
    while (nRow <=11)
    {   if (nRow == 4)
        {
            nRow++;
        }
        if (nRow == 8)
        {
            nRow++;
        }
        int nColumn = 1;
        int nArrayColumn = 1;
        while (nColumn <= 11)
        {   if (nColumn == 4)
            {
                nColumn++;
            }
            if (nColumn == 8)
            {
                nColumn++;
            }

            gLayout->addWidget (grid [nArrayRow] [nArrayColumn], nRow, nColumn);
            nColumn++;
            nArrayColumn++;
        }
        nRow++;
        nArrayRow++;
    }
    gLayout->setColumnMinimumWidth (4,25);
    gLayout->setColumnMinimumWidth (8,25);
    gLayout->setRowMinimumHeight (4,25);
    gLayout->setRowMinimumHeight (8,25);
    setLayout(gLayout);
    initializeSquareNumbers();
    setInitialValues();
}


void SudokuWidget::checkEnteredNumbers()
{
    for (int i=1; i<10; i++)
    {
        for (int l=1; l<10; l++)
        {
            if (grid[i][l]->getValue() != 0)
            {
                bGrid[i][l].init(grid[i][l]->getValue());

            }
            else
            {
                grid[i][l]->setPalette(*palette);
            }

        }
    }
}

void SudokuWidget::solveGrid()
{
    checkEnteredNumbers();
    if (isGridSolved(bGrid))
    {
        QMessageBox::information(this,"Complete!","Calculation already complete!");
        return;
    }
    timer->start();
    working();

    sweep();

    //sweep 15 times to try clearing the grid.
    if (isGridSolved(bGrid) == false)
    {
        int row = 0;
        int col = 0;
        int min = 9;
        for(int i=1; i<10; i++)
        {
            for(int l=1; l<10; l++)
            {
                if(bGrid[i][l].possibilities() < min && bGrid[i][l].possibilities() > 1 && bGrid[i][l].readArray(0) == false)
                {
                    min = bGrid[i][l].possibilities(); //find the cell with the least possibilities.
                    row = i;
                    col = l;
                }
                if(bGrid[i][l].possibilities() == 0)
                {
                    return; // if a cell has 0 possibilities, we messed up. return and increment.
                }
            }
        }

        for (int j=1; j<10; j++)
        {
            if(bGrid[row][col].readArray(j) == true) // if this value is possible... take a guess.
            {
                baseCell fGrid[10][10];
                for( int i=1; i<10; i++)
                {
                    for (int j=1; j<10; j++)
                    {
                        fGrid[i][j].copy(bGrid[i][j]);
                    }
                }
                search(fGrid, row, col, j);
                if (bMarker == true)
                {
                    complete();
                    return;
                }
                else
                {
                    fGrid[row][col].modArray(j);
                }
            }
        }
        return;
    }

    else
    {
      complete();
      return;
    }
    return;
}

void SudokuWidget::sweep() //sweeps the grid bGrid of the widget.
{
    baseCell* currentCell;
    baseCell* compareCell;
    for (int row = 1; row<10; row++)
    {
        for (int col =1; col<10; col++) //for each cell...
        {
            currentCell = &bGrid[row][col]; //currentCell is the cell we're modding.
            for (int r2 =1; r2<10; r2++)
            {
                for( int c2=1; c2<10; c2++) //sweep through all cells.
                {
                    compareCell = &bGrid[r2][c2];
                    if (compareCell->isPeer(currentCell) && currentCell->getValue() != 0 && compareCell->getValue()==0) //if the cells are peers...
                    {
                        int returned = compareCell->modArray(currentCell->getValue());
                        if (returned == 1)
                        {
                            QString err = "Cell ";
                            QString err3= " was impossible to solve.";
                            QString err4 = " x ";
                            err.append(QString::number(row));
                            err.append(err4);
                            err.append(QString::number(col));
                            err.append(err3);
                            QMessageBox::information(this,"Impossible Cell!", err);
                        }
                    }
                }
            }

        }
    }
    if(isGridSolved(bGrid))
    {
        if (bMarker == false)
        {
            bMarker = true;
            complete();
            return;
        }
        return;
    }
}

void SudokuWidget::initializeSquareNumbers()
{
    int nRow = 1;
    while (nRow <=3)
    {
        int nColumn = 1;
        while (nColumn <= 3)
        {
            squareNumberGrid [nRow][nColumn] = 1;
            nColumn++;
        }

        while (nColumn <= 6)
        {
            squareNumberGrid [nRow][nColumn] = 2;
            nColumn++;
        }

        while (nColumn <= 9)
        {
            squareNumberGrid [nRow][nColumn] = 3;
            nColumn++;
        }
        nRow++;
    }

    while (nRow <=6)
    {
        int nColumn = 1;
        while (nColumn <= 3)
        {
            squareNumberGrid [nRow][nColumn] = 4;
            nColumn++;
        }

        while (nColumn <= 6)
        {
            squareNumberGrid [nRow][nColumn] = 5;
            nColumn++;
        }

        while (nColumn <= 9)
        {
            squareNumberGrid [nRow][nColumn] = 6;
            nColumn++;
        }
        nRow++;
    }

    while (nRow <=9)
    {
        int nColumn = 1;
        while (nColumn <= 3)
        {
            squareNumberGrid [nRow][nColumn] = 7;
            nColumn++;
        }

        while (nColumn <= 6)
        {
            squareNumberGrid [nRow][nColumn] = 8;
            nColumn++;
        }

        while (nColumn <= 9)
        {
            squareNumberGrid [nRow][nColumn] = 9;
            nColumn++;
        }
        nRow++;
    }

    nRow = 1;
    while (nRow <=9)
    {
        int nColumn = 1;
        while (nColumn <= 9)
        {
            grid[nRow][nColumn]->setSquareNumber(squareNumberGrid[nRow][nColumn]);
            grid[nRow][nColumn]->setCol(nColumn);
            grid[nRow][nColumn]->setRow(nRow);
            bGrid[nRow][nColumn].setSquare(squareNumberGrid[nRow][nColumn]);
            nColumn++;
        }
        nRow++;
    }


}

void SudokuWidget::setInitialValues()
{   //int NumbersArray [81] = { 9, 0,5,4,2,0,0,0,0,2,0,1,0,8,0,9,5,4,0,0,8,9,0,1,3,0,2,5,9,0,0,4,0,7,0,3,0,4,0,6,0,2,1,8,0,0,1,6,7,0,5,0,2,0,1,2,9,0,0,4,0,3,0,0,8,0,5,1,0,0,9,6,6,0,0,0,7,9,8,0,1};
    int NumbersArray [81] = { 4,0,0,0,0,0,8,0,5,0,3,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,2,0,0,0,0,0,6,0,0,0,0,0,8,0,4,0,0,0,0,0,0,1,0,0,0,0,0,0,0,6,0,3,0,7,0,5,0,0,2,0,0,0,0,0,1,0,4,0,0,0,0,0,0};
    //int NumbersArray [81] = { 8,5,0,0,0,2,4,0,0,7,2,0,0,0,0,0,0,9,0,0,4,0,0,0,0,0,0,0,0,0,1,0,7,0,0,2,3,0,5,0,0,0,9,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,8,0,0,7,0,0,1,7,0,0,0,0,0,0,0,0,0,0,3,6,0,4,0};
    int nArrayIndex = 0;
    int nRow = 1;
    while (nRow <=9)
    {
        int nColumn = 1;
        while (nColumn <= 9)
        {   if ( NumbersArray [nArrayIndex] != 0)
            {

                grid [nRow][nColumn]->setValue(NumbersArray[nArrayIndex]);

            }
            nColumn++;
            nArrayIndex++;
        }
        nRow++;
        if (nArrayIndex == 82)
        {
            break;
        }
    }
}

bool SudokuWidget::isGridSolved(baseCell jGrid [10][10])
{
    for (int nRow =1; nRow <10; nRow++)
    {
        for (int nColumn=1; nColumn < 10; nColumn++)
        {
            //for each cell, sweep through all cells. if any cells had the same value as its peer,
            // puzzle is not solved.

            for(int i=1; i<10; i++)
            {
                for(int j=1; j<10; j++)
                {
                    //if the values are equal and not 0 and cells are peers...
                    if(jGrid[nRow][nColumn].getValue() == jGrid[i][j].getValue() && jGrid[nRow][nColumn].isPeer(jGrid[i][j]))
                    {
                        if (jGrid[i][j].getValue() != 0)
                        {
                            return false;
                        }
                    }
                }
            }
        }
    }

    for (int l=1; l<10; l++)
    {
        for(int k=1; k<10; k++)
        {
            if(jGrid[l][k].getValue() == 0)
            {
                return false;
            }
        }
    }
    this->bMarker = true;
    return true;
}

void SudokuWidget::updateDisplay(baseCell kGrid[10][10])
{
    for (int i=1; i<10; i++)
    {
        for(int r=1; r<10; r++)
        {
            grid[i][r]->setValue(kGrid[i][r].getValue());
// sync the numbers for that cell.
        }
    }
    QCoreApplication::processEvents();
}

void SudokuWidget::search(baseCell dGrid[10][10], int gRow, int gCol, int guess)
{   baseCell eGrid[10][10]; // make a copy of the object we're going to use.
    for( int i=1; i<10; i++)
    {
        for (int j=1; j<10; j++)
        {
            eGrid[i][j].copy(dGrid[i][j]);
        }
    }
    eGrid[gRow][gCol].setGuess(guess);
    //guess as per function call.

    baseCell* currentCell; //sweep cells.
    baseCell* compareCell;

    //sweep here
    for (int row = 1; row<10; row++)
    {
        for (int col =1; col<10; col++) //for each cell...
        {
            currentCell = &eGrid[row][col]; //currentCell is the cell we're modding.
            for (int r2 =1; r2<10; r2++)
            {
                for( int c2=1; c2<10; c2++) //sweep through all cells.
                {
                    compareCell = &eGrid[r2][c2];
                    if (compareCell->isPeer(currentCell) && currentCell->getValue() != 0 && compareCell->getValue()==0) //if the cells are peers...
                    {
                        int returned = compareCell->modArray(currentCell->getValue());
                        if (returned == 1)
                        {
                            QString err = "Cell ";
                            QString err3= " was impossible to solve.";
                            QString err4 = " x ";
                            err.append(QString::number(row));
                            err.append(err4);
                            err.append(QString::number(col));
                            err.append(err3);
                            QMessageBox::information(this,"Impossible Cell!", err);
                        }
                    }
                }
            }

        }
    }
    //when done with sweep, update grid...
    if (timer->elapsed() % 100 == 0)
    {
    updateDisplay(eGrid);
    }

    if(isGridSolved(eGrid))
    {
        updateDisplay(eGrid);
        return;
    }

    if(bMarker == true)
    {
        return;
    }

    int row = 0;
    int col = 0;
    int min = 9;
    for(int i=1; i<10; i++)
    {
        for(int l=1; l<10; l++)
        {
            if(eGrid[i][l].possibilities() < min && eGrid[i][l].possibilities() > 1 && eGrid[i][l].getValue() == 0)
            {
                min = eGrid[i][l].possibilities(); //find the unsolved cell with the least possibilities.
                row = i;
                col = l;
            }
        }
    }
    if (min == 9)
    {
        return;
    }
    for (int j=1; j<10; j++)
    {
        if(eGrid[row][col].readArray(j) == true) // if this value is possible... take a guess.
        {
            search(eGrid, row, col, j);

            if (bMarker == true)
            {
                return;
            }
            else
            {
                eGrid[row][col].modArray(j);
                if (eGrid[row][col].possibilities() == 0) //if we eliminated the last poss-
                    //ible num, return.
                {
                    return;
                }
            }
        }
    }
//if we get to the end, none of our values work. return and move up a level
    // to try again.
    return;
}

bool SudokuWidget::hasConflict(baseCell hGrid[10][10])
{
    for (int nRow =1; nRow <10; nRow++)
    {
        for (int nColumn=1; nColumn < 10; nColumn++)
        {
            //for each cell, sweep through all cells. if any cells had the same value as its peer,
            // puzzle is not solved.
            if (hGrid[nRow][nColumn].possibilities() == 0)
            {
                return true;
            }
            for(int i=1; i<10; i++)
            {
                for(int j=1; j<10; j++)
                {
                    //if the values are equal and cells are peers...
                    if(hGrid[nRow][nColumn].getValue() == hGrid[i][j].getValue() && hGrid[nRow][nColumn].isPeer(hGrid[i][j]))
                    {
                        if (hGrid[nRow][nColumn].getValue() != 0)
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

void SudokuWidget::setpBar(QProgressBar* bar)
{
    pBar = bar;
}

void SudokuWidget::complete()
{
    pBar->setMinimum(1);
    pBar->setMaximum(2);
    pBar->setValue(2);
    QCoreApplication::processEvents();
    double time = (double)timer->elapsed()/1000;
    QString str2 = QString::number(time);
    QString str1 = "Finished in ";
    QString str3 = " seconds.";
    str1.append(str2);
    str1.append(str3);
    QMessageBox::information(this,"Calculation Complete!",str1);
    pBar->hide();
}

void SudokuWidget::working()
{
pBar->setMinimum(0);
pBar->setMaximum(0);
pBar->setValue(0);
pBar->show();
QCoreApplication::processEvents();

}
