#ifndef CCYUVVIDEO_H
#define CCYUVVIDEO_H

#include <QObject>
#include "Common/CCGLShader.h"
#include "CCYUVDataDefine.h"

class CCYUVVideo : public QObject
{
    Q_OBJECT
public:
    explicit CCYUVVideo(QObject *parent = nullptr);
    virtual ~CCYUVVideo();
     void  Render(CCGLCamera* camera, CCYUV_Buffer* yuvBuffer);

private:
    GLuint            m_textures[3];
    CCGLShader*       m_pOpenGLShader;

    QOpenGLBuffer*    m_vertexBuffer;
    QOpenGLBuffer*    m_indexBuffer;


};

#endif // CCYUVVIDEO_H
