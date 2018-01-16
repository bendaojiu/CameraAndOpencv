/* 此类打算包含opencv头文件，作为处理图像的接口类
 * 要求实现多线程
 */
#ifndef OPERATEIMAGEINTERFACE_H
#define OPERATEIMAGEINTERFACE_H

#include <QObject>
#include <QThread>
#include <QImage>

// 引入opencv头文件
#include <opencv2/core.hpp>

class OperateImageInterface : public QObject
{
    Q_OBJECT
public:
    explicit OperateImageInterface(QObject *parent = nullptr);
    virtual ~OperateImageInterface();

    QImage cvMat2QImage(const cv::Mat &mat);
    cv::Mat QImage2cvMat(QImage image);
    
public slots:
    virtual void doImageOperate(QImage image);
    

private:
    QThread *m_thread;
    
    
signals:
    void doneImage(QImage resImage);
};

#endif // OPERATEIMAGEINTERFACE_H
