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

