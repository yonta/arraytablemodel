#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "qtablemodel.hpp"
#include "tablemodel.hpp"
#include "comboboxitemdelegate.hpp"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  qtmodel(new QTableModel(this)),
  tmodel(new TableModel(0, 2, this))
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

  ComboBoxItemDelegate *combo1 = new ComboBoxItemDelegate(ui->tableView);
  ui->tableView->setItemDelegateForColumn(0, combo1);

  // TableModel
  tmodel->setHeaderData(0, Qt::Horizontal, tr("Name"), Qt::DisplayRole);
  tmodel->setHeaderData(1, Qt::Horizontal, tr("Address"), Qt::DisplayRole);
  for (int i = 0; i < 3; ++i) {
    tmodel->insertRows(i, 1);
    QModelIndex index0 = tmodel->index(i, 0);
    QModelIndex index1 = tmodel->index(i, 1);
    tmodel->setData(index0, tr("My Name"));
    tmodel->setData(index1, tr("My Address"));
  }
  ui->tableView_2->setModel(tmodel);

  ComboBoxItemDelegate *combo = new ComboBoxItemDelegate(ui->tableView_2);
  ui->tableView_2->setItemDelegateForColumn(0, combo);
}

MainWindow::~MainWindow()
{
  delete ui;
}
