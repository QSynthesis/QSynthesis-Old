#include "ShortcutsData.h"
#include "Actions/TuningActionList.h"
#include "Actions/VoiceActionList.h"

ShortcutsData *ShortcutsData::defaultData = nullptr;

Q_SINGLETON_DECLARE(ShortcutsData)

ShortcutsData::ShortcutsData() {
}

ShortcutsData::~ShortcutsData() {
}

ShortcutsData::ShortcutsData(Qs::VariableSource source) {
    assert(source == Qs::Default);
    commonShortcuts = BaseActionList::commonDefaultShortcuts();
    projectShortcuts = TuningActionList::defaultShortcuts();
    voiceShortcuts = VoiceActionList::defaultShortcuts();
}

void ShortcutsData::createDefault() {
    assert(!defaultData);
    defaultData = new ShortcutsData(Qs::Default);
}

ShortcutsData ShortcutsData::getDefault() {
    return *defaultData;
}

void ShortcutsData::removeDefault() {
    assert(defaultData);
    delete defaultData;
    defaultData = nullptr;
}

bool ShortcutsData::checkNoConflict(const ShortcutsData &sd, QPair<int, int> *first,
                                    QPair<int, int> *second) {
    const QList<QKeySequence> &commonKeys = sd.commonShortcuts;

    QMap<QKeySequence, int> map;
    QMap<QKeySequence, int> map1;

    for (int i = 0; i < commonKeys.size(); ++i) {
        QKeySequence shortcut = commonKeys.at(i);
        auto it = map.find(shortcut);
        if (it != map.end()) {
            if (first) {
                first->first = 0;
                first->second = it.value();
            }
            if (second) {
                second->first = 0;
                second->second = i + 1;
            }
            return false;
        }
        if (!shortcut.toString().isEmpty()) {
            map.insert(shortcut, i + 1);
        }
    }

    const QList<QKeySequence> &projectKeys = sd.projectShortcuts;
    for (int i = 0; i < projectKeys.size(); ++i) {
        QKeySequence shortcut = projectKeys.at(i);
        auto it = map.find(shortcut);
        if (it != map.end()) {
            if (first) {
                first->first = 0;
                first->second = it.value();
            }
            if (second) {
                second->first = 1;
                second->second = i + 1;
            }
            return false;
        }
        auto it1 = map1.find(shortcut);
        if (it1 != map1.end()) {
            if (first) {
                first->first = 1;
                first->second = it1.value();
            }
            if (second) {
                second->first = 1;
                second->second = i + 1;
            }
            return false;
        }
        if (!shortcut.toString().isEmpty()) {
            map1.insert(shortcut, i + 1);
        }
    }
    map1.clear();

    const QList<QKeySequence> &voiceKeys = sd.voiceShortcuts;
    for (int i = 0; i < voiceKeys.size(); ++i) {
        QKeySequence shortcut = voiceKeys.at(i);
        auto it = map.find(shortcut);
        if (it != map.end()) {
            if (first) {
                first->first = 0;
                first->second = it.value();
            }
            if (second) {
                second->first = 2;
                second->second = i + 1;
            }
            return false;
        }
        auto it1 = map1.find(shortcut);
        if (it1 != map1.end()) {
            if (first) {
                first->first = 2;
                first->second = it1.value();
            }
            if (second) {
                second->first = 2;
                second->second = i + 1;
            }
            return false;
        }
        if (!shortcut.toString().isEmpty()) {
            map1.insert(shortcut, i + 1);
        }
    }
    return true;
}
