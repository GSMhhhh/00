/*
 * The Original Code is Copyright 2021, 陈超
 * Contact QQ: 2475164140
 * 陈超音视频数字图像处理开发实战系列课程
 * 《Qt数字图像处理OpenGL渲染引擎开发实战》
 * chenchao_shenzhen@163.com
 * 课程地址: https://ke.qq.com/course/3615377?tuin=938801ec
 */

#ifndef JCMAINWINDOW_H
#define JCMAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include "CCOpenGLWidget.h"


class JCMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit JCMainWindow(QWidget *parent = 0);
    ~JCMainWindow();

private:
    CCOpenGLWidget*         m_pOpenGLWidget;
    QPushButton*            m_pRecordButton;
private slots:
    void onRecordButtonClicked(bool checked);

};

#endif // JCMAINWINDOW_H
