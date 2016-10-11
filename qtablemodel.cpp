/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qtablemodel.hpp"

QTableModel::QTableModel(QObject *parent)
  : QAbstractTableModel(parent)
{
}

QTableModel::QTableModel(QList<QPair<QString, QString> > pairs, QObject *parent)
  : QAbstractTableModel(parent)
{
  listOfPairs = pairs;
}

int QTableModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return listOfPairs.size();
}

int QTableModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return 2;
}

QVariant QTableModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  if (index.row() >= listOfPairs.size() || index.row() < 0)
    return QVariant();

  if (role == Qt::DisplayRole || role == Qt::EditRole) {
    QPair<QString, QString> pair = listOfPairs.at(index.row());

    if (index.column() == 0)
      return pair.first;
    else if (index.column() == 1)
      return pair.second;
  }
  return QVariant();
}

QVariant QTableModel::headerData(int section, Qt::Orientation orientation,
                                 int role) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  if (orientation == Qt::Horizontal) {
    switch (section) {
      case 0:
        return tr("Name");

      case 1:
        return tr("Address");

      default:
        return QVariant();
    }
  }
  return QVariant();
}

bool QTableModel::insertRows(int position, int rows, const QModelIndex &index)
{
  Q_UNUSED(index);
  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row) {
    QPair<QString, QString> pair(" ", " ");
    listOfPairs.insert(position, pair);
  }

  endInsertRows();
  return true;
}

bool QTableModel::removeRows(int position, int rows, const QModelIndex &index)
{
  Q_UNUSED(index);
  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row) {
    listOfPairs.removeAt(position);
  }

  endRemoveRows();
  return true;
}

bool QTableModel::setData(const QModelIndex &index, const QVariant &value,
                          int role)
{
  if (index.isValid() && role == Qt::EditRole) {
    int row = index.row();

    QPair<QString, QString> p = listOfPairs.value(row);

    if (index.column() == 0)
      p.first = value.toString();
    else if (index.column() == 1)
      p.second = value.toString();
    else
      return false;

    listOfPairs.replace(row, p);
    emit(dataChanged(index, index));

    return true;
  }

  return false;
}

Qt::ItemFlags QTableModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

QList< QPair<QString, QString> > QTableModel::getList()
{
  return listOfPairs;
}
