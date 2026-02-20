/****************************************************************************
** Meta object code from reading C++ file 'PersonItem.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../src/ui/PersonItem.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PersonItem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_ui__PersonItem_t {
    uint offsetsAndSizes[28];
    char stringdata0[15];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[19];
    char stringdata4[15];
    char stringdata5[14];
    char stringdata6[12];
    char stringdata7[8];
    char stringdata8[34];
    char stringdata9[14];
    char stringdata10[22];
    char stringdata11[16];
    char stringdata12[16];
    char stringdata13[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_ui__PersonItem_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_ui__PersonItem_t qt_meta_stringdata_ui__PersonItem = {
    {
        QT_MOC_LITERAL(0, 14),  // "ui::PersonItem"
        QT_MOC_LITERAL(15, 13),  // "requestAddSon"
        QT_MOC_LITERAL(29, 0),  // ""
        QT_MOC_LITERAL(30, 18),  // "requestAddDaughter"
        QT_MOC_LITERAL(49, 14),  // "requestAddWife"
        QT_MOC_LITERAL(64, 13),  // "requestRemove"
        QT_MOC_LITERAL(78, 11),  // "requestEdit"
        QT_MOC_LITERAL(90, 7),  // "clicked"
        QT_MOC_LITERAL(98, 33),  // "const core::entities::PersonN..."
        QT_MOC_LITERAL(132, 13),  // "infoRequested"
        QT_MOC_LITERAL(146, 21),  // "requestToggleCollapse"
        QT_MOC_LITERAL(168, 15),  // "requestRelayout"
        QT_MOC_LITERAL(184, 15),  // "positionChanged"
        QT_MOC_LITERAL(200, 6)   // "newPos"
    },
    "ui::PersonItem",
    "requestAddSon",
    "",
    "requestAddDaughter",
    "requestAddWife",
    "requestRemove",
    "requestEdit",
    "clicked",
    "const core::entities::PersonNode*",
    "infoRequested",
    "requestToggleCollapse",
    "requestRelayout",
    "positionChanged",
    "newPos"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_ui__PersonItem[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   74,    2, 0x06,    1 /* Public */,
       3,    0,   75,    2, 0x06,    2 /* Public */,
       4,    0,   76,    2, 0x06,    3 /* Public */,
       5,    0,   77,    2, 0x06,    4 /* Public */,
       6,    0,   78,    2, 0x06,    5 /* Public */,
       7,    1,   79,    2, 0x06,    6 /* Public */,
       9,    1,   82,    2, 0x06,    8 /* Public */,
      10,    1,   85,    2, 0x06,   10 /* Public */,
      11,    0,   88,    2, 0x06,   12 /* Public */,
      12,    2,   89,    2, 0x06,   13 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8, QMetaType::QPointF,    2,   13,

       0        // eod
};

Q_CONSTINIT const QMetaObject ui::PersonItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsObject::staticMetaObject>(),
    qt_meta_stringdata_ui__PersonItem.offsetsAndSizes,
    qt_meta_data_ui__PersonItem,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_ui__PersonItem_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<PersonItem, std::true_type>,
        // method 'requestAddSon'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'requestAddDaughter'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'requestAddWife'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'requestRemove'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'requestEdit'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const core::entities::PersonNode *, std::false_type>,
        // method 'infoRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const core::entities::PersonNode *, std::false_type>,
        // method 'requestToggleCollapse'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const core::entities::PersonNode *, std::false_type>,
        // method 'requestRelayout'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'positionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const core::entities::PersonNode *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPointF &, std::false_type>
    >,
    nullptr
} };

void ui::PersonItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PersonItem *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->requestAddSon(); break;
        case 1: _t->requestAddDaughter(); break;
        case 2: _t->requestAddWife(); break;
        case 3: _t->requestRemove(); break;
        case 4: _t->requestEdit(); break;
        case 5: _t->clicked((*reinterpret_cast< std::add_pointer_t<const core::entities::PersonNode*>>(_a[1]))); break;
        case 6: _t->infoRequested((*reinterpret_cast< std::add_pointer_t<const core::entities::PersonNode*>>(_a[1]))); break;
        case 7: _t->requestToggleCollapse((*reinterpret_cast< std::add_pointer_t<const core::entities::PersonNode*>>(_a[1]))); break;
        case 8: _t->requestRelayout(); break;
        case 9: _t->positionChanged((*reinterpret_cast< std::add_pointer_t<const core::entities::PersonNode*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QPointF>>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PersonItem::*)();
            if (_t _q_method = &PersonItem::requestAddSon; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PersonItem::*)();
            if (_t _q_method = &PersonItem::requestAddDaughter; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PersonItem::*)();
            if (_t _q_method = &PersonItem::requestAddWife; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PersonItem::*)();
            if (_t _q_method = &PersonItem::requestRemove; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PersonItem::*)();
            if (_t _q_method = &PersonItem::requestEdit; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (PersonItem::*)(const core::entities::PersonNode * );
            if (_t _q_method = &PersonItem::clicked; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (PersonItem::*)(const core::entities::PersonNode * );
            if (_t _q_method = &PersonItem::infoRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (PersonItem::*)(const core::entities::PersonNode * );
            if (_t _q_method = &PersonItem::requestToggleCollapse; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (PersonItem::*)();
            if (_t _q_method = &PersonItem::requestRelayout; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (PersonItem::*)(const core::entities::PersonNode * , const QPointF & );
            if (_t _q_method = &PersonItem::positionChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
    }
}

const QMetaObject *ui::PersonItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::PersonItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__PersonItem.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsObject::qt_metacast(_clname);
}

int ui::PersonItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void ui::PersonItem::requestAddSon()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ui::PersonItem::requestAddDaughter()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ui::PersonItem::requestAddWife()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ui::PersonItem::requestRemove()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ui::PersonItem::requestEdit()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void ui::PersonItem::clicked(const core::entities::PersonNode * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ui::PersonItem::infoRequested(const core::entities::PersonNode * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ui::PersonItem::requestToggleCollapse(const core::entities::PersonNode * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ui::PersonItem::requestRelayout()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void ui::PersonItem::positionChanged(const core::entities::PersonNode * _t1, const QPointF & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
