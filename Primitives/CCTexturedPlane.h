#ifndef CCTEXTUREDPLANE_H
#define CCTEXTUREDPLANE_H

#include <QObject>
#include "Common/CCGLShader.h"
#include "Common/CCGLTexture.h"


class CCTexturedPlane : public QObject
{
public:
    explicit CCTexturedPlane(QObject *parent = nullptr);
    virtual ~CCTexturedPlane();
    void  Render(CCGLCamera* camera, float deltaTime);

private:
    GLuint            m_texture;
    CCGLShader*       m_pOpenGLShader;
    CCGLTexture*      m_pOpenGLTexture;

    QOpenGLBuffer*    m_vertexBuffer;
    QOpenGLBuffer*    m_indexBuffer;

};

#endif // CCTEXTUREDPLANE_H
