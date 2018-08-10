/****************************************************************************
** Knob meta object code from reading C++ file 'knob.h'
**
** Created: Fri Oct 8 13:48:39 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../dialogs/knob.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *Knob::className() const
{
    return "Knob";
}

QMetaObject *Knob::metaObj = 0;
static QMetaObjectCleanUp cleanUp_Knob( "Knob", &Knob::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString Knob::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Knob", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString Knob::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Knob", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* Knob::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QwtKnob::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "controlItem", &static_QUType_ptr, "ViKinemCtrlItem", QUParameter::In }
    };
    static const QUMethod slot_0 = {"setRangeFromItem", 1, param_slot_0 };
    static const QMetaData slot_tbl[] = {
	{ "setRangeFromItem(ViKinemCtrlItem*)", &slot_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"Knob", parentObject,
	slot_tbl, 1,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_Knob.setMetaObject( metaObj );
    return metaObj;
}

void* Knob::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "Knob" ) )
	return this;
    return QwtKnob::qt_cast( clname );
}

bool Knob::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: setRangeFromItem((ViKinemCtrlItem*)static_QUType_ptr.get(_o+1)); break;
    default:
	return QwtKnob::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool Knob::qt_emit( int _id, QUObject* _o )
{
    return QwtKnob::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool Knob::qt_property( int id, int f, QVariant* v)
{
    return QwtKnob::qt_property( id, f, v);
}

bool Knob::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
