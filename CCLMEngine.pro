QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CCLMEngine
TEMPLATE = app


macx {

QMAKE_INFO_PLIST= Info.plist

DEFINES += CCLMENGINE_PROJECT_MACX

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.7

QMAKE_LFLAGS    += -framework QuartzCore
QMAKE_LFLAGS    += -framework Foundation
QMAKE_LFLAGS    += -framework CoreMedia
QMAKE_LFLAGS    += -framework AVFoundation
QMAKE_LFLAGS    += -framework VideoToolbox
QMAKE_LFLAGS    += -framework AudioToolbox
QMAKE_LFLAGS    += -framework VideoDecodeAcceleration
QMAKE_LFLAGS    += -framework CoreGraphics
QMAKE_LFLAGS    += -framework Security
QMAKE_LFLAGS    += -framework OpenAL

INCLUDEPATH += $$PWD/3rdparty/mac/libglew/include
LIBS += -L$$PWD/3rdparty/mac/libglew/lib -lGLEW

INCLUDEPATH += $$PWD/3rdParty/mac/libOpenCV/include
LIBS += -L$$PWD/3rdParty/mac/libOpenCV/lib

LIBS += -lopencv_core.3.3.1 \
        -lopencv_highgui.3.3.1 \
        -lopencv_imgproc.3.3.1 \
        -lopencv_objdetect.3.3.1 \
        -lopencv_video.3.3.1 \
        -lopencv_videoio.3.3.1 \
        -lopencv_imgcodecs.3.3.1 \
        -lopencv_calib3d.3.3.1 \
        -lopencv_features2d.3.3.1 \
        -lopencv_flann.3.3.1 \
        -lopencv_ml.3.3.1

INCLUDEPATH += $$PWD/3rdParty/mac/libx264/include
LIBS += -L$$PWD/3rdParty/mac/libx264/lib -lx264 -lfdk-aac

INCLUDEPATH += $$PWD/3rdParty/mac/libFFmpeg/include
LIBS += -L$$PWD/3rdParty/mac/libFFmpeg/lib -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lswscale -lswresample

INCLUDEPATH += $$PWD/3rdParty/mac/libfaac/include
LIBS += -L$$PWD/3rdParty/mac/libfaac/lib -lfaac

LIBS += -liconv -lz -lbz2 -llzma

INCLUDEPATH += $$PWD/3rdParty/mac/libfacelandmark/include
LIBS += -L$$PWD/3rdParty/mac/libfacelandmark/lib -lfacelandmark

}

win32 {

DEFINES += CCLMENGINE_PROJECT_WIN
CONFIG += resources_big
CONFIG += c++11

LIBS += -lOpenGL32 -lglu32


INCLUDEPATH += $$PWD/3rdparty/win32/libglew/include
LIBS += $$PWD/3rdparty/win32/libglew/lib/glew32.lib

INCLUDEPATH += $$PWD/3rdparty/win32/libOpenCV/include

LIBS += -L$$PWD/3rdparty/win32/libOpenCV/lib \
    -llibopencv_core331 \
    -llibopencv_highgui331 \
    -llibopencv_imgcodecs331 \
    -llibopencv_imgproc331 \
    -llibopencv_features2d331 \
    -llibopencv_calib3d331 \
    -llibopencv_video331 \
    -llibopencv_videoio331 \
    -llibopencv_videostab331 \
    -llibopencv_objdetect331

INCLUDEPATH += $$PWD/3rdParty/win32/libfacelandmark/include
LIBS += -L$$PWD/3rdParty/win32/libfacelandmark/lib -lfacelandmark

LIBS += -L$$PWD/3rdparty/win32/libx264/lib -lfdk-aac -lx264

INCLUDEPATH += $$PWD/3rdparty/win32/libFFmpeg/include
LIBS +=   $$PWD/3rdparty/win32/libFFmpeg/lib/libavformat.dll.a \
          $$PWD/3rdparty/win32/libFFmpeg/lib/libavcodec.dll.a \
          $$PWD/3rdparty/win32/libFFmpeg/lib/libavutil.dll.a \
          $$PWD/3rdparty/win32/libFFmpeg/lib/libswresample.dll.a \
          $$PWD/3rdparty/win32/libFFmpeg/lib/libswscale.dll.a \
          $$PWD/3rdparty/win32/libFFmpeg/lib/libpostproc.dll.a \
          $$PWD/3rdparty/win32/libFFmpeg/lib/libavfilter.dll.a

INCLUDEPATH += $$PWD/3rdParty/win32/libfaac/include
LIBS += -L$$PWD/3rdParty/win32/libfaac/lib -lfaac


}

SOURCES += \
    CCGLCamera.cpp \
    CCGLScene.cpp \
    Common/CCGLShader.cpp \
    Common/CCGLSkybox.cpp \
    Common/CCGLTexture.cpp \
    Primitives/CCMesh.cpp \
    Primitives/CCModelLoader.cpp \
    Primitives/CCStickers.cpp \
    Primitives/CCYUVVideo.cpp \
    Primitives/CCTexturedCube.cpp \
    Primitives/CCTexturedPlane.cpp \
    ccvideowriter.cpp \
    main.cpp \
    JCMainWindow.cpp \
    JCVideoCaptureThread.cpp \
    CCOpenGLWidget.cpp \
    videorecorderinterface.cpp

HEADERS += \
    CCGLCamera.h \
    CCGLScene.h \
    Common/CCGLShader.h \
    Common/CCGLSkybox.h \
    Common/CCGLTexture.h \
    Common/CCGlobalDefine.h \
    Common/CCQueueDefine.h \
    JCMainWindow.h \
    JCVideoCaptureThread.h \
    CCOpenGLWidget.h \
    CCYUVDataDefine.h \
    Primitives/CCMesh.h \
    Primitives/CCModelLoader.h \
    Primitives/CCStickers.h \
    Primitives/CCYUVVideo.h \
    Primitives/CCTexturedCube.h \
    Primitives/CCTexturedPlane.h \
    ccvideowriter.h \
    videorecorderinterface.h



FORMS +=

RESOURCES += \
    CCLMEngine.qrc
