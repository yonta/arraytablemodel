/****************************************************************************
 * Modified by SAITOU Keita
 * The original source code is here
 *   - https://wiki.qt.io/Combo_Boxes_in_Item_Views
 ****************************************************************************/

#ifndef COMBOBOXITEMDELEGATE_HPP
#define COMBOBOXITEMDELEGATE_HPP

#include <QStyledItemDelegate>

class ComboBoxItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ComboBoxItemDelegate(QObject *parent = 0);
    ~ComboBoxItemDelegate();

    virtual QWidget *createEditor(QWidget *parent,
                                  const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model,
                              const QModelIndex &index) const;
};

#endif // COMBOBOXITEMDELEGATE_HPP
