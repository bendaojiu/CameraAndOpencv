#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QCameraInfo>
#include <QImage>
#include <QTimer>

#include "operateimageinterface.h"

class QLabel;
class QCameraViewfinder;
class QCameraImageCapture;
class QLabel;


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();


private slots:
    // 获得摄像头，默认只有一个
    const QCameraInfo getCamera(int id = 0);
    void getImage(int id, const QImage &preview);
    void timerEnd();
    void updateImage(QImage image);

private:
    QLabel *statusBar; // 状态栏
    QGridLayout *m_layout;  // 布局
    QHBoxLayout *imageLayout;
    QCameraViewfinder *viewfinder;  // 播放视频的窗体
    QCameraImageCapture *imageCapture;  // 抓取image
    QLabel *doneImageShow;  // 显示处理后的图片
    QTimer timer;
    OperateImageInterface *operatImage;


signals:
    void getNewImage(QImage image);
};

#endif // WIDGET_H
