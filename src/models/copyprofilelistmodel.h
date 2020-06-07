#ifndef COPYPROFILELISTMODEL_H
#define COPYPROFILELISTMODEL_H

#include <QAbstractListModel>

#include "copyprofile.h"

class CopyProfileListModel : public QAbstractListModel
{
public:
    explicit CopyProfileListModel(QObject *parent = nullptr);

    virtual QVariant data(const QModelIndex &index, int role = Qt::EditRole) const override;
    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    CopyProfile at(int index);
    void clear();
    void addCopyProfile(CopyProfile copyProfile);

private:
    QVector<CopyProfile> _copyProfiles;
};

#endif // COPYPROFILELISTMODEL_H
