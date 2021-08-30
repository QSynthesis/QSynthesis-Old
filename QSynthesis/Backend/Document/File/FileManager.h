#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QFileSystemWatcher>
#include <QObject>

class FileManager : public QObject {
    Q_OBJECT
public:
    FileManager(QObject *parent = nullptr);
    virtual ~FileManager();

    bool load(bool *valid = nullptr);
    bool save();

    bool remove();

    void clear();
    void reset();
    bool watched() const;

    QString filename() const;
    void setFilename(const QString &filename);

protected:
    QString m_filename;
    QFileSystemWatcher m_watcher;

    virtual bool loadCore(bool *valid = nullptr);
    virtual bool saveCore();

    virtual void resetCore();
    virtual void prepareCore();

    virtual void handleChangedCore();
    virtual void handleDeletedCore();

private:
    void handleFileChanged(const QString &path);

signals:
    void changed();
};

#endif // FILEMANAGER_H
