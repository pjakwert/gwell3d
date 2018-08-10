/****************************************************************************
** HelpWidget meta object code from reading C++ file 'helpwidget.h'
**
** Created: Fri Oct 8 13:53:13 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../toolwidgets/helpwidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *HelpWidget::className() const
{
    return "HelpWidget";
}

QMetaObject *HelpWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_HelpWidget( "HelpWidget", &HelpWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString HelpWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "HelpWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString HelpWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "HelpWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* HelpWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"aboutApp", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "aboutApp()", &slot_0, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"HelpWidget", parentObject,
	slot_tbl, 1,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_HelpWidget.setMetaObject( metaObj );
    return metaObj;
}

void* HelpWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "HelpWidget" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool HelpWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: aboutApp(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool HelpWidget::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool HelpWidget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool HelpWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
