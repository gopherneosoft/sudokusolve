#include "mainwindow.h"
#include <QApplication>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{   setWindowIcon(QIcon("logo.icns"));
    sudokuWidget = new SudokuWidget;
    pBar = new QProgressBar(this);
    pBar->setMaximum(10);
    pBar->setMinimum(0);
    pBar->setValue(0);
    vLayout = new QVBoxLayout;
    hLayout = new QHBoxLayout;
    quitButton = new QPushButton ("Quit");
    calculateButton = new QPushButton("Calculate");
    cancelButton = new QPushButton("Cancel");
    hLayout->addWidget(quitButton);
    hLayout->addWidget(calculateButton);
    vLayout->addWidget(sudokuWidget);
    vLayout->addLayout(hLayout);
    vLayout->addWidget(pBar);
    pBar->hide();
    sudokuWidget->setpBar(pBar);
    centralWidget = new QWidget();
    centralWidget->setLayout(vLayout);
    setCentralWidget(centralWidget);

    connect(quitButton,SIGNAL(clicked()),qApp, SLOT(quit()));
    connect(calculateButton, SIGNAL (clicked()), sudokuWidget, SLOT(solveGrid()));
}
MainWindow::~MainWindow()
{

}

