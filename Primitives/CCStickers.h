#ifndef CCSTICKERS_H
#define CCSTICKERS_H

#include <QObject>

#include "Common/CCGLShader.h"
#include "Common/CCGLTexture.h"

class CCStickers : public QObject
{
public:
    explicit CCStickers(QObject *parent = nullptr);
    virtual ~CCStickers();
    void  Render(CCGLCamera* camera, float deltaTime);
    void  UpdateMouseEvent(QPointF pos,float scale);
private:
    GLuint            m_texture;
    CCGLShader*       m_pOpenGLShader;
    CCGLTexture*      m_pOpenGLTexture;

    QOpenGLBuffer*    m_vertexBuffer;
    QOpenGLBuffer*    m_indexBuffer;

    GLdouble   m_Objx = 0;
    GLdouble   m_Objy = 0;
    GLdouble   m_Objz =-1;
    float      m_ObjScale = 1.0;
    CCGLCamera*  m_pCamera = NULL;
};

#endif // CCSTICKERS_H
