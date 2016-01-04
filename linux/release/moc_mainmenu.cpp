/****************************************************************************
** Meta object code from reading C++ file 'mainmenu.h'
**
** Created: Wed Jul 11 06:27:16 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/mainmenu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainmenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainMenu[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      24,    9,    9,    9, 0x08,
      56,    9,    9,    9, 0x08,
      80,    9,    9,    9, 0x08,
     105,    9,    9,    9, 0x08,
     131,    9,    9,    9, 0x08,
     155,    9,    9,    9, 0x08,
     182,    9,    9,    9, 0x08,
     206,    9,    9,    9, 0x08,
     221,    9,    9,    9, 0x08,
     241,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainMenu[] = {
    "MainMenu\0\0moveSquares()\0"
    "on_releasenotesButton_clicked()\0"
    "on_exitButton_clicked()\0"
    "on_scoreButton_clicked()\0"
    "on_donateButton_clicked()\0"
    "on_helpButton_clicked()\0"
    "on_creditsButton_clicked()\0"
    "on_playButton_clicked()\0fetchVersion()\0"
    "fetchReleaseNotes()\0replyFinished(QNetworkReply*)\0"
};

void MainMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainMenu *_t = static_cast<MainMenu *>(_o);
        switch (_id) {
        case 0: _t->moveSquares(); break;
        case 1: _t->on_releasenotesButton_clicked(); break;
        case 2: _t->on_exitButton_clicked(); break;
        case 3: _t->on_scoreButton_clicked(); break;
        case 4: _t->on_donateButton_clicked(); break;
        case 5: _t->on_helpButton_clicked(); break;
        case 6: _t->on_creditsButton_clicked(); break;
        case 7: _t->on_playButton_clicked(); break;
        case 8: _t->fetchVersion(); break;
        case 9: _t->fetchReleaseNotes(); break;
        case 10: _t->replyFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainMenu::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainMenu::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainMenu,
      qt_meta_data_MainMenu, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainMenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainMenu))
        return static_cast<void*>(const_cast< MainMenu*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
