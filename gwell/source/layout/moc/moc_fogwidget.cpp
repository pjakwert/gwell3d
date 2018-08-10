/****************************************************************************
** FogWidget meta object code from reading C++ file 'fogwidget.h'
**
** Created: Wed Oct 13 20:05:22 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../toolwidgets/fogwidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *FogWidget::className() const
{
    return "FogWidget";
}

QMetaObject *FogWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_FogWidget( "FogWidget", &FogWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString FogWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "FogWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString FogWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "FogWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* FogWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ 0, &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"fogToggled", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"fogModeChanged", 1, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ 0, &static_QUType_ptr, "float", QUParameter::In }
    };
    static const QUMethod slot_2 = {"fogDensityChanged", 1, param_slot_2 };
    static const QUParameter param_slot_3[] = {
	{ 0, &static_QUType_ptr, "float", QUParameter::In }
    };
    static const QUMethod slot_3 = {"fogStartChanged", 1, param_slot_3 };
    static const QUParameter param_slot_4[] = {
	{ 0, &static_QUType_ptr, "float", QUParameter::In }
    };
    static const QUMethod slot_4 = {"fogEndChanged", 1, param_slot_4 };
    static const QUParameter param_slot_5[] = {
	{ "color", &static_QUType_varptr, "\x0a", QUParameter::In },
	{ "alpha", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_5 = {"fogColorChanged", 2, param_slot_5 };
    static const QUMethod slot_6 = {"getBackgroundColor", 0, 0 };
    static const QUMethod slot_7 = {"updateWidgets", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "fogToggled(bool)", &slot_0, QMetaData::Private },
	{ "fogModeChanged(int)", &slot_1, QMetaData::Private },
	{ "fogDensityChanged(float)", &slot_2, QMetaData::Private },
	{ "fogStartChanged(float)", &slot_3, QMetaData::Private },
	{ "fogEndChanged(float)", &slot_4, QMetaData::Private },
	{ "fogColorChanged(const QColor&,int)", &slot_5, QMetaData::Private },
	{ "getBackgroundColor()", &slot_6, QMetaData::Private },
	{ "updateWidgets()", &slot_7, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ "fog", &static_QUType_ptr, "FogStruct", QUParameter::In },
	{ "whichParamChanged", &static_QUType_ptr, "FogParamsEnum", QUParameter::In }
    };
    static const QUMethod signal_0 = {"fogChanged", 2, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "fogChanged(FogStruct*,FogParamsEnum)", &signal_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"FogWidget", parentObject,
	slot_tbl, 8,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_FogWidget.setMetaObject( metaObj );
    return metaObj;
}

void* FogWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "FogWidget" ) )
	return this;
    return QWidget::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL fogChanged
void FogWidget::fogChanged( FogStruct* t0, FogParamsEnum t1 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 0 );
    if ( !clist )
	return;
    QUObject o[3];
    static_QUType_ptr.set(o+1,t0);
    static_QUType_ptr.set(o+2,&t1);
    activate_signal( clist, o );
}

bool FogWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: fogToggled((bool)static_QUType_bool.get(_o+1)); break;
    case 1: fogModeChanged((int)static_QUType_int.get(_o+1)); break;
    case 2: fogDensityChanged((float)(*((float*)static_QUType_ptr.get(_o+1)))); break;
    case 3: fogStartChanged((float)(*((float*)static_QUType_ptr.get(_o+1)))); break;
    case 4: fogEndChanged((float)(*((float*)static_QUType_ptr.get(_o+1)))); break;
    case 5: fogColorChanged((const QColor&)*((const QColor*)static_QUType_ptr.get(_o+1)),(int)static_QUType_int.get(_o+2)); break;
    case 6: getBackgroundColor(); break;
    case 7: updateWidgets(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool FogWidget::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: fogChanged((FogStruct*)static_QUType_ptr.get(_o+1),(FogParamsEnum)(*((FogParamsEnum*)static_QUType_ptr.get(_o+2)))); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool FogWidget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool FogWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
