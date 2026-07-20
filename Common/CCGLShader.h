/*
 * The Original Code is Copyright 2021, 陈超
 * Contact QQ: 2475164140
 * 陈超音视频数字图像处理开发实战系列课程
 * 《Qt数字图像处理OpenGL渲染引擎开发实战》
 * chenchao_shenzhen@163.com
 * 课程地址: https://ke.qq.com/course/3615377?tuin=938801ec
 */

#ifndef CCGLSHADER_H
#define CCGLSHADER_H



#include "Common/CCGlobalDefine.h"
#include <QObject>
#include <QOpenGLShader>


class CCGLShader : public QObject
{
public:
    explicit CCGLShader(QObject *parent = nullptr);
    virtual ~CCGLShader();

    void  SetupShaderResources(const QString& vs, const QString& fs);
    QOpenGLShaderProgram* GetShaderProgram(){ return m_pShaderProgram; }
    void  Use();
    void  UnUse();

private:
    QOpenGLShaderProgram*   m_pShaderProgram;

};

#endif // CCGLSHADER_H
