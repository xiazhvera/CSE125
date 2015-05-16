HEADERS       = glwidget.h \
                window.h \
                mainwindow.h \
                logo.h \
    mainMenu.h \
    battlefieldView.h \
    buildView.h \
    views.h
SOURCES       = glwidget.cpp \
                main.cpp \
                window.cpp \
                mainwindow.cpp \
                logo.cpp \
    mainMenu.cpp \
    battlefieldView.cpp \
    buildView.cpp

QT           += widgets

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/hellogl2
INSTALLS += target