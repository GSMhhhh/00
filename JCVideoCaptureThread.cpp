#include "JCVideoCaptureThread.h"
#include <QDebug>
#include <QApplication>
#include "Facelandmark.h"


JCVideoCaptureThread::JCVideoCaptureThread(QObject *parent) : QThread(parent)
{
    m_bCaptureStatus = false;

}

JCVideoCaptureThread::~JCVideoCaptureThread()
{
}

void JCVideoCaptureThread::StartCaptureVideoWithSize(int width,int height)
{

    m_videoWidth= width;
    m_videoHeight = height;

    m_videoCapture.open(0);
    if (!m_videoCapture.isOpened())
    {
          qDebug()<<"Error,can't open camera device."<<Qt::endl;
    }

    m_bCaptureStatus = true;

    // 先启动线程，保证摄像头采集不依赖人脸检测
    start();

    // 修复：中文路径需要用 toLocal8Bit()，否则 C 库 fopen 无法识别 UTF-8 路径
    QString filePath = QApplication::applicationDirPath() + "/Resources";
    m_bFaceTrackerReady = FACETRACKER_API_init_facetracker_resources(filePath.toLocal8Bit().data());
    if(!m_bFaceTrackerReady){
        qDebug()<<"init facetracker failed, camera will work without face detection.";
        // 不要 return，线程已经启动，摄像头继续工作
    }

}
void JCVideoCaptureThread::StopCaptureVideo()
{
    m_bCaptureStatus = false;

}

void JCVideoCaptureThread::run()
{
    while(m_bCaptureStatus)
    {
        cv::Mat videoFrame;

        m_videoCapture>>videoFrame;

        if (!videoFrame.empty())
        {
            cv::resize(videoFrame,videoFrame,cv::Size(640,480));
            if(m_bFaceTrackerReady){
                FACETRACKER_API_facetracker_obj_track(videoFrame);
                ofVec2f posVec2f=FACETRACKER_API_getPosition(videoFrame);
                float currentScale = FACETRACKER_API_getScale(videoFrame);

                if(posVec2f.x != -1 && posVec2f.y != -1){
                    QPoint facePoint = QPoint(posVec2f.x,posVec2f.y);
                    emit OnFaceHeadPostionUpdate(facePoint,currentScale);
                }
            }


            cv::Mat bgrCVFrame(videoFrame);
            cv::Mat yuvCVFrame;

            if(1 == videoFrame.channels()){
                cv::cvtColor(videoFrame, bgrCVFrame, CV_GRAY2BGR);
            }
            cv::cvtColor(bgrCVFrame, yuvCVFrame, CV_BGR2YUV_I420);

            int lumaSize = m_videoWidth* m_videoHeight;
            int uv_stride = (m_videoWidth+1) / 2;
            int chromaSize = uv_stride *((m_videoHeight +1) / 2);

            uint8_t *Y_data_Dst = yuvCVFrame.data;
            uint8_t *U_data_Dst = yuvCVFrame.data + lumaSize;
            uint8_t *V_data_Dst = yuvCVFrame.data + lumaSize + chromaSize;

            CCYUV_Frame  yuvFrame;
            memset(&yuvFrame,0,sizeof(yuvFrame));

            yuvFrame.luma.dataBuffer = Y_data_Dst;
            yuvFrame.chromaB.dataBuffer = U_data_Dst;
            yuvFrame.chromaR.dataBuffer = V_data_Dst;

            yuvFrame.luma.length = lumaSize;
            yuvFrame.chromaB.length = chromaSize;
            yuvFrame.chromaR.length = chromaSize;

            yuvFrame.width =   m_videoWidth;
            yuvFrame.height =  m_videoHeight;

            emit OnCapturedYUVUpdate(&yuvFrame);

        }


    }
}




