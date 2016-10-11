#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "qtablemodel.hpp"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  qtmodel(new QTableModel)
{
  ui->setupUi(this);

  // QTableModel
  for (int i = 0; i < 3; ++i) {
    qtmodel->insertRows(i, 1);
    QModelIndex index0 = qtmodel->index(i, 0);
    QModelIndex index1 = qtmodel->index(i, 1);
    qtmodel->setData(index0, tr("My Name"));
    qtmodel->setData(index1, tr("My Address"));
  }
  ui->tableView->setModel(qtmodel);
}

MainWindow::~MainWindow()
{
  delete ui;
}
