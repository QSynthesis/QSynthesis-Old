#include "mainwindow.h"

void MainWindow::initSettingIni() {
    SettingIniFile reader;
    reader.setFilename(settingIniPath());

    bool aSuccess = reader.load();
    if (!aSuccess) {
        saveSettingIni();
    } else {
        qDebug() << "[I/O]"
                 << "setting.ini found";
        settingIni = reader.data();
    }
}

void MainWindow::saveSettingIni() {
    SettingIniFile reader;
    reader.setFilename(settingIniPath());
    reader.setData(settingIni);

    bool aSuccess = reader.save();
    if (!aSuccess) {
        QMessageBox::warning(nullptr, MainTitle,
                             tr("Unable to write %1!").arg(FILE_NAME_SETTING_INI));
        exitOnNoIOPermission();
    } else {
        qDebug() << "[I/O]"
                 << "setting.ini write";
    }
}

void MainWindow::initShortcutsData() {
    QString filename = keyboardConfigPath();
    ShortcutsFile reader(filename);
    bool valid = false;
    if (!reader.load(&valid) || !valid) {
        if (!reader.save()) {
            exitOnNoIOPermission();
        }
    }
    shortcuts = reader.data();
}

void MainWindow::initConfigData() {
    config = ConfigData();
    QString filename = settingConifgPath();
}

void MainWindow::initVoice() {
    voice = new VoiceCollect(voiceProfile());
    if (!voice->load()) {
        exitOnNoIOPermission();
    }
}

void MainWindow::initPlugins() {
    plugins = new PluginsCollect(pluginsProfile());
    if (!plugins->load()) {
        exitOnNoIOPermission();
    }
}

void MainWindow::initThemes() {
    themes = new NormalFileCollect(themesProfile());
    if (!themes->load()) {
        exitOnNoIOPermission();
    }
}

void MainWindow::initLanguages() {
    languages = new NormalFileCollect(languagesProfile());
    if (!languages->load()) {
        exitOnNoIOPermission();
    }
}
