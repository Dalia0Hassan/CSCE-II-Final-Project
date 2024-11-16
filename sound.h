#ifndef SOUND_H
#define SOUND_H
#include <QMediaPlayer>
#include <QAudioOutput>

class Sound : public QMediaPlayer
{
public:
    Sound(QString, float = 1, QMediaPlayer::Loops = Once);
    void play();

    void setVolume(qreal volume) {
        audioOutput->setVolume(volume);
    }

    float volume() {
        return audioOutput->volume();
    }
private:
    QAudioOutput *audioOutput;
};

#endif // SOUND_H
