/*
 * The Original Code is Copyright 2021, 陈超
 * Contact QQ: 2475164140
 * 陈超音视频数字图像处理开发实战系列课程
 * 《Qt数字图像处理OpenGL渲染引擎开发实战》
 * chenchao_shenzhen@163.com
 * 课程地址: https://ke.qq.com/course/3615377?tuin=938801ec
 */

#ifndef CCQUEUEDEFINE_H
#define CCQUEUEDEFINE_H

#include <QList>
#include <QMutex>

template <class T>
class JCTSQueue : public QList<T>
{
public:
    JCTSQueue()
    {

    }

    ~JCTSQueue()
    {

    }
    void enqueue( const T &t ) {
        m_mutex.lock();
        QList<T>::append(t);
        m_mutex.unlock();
    }

    T dequeue()
    {
        m_mutex.lock();
        T t = NULL;
        if ( !QList<T>::isEmpty() )
            t = QList<T>::takeFirst();
        m_mutex.unlock();
        return t;
    }

    bool isEmpty()
    {
        m_mutex.lock();
        bool b = QList<T>::isEmpty();
        m_mutex.unlock();
        return b;
    }

private:
    QMutex m_mutex;
};

#endif // CCQUEUEDEFINE_H
