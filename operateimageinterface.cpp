#include "operateimageinterface.h"
#include <QDebug>

// 引入opencv头文件
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

OperateImageInterface::OperateImageInterface(QObject *parent) : QObject(parent)
{
    m_thread = new QThread();
    
    this->moveToThread(m_thread);
    m_thread->start();
}

OperateImageInterface::~OperateImageInterface()
{

}

QImage OperateImageInterface::cvMat2QImage(const cv::Mat &mat)
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if (mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate color indexes to qRgb value)
        image.setColorCount(256);
        for (int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for (int row = 0; row < mat.rows; row++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }

        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if (mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if (mat.type() == CV_8UC4)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimesions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        qDebug() << "Unknown cv::Mat type" << mat.type();
        return QImage();
    }
}

cv::Mat OperateImageInterface::QImage2cvMat(QImage image)
{
    cv::Mat mat;
    switch (image.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    default:
        image = image.convertToFormat(QImage::Format_RGB888);
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, CV_BGR2RGB);
    }

    return mat;
}

// 处理image的槽
void OperateImageInterface::doImageOperate(QImage image)
{
//    int width= image.width();
//    int height = image.height();
//    QImage resImage(width, height, QImage::Format_RGB32);
//    for (int i = 0; i < width; i++)
//    {
//        for (int j = 0; j < height; j++)
//        {
//            QColor m_color = image.pixelColor(i, j);
//            if ((m_color.red() + m_color.green() + m_color.blue()) > 1.5)
//                resImage.setPixelColor(i, j, Qt::black);
//            else
//                resImage.setPixelColor(i, j, Qt::white);
//        }
//    }
    cv::Mat mat = QImage2cvMat(image);
    QImage resImage = cvMat2QImage(mat);

    emit doneImage(resImage);
}
