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
