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
    QByteArrayData data[19];
    char stringdata0[204];
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
QT_MOC_LITERAL(7, 67, 10), // "DEFpackAdd"
QT_MOC_LITERAL(8, 78, 10), // "RFRpackAdd"
QT_MOC_LITERAL(9, 89, 10), // "RCNpackAdd"
QT_MOC_LITERAL(10, 100, 10), // "GFIpackAdd"
QT_MOC_LITERAL(11, 111, 10), // "AFIpackAdd"
QT_MOC_LITERAL(12, 122, 10), // "DFIpackAdd"
QT_MOC_LITERAL(13, 133, 12), // "disconnected"
QT_MOC_LITERAL(14, 146, 11), // "reconnected"
QT_MOC_LITERAL(15, 158, 12), // "read_handler"
QT_MOC_LITERAL(16, 171, 14), // "HBTpackHandler"
QT_MOC_LITERAL(17, 186, 9), // "reconnect"
QT_MOC_LITERAL(18, 196, 7) // "relogin"

    },
    "TcpConnect\0HBTpackAdd\0\0LGNpackAdd\0"
    "RGTpackAdd\0SCUpackAdd\0ADFpackAdd\0"
    "DEFpackAdd\0RFRpackAdd\0RCNpackAdd\0"
    "GFIpackAdd\0AFIpackAdd\0DFIpackAdd\0"
    "disconnected\0reconnected\0read_handler\0"
    "HBTpackHandler\0reconnect\0relogin"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TcpConnect[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x06 /* Public */,
       3,    0,  100,    2, 0x06 /* Public */,
       4,    0,  101,    2, 0x06 /* Public */,
       5,    0,  102,    2, 0x06 /* Public */,
       6,    0,  103,    2, 0x06 /* Public */,
       7,    0,  104,    2, 0x06 /* Public */,
       8,    0,  105,    2, 0x06 /* Public */,
       9,    0,  106,    2, 0x06 /* Public */,
      10,    0,  107,    2, 0x06 /* Public */,
      11,    0,  108,    2, 0x06 /* Public */,
      12,    0,  109,    2, 0x06 /* Public */,
      13,    0,  110,    2, 0x06 /* Public */,
      14,    0,  111,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    0,  112,    2, 0x08 /* Private */,
      16,    0,  113,    2, 0x08 /* Private */,
      17,    0,  114,    2, 0x08 /* Private */,
      18,    0,  115,    2, 0x08 /* Private */,

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
        case 5: _t->DEFpackAdd(); break;
        case 6: _t->RFRpackAdd(); break;
        case 7: _t->RCNpackAdd(); break;
        case 8: _t->GFIpackAdd(); break;
        case 9: _t->AFIpackAdd(); break;
        case 10: _t->DFIpackAdd(); break;
        case 11: _t->disconnected(); break;
        case 12: _t->reconnected(); break;
        case 13: _t->read_handler(); break;
        case 14: _t->HBTpackHandler(); break;
        case 15: _t->reconnect(); break;
        case 16: _t->relogin(); break;
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
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpConnect::DEFpackAdd)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (TcpConnect::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpConnect::RFRpackAdd)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (TcpConnect::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpConnect::RCNpackAdd)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (TcpConnect::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpConnect::GFIpackAdd)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (TcpConnect::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpConnect::AFIpackAdd)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (TcpConnect::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpConnect::DFIpackAdd)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (TcpConnect::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpConnect::disconnected)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (TcpConnect::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpConnect::reconnected)) {
                *result = 12;
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
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
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
void TcpConnect::DEFpackAdd()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void TcpConnect::RFRpackAdd()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void TcpConnect::RCNpackAdd()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void TcpConnect::GFIpackAdd()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void TcpConnect::AFIpackAdd()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void TcpConnect::DFIpackAdd()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void TcpConnect::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void TcpConnect::reconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
