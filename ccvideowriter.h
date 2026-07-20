/*
 * The Original Code is Copyright 2021, 陈超
 * Contact QQ: 2475164140
 * 陈超音视频数字图像处理开发实战系列课程
 * 《Qt数字图像处理OpenGL渲染引擎开发实战》
 * chenchao_shenzhen@163.com
 * 课程地址: https://ke.qq.com/course/3615377?tuin=938801ec
 */

#ifndef CCVIDEOWRITER_H
#define CCVIDEOWRITER_H

extern "C" {

#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavutil/opt.h>
}

#include <pthread.h>
#include <iostream>
#include "faac.h"

typedef struct MP4_AAC_CONFIGURE
{
    faacEncHandle hEncoder;        //音频文件描述符
    unsigned int nSampleRate;     //音频采样数
    unsigned int nChannels;  	      //音频声道数
    unsigned int nPCMBitSize;        //音频采样精度
    unsigned int nInputSamples;      //每次调用编码时所应接收的原始数据长度
    unsigned int nMaxOutputBytes;    //每次调用编码时生成的AAC数据的最大长度
    unsigned char* pcmBuffer;       //pcm数据
    unsigned char* aacBuffer;       //aac数据

}AACEncodeConfig;

using namespace std;

class CCVideoWriter
{
public:
    CCVideoWriter();
    virtual ~CCVideoWriter();
    static CCVideoWriter* GetInstance();


private:

    AVFormatContext         *avFormatCtx;

    AVCodecContext          *videoCodecCtx;
    AVCodecContext          *audioCodecCtx;

    AVStream                *videoStream;
    AVStream                *audioStream;

    SwsContext              *videoSwCtx;

    AVFrame                 *yuvFrame; //RGB-->YUV-->H.264

    string                  m_filePath;

    bool                    m_bRecording;
    unsigned long           startTimeStamp;

    pthread_mutex_t         videoWriterMutex;

    int m_videoInWidth; int m_videoInHeight;
    int m_videoOutWidth;int m_videoOutHeight;
    int m_videoOutBitrate;

    int m_audioInSamplerate; int m_audioInChannels;
    int m_audioOutSamplerate; int m_audioOutChannels;
    int m_audioOutBitrate;

    long long                   m_lastPts;

    int                         m_audioFramePts = 0;
    int                         m_samples =960;

    int                         m_pcmBufferSize=0;
    int                         m_pcmBufferRemainSize=0;
    int                         m_pcmWriteRemainSize=0;
    AACEncodeConfig*            g_aacEncodeConfig;


public:
    bool StartRecordWithFilePath(const char* file);
    void StopRecordReleaseAllResources();

    bool WriteVideoFrameWithRGBData(const unsigned char* rgb);
    bool WriteAudioFrameWithPCMData(unsigned char* data, int captureSize);

    void SetupInputResolution(int w,int h);
    void SetupOutputResolution(int w,int h);

private:

    bool addVideoStream();
    bool addAudioStream();

    bool writeFrame(AVPacket* packet);

    bool endWriteMp4File();

    void releaseAllRecordResources();
    unsigned long  getTickCount();

    AACEncodeConfig* initAudioEncodeConfiguration();
    void ReleaseAccConfiguration();

    int linearPCM2AAC(unsigned char * pData,int captureSize);

};

#endif // CCVIDEOWRITER_H
