/*
 * The Original Code is Copyright 2021, 陈超
 * Contact QQ: 2475164140
 * 陈超音视频数字图像处理开发实战系列课程
 * 《Qt数字图像处理OpenGL渲染引擎开发实战》
 * chenchao_shenzhen@163.com
 * 课程地址: https://ke.qq.com/course/3615377?tuin=938801ec
 */

#ifndef CCGLSCENE_H
#define CCGLSCENE_H

#include <QObject>

#include "CCGLCamera.h"
#include "JCVideoCaptureThread.h"


#include "Common/CCGLSkybox.h"
#include "Primitives/CCTexturedCube.h"
#include "Primitives/CCStickers.h"
#include "Common/CCQueueDefine.h"
#include "Primitives/CCYUVVideo.h"
#include "Primitives/CCModelLoader.h"
#include <QPointF>

class CCGLScene: public QObject
{
    Q_OBJECT
public:
    explicit CCGLScene(int width, int height, QObject *parent = nullptr);
    virtual ~CCGLScene();

    void  SetupSceneResources();

    void  Render(float deltaTime);
    void  Resize(int width,int height);
    void  UpdateMouseEvent(QPointF pos);

private slots:
    void onVideoFrameUpdate(CCYUV_Frame* yuvFrame);
    void onHeadPositionUpdate(QPoint pos,float scale);

private:

    CCGLCamera      *m_pCamera;

    QPointF       m_mousePos = QPointF(0,0);

    int           m_nSceneWidth  = 800;
    int           m_nSceneHeight = 600;

    CCGLSkybox*         m_pSkyBox;
    CCTexturedCube*     m_pTexturedCube;
    CCStickers*         m_pStickers;
    CCModelLoader*      m_pObjLoader;

    CCYUVVideo*         m_pYUVVideo;

    JCVideoCaptureThread*   m_pVideoCaptureThread;
    JCTSQueue<CCYUV_Buffer*>    m_yuvBuffQueue;

    CCYUV_Buffer*           m_pLastBuffer;

    QPointF                 m_lmpos;
    float                   m_currScale;

};

#endif // CCGLSCENE_H
