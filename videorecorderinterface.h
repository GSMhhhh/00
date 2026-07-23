#ifndef VIDEORECORDERINTERFACE_H
#define VIDEORECORDERINTERFACE_H


extern "C"
{

void AVRecorderAPI_setupInputResolution(int w, int h);

void AVRecorderAPI_setupOutputResolution(int w, int h);

void AVRecorderAPI_startRecordVideoWithPath(const char* path,const char* devName);

void AVRecorderAPI_stopRecordReleaseAllResources();

void AVRecorderAPI_writeVideoData(unsigned char* rgbBuffer, int len);


}


#endif // VIDEORECORDERINTERFACE_H
