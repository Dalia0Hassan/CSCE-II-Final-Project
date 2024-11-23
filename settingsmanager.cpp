#include "settingsmanager.h"

SettingsManager::SettingsManager() {
    // Create new instance of QSettings if it is not already created
    QSettings::setDefaultFormat(QSettings::IniFormat);
    settings = new QSettings();
    settings->setValue("audio/jump1" , "qrc:/Assets/audio/man_jumps_1.wav");
    settings->setValue("audio/walk1" , "qrc:/Assets/audio/man_walks.wav");
    settings->setValue("audio/bg/music1", "qrc:/Assets/audio/bg_music_1.mp3");
    settings->setValue("audio/volume", .125);
    settings->setValue("window/width", 1024);
    settings->setValue("window/height", 768);
    settings->setValue("player/pos_x", 150);
    settings->setValue("player/pos_y", 200);
    settings->setValue("level1/bg" , ":/Assets/images/bg_8.jpg");
    settings->setValue("spikes/1", ":/Assets/images/Spikes/1.png");
    settings->setValue("spikes/2", ":/Assets/images/Spikes/2.png");
    settings->setValue("blocks/1", ":/Assets/images/Blocks/1.png");
    settings->setValue("blocks/2", ":/Assets/images/Blocks/2.png");
    settings->setValue("blocks/3", ":/Assets/images/Blocks/3.png");
    settings->setValue("blocks/4", ":/Assets/images/Blocks/4.png");
    settings->setValue("blocks/5", ":/Assets/images/Blocks/5.png");
    settings->setValue("blocks/6", ":/Assets/images/Blocks/6.png");
}

SettingsManager::~SettingsManager() {
    // Delete the settings object
    delete settings;
}

SettingsManager SM = SettingsManager();

