#ifndef PLUGININFO_H
#define PLUGININFO_H

#include "Files/BaseDirInfo.h"
#include "Macros.h"

class PluginInfo : public BaseDirInfo {
    Q_CHARSET
public:
    PluginInfo();
    PluginInfo(const QString &dirname);
    virtual ~PluginInfo();

protected:
    PluginInfo(Qs::VariableSource source);

private:
    void init();

protected:
    bool loadCore(bool *valid) override;
    bool saveCore() override;

    void resetCore() override;

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
    bool m_useShell;
    bool m_allNote;

    QString m_charset;
    QString m_name;
    QString m_ustVersion;
    QString m_execute;

    QStringList m_custom; // Other information which can't be edited

private:
    QString infoFilename() const override;
};

#endif // PLUGININFO_H
