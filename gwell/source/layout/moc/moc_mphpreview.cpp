/****************************************************************************
** MphPreview meta object code from reading C++ file 'mphpreview.h'
**
** Created: Wed Oct 13 20:05:28 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../toolwidgets/mphpreview.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MphPreview::className() const
{
    return "MphPreview";
}

QMetaObject *MphPreview::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MphPreview( "MphPreview", &MphPreview::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString MphPreview::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MphPreview", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MphPreview::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MphPreview", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MphPreview::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QFrame::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"MphPreview", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_MphPreview.setMetaObject( metaObj );
    return metaObj;
}

void* MphPreview::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "MphPreview" ) )
	return this;
    if ( !qstrcmp( clname, "QFilePreview" ) )
	return (QFilePreview*)this;
    return QFrame::qt_cast( clname );
}

bool MphPreview::qt_invoke( int _id, QUObject* _o )
{
    return QFrame::qt_invoke(_id,_o);
}

bool MphPreview::qt_emit( int _id, QUObject* _o )
{
    return QFrame::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool MphPreview::qt_property( int id, int f, QVariant* v)
{
    return QFrame::qt_property( id, f, v);
}

bool MphPreview::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
