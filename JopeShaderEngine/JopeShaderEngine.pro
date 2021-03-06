#-------------------------------------------------
#
# Project created by QtCreator 2019-03-26T10:52:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JopeShaderEngine
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    openglwidget.cpp \
    gameobject.cpp \
    hierarchy.cpp \
    inspector.cpp \
    component.cpp \
    comptransform.cpp \
    compcamera.cpp \
    transformui.cpp \
    resource.cpp \
    resourcemesh.cpp \
    submesh.cpp \
    compmeshrenderer.cpp \
    meshrendererui.cpp \
    resourcematerial.cpp

HEADERS += \
        mainwindow.h \
    openglwidget.h \
    gameobject.h \
    hierarchy.h \
    inspector.h \
    component.h \
    comptransform.h \
    compcamera.h \
    transformui.h \
    resource.h \
    resourcemesh.h \
    submesh.h \
    vertexformat.h \
    compmeshrenderer.h \
    meshrendererui.h \
    resourcematerial.h

FORMS += \
        mainwindow.ui \
    hierarchy.ui \
    transformui.ui \
    meshrendererui.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    vertex_shader.vert \
    fragment_shader.frag \
    Shaders/quad_vert_shader.vert \
    Shaders/quad_frag_shader.frag \
    Shaders/light_vert_shader.vert \
    Shaders/light_frag_shader.frag \
    Shaders/blur_frag_shader.frag \
    Shaders/blur_vert_shader.vert \
    Shaders/depth_field_vert_shader.vert \
    Shaders/depth_field_frag_shader.frag \
    Shaders/color_frag_shader.frag \
    Shaders/color_vert_shader.vert

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/Assimp/lib/ -lassimp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/Assimp/lib/ -lassimpd

INCLUDEPATH += $$PWD/Assimp/include
DEPENDPATH += $$PWD/Assimp/include
