#-------------------------------------------------
#
# Project created by QtCreator 2017-01-05T21:53:22
#
#-------------------------------------------------

QT       += core gui

            greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

                        TARGET = SudokuSolve
                                 TEMPLATE = app


                                            SOURCES += main.cpp\
                                                    mainwindow.cpp \
                                                    basecell.cpp \
                                                    sudokucell.cpp \
                                                    sudokuwidget.cpp

                                                    HEADERS  += mainwindow.h \
                                                            basecell.h \
                                                            sudokucell.h \
                                                            sudokuwidget.h
