#include "CCGLScene.h"


CCGLScene::CCGLScene(int width, int height,QObject *parent) :QObject(parent),
                     m_nSceneWidth(width),m_nSceneHeight(height)
{

    m_pLastBuffer = NULL;
    m_currScale = 1.0;
    m_pVideoCaptureThread = new JCVideoCaptureThread();
    connect(m_pVideoCaptureThread,SIGNAL(OnCapturedYUVUpdate(CCYUV_Frame* )),this,SLOT(onVideoFrameUpdate(CCYUV_Frame*)),Qt::DirectConnection);
    connect(m_pVideoCaptureThread,SIGNAL(OnFaceHeadPostionUpdate(QPoint,float)),this,SLOT(onHeadPositionUpdate(QPoint,float)),Qt::DirectConnection);
    connect(m_pVideoCaptureThread,SIGNAL(finished()),m_pVideoCaptureThread,SLOT(deleteLater()));

    m_pVideoCaptureThread->StartCaptureVideoWithSize(640,480);

}

CCGLScene::~CCGLScene()
{

    CCGLSafePtrDelete(m_pCamera);
    CCGLSafePtrDelete(m_pYUVVideo);

    CCGLSafePtrDelete(m_pStickers);
    CCGLSafePtrDelete(m_pSkyBox);
    CCGLSafePtrDelete(m_pTexturedCube);
    CCGLSafePtrDelete(m_pObjLoader);

    if(m_pVideoCaptureThread){

        m_pVideoCaptureThread->StopCaptureVideo();

        m_pVideoCaptureThread->quit();
        m_pVideoCaptureThread->wait();
    }

    if(m_pLastBuffer != NULL){
        if(m_pLastBuffer->buffer != NULL){
            free(m_pLastBuffer->buffer);
            m_pLastBuffer->buffer = NULL;
        }
        delete  m_pLastBuffer;
        m_pLastBuffer= NULL;
    }
}

void CCGLScene::SetupSceneResources()
{
    m_pCamera = new CCGLCamera();
    m_pSkyBox   = new CCGLSkybox();
    m_pTexturedCube = new CCTexturedCube();
    m_pObjLoader = new CCModelLoader();
    m_pObjLoader->LoadModelFromFile(":/res/Models/monkey.obj");

    m_pStickers = new CCStickers();
    m_pYUVVideo = new CCYUVVideo();

}

void CCGLScene::Render(float deltaTime)
{

    m_pSkyBox->Render(m_pCamera,deltaTime);
    //m_pTexturedCube->Render(m_pCamera,deltaTime);
    //m_pStickers->Render(m_pCamera,deltaTime);
    //m_pStickers->UpdateMouseEvent(m_lmpos,m_currScale);
    m_pObjLoader->Render(m_pCamera,deltaTime);
    m_pObjLoader->UpdateMouseEvent(m_lmpos,m_currScale);

    if(!m_yuvBuffQueue.isEmpty()){

        CCYUV_Buffer* yuvBuffer = (CCYUV_Buffer*)m_yuvBuffQueue.dequeue();

        if( yuvBuffer != NULL && yuvBuffer->buffer != NULL ){
            m_pYUVVideo->Render(m_pCamera,yuvBuffer);

            unsigned int buffLen = yuvBuffer->ylength + yuvBuffer->ulength +yuvBuffer->vlength;
            if(m_pLastBuffer == NULL){
                 m_pLastBuffer = new CCYUV_Buffer;
                 m_pLastBuffer->buffer = (unsigned char*)malloc(buffLen);
            }

            memcpy(m_pLastBuffer->buffer,yuvBuffer->buffer,buffLen);
            m_pLastBuffer->width = yuvBuffer->width;
            m_pLastBuffer->height = yuvBuffer->height;
            m_pLastBuffer->ylength = yuvBuffer->ylength;
            m_pLastBuffer->ulength = yuvBuffer->ulength;
            m_pLastBuffer->vlength = yuvBuffer->vlength;
        }

        if(yuvBuffer != NULL){
            if(yuvBuffer->buffer != NULL){
                free(yuvBuffer->buffer);
                yuvBuffer->buffer = NULL;
            }
            delete yuvBuffer;
            yuvBuffer = NULL;
        }
    }
    else
    {
        if(m_pLastBuffer){
            m_pYUVVideo->Render(m_pCamera,m_pLastBuffer);

        }
    }


}


void CCGLScene::onVideoFrameUpdate(CCYUV_Frame* yuvFrame)
{

    if(yuvFrame == NULL ){
        return;
    }

    CCYUV_Buffer* yuvBuffer = new CCYUV_Buffer;


    yuvBuffer->width =  yuvFrame->width;
    yuvBuffer->height = yuvFrame->height;

    yuvBuffer->ylength = yuvFrame->luma.length;
    yuvBuffer->ulength = yuvFrame->chromaB.length;
    yuvBuffer->vlength = yuvFrame->chromaR.length;


    //申请内存存一帧yuv图像数据,其大小为分辨率的1.5倍
    int nLen = yuvBuffer->ylength + yuvBuffer->ulength +yuvBuffer->vlength;

    yuvBuffer->buffer = ( unsigned char*) malloc(nLen);

    memcpy(yuvBuffer->buffer,yuvFrame->luma.dataBuffer,yuvBuffer->ylength);
    memcpy(yuvBuffer->buffer+yuvBuffer->ylength,yuvFrame->chromaB.dataBuffer,yuvBuffer->ulength);
    memcpy(yuvBuffer->buffer+yuvBuffer->ylength +yuvBuffer->ulength,yuvFrame->chromaR.dataBuffer,yuvBuffer->ulength);

    if(m_yuvBuffQueue.size() <3){
           m_yuvBuffQueue.enqueue(yuvBuffer);
    }
    else{
        if(yuvBuffer != NULL){
            if(yuvBuffer->buffer != NULL){
                free(yuvBuffer->buffer);
                yuvBuffer->buffer = NULL;
            }
            delete yuvBuffer;
            yuvBuffer = NULL;
        }
    }


}

void CCGLScene::onHeadPositionUpdate(QPoint pos,float scale)
{
    m_lmpos = QPointF(pos.x(),pos.y());
    m_currScale = scale;
    //qDebug()<<"Position:"<<pos.x() <<" "<<pos.y()<<Qt::endl;
}

void  CCGLScene::Resize(int width,int height)
{
    m_nSceneWidth  = width;
    m_nSceneHeight = height;

}

void CCGLScene::UpdateMouseEvent(QPointF pos)
{
    //m_pStickers->UpdateMouseEvent(pos);

}
