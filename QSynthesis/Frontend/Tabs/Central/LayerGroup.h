#ifndef LAYERGROUP_H
#define LAYERGROUP_H

#include <QObject>

class LayerGroup : public QObject {
    Q_OBJECT
public:
    explicit LayerGroup(QObject *parent = nullptr);
    ~LayerGroup();

signals:
};

#endif // LAYERGROUP_H
