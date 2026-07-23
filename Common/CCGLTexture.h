#ifndef CCGLTEXTURE_H
#define CCGLTEXTURE_H

#include <QObject>
#include "Common/CCGlobalDefine.h"

class CCGLTexture : public QObject
{

public:
    explicit CCGLTexture(QObject *parent = nullptr);
    virtual ~CCGLTexture();

    GLuint CreateOpenGLTexture(QString& pathString);
    GLuint CreateOpenGLSkyBoxTexture(QString& pathString);
};

#endif // CCGLTEXTURE_H
