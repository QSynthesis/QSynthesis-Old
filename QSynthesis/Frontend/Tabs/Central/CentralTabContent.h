#ifndef CENTRALTABCONTENT_H
#define CENTRALTABCONTENT_H

#include "MoreWidget.h"

class CentralTabContent : public MoreWidget {
    Q_OBJECT
public:
    explicit CentralTabContent(QWidget *parent = nullptr);
    virtual ~CentralTabContent();
};

#endif // CENTRALTABCONTENT_H
