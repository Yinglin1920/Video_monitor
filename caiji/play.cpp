#include "play.h"
#include "ui_play.h"


Play::Play(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Play)
{
    ui->setupUi(this);

    media = new Phonon::MediaObject;
    vwidget = new Phonon::VideoWidget(ui->VideoWidget);
    vwidget->resize(431,271);

    Phonon::createPath(media,vwidget);

    button_init();

}

Play::~Play()
{
    delete ui;
}

void Play::on_pushButton_play_clicked()
{
    media->play();
}

void Play::on_pushButton_stop_clicked()
{
    media->stop();
}

void Play::on_pushButton_pause_clicked()
{
    media->pause();
}

void Play::on_pushButton_openfile_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,tr("Open Image"),".",tr("Movie(*.avi *.rmvb *.flv);;Music(*.mp3 *.wma)"));
    if(path.length()!=0)
       {
           filePath = path;
           media->setCurrentSource(Phonon::MediaSource(filePath));

           media->play();
    }
}

void Play::button_init()
{
    ui->pushButton_openfile->setStyleSheet( "QPushButton{border-image: url(:/res/openfile_unsel.png); }"
                                        "QPushButton:pressed{border-image:url(:/res/openfile.png);}");
    ui->pushButton_play->setStyleSheet( "QPushButton{border-image: url(:/res/play_unsel.png); }"
                                        "QPushButton:pressed{border-image:url(:/res/play.png);}");
    ui->pushButton_pause->setStyleSheet( "QPushButton{border-image: url(:/res/pause_unsel.png); }"
                                        "QPushButton:pressed{border-image:url(:/res/pause.png);}");
    ui->pushButton_stop->setStyleSheet( "QPushButton{border-image: url(:/res/stop_unsel.png); }"
                                        "QPushButton:pressed{border-image:url(:/res/stop.png);}");
}
