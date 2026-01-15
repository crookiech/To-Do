/****************************************************************************
** Meta object code from reading C++ file 'auth_dialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../auth_dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'auth_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Auth_Dialog_t {
    QByteArrayData data[13];
    char stringdata0[198];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Auth_Dialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Auth_Dialog_t qt_meta_stringdata_Auth_Dialog = {
    {
QT_MOC_LITERAL(0, 0, 11), // "Auth_Dialog"
QT_MOC_LITERAL(1, 12, 22), // "on_loginButton_clicked"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 25), // "on_registerButton_clicked"
QT_MOC_LITERAL(4, 62, 16), // "on_login_success"
QT_MOC_LITERAL(5, 79, 7), // "user_id"
QT_MOC_LITERAL(6, 87, 23), // "on_registration_success"
QT_MOC_LITERAL(7, 111, 15), // "on_user_checked"
QT_MOC_LITERAL(8, 127, 6), // "exists"
QT_MOC_LITERAL(9, 134, 14), // "on_login_error"
QT_MOC_LITERAL(10, 149, 13), // "error_message"
QT_MOC_LITERAL(11, 163, 21), // "on_registration_error"
QT_MOC_LITERAL(12, 185, 12) // "on_api_error"

    },
    "Auth_Dialog\0on_loginButton_clicked\0\0"
    "on_registerButton_clicked\0on_login_success\0"
    "user_id\0on_registration_success\0"
    "on_user_checked\0exists\0on_login_error\0"
    "error_message\0on_registration_error\0"
    "on_api_error"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Auth_Dialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    1,   56,    2, 0x08 /* Private */,
       6,    0,   59,    2, 0x08 /* Private */,
       7,    1,   60,    2, 0x08 /* Private */,
       9,    1,   63,    2, 0x08 /* Private */,
      11,    1,   66,    2, 0x08 /* Private */,
      12,    1,   69,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   10,

       0        // eod
};

void Auth_Dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Auth_Dialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_loginButton_clicked(); break;
        case 1: _t->on_registerButton_clicked(); break;
        case 2: _t->on_login_success((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_registration_success(); break;
        case 4: _t->on_user_checked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_login_error((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->on_registration_error((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->on_api_error((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Auth_Dialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_Auth_Dialog.data,
    qt_meta_data_Auth_Dialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Auth_Dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Auth_Dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Auth_Dialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Auth_Dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
