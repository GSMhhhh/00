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
