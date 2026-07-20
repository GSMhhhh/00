/*
 * The Original Code is Copyright 2021, 陈超
 * Contact QQ: 2475164140
 * 陈超音视频数字图像处理开发实战系列课程
 * 《Qt数字图像处理OpenGL渲染引擎开发实战》
 * chenchao_shenzhen@163.com
 * 课程地址: https://ke.qq.com/course/3615377?tuin=938801ec
 */

#ifndef CCYUVDATADEFINE_H
#define CCYUVDATADEFINE_H

#include <stdint.h>
#include <stdio.h>
;
#pragma pack(push, 1)

typedef struct frameChannelDef
{
    unsigned int    length;
    unsigned char*  dataBuffer;

}CCFrameChannel;

typedef struct  YUVDataDef
{
    unsigned int    width;
    unsigned int    height;
    CCFrameChannel       luma;
    CCFrameChannel       chromaB;
    CCFrameChannel       chromaR;

}CCYUV_Frame;

typedef struct  YUVBuffDef
{
    unsigned int    width;
    unsigned int    height;
    unsigned int    ylength;
    unsigned int    ulength;
    unsigned int    vlength;
    unsigned char*  buffer;

}CCYUV_Buffer;

#pragma pack(pop)

#endif // CCYUVDATADEFINE_H
