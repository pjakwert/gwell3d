/****************************************************************************
** TranslateModifier meta object code from reading C++ file 'm_trans.h'
**
** Created: Wed Oct 13 20:02:39 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../modifiers/m_trans.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *TranslateModifier::className() const
{
    return "TranslateModifier";
}

QMetaObject *TranslateModifier::metaObj = 0;
static QMetaObjectCleanUp cleanUp_TranslateModifier( "TranslateModifier", &TranslateModifier::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString TranslateModifier::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "TranslateModifier", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString TranslateModifier::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "TranslateModifier", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* TranslateModifier::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = MModifier::staticMetaObject();
    static const QUParameter param_signal_0[] = {
	{ "mType", &static_QUType_ptr, "MModifier::ModifierType", QUParameter::In },
	{ "v", &static_QUType_ptr, "Vector3f", QUParameter::In }
    };
    static const QUMethod signal_0 = {"vectorChanged", 2, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "vectorChanged(MModifier::ModifierType,Vector3f)", &signal_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"TranslateModifier", parentObject,
	0, 0,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_TranslateModifier.setMetaObject( metaObj );
    return metaObj;
}

void* TranslateModifier::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "TranslateModifier" ) )
	return this;
    return MModifier::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL vectorChanged
void TranslateModifier::vectorChanged( MModifier::ModifierType t0, Vector3f t1 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 0 );
    if ( !clist )
	return;
    QUObject o[3];
    static_QUType_ptr.set(o+1,&t0);
    static_QUType_ptr.set(o+2,&t1);
    activate_signal( clist, o );
}

bool TranslateModifier::qt_invoke( int _id, QUObject* _o )
{
    return MModifier::qt_invoke(_id,_o);
}

bool TranslateModifier::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: vectorChanged((MModifier::ModifierType)(*((MModifier::ModifierType*)static_QUType_ptr.get(_o+1))),(Vector3f)(*((Vector3f*)static_QUType_ptr.get(_o+2)))); break;
    default:
	return MModifier::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool TranslateModifier::qt_property( int id, int f, QVariant* v)
{
    return MModifier::qt_property( id, f, v);
}

bool TranslateModifier::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
