#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include<QVideoWidget>
#include<QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QMediaPlayer*play;     //播放器
    QMediaPlaylist*playlist;//播放列表
    QString path;            //视频路径

private slots:
    void on_pushButton_clicked();


    void on_pushButton_2_clicked();

    bool eventFilter(QObject *target, QEvent *event); //esc退出全屏&鼠标双击视频全屏

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
