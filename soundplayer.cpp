#include "soundplayer.h"
#include "settingsmanager.h"

SoundPlayer::SoundPlayer() {}

void SoundPlayer::init() {
    // Starting menu music
    startingMenuMusic = new Sound(SM.settings->value("audio/startingMenu/music").toString(), 0.85, QMediaPlayer::Infinite);
    // Button click sound
    buttonClickSound = new Sound(SM.settings->value("audio/startingMenu/clickSound").toString());
    // Background music
    bgMusic = new Sound(SM.settings->value("audio/bg/music").toString(), 0.125, QMediaPlayer::Loops::Infinite);
    // Victory sound
    victorySound = new Sound(SM.settings->value("audio/victorySound").toString());
    levelWinSound = new Sound(SM.settings->value("audio/levelWinSound").toString());
    // Player sounds
    jumpSound = new Sound(SM.settings->value("audio/jumpSound").toString());
    walkSound = new Sound(SM.settings->value("audio/walkSound").toString(), 1, QMediaPlayer::Infinite);
    dieSound = new Sound(SM.settings->value("audio/dieSound").toString());
    destroySound = new Sound(SM.settings->value("audio/destroySound").toString());
    shieldActiviationSound = new Sound(SM.settings->value("audio/shieldActivationSound").toString());
    coinSound = new Sound(SM.settings->value("audio/coinSound").toString());
    wooHooSound = new Sound(SM.settings->value("audio/wooHooSound").toString());
}

SoundPlayer::~SoundPlayer() {
    delete startingMenuMusic;
    delete bgMusic;
    delete victorySound;
    delete levelWinSound;
    delete jumpSound;
    delete walkSound;
    delete dieSound;
    delete destroySound;
    delete shieldActiviationSound;
    delete coinSound;
    delete wooHooSound;
    delete buttonClickSound;
}

SoundPlayer SP = SoundPlayer();
