#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <QDir>
#include <QObject>
#include <QSharedMemory>

#include "QUtils.h"

class MemoryManager : public QObject {
    Q_OBJECT
public:
    explicit MemoryManager(QObject *parent = nullptr);
    ~MemoryManager();

    bool load();

    QString tempDir() const;

private:
    QString m_tempDir;
    QSharedMemory m_shared;
};

#endif // MEMORYMANAGER_H
