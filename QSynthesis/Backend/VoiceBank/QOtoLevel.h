#ifndef QOTOLEVEL_H
#define QOTOLEVEL_H

#include "Directory/DirectoryCollect.h"
#include "QOtoIni.h"
#include "QOtoSample.h"

class QOtoLevel : public DirectoryCollect {
    Q_OBJECT
public:
    explicit QOtoLevel(QOtoLevel *parent = nullptr);
    explicit QOtoLevel(const QString &dir, QOtoLevel *parent = nullptr);
    ~QOtoLevel();

    QOtoLevel *root();
    QList<QOtoLevel *> dirs() const;

    void setOtoData(const QOtoSampleList &otoData);
    QOtoSampleList otoData() const;
    QString otoFilename() const;

protected:
    QOtoIni otoIni;

    virtual bool loadCore() override;
    virtual bool saveCore() override;

    virtual void prepareCore() override;
    DirectoryManager *addDirCore(const QString &dir, bool init) override;
    void removeDirCore(DirectoryManager *dir, bool init) override;

private:
    void init();

    // When self changes
    void handleOtoIniChanged();
    void handleChangedCore() override;

    // Root slots
    void handleLevelCreated(QOtoLevel *level, bool init);
    void handleLevelDestroyed(QOtoLevel *level, bool init);

    void handleLevelOtoIniChanged(QOtoLevel *level);
    void handleLevelChanged(QOtoLevel *level);

signals:
    void levelCreated(QOtoLevel *level, bool init);
    void levelDestroyed(QOtoLevel *level, bool init);

    void levelOtoIniChanged(QOtoLevel *level);
    void levelChanged(QOtoLevel *level);
};

#endif // QOTOLEVEL_H
