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
