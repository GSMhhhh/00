/*
 * The Original Code is Copyright 2021, 陈超
 * Contact QQ: 2475164140
 * 陈超音视频数字图像处理开发实战系列课程
 * 《Qt数字图像处理OpenGL渲染引擎开发实战》
 * chenchao_shenzhen@163.com
 * 课程地址: https://ke.qq.com/course/3615377?tuin=938801ec
 */

#include "JCMainWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QDebug>


JCMainWindow::JCMainWindow(QWidget *parent) :QWidget(parent)
{
    resize(640,480);

    m_pOpenGLWidget = new CCOpenGLWidget(this);
    //m_pOpenGLWidget->setBaseSize(640,480);
    QHBoxLayout* mainlayout = new QHBoxLayout(this);
    mainlayout->setContentsMargins(1,1,1,1);
    mainlayout->addWidget(m_pOpenGLWidget);

    m_pRecordButton = new QPushButton(this);
    m_pRecordButton->setFixedSize(QSize(40,40));
    m_pRecordButton->setAutoFillBackground(true);
    m_pRecordButton->setCheckable(true);
    m_pRecordButton->setChecked(false);
    m_pRecordButton->setIcon(QIcon(":/res/Images/RecordButton_Start_bg.png"));
    m_pRecordButton->setIconSize(QSize(40,40));
    m_pRecordButton->setStyleSheet("QPushButton{background:rgba(0,0,0,0);border:1px solid rgba(0,0,0,0);}");

    connect(m_pRecordButton,SIGNAL(clicked(bool)),this,SLOT(onRecordButtonClicked(bool)));

    QSpacerItem* topItem = new QSpacerItem(20,200,QSizePolicy::Fixed,QSizePolicy::Expanding);
    QSpacerItem* bottomItem = new QSpacerItem(20,15,QSizePolicy::Fixed,QSizePolicy::Fixed);

    QSpacerItem* leftItem = new QSpacerItem(100,20,QSizePolicy::Expanding,QSizePolicy::Fixed);
    QSpacerItem* rightItem = new QSpacerItem(100,20,QSizePolicy::Expanding,QSizePolicy::Fixed);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addSpacerItem(leftItem);
    buttonLayout->addWidget(m_pRecordButton);
    buttonLayout->addSpacerItem(rightItem);


    QVBoxLayout* frontLayout = new QVBoxLayout(m_pOpenGLWidget);
    frontLayout->addSpacerItem(topItem);
    frontLayout->addLayout(buttonLayout);
    frontLayout->addSpacerItem(bottomItem);

}

JCMainWindow::~JCMainWindow()
{
    if(m_pOpenGLWidget){
        delete m_pOpenGLWidget;
        m_pOpenGLWidget = NULL;
    }
}
void JCMainWindow::onRecordButtonClicked(bool bChecked)
{
    qDebug()<<"record:"<<bChecked;
    if(bChecked){
        m_pRecordButton->setIcon(QIcon(":/res/Images/RecordButton_Stop_bg.png"));
        m_pOpenGLWidget->StartRecordVideo();
    }else{
        m_pRecordButton->setIcon(QIcon(":/res/Images/RecordButton_Start_bg.png"));
        m_pOpenGLWidget->StopRecordVideo();
    }
}
