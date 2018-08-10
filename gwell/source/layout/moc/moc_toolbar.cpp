/****************************************************************************
** ToolBar meta object code from reading C++ file 'toolbar.h'
**
** Created: Wed Oct 13 20:01:04 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../toolbar.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *ToolBar::className() const
{
    return "ToolBar";
}

QMetaObject *ToolBar::metaObj = 0;
static QMetaObjectCleanUp cleanUp_ToolBar( "ToolBar", &ToolBar::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString ToolBar::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ToolBar", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString ToolBar::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ToolBar", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* ToolBar::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"ToolBar", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_ToolBar.setMetaObject( metaObj );
    return metaObj;
}

void* ToolBar::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "ToolBar" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool ToolBar::qt_invoke( int _id, QUObject* _o )
{
    return QWidget::qt_invoke(_id,_o);
}

bool ToolBar::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool ToolBar::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool ToolBar::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
