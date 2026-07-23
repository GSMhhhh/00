#ifndef CCGLOBALDEFINE_H
#define CCGLOBALDEFINE_H


#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QVector2D>
#include <QVector3D>
#include <QDebug>
#include <QPoint>
#include <QPointF>
#include "CCGLCamera.h"



#ifdef CCLMENGINE_PROJECT_MACX
#include <OpenGL/glu.h>
#elif CCLMENGINE_PROJECT_WIN
#include <GL/glu.h>
#else
#endif




struct CCVertex{
    float x,y,z;
    float u,v;
};

template<typename T>
void CCGLSafePtrDelete(T* ptr)
{
    delete ptr;
    ptr = NULL;
}

class CCGlobalDefine
{
    inline static void PrintGLError()
    {
        GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
             qDebug()<<"glError:"<<err;
        }
    }

};

#endif // CCGLOBALDEFINE_H
