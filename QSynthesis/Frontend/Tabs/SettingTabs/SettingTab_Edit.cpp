#include "../SettingTab.h"

void SettingTab::undo() {
    if (!earliest()) {
        historyIndex--;
        // Do something with historyList.at(historyIndex)
        operationHandler(historyList.at(historyIndex), true);
    }
    setEdited(savedHistoryIndex != historyIndex);
    updateMenuCore();
}

void SettingTab::redo() {
    if (!latest()) {
        // Do something with historyList.at(historyIndex)
        operationHandler(historyList.at(historyIndex), false);
        historyIndex++;
    }
    setEdited(savedHistoryIndex != historyIndex);
    updateMenuCore();
}

bool SettingTab::operationHandler(SettingOperation* op, bool undo)
{
    if (op == nullptr)
        return true;

    QString sType = settingTypeToString(op->type);
    QJsonObject obj = settingObj.value(sType).toObject();
    QJsonValue val = undo ? op->fromVal : op->toVal;

    bool tmpFlag = historyBlock;
    historyBlock = true;
    switch (op->type) {
    // 1 Edit
    case Edit:
        if (op->key == "propertyClear") {
            propertyClear->setChecked(val.toBool());
        }
        else if (op->key == "batchMove") {
            batchMove->setChecked(val.toBool());
        }
        break;

    // 2 Keyboard
    case KeyBoard:
        // 2.1 Wheel
        if (op->key == "HZoom") {
            HZoom->setCurrentText(val.toString());
        }
        else if (op->key == "VZoom") {
            VZoom->setCurrentText(val.toString());
        }
        else if (op->key == "HMove") {
            HMove->setCurrentText(val.toString());
        }
        else if (op->key == "VMove") {
            VMove->setCurrentText(val.toString());
        }

        // 2.2 Drag
        else if (op->key == "pageDrag") {
            pageDrag->setCurrentText(val.toString());
        }
        else if (op->key == "regionSelect") {
            regionSelect->setCurrentText(val.toString());
        }
        else if (op->key == "addPointForward") {
            addPointForward->setCurrentText(val.toString());
        }

        // 2.3 Mode2
        else if (op->key == "mode2_HAttach") {
            mode2_HAttach->setCurrentText(val.toString());
        }
        else if (op->key == "mode2_VAttach") {
            mode2_VAttach->setCurrentText(val.toString());
        }
        else if (op->key == "mode2_CAttach") {
            mode2_CAttach->setCurrentText(val.toString());
        }

        // 2.4 Envelope
        else if (op->key == "envelope_HAttach") {
            envelope_HAttach->setCurrentText(val.toString());
        }
        else if (op->key == "envelope_VAttach") {
            envelope_VAttach->setCurrentText(val.toString());
        }
        else if (op->key == "envelope_CAttach") {
            envelope_CAttach->setCurrentText(val.toString());
        }

        // 2.5 Right Click
        else if (op->key == "defaultMenu") {
            defaultMenu->setCurrentText(val.toString());
        }
        else if (op->key == "pluginMenu") {
            pluginMenu->setCurrentText(val.toString());
        }
        else if (op->key == "sampleMenu") {
            sampleMenu->setCurrentText(val.toString());
        }
        else if (op->key == "toolMenu") {
            toolMenu->setCurrentText(val.toString());
        }
        else if (op->key == "immRender") {
            immRender->setCurrentText(val.toString());
        }

        // 2.6 Drag Backward
        else if (op->key == "moveNoteBackward") {
            moveNoteBackward->setCurrentText(val.toString());
        }
        else if (op->key == "singleCoverBackward") {
            singleCoverBackward->setCurrentText(val.toString());
        }
        else if (op->key == "anyCoverBackward") {
            anyCoverBackward->setCurrentText(val.toString());
        }

        // 2.7 Drag Forward
        else if (op->key == "moveNoteForward") {
            moveNoteForward->setCurrentText(val.toString());
        }
        else if (op->key == "stretchNoteForward") {
            stretchNoteForward->setCurrentText(val.toString());
        }
        else if (op->key == "addRestForward") {
            addRestForward->setCurrentText(val.toString());
        }
        break;

    // 3 Mouse
    case Mouse:
        // 3.1 Mode2-Add
        if (op->key == "mode2_AddPoint") {
            mode2_AddPoint->setCurrentText(val.toString());
        }

        // 3.2 Mode2-Modify
        else if (op->key == "mode2_RemovePoint") {
            mode2_RemovePoint->setCurrentText(val.toString());
        }
        else if (op->key == "mode2_ChangeType") {
            mode2_ChangeType->setCurrentText(val.toString());
        }
        else if (op->key == "mode2_OpenMenu") {
            mode2_OpenMenu->setCurrentText(val.toString());
        }

        // 3.3 Envelope-Add
        else if (op->key == "envelope_AddPoint") {
            envelope_AddPoint->setCurrentText(val.toString());
        }

        // 3.4 Envelope-Modify
        else if (op->key == "envelope_RemovePoint") {
            envelope_RemovePoint->setCurrentText(val.toString());
        }
        else if (op->key == "envelope_Standardize") {
            envelope_Standardize->setCurrentText(val.toString());
        }
        else if (op->key == "envelope_OpenMenu") {
            envelope_OpenMenu->setCurrentText(val.toString());
        }
        break;

    // 4 Render
    case Render:
        if (op->key == "notBase64") {
            notBase64->setChecked(val.toBool());
        }
        else if (op->key == "notCMD") {
            notCMD->setChecked(val.toBool());
        }
        else if (op->key == "threadNum") {
            threadNum->setCurrentText(val.toString());
        }
        break;

    // 5 Cache
    case Cache:
        if (op->key == "noCache") {
            noCache->setChecked(val.toBool());
        }
        else if (op->key == "cacheClear") {
            QString str = val.toString();
            if (str == "noClear") {
                noClear->click();
            }
            else if (str == "clearOnFileClose") {
                clearOnFileClose->click();
            }
            else if (str == "clearOnWindowClose") {
                clearOnWindowClose->click();
            }
            else if (str == "clearWhenFull") {
                clearWhenFull->click();
            }
        }
        else if (op->key == "cacheCapacity") {
            cacheCapacity->setValue(val.toInt());
        }
        break;

    default:
        historyBlock = tmpFlag;
        return false;
    }
    historyBlock = tmpFlag;

    obj.remove(op->key);
    obj.insert(op->key, val);
    settingObj.remove(sType);
    settingObj.insert(sType, QJsonValue(obj));

    return operationHandler(op->next, undo);
}

bool SettingTab::earliest() {
    return historyIndex == 0;
}

bool SettingTab::latest() {
    return historyIndex == historyList.size();
}

void SettingTab::addHistory(SettingOperation *s) {
    // Saved status doesn't exist
    if (savedHistoryIndex > historyIndex) {
        savedHistoryIndex = -1;
    }
    // Remove all operations after
    while (historyList.size() > historyIndex) {
        delete historyList.back();
        historyList.pop_back();
    }
    historyList.append(s);
    historyIndex++;

    setEdited(savedHistoryIndex != historyIndex);
}
