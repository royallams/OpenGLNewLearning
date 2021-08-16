TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Camera.cpp \
        Light.cpp \
        Mesh.cpp \
        Shader.cpp \
        Texture.cpp \
        Window.cpp \
        main.cpp

HEADERS += \
    Camera.h \
    Light.h \
    Mesh.h \
    Shader.h \
    Texture.h \
    Window.h \
    stb_image.h



unix:!macx: LIBS += -L$$PWD/../../../ExternalLibs/GLEW_LINUX/lib/ -lGLEW

INCLUDEPATH += $$PWD/../../../ExternalLibs/GLEW_LINUX/include
DEPENDPATH += $$PWD/../../../ExternalLibs/GLEW_LINUX/include



INCLUDEPATH += $$PWD/../../../ExternalLibs/GLM
DEPENDPATH += $$PWD/../../../ExternalLibs/GLM


unix:!macx: LIBS += -L$$PWD/../../../ExternalLibs/GLFW_LINUX/Build/src/ -lglfw3

INCLUDEPATH += $$PWD/../../../ExternalLibs/GLFW_LINUX/include
DEPENDPATH += $$PWD/../../../ExternalLibs/GLFW_LINUX/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../ExternalLibs/GLFW_LINUX/Build/src/libglfw3.a

unix:!macx: LIBS += -lGL
unix:!macx: LIBS += -ldl
unix:!macx: LIBS += -lX11
unix:!macx: LIBS += -lpthread
