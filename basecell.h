#ifndef BASECELL_H
#define BASECELL_H


class baseCell
{
public:
    baseCell(int, int, int);
    baseCell();
    bool isPeer(baseCell);
    bool isPeer(baseCell*);
    void copy(baseCell);
    bool isSolved();
    void setRow(int r);
    void setCol(int c);
    void setSquare(int sq);
    int getRow();
    int getCol();
    int getSquare();
    int modArray(int);
    int modArray(int, bool);
    bool readArray(int);
    void setValue(int);
    int getValue();
    bool isGuess();
    void setGuess(int);
    void init(int);
    int possibilities();
    void setOG(bool);
    bool getOG();


protected:
    bool solArray[10];
    int value;
    int square;
    int row;
    int col;
    bool guess;
    bool wasOG;
};

#endif // BASECELL_H
