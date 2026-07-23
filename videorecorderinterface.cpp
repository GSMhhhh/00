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
