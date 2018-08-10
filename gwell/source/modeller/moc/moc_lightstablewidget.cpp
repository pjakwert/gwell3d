/****************************************************************************
** LightsTableWidget meta object code from reading C++ file 'lightstablewidget.h'
**
** Created: Fri Oct 8 13:51:56 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../toolwidgets/lightstablewidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *LightsTableWidget::className() const
{
    return "LightsTableWidget";
}

QMetaObject *LightsTableWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_LightsTableWidget( "LightsTableWidget", &LightsTableWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString LightsTableWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "LightsTableWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString LightsTableWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "LightsTableWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* LightsTableWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QTable::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "lightsList", &static_QUType_ptr, "QPtrList<Light>", QUParameter::In }
    };
    static const QUMethod slot_0 = {"setLightsList", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ "bulbOrSpotlight", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"addLight", 1, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ "bulbOrSpotlight", &static_QUType_int, 0, QUParameter::In },
	{ "isMovingWithCamera", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"addLight", 2, param_slot_2 };
    static const QUMethod slot_3 = {"deleteLight", 0, 0 };
    static const QUParameter param_slot_4[] = {
	{ 0, &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"toggleLight", 1, param_slot_4 };
    static const QUParameter param_slot_5[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_5 = {"bulbOrSpotChanged", 1, param_slot_5 };
    static const QUParameter param_slot_6[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In },
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_6 = {"currentLightChanged", 2, param_slot_6 };
    static const QUParameter param_slot_7[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In },
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_7 = {"userChangedName", 2, param_slot_7 };
    static const QMetaData slot_tbl[] = {
	{ "setLightsList(QPtrList<Light>*)", &slot_0, QMetaData::Public },
	{ "addLight(int)", &slot_1, QMetaData::Public },
	{ "addLight(int,bool)", &slot_2, QMetaData::Public },
	{ "deleteLight()", &slot_3, QMetaData::Public },
	{ "toggleLight(bool)", &slot_4, QMetaData::Private },
	{ "bulbOrSpotChanged(int)", &slot_5, QMetaData::Private },
	{ "currentLightChanged(int,int)", &slot_6, QMetaData::Private },
	{ "userChangedName(int,int)", &slot_7, QMetaData::Private }
    };
    static const QUParameter param_signal_0[] = {
	{ "light", &static_QUType_ptr, "Light", QUParameter::In }
    };
    static const QUMethod signal_0 = {"lightSelected", 1, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ "light", &static_QUType_ptr, "Light", QUParameter::In }
    };
    static const QUMethod signal_1 = {"lightParamsChanged", 1, param_signal_1 };
    static const QUMethod signal_2 = {"lightRemoved", 0, 0 };
    static const QUMethod signal_3 = {"lightAdded", 0, 0 };
    static const QMetaData signal_tbl[] = {
	{ "lightSelected(Light*)", &signal_0, QMetaData::Private },
	{ "lightParamsChanged(Light*)", &signal_1, QMetaData::Private },
	{ "lightRemoved()", &signal_2, QMetaData::Private },
	{ "lightAdded()", &signal_3, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"LightsTableWidget", parentObject,
	slot_tbl, 8,
	signal_tbl, 4,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_LightsTableWidget.setMetaObject( metaObj );
    return metaObj;
}

void* LightsTableWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "LightsTableWidget" ) )
	return this;
    return QTable::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL lightSelected
void LightsTableWidget::lightSelected( Light* t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 0 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_ptr.set(o+1,t0);
    activate_signal( clist, o );
}

// SIGNAL lightParamsChanged
void LightsTableWidget::lightParamsChanged( Light* t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 1 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_ptr.set(o+1,t0);
    activate_signal( clist, o );
}

// SIGNAL lightRemoved
void LightsTableWidget::lightRemoved()
{
    activate_signal( staticMetaObject()->signalOffset() + 2 );
}

// SIGNAL lightAdded
void LightsTableWidget::lightAdded()
{
    activate_signal( staticMetaObject()->signalOffset() + 3 );
}

bool LightsTableWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: setLightsList((QPtrList<Light>*)static_QUType_ptr.get(_o+1)); break;
    case 1: addLight((int)static_QUType_int.get(_o+1)); break;
    case 2: addLight((int)static_QUType_int.get(_o+1),(bool)static_QUType_bool.get(_o+2)); break;
    case 3: deleteLight(); break;
    case 4: toggleLight((bool)static_QUType_bool.get(_o+1)); break;
    case 5: bulbOrSpotChanged((int)static_QUType_int.get(_o+1)); break;
    case 6: currentLightChanged((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 7: userChangedName((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    default:
	return QTable::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool LightsTableWidget::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: lightSelected((Light*)static_QUType_ptr.get(_o+1)); break;
    case 1: lightParamsChanged((Light*)static_QUType_ptr.get(_o+1)); break;
    case 2: lightRemoved(); break;
    case 3: lightAdded(); break;
    default:
	return QTable::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool LightsTableWidget::qt_property( int id, int f, QVariant* v)
{
    return QTable::qt_property( id, f, v);
}

bool LightsTableWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
