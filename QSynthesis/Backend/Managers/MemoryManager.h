#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <QObject>
#include <QSharedMemory>

#include "QUtils.h"

#define qMemory MemoryManager::instance()

class MemoryManager : public QObject {
    Q_OBJECT
    Q_SINGLETON(MemoryManager)
public:
    explicit MemoryManager(QObject *parent = nullptr);
    ~MemoryManager();

    bool load();

private:
    QString m_tempDir;
    QSharedMemory m_shared;

public:
    static QString tempDir();
};

#endif // MEMORYMANAGER_H
