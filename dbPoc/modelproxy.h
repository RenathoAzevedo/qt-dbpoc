#ifndef MODELPROXY_H
#define MODELPROXY_H

#include <QIdentityProxyModel>
class ModelProxy : public QIdentityProxyModel
{

public:
   explicit ModelProxy(QObject* parent = 0);
    ~ModelProxy();
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // MODELPROXY_H
