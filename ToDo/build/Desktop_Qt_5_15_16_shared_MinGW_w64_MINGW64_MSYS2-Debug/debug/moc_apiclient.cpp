/****************************************************************************
** Meta object code from reading C++ file 'apiclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../apiclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'apiclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ApiClient_t {
    QByteArrayData data[22];
    char stringdata0[239];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ApiClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ApiClient_t qt_meta_stringdata_ApiClient = {
    {
QT_MOC_LITERAL(0, 0, 9), // "ApiClient"
QT_MOC_LITERAL(1, 10, 19), // "registrationSuccess"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 7), // "user_id"
QT_MOC_LITERAL(4, 39, 17), // "registrationError"
QT_MOC_LITERAL(5, 57, 5), // "error"
QT_MOC_LITERAL(6, 63, 12), // "loginSuccess"
QT_MOC_LITERAL(7, 76, 10), // "loginError"
QT_MOC_LITERAL(8, 87, 11), // "userChecked"
QT_MOC_LITERAL(9, 99, 6), // "exists"
QT_MOC_LITERAL(10, 106, 7), // "message"
QT_MOC_LITERAL(11, 114, 11), // "tasksLoaded"
QT_MOC_LITERAL(12, 126, 17), // "std::vector<Task>"
QT_MOC_LITERAL(13, 144, 5), // "tasks"
QT_MOC_LITERAL(14, 150, 11), // "taskCreated"
QT_MOC_LITERAL(15, 162, 7), // "task_id"
QT_MOC_LITERAL(16, 170, 11), // "taskUpdated"
QT_MOC_LITERAL(17, 182, 11), // "taskDeleted"
QT_MOC_LITERAL(18, 194, 8), // "apiError"
QT_MOC_LITERAL(19, 203, 14), // "onNetworkReply"
QT_MOC_LITERAL(20, 218, 14), // "QNetworkReply*"
QT_MOC_LITERAL(21, 233, 5) // "reply"

    },
    "ApiClient\0registrationSuccess\0\0user_id\0"
    "registrationError\0error\0loginSuccess\0"
    "loginError\0userChecked\0exists\0message\0"
    "tasksLoaded\0std::vector<Task>\0tasks\0"
    "taskCreated\0task_id\0taskUpdated\0"
    "taskDeleted\0apiError\0onNetworkReply\0"
    "QNetworkReply*\0reply"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ApiClient[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    1,   72,    2, 0x06 /* Public */,
       6,    1,   75,    2, 0x06 /* Public */,
       7,    1,   78,    2, 0x06 /* Public */,
       8,    2,   81,    2, 0x06 /* Public */,
      11,    1,   86,    2, 0x06 /* Public */,
      14,    1,   89,    2, 0x06 /* Public */,
      16,    1,   92,    2, 0x06 /* Public */,
      17,    1,   95,    2, 0x06 /* Public */,
      18,    1,   98,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      19,    1,  101,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    9,   10,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 20,   21,

       0        // eod
};

void ApiClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ApiClient *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->registrationSuccess((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->registrationError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->loginSuccess((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->loginError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->userChecked((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->tasksLoaded((*reinterpret_cast< const std::vector<Task>(*)>(_a[1]))); break;
        case 6: _t->taskCreated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->taskUpdated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->taskDeleted((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->apiError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->onNetworkReply((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ApiClient::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ApiClient::registrationSuccess)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ApiClient::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ApiClient::registrationError)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ApiClient::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ApiClient::loginSuccess)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ApiClient::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ApiClient::loginError)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ApiClient::*)(bool , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ApiClient::userChecked)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ApiClient::*)(const std::vector<Task> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ApiClient::tasksLoaded)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ApiClient::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ApiClient::taskCreated)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ApiClient::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ApiClient::taskUpdated)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (ApiClient::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ApiClient::taskDeleted)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (ApiClient::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ApiClient::apiError)) {
                *result = 9;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ApiClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ApiClient.data,
    qt_meta_data_ApiClient,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ApiClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ApiClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ApiClient.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ApiClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void ApiClient::registrationSuccess(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ApiClient::registrationError(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ApiClient::loginSuccess(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ApiClient::loginError(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ApiClient::userChecked(bool _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ApiClient::tasksLoaded(const std::vector<Task> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ApiClient::taskCreated(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ApiClient::taskUpdated(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ApiClient::taskDeleted(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void ApiClient::apiError(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
