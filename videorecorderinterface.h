/*
 * The Original Code is Copyright 2021, 陈超
 * Contact QQ: 2475164140
 * 陈超音视频数字图像处理开发实战系列课程
 * 《Qt数字图像处理OpenGL渲染引擎开发实战》
 * chenchao_shenzhen@163.com
 * 课程地址: https://ke.qq.com/course/3615377?tuin=938801ec
 */

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
