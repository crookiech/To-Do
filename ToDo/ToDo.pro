QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    add.cpp \
    api_client.cpp \
    auth_dialog.cpp \
    calendar.cpp \
    edit.cpp \
    globals.cpp \
    json_file_manager.cpp \
    main.cpp \
    main_window.cpp \
    todo_list.cpp \
    working_with_files.cpp

HEADERS += \
    add.h \
    api_client.h \
    auth_dialog.h \
    calendar.h \
    edit.h \
    globals.h \
    json_file_manager.h \
    main_window.h \
    todo_list.h \
    working_with_files.h

FORMS += \
    add.ui \
    calendar.ui \
    edit.ui \
    main_window.ui \
    todo_list.ui \
    auth.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
