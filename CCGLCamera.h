/*
 * The Original Code is Copyright 2021, 陈超
 * Contact QQ: 2475164140
 * 陈超音视频数字图像处理开发实战系列课程
 * 《Qt数字图像处理OpenGL渲染引擎开发实战》
 * chenchao_shenzhen@163.com
 * 课程地址: https://ke.qq.com/course/3615377?tuin=938801ec
 */

#ifndef GLCAMERA_H
#define GLCAMERA_H

#include <QObject>
#include <QMatrix4x4>
#include <QVector3D>



class CCGLCamera
{

public:
    explicit CCGLCamera();
    virtual ~CCGLCamera();
    QVector3D GetEyePosition(){ return eye;}

public:

    QMatrix4x4   viewMatrix ;
    QMatrix4x4   projectionMatrix;

    QVector3D    eye = QVector3D(0,0,1);
    QVector3D    center = QVector3D(0,0,0);
    QVector3D    up = QVector3D(0,1,0);


};

#endif // GLCAMERA_H
