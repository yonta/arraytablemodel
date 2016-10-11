#-------------------------------------------------
#
# Project created by QtCreator 2016-10-10T23:21:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestGUI
TEMPLATE = app


SOURCES += \
  main.cpp \
  mainwindow.cpp \
  qtablemodel.cpp \
  tablemodel.cpp \
  comboboxitemdelegate.cpp

HEADERS += \
  mainwindow.hpp \
  qtablemodel.hpp \
  tablemodel.hpp \
  comboboxitemdelegate.hpp

FORMS    += mainwindow.ui
