#ifndef CCGLSKYBOX_H
#define CCGLSKYBOX_H

#include <GL/glew.h>
#include <QObject>
#include "CCGLShader.h"
#include "CCGLTexture.h"

class CCGLSkybox : public QObject
{
public:
    explicit CCGLSkybox(QObject *parent = nullptr);
    virtual ~CCGLSkybox();

    void  Render(CCGLCamera* camera, float deltaTime);


private:

    GLuint            m_texture[6];
    CCGLShader*       m_pOpenGLShader;
    CCGLTexture*      m_pOpenGLTexture;

    QOpenGLBuffer*    m_vertexBuffer;
    QOpenGLBuffer*    m_indexBuffer;

};

#endif // CCGLSKYBOX_H
