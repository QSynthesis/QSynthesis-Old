#ifndef CENTRALTAB_H
#define CENTRALTAB_H

#include "BaseTab.h"

#include "QUtils.h"

class CentralTab : public BaseTab {
    Q_OBJECT
public:
    // 5 kind of Tab Types
    typedef Qs::MainTabs TabType;

    TabType tabType() const; // Get Tab Type

    explicit CentralTab(TabWidget *parent = nullptr);
    virtual ~CentralTab();

public:
    virtual bool load();
    virtual bool save();
    virtual bool saveAs(const QString &filename);
    virtual bool restore();

    QString filename() const;                       // Get file name Set to the tab
    virtual void setFilename(const QString &value); // Set file name

    QString fixedname() const;
    virtual void setFixedname(const QString &value);

    virtual void awake(); // Window Activate
    virtual void sleep(); // Window Deactivate

    virtual void enter() override; // Tab Switch In
    virtual void leave() override; // Tab Switch Out

    virtual void change();

    bool isEdited() const;              // Get if the file is changed by editor
    virtual void setEdited(bool value); // Set the status of edited

protected:
    TabType m_type;

    QString m_filename;
    QString m_fixedname;

    bool edited;

    virtual void updateMenuRoot();   // Update Menu Bar when switch to this tab
    virtual void updateStatusRoot(); // Update tab status when switch to this tab
    virtual void updateMenuCore();   // Update Menu Bar when do something

    virtual void setTabName(const QString &value) override; // Set the title of tab
    virtual void updateTabName() override;

public:
    // Edit
    virtual void undo();
    virtual void redo();
    virtual void selectAll();
    virtual void deselect();

    // Modify
    virtual void reset();

    // Preview
    virtual void play();
    virtual void replay();
    virtual void stop();
};

class CentralTabContent : public QWidget {
    Q_OBJECT
public:
    explicit CentralTabContent(QWidget *parent = nullptr) : QWidget(parent) {
        setAttribute(Qt::WA_StyledBackground);
    }
    virtual ~CentralTabContent() {
    }
};

#endif // CENTRALTAB_H
