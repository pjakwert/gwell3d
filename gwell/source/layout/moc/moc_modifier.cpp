/****************************************************************************
** MModifier meta object code from reading C++ file 'modifier.h'
**
** Created: Wed Oct 13 20:03:10 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../modifiers/modifier.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MModifier::className() const
{
    return "MModifier";
}

QMetaObject *MModifier::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MModifier( "MModifier", &MModifier::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString MModifier::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MModifier", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MModifier::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MModifier", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MModifier::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QObject::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"MModifier", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_MModifier.setMetaObject( metaObj );
    return metaObj;
}

void* MModifier::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "MModifier" ) )
	return this;
    return QObject::qt_cast( clname );
}

bool MModifier::qt_invoke( int _id, QUObject* _o )
{
    return QObject::qt_invoke(_id,_o);
}

bool MModifier::qt_emit( int _id, QUObject* _o )
{
    return QObject::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool MModifier::qt_property( int id, int f, QVariant* v)
{
    return QObject::qt_property( id, f, v);
}

bool MModifier::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
