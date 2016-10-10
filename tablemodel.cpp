/****************************************************************************
 * Modified by SAITOU Keita
 * A original and this source code license are below.
 ****************************************************************************/
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

#include <QVector>
#include <QString>
#include "tablemodel.hpp"

TableModel::TableModel(QObject *parent)
  : QAbstractTableModel(parent), body(), header(), row(0)
{
}

TableModel::TableModel(int row, int column, QObject *parent)
  : QAbstractTableModel(parent),
    body(row, QVector<QString>(column)), header(column), row(row)
{
}

TableModel::TableModel(const QVector<QVector<QString> > &b,
                       const QVector<QString> &h, QObject *parent)
  : QAbstractTableModel(parent), body(b), header(h), row(b.size())
{
  const int header_size = header.size();
  bool same_len = true;
  for (int i = 0; i < body.size(); ++i)
    same_len &= body[i].size() == header_size;

  if (!same_len)
    for (int i = 0; i < body.size(); ++i) {
      body[i].resize(header_size);
      body[i].squeeze();
    }
}

int TableModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return row;
}

int TableModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return header.size();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid()) return QVariant();

  if (index.row() < 0 || index.row() >= row ||
      index.column() < 0 || index.column() >= header.size())
    return QVariant();

  if (role == Qt::DisplayRole) return body[index.row()][index.column()];

  return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation,
                                int role) const
{
  if (role != Qt::DisplayRole) return QVariant();

  if (orientation == Qt::Horizontal) {
    if (section < 0 || section >= header.size()) return QVariant();
    else return header[section];
  }

  if (orientation == Qt::Vertical) {
    if (section < 0 || section >= row) return QVariant();
    else return section + 1; // one origin
  }

  return QVariant();
}

bool TableModel::insertRows(int position, int rows, const QModelIndex &index)
{
  Q_UNUSED(index);
  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int r = 0; r < rows; ++r) {
    QVector<QString> empty(header.size(), tr(""));
    body.insert(position, empty);
  }
  row += rows;

  endInsertRows();
  return true;
}

bool TableModel::removeRows(int position, int rows, const QModelIndex &index)
{
  Q_UNUSED(index);
  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  if (position + rows > row) return false;

  body.remove(position, rows);
  row -= rows;

  endRemoveRows();
  return true;
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value,
                         int role)
{
  if (index.isValid() && role == Qt::EditRole) {
    body[index.row()][index.column()] = value.toString();
    emit(dataChanged(index, index));
    return true;
  } else {
    return false;
  }
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
  if (!index.isValid()) return Qt::ItemIsEnabled;
  else return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool TableModel::insert(int position, const QVector<QString> &value)
{
  if (position < 0 || position >= header.size()) return false;

  if (value.size() != header.size()) return false;

  beginInsertRows(QModelIndex(), position, position);
  body.insert(position, value);
  row += 1;
  endInsertRows();
  return true;
}

QVector<QVector<QString> > TableModel::getVector() const
{
  return body;
}
