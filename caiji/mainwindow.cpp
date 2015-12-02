#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <pthread.h>
//#include"video_capture.h"
#include"cthread.h"
#include<QtGui>
#include"Dis_thread.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/res/camera.ico"));

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    //button_init();

   cam_l     = NULL;
   imag    = new QImage();         // 初始化
   dis_thread = new Dis_thread();
   starvideomonitor();

   sensorThread = new ssThread();
   connect(sensorThread,SIGNAL(SENSOR_ALEART(QString)),this,SLOT(SENSOR_ALEART(QString)));

   sensorThread->start();


}

MainWindow::~MainWindow()
{
    delete ui;
    cvReleaseCapture(&cam_l);
    cvReleaseVideoWriter(&video);
    dis_thread->exit();
    sensorThread->stop();
}

void MainWindow::button_init()
{
//    ui->pushButton_left->setStyleSheet( "QPushButton{border-image: url(:/res/left-arrow_unsel.png); }"
//                                        "QPushButton:pressed{border-image:url(:/res/left-arrow.png);}");
//    ui->pushButton_right->setStyleSheet( "QPushButton{border-image: url(:/res/right-arrow_unsel.png); }"
//                                        "QPushButton:pressed{border-image:url(:/res/right-arrow.png);}");
//    ui->pushButton_up->setStyleSheet( "QPushButton{border-image: url(:/res/up-arrow_unsel.png); }"
//                                        "QPushButton:pressed{border-image:url(:/res/up-arrow.png);}");
//    ui->pushButton_down->setStyleSheet( "QPushButton{border-image: url(:/res/down-arrow_unsel.png); }"
//                                        "QPushButton:pressed{border-image:url(:/res/down-arrow.png);}");
}

void MainWindow::open()
{
    this->hide();
    play.show();
    play.exec();
    this->show();

}

void MainWindow::save()
{
    frame = cvQueryFrame(cam_l);
    video = cvCreateVideoWriter("/home/pi/caiji2/save.avi" , CV_FOURCC('X' , 'V' , 'I' , 'D') ,
                                8 , cvSize(frame->width , frame->height ) );

    if(cvWriteFrame(video,frame))
    {
        QMessageBox::information(this , "information" , "start svae video" , QMessageBox::Yes ,
                             QMessageBox::Yes);
         ui->pushButton_recode->setStyleSheet( "QPushButton{border-image: url(:/res/lightbulb.png);}");
    }

//    t = new cthread();
//    t.create_thread();

}

void MainWindow::cut()
{
     IplImage  *frame_l = cvQueryFrame(cam_l);// 从摄像头中抓取并返回每一帧
    QImage image = QImage((const unsigned char*)frame_l->imageData,
                          frame_l->width, frame_l->height,
                          QImage::Format_RGB888).rgbSwapped();

    QFile file("/home/pi/caiji2/cam.png");
    if(!file.open(QIODevice::ReadWrite))
    {
        QMessageBox::warning(this , "waring" , "open file error" , QMessageBox::Yes ,
                             QMessageBox::Yes);
        return;
    }
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer,"png");
    file.write(ba);
    QMessageBox::information(this , "information" , "save success" , QMessageBox::Yes,
                         QMessageBox::Yes);
}

void MainWindow::exit()
{
    delete ui;
    cvReleaseCapture(&cam_l);
    cvReleaseVideoWriter(&video);
    dis_thread->exit();
    exit();
}

void MainWindow::createActions()
{
    openAct = new QAction( QIcon(":/res/open.png") , tr("&Open") , this);
    openAct->setStatusTip(tr("open video"));
    connect(openAct , SIGNAL(triggered()) , this , SLOT( open() ) );

    saveAct = new QAction( QIcon(":/res/save.png") , tr("&Save") , this);
    saveAct->setStatusTip(tr("save video"));
    connect(saveAct , SIGNAL(triggered()) , this , SLOT( save() ) );

    cutAct = new QAction( QIcon(":/res/cut.png") , tr("&Cut") , this);
    cutAct->setStatusTip(tr("cut a frame"));
    connect(cutAct , SIGNAL(triggered()) , this , SLOT( cut() ) );

    exitAct = new QAction( QIcon(":/res/exit.png") , tr("&Exit") , this);
    exitAct->setStatusTip(tr("exit programe"));
    connect(exitAct , SIGNAL(triggered()) , this , SLOT( exit() ) );

}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(cutAct);
    fileMenu->addAction(exitAct);

    menuBar()->addSeparator();
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addAction(cutAct);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::readFrame()
{
    frame = cvQueryFrame(cam_l);// 从摄像头中抓取并返回每一帧

    // 将抓取到的帧，转换为QImage格式。QImage::Format_RGB888不同的摄像头用不同的格式。
    QImage image = QImage((const unsigned char*)frame->imageData, frame->width, frame->height, QImage::Format_RGB888).rgbSwapped();

    ui->label->setPixmap(QPixmap::fromImage(image));  // 将图片显示到label上
    ui->label_time->setText(QTime::currentTime().toString("hh:mm:ss.zzz"));
}

void MainWindow::starvideomonitor()
{
    cam_l = cvCreateCameraCapture(0);//打开摄像头，从摄像头中获取视频
    connect(dis_thread , SIGNAL(dispaly()) , this , SLOT(readFrame()) );
    dis_thread->start();

}

void MainWindow::SENSOR_ALEART(QString sensorName)
{
    if(sensorName=="FLAME")
    {
        qDebug()<<"FLAME";
        ui->pushButton_flame->setStyleSheet( "QPushButton{border-image: url(:/res/flame.png);}");
    }
    if(sensorName=="SHAKE")      
    {
        qDebug()<<"SHAKE";
        ui->pushButton_shake->setStyleSheet( "QPushButton{border-image: url(:/res/shake.png);}");
    }
    if(sensorName=="SMOKE")
    {
        qDebug()<<"SMOKE";
        ui->pushButton_smoke->setStyleSheet( "QPushButton{border-image: url(:/res/smoke.png);}");
    }
   }

