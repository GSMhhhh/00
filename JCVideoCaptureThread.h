/*
 * The Original Code is Copyright 2021, 陈超
 * Contact QQ: 2475164140
 * 陈超音视频数字图像处理开发实战系列课程
 * 《Qt数字图像处理OpenGL渲染引擎开发实战》
 * chenchao_shenzhen@163.com
 * 课程地址: https://ke.qq.com/course/3615377?tuin=938801ec
 */

#ifndef JCVIDEOCAPTURETHREAD_H
#define JCVIDEOCAPTURETHREAD_H

#include <QObject>
#include <QThread>

#include <opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <QPoint>
#include "CCYUVDataDefine.h"


class JCVideoCaptureThread : public QThread
{
    Q_OBJECT
public:
    explicit JCVideoCaptureThread(QObject *parent = nullptr);
    virtual ~JCVideoCaptureThread();

    void    StartCaptureVideoWithSize(int width,int height);
    void    StopCaptureVideo();
protected:
    void run();

signals:
    void    OnCapturedYUVUpdate(CCYUV_Frame* yuv);
    void    OnFaceHeadPostionUpdate(QPoint pos,float scale);

private:
    void decodeH264AndUpdateYUVFrame(uint8_t * buff,int len);

private:

    int               m_videoWidth;
    int               m_videoHeight;

    cv::VideoCapture  m_videoCapture;
    bool              m_bCaptureStatus;
    bool              m_bFaceTrackerReady = false;

};

#endif // JCVIDEOCAPTURETHREAD_H
