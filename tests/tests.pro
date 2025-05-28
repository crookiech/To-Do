# QT += testlib
# QT -= gui

# CONFIG += qt console warn_on depend_includepath testcase
# CONFIG -= app_bundle

# TEMPLATE = app

# SOURCES +=  tst_testtodolist.cpp


QT += testlib core gui widgets

CONFIG += c++17 cmdline

INCLUDEPATH += ../ToDo
DEPENDPATH += ../ToDo

SOURCES += \
    testtodolist.cpp

HEADERS += \
    testtodolist.h

SOURCES += ../ToDo/todolist.cpp \
           ../ToDo/workingwithfiles.cpp \
           ../ToDo/add.cpp \
           ../ToDo/calendar.cpp \
           ../ToDo/edit.cpp
HEADERS += ../ToDo/todolist.h \
           ../ToDo/workingwithfiles.h \
           ../ToDo/add.h \
           ../ToDo/calendar.h \
           ../ToDo/edit.h

FORMS += ../ToDo/todolist.ui \
         ../ToDo/add.ui \
         ../ToDo/calendar.ui \
         ../ToDo/edit.ui

RESOURCES += ../ToDo/resources.qrc
