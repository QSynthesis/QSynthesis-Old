#ifndef PLUGININFO_H
#define PLUGININFO_H

#include "DirectoryManager.h"
#include "File/NormalFile.h"

class PluginInfo : public DirectoryManager {
    Q_OBJECT
    Q_CHARSET
public:
    explicit PluginInfo(QObject *parent = nullptr);
    explicit PluginInfo(const QString &dir, QObject *parent = nullptr);
    virtual ~PluginInfo();

public:
    bool useShell() const;
    QString name() const;
    QString ustVersion() const;
    bool allNote() const;
    bool valid() const;
    QString charset() const;
    QStringList custom() const;

    QString exePath() const;
    void setExePath(const QString &path);

    void setUseShell(bool useShell);
    void setAllNote(bool allNote);
    void setCharset(const QString &charset);
    void setName(const QString &name);
    void setUstVersion(const QString &ustVersion);
    void setCustom(const QStringList &custom);

protected:
    virtual bool loadCore() override;
    virtual bool saveCore() override;

    virtual void resetCore() override;
    virtual void prepareCore() override;

    bool loadPluginTxt();
    bool savePluginTxt();

protected:
    NormalFile pluginTxt;

    bool m_useShell;
    bool m_allNote;

    QString m_charset;
    QString m_name;
    QString m_ustVersion;
    QString m_execute;

    QStringList m_custom; // Other information which can't be edited

private:
    void init();

    void handleChangedCore() override;
    void handlePluginTxtChanged();

signals:
    void pluginTxtChanged();
};

#endif // PLUGININFO_H
