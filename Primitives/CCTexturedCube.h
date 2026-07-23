#ifndef CCTEXTUREDCUBE_H
#define CCTEXTUREDCUBE_H

#include <QObject>
#include "Common/CCGLShader.h"
#include "Common/CCGLTexture.h"

class CCTexturedCube : public QObject
{
public:
    explicit CCTexturedCube(QObject *parent = nullptr);
    virtual ~CCTexturedCube();

    void  Render(CCGLCamera* camera, float deltaTime);


private:

    GLuint            m_texture[6];
    CCGLShader*       m_pOpenGLShader;
    CCGLTexture*      m_pOpenGLTexture;

    QOpenGLBuffer*    m_vertexBuffer;
    QOpenGLBuffer*    m_indexBuffer;


    float             m_angle = 0.0;
};

#endif // CCTEXTUREDCUBE_H
