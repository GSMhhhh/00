/*
 * The Original Code is Copyright 2021, 陈超
 * Contact QQ: 2475164140
 * 陈超音视频数字图像处理开发实战系列课程
 * 《Qt数字图像处理OpenGL渲染引擎开发实战》
 * chenchao_shenzhen@163.com
 * 课程地址: https://ke.qq.com/course/3615377?tuin=938801ec
 */

#include "CCGLCamera.h"
#include <QDebug>



CCGLCamera::CCGLCamera()
{

    viewMatrix.setToIdentity();
    projectionMatrix.setToIdentity();

    projectionMatrix.ortho(-1,1,-1,1,0.1,1000);
    //projectionMatrix.perspective(25,64/48,0.1,1000);
    viewMatrix.lookAt(eye,center,up);

}
CCGLCamera::~CCGLCamera()
{

}

