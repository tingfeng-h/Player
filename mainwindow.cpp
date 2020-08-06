#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Player");

    //创建播放器&播放界面实例
    play=new QMediaPlayer(this);
    playlist=new QMediaPlaylist(this);

    ui->widget->installEventFilter(this);

    //同步播放时间&调节播放时间
    connect(play,&QMediaPlayer::durationChanged,ui->label_3,[this](qint64 dur){
        ui->horizontalSlider_2->setMaximum(dur);
        ui->label_3->setText("/"+(QString::number(dur/60000).length()<2?"0"+QString::number(dur/60000):QString::number(dur/60000))+":"+(QString::number(dur%60000/1000).length()<2?"0"+QString::number(dur%60000/1000):QString::number(dur%60000/1000)));
    });
    connect(play,&QMediaPlayer::positionChanged,ui->label_4,[this](qint64 time){
        ui->horizontalSlider_2->setValue(time);
        ui->label_4->setText((QString::number(time/60000).length()<2?"0"+QString::number(time/60000):QString::number(time/60000))+":"+(QString::number(time%60000/1000).length()<2?"0"+QString::number(time%60000/1000):QString::number(time%60000/1000)));
    });
    connect(ui->horizontalSlider_2,&QAbstractSlider::sliderMoved,[this](int time){
        ui->label_4->setText((QString::number(time/60000).length()<2?"0"+QString::number(time/60000):QString::number(time/60000))+":"+(QString::number(time%60000/1000).length()<2?"0"+QString::number(time%60000/1000):QString::number(time%60000/1000)));
        play->setPosition(time);
    });

    //音量调节
    connect(ui->horizontalSlider,&QAbstractSlider::valueChanged,[this](int value){
        play->setVolume(value);
    });
    ui->horizontalSlider->setValue(50);
    play->setVolume(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    path=QFileDialog::getOpenFileName(this,"打开文件","C:\\Users\\86159\\Desktop");
    //视频加入播放列表
    playlist->clear();
    playlist->addMedia(QUrl::fromLocalFile(path));
    //为播放器设置播放列表
    play->setPlaylist(playlist);
    //设置视频输出的窗口
    play->setVideoOutput(ui->widget);
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
}


void MainWindow::on_pushButton_2_clicked()
{
    static bool flag=true;
    if(flag)
    {
        play->play();
        ui->pushButton_2->setText("暂停");
        flag=false;
    }
    else
    {
        play->pause();
        ui->pushButton_2->setText("播放");
        flag=true;
    }
}

 bool MainWindow::eventFilter(QObject *target, QEvent *event)
 {
     if(target==ui->widget)
     {
         if(event->type()==QEvent::KeyPress)
         {
             QKeyEvent*e=static_cast<QKeyEvent*>(event);
             if(e->key()==Qt::Key_Escape)
             {
                 ui->widget->setFullScreen(false);
                 return true;
             }
         }
         if(event->type()==QEvent::MouseButtonDblClick)
         {
             ui->widget->setFullScreen(true);
         }
     }
     return QMainWindow::eventFilter(target,event);
 }

void MainWindow::on_pushButton_3_clicked()
{
    ui->widget->setFullScreen(true);
}

