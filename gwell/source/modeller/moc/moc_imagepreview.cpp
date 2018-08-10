/****************************************************************************
** ImagePreview meta object code from reading C++ file 'imagepreview.h'
**
** Created: Fri Oct 8 13:47:21 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../dialogs/imagepreview.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *ImagePreview::className() const
{
    return "ImagePreview";
}

QMetaObject *ImagePreview::metaObj = 0;
static QMetaObjectCleanUp cleanUp_ImagePreview( "ImagePreview", &ImagePreview::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString ImagePreview::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ImagePreview", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString ImagePreview::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ImagePreview", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* ImagePreview::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QFrame::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"ImagePreview", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_ImagePreview.setMetaObject( metaObj );
    return metaObj;
}

void* ImagePreview::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "ImagePreview" ) )
	return this;
    if ( !qstrcmp( clname, "QFilePreview" ) )
	return (QFilePreview*)this;
    return QFrame::qt_cast( clname );
}

bool ImagePreview::qt_invoke( int _id, QUObject* _o )
{
    return QFrame::qt_invoke(_id,_o);
}

bool ImagePreview::qt_emit( int _id, QUObject* _o )
{
    return QFrame::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool ImagePreview::qt_property( int id, int f, QVariant* v)
{
    return QFrame::qt_property( id, f, v);
}

bool ImagePreview::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
