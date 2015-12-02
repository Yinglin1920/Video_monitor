#ifndef PLAY_H
#define PLAY_H

#include <QDialog>
#include <Phonon/AudioOutput>
#include <Phonon/SeekSlider>
#include <Phonon/VideoWidget>
#include <Phonon/MediaObject>

#include <Phonon/VolumeSlider>
#include <Phonon/BackendCapabilities>
#include <QFileDialog>
#include <QStandardItem>

namespace Ui {
class Play;
}

class Play : public QDialog
{
    Q_OBJECT
    
public:
    explicit Play(QWidget *parent = 0);
    ~Play();

    
private slots:
    void on_pushButton_play_clicked();

    void on_pushButton_stop_clicked();

    void on_pushButton_pause_clicked();


    void on_pushButton_openfile_clicked();

private:
    Ui::Play *ui;

    Phonon::MediaObject *media;  //player widget
    Phonon::VideoWidget *vwidget;   //video widget
    Phonon::AudioOutput *aOutput;
    Phonon::VolumeSlider *volumeSlider;
    Phonon::SeekSlider *seekSlider;
    QString filePath;

    QStandardItemModel *standardItemModel;

public:
        void setPath();
         void button_init();

};

#endif // PLAY_H
