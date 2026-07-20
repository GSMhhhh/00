/*
 * The Original Code is Copyright 2021, 陈超
 * Contact QQ: 2475164140
 * 陈超音视频数字图像处理开发实战系列课程
 * 《Qt数字图像处理OpenGL渲染引擎开发实战》
 * chenchao_shenzhen@163.com
 * 课程地址: https://ke.qq.com/course/3615377?tuin=938801ec
 */

#include "JCMainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //qputenv("QT_SCALE_FACTOR", "2.0");
    QApplication a(argc, argv);
    JCMainWindow w;
    w.show();

    return a.exec();
}
