#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include "sound.h"
class SoundPlayer
{
public:
    Sound *startingMenuMusic = nullptr, *bgMusic = nullptr, *victorySound = nullptr, *buttonClickSound = nullptr;
    Sound *jumpSound = nullptr, *walkSound = nullptr, *dieSound = nullptr, *destroySound = nullptr,
        *shieldActiviationSound = nullptr, *wooHooSound = nullptr, *coinSound = nullptr;
    Sound *levelWinSound = nullptr;

public:
    SoundPlayer();
    void init();
    ~SoundPlayer();
};

extern SoundPlayer SP;

#endif // SOUNDPLAYER_H
