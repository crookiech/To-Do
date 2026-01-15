/****************************************************************************
** Meta object code from reading C++ file 'api_client.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../api_client.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'api_client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Api_Client_t {
    QByteArrayData data[22];
    char stringdata0[260];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Api_Client_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Api_Client_t qt_meta_stringdata_Api_Client = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Api_Client"
QT_MOC_LITERAL(1, 11, 13), // "login_success"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 7), // "user_id"
QT_MOC_LITERAL(4, 34, 11), // "login_error"
QT_MOC_LITERAL(5, 46, 13), // "error_message"
QT_MOC_LITERAL(6, 60, 20), // "registration_success"
QT_MOC_LITERAL(7, 81, 18), // "registration_error"
QT_MOC_LITERAL(8, 100, 12), // "user_checked"
QT_MOC_LITERAL(9, 113, 6), // "exists"
QT_MOC_LITERAL(10, 120, 7), // "message"
QT_MOC_LITERAL(11, 128, 12), // "task_created"
QT_MOC_LITERAL(12, 141, 7), // "task_id"
QT_MOC_LITERAL(13, 149, 12), // "tasks_loaded"
QT_MOC_LITERAL(14, 162, 17), // "std::vector<Task>"
QT_MOC_LITERAL(15, 180, 5), // "tasks"
QT_MOC_LITERAL(16, 186, 12), // "task_updated"
QT_MOC_LITERAL(17, 199, 12), // "task_deleted"
QT_MOC_LITERAL(18, 212, 9), // "api_error"
QT_MOC_LITERAL(19, 222, 16), // "on_network_reply"
QT_MOC_LITERAL(20, 239, 14), // "QNetworkReply*"
QT_MOC_LITERAL(21, 254, 5) // "reply"

    },
    "Api_Client\0login_success\0\0user_id\0"
    "login_error\0error_message\0"
    "registration_success\0registration_error\0"
    "user_checked\0exists\0message\0task_created\0"
    "task_id\0tasks_loaded\0std::vector<Task>\0"
    "tasks\0task_updated\0task_deleted\0"
    "api_error\0on_network_reply\0QNetworkReply*\0"
    "reply"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Api_Client[] = {

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
      13,    1,   89,    2, 0x06 /* Public */,
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
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 20,   21,

       0        // eod
};

void Api_Client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Api_Client *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->login_success((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->login_error((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->registration_success((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->registration_error((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->user_checked((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->task_created((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->tasks_loaded((*reinterpret_cast< const std::vector<Task>(*)>(_a[1]))); break;
        case 7: _t->task_updated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->task_deleted((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->api_error((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->on_network_reply((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
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
            using _t = void (Api_Client::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Api_Client::login_success)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Api_Client::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Api_Client::login_error)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Api_Client::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Api_Client::registration_success)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Api_Client::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Api_Client::registration_error)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Api_Client::*)(bool , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Api_Client::user_checked)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Api_Client::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Api_Client::task_created)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Api_Client::*)(const std::vector<Task> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Api_Client::tasks_loaded)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Api_Client::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Api_Client::task_updated)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (Api_Client::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Api_Client::task_deleted)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (Api_Client::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Api_Client::api_error)) {
                *result = 9;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Api_Client::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Api_Client.data,
    qt_meta_data_Api_Client,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Api_Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Api_Client::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Api_Client.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Api_Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void Api_Client::login_success(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Api_Client::login_error(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Api_Client::registration_success(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Api_Client::registration_error(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Api_Client::user_checked(bool _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Api_Client::task_created(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Api_Client::tasks_loaded(const std::vector<Task> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Api_Client::task_updated(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Api_Client::task_deleted(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void Api_Client::api_error(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
