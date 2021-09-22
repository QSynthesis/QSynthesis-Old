#ifndef SHORTCUTSDATA_H
#define SHORTCUTSDATA_H

#include <QKeySequence>
#include <QObject>

#include "Macros.h"
#include "Types.h"

class ShortcutsData {
    Q_SINGLETON(ShortcutsData)

public:
    ShortcutsData();
    virtual ~ShortcutsData();

    QList<QKeySequence> commonShortcuts;
    QList<QKeySequence> projectShortcuts;
    QList<QKeySequence> voiceShortcuts;

private:
    ShortcutsData(Qs::VariableSource source);

    static ShortcutsData *defaultData;

public:
    static void createDefault();
    static ShortcutsData getDefault();
    static void removeDefault();

    static bool checkNoConflict(const ShortcutsData &sd, QPair<int, int> *first = nullptr,
                                QPair<int, int> *second = nullptr);
};

#endif // SHORTCUTSDATA_H
