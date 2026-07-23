#ifndef CCMESH_H
#define CCMESH_H


#include <QWidget>
#include <QVector2D>
#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>
#include "Common/CCGlobalDefine.h"
#include "Common/CCGLShader.h"
#include "Common/CCGLTexture.h"


;
#pragma pack(push, 1)
typedef struct VertexData
{
    VertexData ()
    {
    }
    VertexData (QVector3D p, QVector2D t, QVector3D n) :
        position(p), textCoord(t), normal(n)
    {
    }

    QVector3D position;
    QVector2D textCoord;
    QVector3D normal;
    QVector3D tangent;
    QVector3D bitangent;

}CCVertexData;
#pragma pack(pop)

class CCMesh
{
public:
    CCMesh();
    CCMesh(const QVector<CCVertexData> &vertData, const QVector<GLuint> &indexes);
    virtual ~CCMesh();
    void Render(CCGLCamera* camera, float deltaTime);
    void Rotate(const float &angle,const QVector3D &t);
    void Translate(const QVector3D &t);
    void Scale(const float &s);
    void UpdateModelPosition(QPointF pos,float scale);
private:
    void init(const QVector<VertexData> &vertData, const QVector<GLuint> &indexes);

private:

    CCGLShader*      m_pOpenGLShader;

    QOpenGLBuffer*   m_vertexBuffer;
    QOpenGLBuffer*   m_indexBuffer;

    GLuint           m_diffuseId;
    GLuint           m_normalId;
    GLuint           m_specularId;

    CCGLTexture*      m_pDiffuseTexture;
    CCGLTexture*      m_pNormalTexture;
    CCGLTexture*      m_pSpecularTexture;

    GLdouble   m_Objx = 0;
    GLdouble   m_Objy = 0;
    GLdouble   m_Objz =-1;
    float      m_ObjScale = 1.0;

};

#endif // CCMESH_H
