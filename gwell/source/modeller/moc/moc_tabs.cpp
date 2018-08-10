/****************************************************************************
** Tabs meta object code from reading C++ file 'tabs.h'
**
** Created: Fri Oct 8 13:46:17 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../tabs.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *Tabs::className() const
{
    return "Tabs";
}

QMetaObject *Tabs::metaObj = 0;
static QMetaObjectCleanUp cleanUp_Tabs( "Tabs", &Tabs::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString Tabs::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Tabs", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString Tabs::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Tabs", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* Tabs::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QTabBar::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"Tabs", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_Tabs.setMetaObject( metaObj );
    return metaObj;
}

void* Tabs::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "Tabs" ) )
	return this;
    return QTabBar::qt_cast( clname );
}

bool Tabs::qt_invoke( int _id, QUObject* _o )
{
    return QTabBar::qt_invoke(_id,_o);
}

bool Tabs::qt_emit( int _id, QUObject* _o )
{
    return QTabBar::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool Tabs::qt_property( int id, int f, QVariant* v)
{
    return QTabBar::qt_property( id, f, v);
}

bool Tabs::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
