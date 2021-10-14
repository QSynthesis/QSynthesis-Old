#ifndef OTOINFOAREA_H
#define OTOINFOAREA_H

#include <QGridLayout>
#include <QWidget>

#include "../Modules/ImageLabel.h"
#include "../VoiceTabs/ImageTab.h"
#include "../VoiceTabs/PrefixMapTab.h"
#include "../VoiceTabs/TextBoxTab.h"
#include "Containers/TabWidget.h"
#include "Controls/Group/LineControl.h"
#include "VoiceBankArea.h"

class NonOtoOperation;

class OtoInfoArea : public VoiceBankArea {
    Q_OBJECT
public:
    explicit OtoInfoArea(VoiceBankTab *tab,QWidget *parent = nullptr);
    ~OtoInfoArea();

private:
    void init();

public:
    void initExtern();

    void saveOperation(NonOtoOperation *no);                     // Out
    bool handleOperation(NonOtoOperation *no, bool undo = true); // In

    QMap<int, QString> prefixMap() const;
    void setPrefixMap(const QMap<int, QString> &prefixMap);

    QMap<int, QString> suffixMap() const;
    void setSuffixMap(const QMap<int, QString> &suffixMap);

    QString name() const;
    void setName(const QString &name);

    QString author() const;
    void setAuthor(const QString &author);

    QString text() const;
    void setText(const QString &text);

    QString avatar() const;
    QPixmap avatarImage() const;
    bool setAvatar(const QString &path);
    void resetAvatar();

    QString sprite() const;
    QPixmap spriteImage() const;
    bool setSprite(const QString &path);
    void resetSprite();

public:
    void locatePrefix(int noteNum);

private:
    ImageLabel *lbImage;

    LineControl *lcName;
    LineControl *lcAuthor;

    TabWidget *infoTabs;

    TextBoxTab *readmeTab;
    PrefixMapTab *prefixTab;
    ImageTab *imageTab;

    QGridLayout *mainLayout;

    // Data
private:
    QMap<int, QString> m_prefixMap;
    QMap<int, QString> m_suffixMap;

    QString m_name;
    QString m_author;
    QString m_text;

    QString m_avatar;
    QPixmap m_avatarImg;

    QString m_sprite;
    QPixmap m_spriteImg;

    void handleRevealAvatar();
    void handleReplaceAvatar(QString path);
    void handleRemoveAvatar();

    void handleRevealSprite();
    void handleReplaceSprite(QString path);
    void handleRemoveSprite();

    void handleNameChanged();
    void handleAuthorChanged();

    void handlePrefixChanged(int noteNum, QString value);
    void handleSuffixChanged(int noteNum, QString value);
    void handleTextChanged(QString text);

    void handleAvatarChanged(QString modified, QString origin);
    void handleSpriteChanged(QString modified, QString origin);
};

#endif // OTOINFOAREA_H
