QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adddialog.cpp \
    agentsinfotable.cpp \
    cagent.cpp \
    deletedialog.cpp \
    editdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    readonlydelegate.cpp \
    seekbybirthdatedialog.cpp \
    seekbyeducationdialog.cpp \
    seekbymarrieddialog.cpp \
    seekbystatusdialog.cpp

HEADERS += \
    adddialog.h \
    agentsinfotable.h \
    cagent.h \
    deletedialog.h \
    editdialog.h \
    mainwindow.h \
    readonlydelegate.h \
    seekbybirthdatedialog.h \
    seekbyeducationdialog.h \
    seekbymarrieddialog.h \
    seekbystatusdialog.h

FORMS += \
    adddialog.ui \
    deletedialog.ui \
    editdialog.ui \
    mainwindow.ui \
    seekbybirthdatedialog.ui \
    seekbyeducationdialog.ui \
    seekbymarrieddialog.ui \
    seekbystatusdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
