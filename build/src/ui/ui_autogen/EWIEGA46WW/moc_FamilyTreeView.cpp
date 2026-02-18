/****************************************************************************
** Meta object code from reading C++ file 'FamilyTreeView.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../src/ui/FamilyTreeView.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FamilyTreeView.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_ui__FamilyTreeView_t {
    uint offsetsAndSizes[18];
    char stringdata0[19];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[34];
    char stringdata4[22];
    char stringdata5[27];
    char stringdata6[23];
    char stringdata7[22];
    char stringdata8[20];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_ui__FamilyTreeView_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_ui__FamilyTreeView_t qt_meta_stringdata_ui__FamilyTreeView = {
    {
        QT_MOC_LITERAL(0, 18),  // "ui::FamilyTreeView"
        QT_MOC_LITERAL(19, 13),  // "personClicked"
        QT_MOC_LITERAL(33, 0),  // ""
        QT_MOC_LITERAL(34, 33),  // "const core::entities::PersonN..."
        QT_MOC_LITERAL(68, 21),  // "personAddSonRequested"
        QT_MOC_LITERAL(90, 26),  // "personAddDaughterRequested"
        QT_MOC_LITERAL(117, 22),  // "personAddWifeRequested"
        QT_MOC_LITERAL(140, 21),  // "personRemoveRequested"
        QT_MOC_LITERAL(162, 19)   // "personEditRequested"
    },
    "ui::FamilyTreeView",
    "personClicked",
    "",
    "const core::entities::PersonNode*",
    "personAddSonRequested",
    "personAddDaughterRequested",
    "personAddWifeRequested",
    "personRemoveRequested",
    "personEditRequested"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_ui__FamilyTreeView[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   50,    2, 0x06,    1 /* Public */,
       4,    2,   53,    2, 0x06,    3 /* Public */,
       5,    2,   58,    2, 0x06,    6 /* Public */,
       6,    1,   63,    2, 0x06,    9 /* Public */,
       7,    1,   66,    2, 0x06,   11 /* Public */,
       8,    1,   69,    2, 0x06,   13 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    2,    2,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    2,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

Q_CONSTINIT const QMetaObject ui::FamilyTreeView::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsView::staticMetaObject>(),
    qt_meta_stringdata_ui__FamilyTreeView.offsetsAndSizes,
    qt_meta_data_ui__FamilyTreeView,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_ui__FamilyTreeView_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<FamilyTreeView, std::true_type>,
        // method 'personClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const core::entities::PersonNode *, std::false_type>,
        // method 'personAddSonRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const core::entities::PersonNode *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const core::entities::PersonNode *, std::false_type>,
        // method 'personAddDaughterRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const core::entities::PersonNode *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const core::entities::PersonNode *, std::false_type>,
        // method 'personAddWifeRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const core::entities::PersonNode *, std::false_type>,
        // method 'personRemoveRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const core::entities::PersonNode *, std::false_type>,
        // method 'personEditRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const core::entities::PersonNode *, std::false_type>
    >,
    nullptr
} };

void ui::FamilyTreeView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FamilyTreeView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->personClicked((*reinterpret_cast< std::add_pointer_t<const core::entities::PersonNode*>>(_a[1]))); break;
        case 1: _t->personAddSonRequested((*reinterpret_cast< std::add_pointer_t<const core::entities::PersonNode*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<const core::entities::PersonNode*>>(_a[2]))); break;
        case 2: _t->personAddDaughterRequested((*reinterpret_cast< std::add_pointer_t<const core::entities::PersonNode*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<const core::entities::PersonNode*>>(_a[2]))); break;
        case 3: _t->personAddWifeRequested((*reinterpret_cast< std::add_pointer_t<const core::entities::PersonNode*>>(_a[1]))); break;
        case 4: _t->personRemoveRequested((*reinterpret_cast< std::add_pointer_t<const core::entities::PersonNode*>>(_a[1]))); break;
        case 5: _t->personEditRequested((*reinterpret_cast< std::add_pointer_t<const core::entities::PersonNode*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FamilyTreeView::*)(const core::entities::PersonNode * );
            if (_t _q_method = &FamilyTreeView::personClicked; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FamilyTreeView::*)(const core::entities::PersonNode * , const core::entities::PersonNode * );
            if (_t _q_method = &FamilyTreeView::personAddSonRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FamilyTreeView::*)(const core::entities::PersonNode * , const core::entities::PersonNode * );
            if (_t _q_method = &FamilyTreeView::personAddDaughterRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (FamilyTreeView::*)(const core::entities::PersonNode * );
            if (_t _q_method = &FamilyTreeView::personAddWifeRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (FamilyTreeView::*)(const core::entities::PersonNode * );
            if (_t _q_method = &FamilyTreeView::personRemoveRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (FamilyTreeView::*)(const core::entities::PersonNode * );
            if (_t _q_method = &FamilyTreeView::personEditRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject *ui::FamilyTreeView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::FamilyTreeView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__FamilyTreeView.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsView::qt_metacast(_clname);
}

int ui::FamilyTreeView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ui::FamilyTreeView::personClicked(const core::entities::PersonNode * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::FamilyTreeView::personAddSonRequested(const core::entities::PersonNode * _t1, const core::entities::PersonNode * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::FamilyTreeView::personAddDaughterRequested(const core::entities::PersonNode * _t1, const core::entities::PersonNode * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ui::FamilyTreeView::personAddWifeRequested(const core::entities::PersonNode * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ui::FamilyTreeView::personRemoveRequested(const core::entities::PersonNode * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ui::FamilyTreeView::personEditRequested(const core::entities::PersonNode * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
