#include <QMutableListIterator>

#include "copyprofilelistmodel.h"

CopyProfileListModel::CopyProfileListModel(QObject *parent) : QAbstractListModel(parent)
{
}

QVariant CopyProfileListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= _copyProfiles.size())
    {
        return QVariant();
    }

    switch (role)
    {
    case Qt::DisplayRole:
    case Qt::EditRole:
    case Qt::ToolTipRole:
    case Qt::StatusTipRole:
    case Qt::WhatsThisRole:
    case Qt::AccessibleTextRole:
    case Qt::AccessibleDescriptionRole:
        return _copyProfiles.at(index.row()).name();
        break;
    case CopyProfile::Role::IsActualSizeRole:
        return _copyProfiles.at(index.row()).isActualSize();
        break;
    }

    return QVariant();
}

bool CopyProfileListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);

    beginRemoveRows(QModelIndex(), row, row + count);
    _copyProfiles.remove(row, count);
    endRemoveRows();

    return true;
}

int CopyProfileListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return _copyProfiles.size();
}

CopyProfile CopyProfileListModel::at(int index)
{
    return _copyProfiles.at(index);
}

void CopyProfileListModel::clear()
{
    removeRows(0, _copyProfiles.size());
}

void CopyProfileListModel::addCopyProfile(CopyProfile copyProfile)
{
    if (_copyProfiles.indexOf(copyProfile) < 0)
    {
        beginInsertRows(QModelIndex(), _copyProfiles.size(), _copyProfiles.size());
        _copyProfiles.append(copyProfile);
        endInsertRows();
    }
}
