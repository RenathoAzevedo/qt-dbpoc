#include "modelproxy.h"

ModelProxy::ModelProxy(QObject* parent): QIdentityProxyModel(parent)
{

}
ModelProxy::~ModelProxy()
{

}

QVariant ModelProxy::data(const QModelIndex &index, int role) const
{
    if (role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter;
    }
    return QIdentityProxyModel::data(index, role);
}
