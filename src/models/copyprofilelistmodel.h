#ifndef COPYPROFILELISTMODEL_H
#define COPYPROFILELISTMODEL_H

#include <QAbstractListModel>

#include "copyprofile.h"

class CopyProfileListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CopyProfileListModel(QObject *parent = nullptr);

    virtual QVariant data(const QModelIndex &index, int role = Qt::EditRole) const override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    void addCopyProfile(CopyProfile *copyProfile);
    void removeCopyProfile(CopyProfile *copyProfile);

private:
    QList<CopyProfile *> _copyProfiles;
};

#endif // COPYPROFILELISTMODEL_H
