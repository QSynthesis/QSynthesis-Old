#ifndef NOTEPROPERTIESDIALOG_H
#define NOTEPROPERTIESDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

#include "../Controls/CustomControls.h"
#include "Backend/Note/QLinkNote.h"
#include "BaseDialog.h"
#include "QUtils.h"

class NotePropertiesDialog : public BaseDialog {
    Q_OBJECT
public:
    explicit NotePropertiesDialog(NoteProperties &np, int count, QWidget *parent = nullptr);
    ~NotePropertiesDialog();

    int exec() override;

private:
    NoteProperties &orgValues;
    int count;

    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;

    QPushButton *btnCancel, *btnOK;

    SlideLineControl *scIntensity, *scModulation;
    LineControl *tcFlags;

    LineControl *tcVelocity, *tcStartPoint;
    LineControl *tcPreUtterance, *tcOverlap;
    LineControl *tcLength;

    const QString ambiguousValue = " ";

    void init();

    void onOKClicked();
    void onCancelClicked();

    void SetCurrentValues();
    void SaveCurrentValues();

    void closeEvent(QCloseEvent *event) override;
};

#endif // NOTEPROPERTIESDIALOG_H
