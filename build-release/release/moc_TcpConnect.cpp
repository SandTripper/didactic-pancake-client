/****************************************************************************
** Meta object code from reading C++ file 'TcpConnect.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../didactic-pancake-client/TcpConnect.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TcpConnect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TcpConnect_t {
    QByteArrayData data[15];
    char stringdata0[160];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TcpConnect_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TcpConnect_t qt_meta_stringdata_TcpConnect = {
    {
QT_MOC_LITERAL(0, 0, 10), // "TcpConnect"
QT_MOC_LITERAL(1, 11, 10), // "HBTpackAdd"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 10), // "LGNpackAdd"
QT_MOC_LITERAL(4, 34, 10), // "RGTpackAdd"
QT_MOC_LITERAL(5, 45, 10), // "SCUpackAdd"
QT_MOC_LITERAL(6, 56, 10), // "ADFpackAdd"
QT_MOC_LITERAL(7, 67, 10), // "RFRpackAdd"
QT_MOC_LITERAL(8, 78, 10), // "RCNpackAdd"
QT_MOC_LITERAL(9, 89, 12), // "disconnected"
QT_MOC_LITERAL(10, 102, 11), // "reconnected"
QT_MOC_LITERAL(11, 114, 12), // "read_handler"
QT_MOC_LITERAL(12, 127, 14), // "HBTpackHandler"
QT_MOC_LITERAL(13, 142, 9), // "reconnect"
QT_MOC_LITERAL(14, 152, 7) // "relogin"

    },
    "TcpConnect\0HBTpackAdd\0\0LGNpackAdd\0"
    "RGTpackAdd\0SCUpackAdd\0ADFpackAdd\0"
    "RFRpackAdd\0RCNpackAdd\0disconnected\0"
    "reconnected\0read_handler\0HBTpackHandler\0"
    "reconnect\0relogin"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TcpConnect[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,
       3,    0,   80,    2, 0x06 /* Public */,
       4,    0,   81,    2, 0x06 /* Public */,
       5,    0,   82,    2, 0x06 /* Public */,
       6,    0,   83,    2, 0x06 /* Public */,
       7,    0,   84,    2, 0x06 /* Public */,
       8,    0,   85,    2, 0x06 /* Public */,
       9,    0,   86,    2, 0x06 /* Public */,
      10,    0,   87,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   88,    2, 0x08 /* Private */,
      12,    0,   89,    2, 0x08 /* Private */,
      13,    0,   90,    2, 0x08 /* Private */,
      14,    0,   91,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TcpConnect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TcpConnect *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->HBTpackAdd(); break;
        case 1: _t->LGNpackAdd(); break;
        case 2: _t->RGTpackAdd(); break;
        case 3: _t->SCUpackAdd(); break;
        case 4: _t->ADFpackAdd(); break;
        case 5: _t->RFRpackAdd(); break;
        case 6: _t->RCNpackAdd(); break;
        case 7: _t->disconnected(); break;
        case 8: _t->reconnected(); break;
        case 9: _t->read_handler(); break;
        case 10: _t->HBTpackHandler(); break;
        case 11: _t->reconnect(); break;
        case 12: _t->relogin(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TcpConnect::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpConnect::HBTpackAdd)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TcpConnect::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpConnect::LGNpackAdd)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TcpConnect::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpConnect::RGTpackAdd)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (TcpConnect::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpConnect::SCUpackAdd)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (TcpConnect::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpConnect::ADFpackAdd)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (TcpConnect::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpConnect::RFRpackAdd)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (TcpConnect::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpConnect::RCNpackAdd)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (TcpConnect::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpConnect::disconnected)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (TcpConnect::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpConnect::reconnected)) {
                *result = 8;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject TcpConnect::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_TcpConnect.data,
    qt_meta_data_TcpConnect,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TcpConnect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TcpConnect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TcpConnect.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TcpConnect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void TcpConnect::HBTpackAdd()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void TcpConnect::LGNpackAdd()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void TcpConnect::RGTpackAdd()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void TcpConnect::SCUpackAdd()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void TcpConnect::ADFpackAdd()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void TcpConnect::RFRpackAdd()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void TcpConnect::RCNpackAdd()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void TcpConnect::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void TcpConnect::reconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
