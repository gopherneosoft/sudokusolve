#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <sudokuwidget.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
friend class SudokuWidget;
public:
    MainWindow(QWidget *parent = 0);

    ~MainWindow();

    QHBoxLayout* hLayout;
    QVBoxLayout* vLayout;
    QPushButton* quitButton;
    QPushButton* calculateButton;
    QPushButton* cancelButton;
    SudokuWidget* sudokuWidget;
    QWidget* centralWidget;
    QProgressBar* pBar;

    QIntValidator* v;
    int createElements();
    int placeElements();

};

#endif // MAINWINDOW_H
