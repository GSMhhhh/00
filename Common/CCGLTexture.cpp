#include "CCGLTexture.h"
#include <QImage>

CCGLTexture::CCGLTexture(QObject *parent) : QObject(parent)
{
}

CCGLTexture::~CCGLTexture()
{
}

GLuint CCGLTexture::CreateOpenGLTexture(QString& pathString)
{
    GLuint textureID;

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1,&textureID);//产生纹理索引
    glBindTexture(GL_TEXTURE_2D,textureID);//绑定纹理索引，之后的操作都针对当前纹理索引

    QImage texImage= QImage(pathString.toLocal8Bit().data()).mirrored();

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);//指当纹理图象被使用到一个大于它的形状上时
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);//指当纹理图象被使用到一个小于或等于它的形状上时
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,texImage.width(),texImage.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,texImage.rgbSwapped().bits());//指定参数，生成纹理

    return textureID;

}

GLuint CCGLTexture::CreateOpenGLSkyBoxTexture(QString& pathString)
{
    GLuint textureID;

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1,&textureID);//产生纹理索引
    glBindTexture(GL_TEXTURE_2D,textureID);//绑定纹理索引，之后的操作都针对当前纹理索引

    QImage texImage= QImage(pathString.toLocal8Bit().data()).mirrored();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);//指当纹理图象被使用到一个大于它的形状上时
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);//指当纹理图象被使用到一个小于或等于它的形状上时
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,texImage.width(),texImage.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,texImage.rgbSwapped().bits());//指定参数，生成纹理

    glBindTexture(GL_TEXTURE_2D, 0);

    return textureID;

}
