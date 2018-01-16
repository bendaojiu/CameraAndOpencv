#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QLabel>
#include <QTime>
#include "widget.h"
#include <QDebug>

static QTime startTime;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    doneImageShow = new QLabel();
    doneImageShow->setMinimumSize(250, 400);
    statusBar = new QLabel();
    statusBar->setStyleSheet("border: 2px solid; border-color: black");
    m_layout = new QGridLayout();
    imageLayout = new QHBoxLayout();
    viewfinder = new QCameraViewfinder();
    viewfinder->setMinimumSize(50, 50);
    QCameraInfo cameraInfo = getCamera();
    if (cameraInfo == (QCameraInfo)0)
    {
        // 说明没有获取成功
        this->statusBar->setText("No Camera Found");
    }
    else
    {
        QCamera *camera = new QCamera(cameraInfo);
        camera->setViewfinder(viewfinder);
        imageCapture = new QCameraImageCapture(camera);
        camera->setCaptureMode(QCamera::CaptureStillImage);
        qDebug() << connect(imageCapture, &QCameraImageCapture::imageCaptured, this, &Widget::getImage);
        camera->start();    // 加上start才开始显示。。。。
    }

//    m_layout->addWidget(viewfinder, 0, 0, 1, 1);
//    m_layout->addWidget(doneImageShow, 0, 1, 1, 1);
    imageLayout->addWidget(viewfinder);
    imageLayout->setStretchFactor(viewfinder, 2);
    imageLayout->addWidget(doneImageShow);
    imageLayout->setStretchFactor(doneImageShow, 5);
    m_layout->addLayout(imageLayout, 0, 0, 10, 2);
    m_layout->addWidget(statusBar, 10, 0, 1, 2);
    this->statusBar->setText("已经打开摄像头");
    connect(&timer, &QTimer::timeout, this, &Widget::timerEnd);
    timer.start(16);

    operatImage = new OperateImageInterface();

    connect(this, &Widget::getNewImage, operatImage, &OperateImageInterface::doImageOperate);
    connect(operatImage, &OperateImageInterface::doneImage, this, &Widget::updateImage);
    this->setLayout(m_layout);
    this->resize(600, 500);
}

Widget::~Widget()
{

}

const QCameraInfo Widget::getCamera(int id)
{
    QList<QCameraInfo> cameraList = QCameraInfo::availableCameras();
    if (cameraList.length() == 0)   // 说明没有找到摄像头
    {
        qDebug() << "Camera not found!!!";
        return (QCameraInfo)0;
    }
    return cameraList.at(id);
}

void Widget::getImage(int id, const QImage &preview)
{
    QImage image = preview;
    startTime.restart();
    emit getNewImage(image);
}

void Widget::timerEnd()
{
    this->imageCapture->capture();
}

void Widget::updateImage(QImage image)
{
    QPixmap pixmap = QPixmap::fromImage(image);
    this->doneImageShow->setPixmap(pixmap.scaledToWidth(250));
    qDebug() << startTime.elapsed();
}
