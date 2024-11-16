#include "sound.h"

Sound::Sound(QString sourcePath, float volume, QMediaPlayer::Loops loops) {
    // Create a new audio output object
    audioOutput = new QAudioOutput();
    audioOutput->setVolume(volume);
    setAudioOutput(audioOutput);

    // Source of the sound
    setSource(QUrl(sourcePath));

    // Set the number of loops
    setLoops(loops);
}

void Sound::play()
{
    QMediaPlayer::stop();
    QMediaPlayer::play();
}
