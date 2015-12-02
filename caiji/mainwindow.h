#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <opencv/highgui.h>  //包含opencv库头文件
#include<linux/videodev2.h>
#include"play.h"

#include<QDebug>
#include<ssthread.h>



namespace Ui {
class MainWindow;
}

class Dis_thread;
class cthread;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void button_init();
    
private slots:
//    void on_pushButton_clicked();

    void open();
    void save();
    void cut();
    void exit();

    void starvideomonitor();
    void readFrame();

    void SENSOR_ALEART(QString sensorName);

private:
    Ui::MainWindow *ui;

    Play play;

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
//    void LoadFile(const QString &fileName);

    QMenu *fileMenu;
    QToolBar *fileToolBar;

    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *cutAct;
    QAction *exitAct;

    Dis_thread *dis_thread;
    cthread *t;
    ssThread *sensorThread;


    QTimer    *timer;
    QImage    *imag;
    CvCapture *cam_l;// 视频获取结构， 用来作为视频获取函数的一个参数
    IplImage  *frame;//申请IplImage类型指针，就是申请内存空间来存放每一帧图像
    CvVideoWriter *video;
    void cvxCopyQImage(const QImage *qImage, IplImage *pIplImage);
    void Ipl2QImageRGB32(IplImage* iplImage,QImage* qImage);
};

#endif // MAINWINDOW_H
