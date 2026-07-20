/*
 * The Original Code is Copyright 2021, 陈超
 * Contact QQ: 2475164140
 * 陈超音视频数字图像处理开发实战系列课程
 * 《Qt数字图像处理OpenGL渲染引擎开发实战》
 * chenchao_shenzhen@163.com
 * 课程地址: https://ke.qq.com/course/3615377?tuin=938801ec
 */

#include "videorecorderinterface.h"
#include "ccvideowriter.h"


static bool m_bIsRecording=false;

void AVRecorderAPI_setupInputResolution(int w, int h)
{
    CCVideoWriter::GetInstance()->SetupInputResolution(w,h);
}

void AVRecorderAPI_setupOutputResolution(int w, int h)
{
    CCVideoWriter::GetInstance()->SetupOutputResolution(w,h);
}

void updateDataCallBack(unsigned long userData,int length, char* buffer)
{
    if(!m_bIsRecording){
        return;
    }

    if(length > 128 ){
         //qDebug()<<"xxxxxxx "<<length;
        CCVideoWriter::GetInstance()->WriteAudioFrameWithPCMData((unsigned char*)buffer,length);
    }
    return;

}

void AVRecorderAPI_startRecordVideoWithPath(const char* path,const char* devName)
{
    bool retValue = CCVideoWriter::GetInstance()->StartRecordWithFilePath(path);
    if( !retValue ){
        return ;
    }


    m_bIsRecording=true;

    return;
}

void AVRecorderAPI_stopRecordReleaseAllResources()
{
    m_bIsRecording=false;

    CCVideoWriter::GetInstance()->StopRecordReleaseAllResources();

}

void AVRecorderAPI_writeVideoData(unsigned char* rgbBuffer, int len)
{

    if(m_bIsRecording == false){
        return;
    }
    CCVideoWriter::GetInstance()->WriteVideoFrameWithRGBData((const unsigned char*)rgbBuffer);

    return;
}
