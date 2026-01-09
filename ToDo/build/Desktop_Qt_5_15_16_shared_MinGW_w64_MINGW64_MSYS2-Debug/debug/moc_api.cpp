/****************************************************************************
** Meta object code from reading C++ file 'api.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../api.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'api.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_api_t {
    QByteArrayData data[23];
    char stringdata0[274];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_api_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_api_t qt_meta_stringdata_api = {
    {
QT_MOC_LITERAL(0, 0, 3), // "api"
QT_MOC_LITERAL(1, 4, 12), // "loginSuccess"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 6), // "userId"
QT_MOC_LITERAL(4, 25, 11), // "loginFailed"
QT_MOC_LITERAL(5, 37, 5), // "error"
QT_MOC_LITERAL(6, 43, 19), // "registrationSuccess"
QT_MOC_LITERAL(7, 63, 18), // "registrationFailed"
QT_MOC_LITERAL(8, 82, 15), // "logoutCompleted"
QT_MOC_LITERAL(9, 98, 11), // "tasksLoaded"
QT_MOC_LITERAL(10, 110, 18), // "QList<QJsonObject>"
QT_MOC_LITERAL(11, 129, 5), // "tasks"
QT_MOC_LITERAL(12, 135, 9), // "taskAdded"
QT_MOC_LITERAL(13, 145, 4), // "task"
QT_MOC_LITERAL(14, 150, 11), // "taskUpdated"
QT_MOC_LITERAL(15, 162, 11), // "taskDeleted"
QT_MOC_LITERAL(16, 174, 6), // "taskId"
QT_MOC_LITERAL(17, 181, 19), // "taskOperationFailed"
QT_MOC_LITERAL(18, 201, 12), // "networkError"
QT_MOC_LITERAL(19, 214, 22), // "authenticationRequired"
QT_MOC_LITERAL(20, 237, 15), // "onReplyFinished"
QT_MOC_LITERAL(21, 253, 14), // "QNetworkReply*"
QT_MOC_LITERAL(22, 268, 5) // "reply"

    },
    "api\0loginSuccess\0\0userId\0loginFailed\0"
    "error\0registrationSuccess\0registrationFailed\0"
    "logoutCompleted\0tasksLoaded\0"
    "QList<QJsonObject>\0tasks\0taskAdded\0"
    "task\0taskUpdated\0taskDeleted\0taskId\0"
    "taskOperationFailed\0networkError\0"
    "authenticationRequired\0onReplyFinished\0"
    "QNetworkReply*\0reply"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_api[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       4,    1,   82,    2, 0x06 /* Public */,
       6,    0,   85,    2, 0x06 /* Public */,
       7,    1,   86,    2, 0x06 /* Public */,
       8,    0,   89,    2, 0x06 /* Public */,
       9,    1,   90,    2, 0x06 /* Public */,
      12,    1,   93,    2, 0x06 /* Public */,
      14,    1,   96,    2, 0x06 /* Public */,
      15,    1,   99,    2, 0x06 /* Public */,
      17,    1,  102,    2, 0x06 /* Public */,
      18,    1,  105,    2, 0x06 /* Public */,
      19,    0,  108,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      20,    1,  109,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::QJsonObject,   13,
    QMetaType::Void, QMetaType::QJsonObject,   13,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 21,   22,

       0        // eod
};

void api::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<api *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->loginSuccess((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->loginFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->registrationSuccess(); break;
        case 3: _t->registrationFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->logoutCompleted(); break;
        case 5: _t->tasksLoaded((*reinterpret_cast< const QList<QJsonObject>(*)>(_a[1]))); break;
        case 6: _t->taskAdded((*reinterpret_cast< const QJsonObject(*)>(_a[1]))); break;
        case 7: _t->taskUpdated((*reinterpret_cast< const QJsonObject(*)>(_a[1]))); break;
        case 8: _t->taskDeleted((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->taskOperationFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->networkError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->authenticationRequired(); break;
        case 12: _t->onReplyFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QJsonObject> >(); break;
            }
            break;
        case 12:
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
            using _t = void (api::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&api::loginSuccess)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (api::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&api::loginFailed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (api::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&api::registrationSuccess)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (api::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&api::registrationFailed)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (api::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&api::logoutCompleted)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (api::*)(const QList<QJsonObject> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&api::tasksLoaded)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (api::*)(const QJsonObject & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&api::taskAdded)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (api::*)(const QJsonObject & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&api::taskUpdated)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (api::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&api::taskDeleted)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (api::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&api::taskOperationFailed)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (api::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&api::networkError)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (api::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&api::authenticationRequired)) {
                *result = 11;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject api::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_api.data,
    qt_meta_data_api,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *api::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *api::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_api.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int api::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void api::loginSuccess(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void api::loginFailed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void api::registrationSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void api::registrationFailed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void api::logoutCompleted()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void api::tasksLoaded(const QList<QJsonObject> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void api::taskAdded(const QJsonObject & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void api::taskUpdated(const QJsonObject & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void api::taskDeleted(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void api::taskOperationFailed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void api::networkError(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void api::authenticationRequired()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
