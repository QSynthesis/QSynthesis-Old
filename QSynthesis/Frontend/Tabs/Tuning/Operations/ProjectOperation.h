#ifndef PROJECTOPERATION_H
#define PROJECTOPERATION_H

#include "TuneOperation.h"

class ProjectOperation : public TuneOperation {
public:
    ProjectOperation();
    virtual ~ProjectOperation();

    bool differ() const override;

    QString orgWavtool() const;
    void setOrgWavtool(const QString &orgWavtool);

    QString newWavtool() const;
    void setNewWavtool(const QString &newWavtool);

    QString orgOutfile() const;
    void setOrgOutfile(const QString &orgOutfile);

    QString newOutfile() const;
    void setNewOutfile(const QString &newQutfile);

    QString orgCache() const;
    void setOrgCache(const QString &orgCache);

    QString newCache() const;
    void setNewCache(const QString &newCache);

private:
    QString m_orgWavtool, m_newWavtool;
    QString m_orgOutfile, m_newOutfile;
    QString m_orgCache, m_newCache;

};

#endif // PROJECTOPERATION_H
