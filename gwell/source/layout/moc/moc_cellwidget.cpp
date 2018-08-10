/****************************************************************************
** CellWidget meta object code from reading C++ file 'cellwidget.h'
**
** Created: Wed Oct 13 20:00:23 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../cellwidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *CellWidget::className() const
{
    return "CellWidget";
}

QMetaObject *CellWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_CellWidget( "CellWidget", &CellWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString CellWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "CellWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString CellWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "CellWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* CellWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QFrame::staticMetaObject();
    static const QUMethod slot_0 = {"toggleVisibility", 0, 0 };
    static const QUMethod slot_1 = {"hidePrivateButtons", 0, 0 };
    static const QUParameter param_slot_2[] = {
	{ "on", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"cameraToggled", 1, param_slot_2 };
    static const QUMethod slot_3 = {"showAll", 0, 0 };
    static const QUParameter param_slot_4[] = {
	{ "on", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"gridToggled", 1, param_slot_4 };
    static const QUParameter param_slot_5[] = {
	{ "on", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_5 = {"axisToggled", 1, param_slot_5 };
    static const QUParameter param_slot_6[] = {
	{ "on", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_6 = {"boxesToggled", 1, param_slot_6 };
    static const QUParameter param_slot_7[] = {
	{ "on", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_7 = {"lightsToggled", 1, param_slot_7 };
    static const QUParameter param_slot_8[] = {
	{ "direction", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_8 = {"viewDirChanged", 1, param_slot_8 };
    static const QUParameter param_slot_9[] = {
	{ "viewType", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_9 = {"viewTypeChanged", 1, param_slot_9 };
    static const QUParameter param_slot_10[] = {
	{ "viewProj", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_10 = {"viewProjChanged", 1, param_slot_10 };
    static const QUMethod slot_11 = {"screenshotClicked", 0, 0 };
    static const QUMethod slot_12 = {"maximizeClicked", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "toggleVisibility()", &slot_0, QMetaData::Public },
	{ "hidePrivateButtons()", &slot_1, QMetaData::Public },
	{ "cameraToggled(bool)", &slot_2, QMetaData::Private },
	{ "showAll()", &slot_3, QMetaData::Private },
	{ "gridToggled(bool)", &slot_4, QMetaData::Private },
	{ "axisToggled(bool)", &slot_5, QMetaData::Private },
	{ "boxesToggled(bool)", &slot_6, QMetaData::Private },
	{ "lightsToggled(bool)", &slot_7, QMetaData::Private },
	{ "viewDirChanged(int)", &slot_8, QMetaData::Private },
	{ "viewTypeChanged(int)", &slot_9, QMetaData::Private },
	{ "viewProjChanged(int)", &slot_10, QMetaData::Private },
	{ "screenshotClicked()", &slot_11, QMetaData::Private },
	{ "maximizeClicked()", &slot_12, QMetaData::Private }
    };
    static const QUParameter param_signal_0[] = {
	{ "on", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"moveCamera", 1, param_signal_0 };
    static const QUMethod signal_1 = {"showEntireScene", 0, 0 };
    static const QUParameter param_signal_2[] = {
	{ "on", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod signal_2 = {"showGrid", 1, param_signal_2 };
    static const QUParameter param_signal_3[] = {
	{ "on", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod signal_3 = {"showAxis", 1, param_signal_3 };
    static const QUParameter param_signal_4[] = {
	{ "on", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod signal_4 = {"showBoxes", 1, param_signal_4 };
    static const QUParameter param_signal_5[] = {
	{ "on", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod signal_5 = {"showLights", 1, param_signal_5 };
    static const QUParameter param_signal_6[] = {
	{ "direction", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_6 = {"viewDirectionChanged", 1, param_signal_6 };
    static const QUParameter param_signal_7[] = {
	{ "type", &static_QUType_ptr, "DrawMethod", QUParameter::In }
    };
    static const QUMethod signal_7 = {"setViewType", 1, param_signal_7 };
    static const QUParameter param_signal_8[] = {
	{ "type", &static_QUType_ptr, "qglviewer::Camera::Type", QUParameter::In }
    };
    static const QUMethod signal_8 = {"setProjType", 1, param_signal_8 };
    static const QUMethod signal_9 = {"makeScreenshot", 0, 0 };
    static const QUMethod signal_10 = {"maximize", 0, 0 };
    static const QMetaData signal_tbl[] = {
	{ "moveCamera(bool)", &signal_0, QMetaData::Private },
	{ "showEntireScene()", &signal_1, QMetaData::Private },
	{ "showGrid(bool)", &signal_2, QMetaData::Private },
	{ "showAxis(bool)", &signal_3, QMetaData::Private },
	{ "showBoxes(bool)", &signal_4, QMetaData::Private },
	{ "showLights(bool)", &signal_5, QMetaData::Private },
	{ "viewDirectionChanged(int)", &signal_6, QMetaData::Private },
	{ "setViewType(DrawMethod)", &signal_7, QMetaData::Private },
	{ "setProjType(qglviewer::Camera::Type)", &signal_8, QMetaData::Private },
	{ "makeScreenshot()", &signal_9, QMetaData::Private },
	{ "maximize()", &signal_10, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"CellWidget", parentObject,
	slot_tbl, 13,
	signal_tbl, 11,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_CellWidget.setMetaObject( metaObj );
    return metaObj;
}

void* CellWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "CellWidget" ) )
	return this;
    return QFrame::qt_cast( clname );
}

// SIGNAL moveCamera
void CellWidget::moveCamera( bool t0 )
{
    activate_signal_bool( staticMetaObject()->signalOffset() + 0, t0 );
}

// SIGNAL showEntireScene
void CellWidget::showEntireScene()
{
    activate_signal( staticMetaObject()->signalOffset() + 1 );
}

// SIGNAL showGrid
void CellWidget::showGrid( bool t0 )
{
    activate_signal_bool( staticMetaObject()->signalOffset() + 2, t0 );
}

// SIGNAL showAxis
void CellWidget::showAxis( bool t0 )
{
    activate_signal_bool( staticMetaObject()->signalOffset() + 3, t0 );
}

// SIGNAL showBoxes
void CellWidget::showBoxes( bool t0 )
{
    activate_signal_bool( staticMetaObject()->signalOffset() + 4, t0 );
}

// SIGNAL showLights
void CellWidget::showLights( bool t0 )
{
    activate_signal_bool( staticMetaObject()->signalOffset() + 5, t0 );
}

// SIGNAL viewDirectionChanged
void CellWidget::viewDirectionChanged( int t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 6, t0 );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL setViewType
void CellWidget::setViewType( DrawMethod t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 7 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_ptr.set(o+1,&t0);
    activate_signal( clist, o );
}

// SIGNAL setProjType
void CellWidget::setProjType( qglviewer::Camera::Type t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 8 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_ptr.set(o+1,&t0);
    activate_signal( clist, o );
}

// SIGNAL makeScreenshot
void CellWidget::makeScreenshot()
{
    activate_signal( staticMetaObject()->signalOffset() + 9 );
}

// SIGNAL maximize
void CellWidget::maximize()
{
    activate_signal( staticMetaObject()->signalOffset() + 10 );
}

bool CellWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: toggleVisibility(); break;
    case 1: hidePrivateButtons(); break;
    case 2: cameraToggled((bool)static_QUType_bool.get(_o+1)); break;
    case 3: showAll(); break;
    case 4: gridToggled((bool)static_QUType_bool.get(_o+1)); break;
    case 5: axisToggled((bool)static_QUType_bool.get(_o+1)); break;
    case 6: boxesToggled((bool)static_QUType_bool.get(_o+1)); break;
    case 7: lightsToggled((bool)static_QUType_bool.get(_o+1)); break;
    case 8: viewDirChanged((int)static_QUType_int.get(_o+1)); break;
    case 9: viewTypeChanged((int)static_QUType_int.get(_o+1)); break;
    case 10: viewProjChanged((int)static_QUType_int.get(_o+1)); break;
    case 11: screenshotClicked(); break;
    case 12: maximizeClicked(); break;
    default:
	return QFrame::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool CellWidget::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: moveCamera((bool)static_QUType_bool.get(_o+1)); break;
    case 1: showEntireScene(); break;
    case 2: showGrid((bool)static_QUType_bool.get(_o+1)); break;
    case 3: showAxis((bool)static_QUType_bool.get(_o+1)); break;
    case 4: showBoxes((bool)static_QUType_bool.get(_o+1)); break;
    case 5: showLights((bool)static_QUType_bool.get(_o+1)); break;
    case 6: viewDirectionChanged((int)static_QUType_int.get(_o+1)); break;
    case 7: setViewType((DrawMethod)(*((DrawMethod*)static_QUType_ptr.get(_o+1)))); break;
    case 8: setProjType((qglviewer::Camera::Type)(*((qglviewer::Camera::Type*)static_QUType_ptr.get(_o+1)))); break;
    case 9: makeScreenshot(); break;
    case 10: maximize(); break;
    default:
	return QFrame::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool CellWidget::qt_property( int id, int f, QVariant* v)
{
    return QFrame::qt_property( id, f, v);
}

bool CellWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
