QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    XMLtoJSON/build_xml_tree.cpp \
    XMLtoJSON/xml_tree.cpp \
    XMLtoJSON/xmltojson.cpp \
    binaryTree.cpp \
    compression.cpp \
    consistency.cpp \
    graph.cpp \
    main.cpp \
    mainwindow.cpp \
    prettyxml.cpp \
    sngraph.cpp \
    tree.cpp

HEADERS += \
    XMLtoJSON/build_xml_tree.h \
    XMLtoJSON/xml_tree.h \
    XMLtoJSON/xmltojson.h \
    binaryTree.h \
    compression.h \
    consistency.h \
    graph.h \
    mainwindow.h \
    prettyxml.h \
    sngraph.h \
    tree.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc
