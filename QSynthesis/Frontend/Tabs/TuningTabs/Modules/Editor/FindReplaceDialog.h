#ifndef FINDREPLACEDIALOG_H
#define FINDREPLACEDIALOG_H

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>

#include "Controls/FixedLineEdit.h"
#include "Customs/TransparentContainer.h"
#include "Templates/IconButton.h"
#include "Templates/TextButton.h"

class FindReplaceDialog : public TransparentContainer {
    Q_OBJECT
public:
    explicit FindReplaceDialog(QWidget *parent = nullptr);
    ~FindReplaceDialog();

    bool matchCase() const;
    bool matchWord() const;
    bool preserveCase() const;

    QString findText() const;
    QString replaceText() const;

    int current() const;
    void setCurrent(int current);

    int total() const;
    void setTotal(int total);

    void setFindTextFocus();

private:
    QGridLayout *mainLayout;

    FixedLineEdit *findEdit;
    FixedLineEdit *replaceEdit;

    TextButton *btnCase;
    TextButton *btnWord;
    TextButton *btnReserve;

    QLabel *lbResult;

    IconButton *btnPrev, *btnNext, *btnClose;
    IconButton *btnReplace, *btnReplaceAll;

    int m_current, m_total;

    void updateCaption();

    void handleCaseBtnToggled(bool checked);
    void handleWordBtnToggled(bool checked);
    void handleReserveBtnToggled(bool checked);

    void handlePrevBtnClicked();
    void handleNextBtnClicked();
    void handleReplaceBtnClicked();
    void handleReplaceAllBtnClicked();

    void handleFindTextChanged(const QString &text);

    void handleCloseBtnClicked();

private:
    bool eventFilter(QObject *obj, QEvent *event) override;

signals:
    void findStateChanged();

    void prevRequested();
    void nextRequested();
    void replaceRequested();
    void replaceAllRequested();

    void closeRequested();
};

#endif // FINDREPLACEDIALOG_H
