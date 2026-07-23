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
