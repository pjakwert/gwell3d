/****************************************************************************
** StartWidget meta object code from reading C++ file 'startwidget.h'
**
** Created: Wed Oct 13 20:00:52 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../startwidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *StartWidget::className() const
{
    return "StartWidget";
}

QMetaObject *StartWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_StartWidget( "StartWidget", &StartWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString StartWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "StartWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString StartWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "StartWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* StartWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod signal_0 = {"clicked", 0, 0 };
    static const QMetaData signal_tbl[] = {
	{ "clicked()", &signal_0, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"StartWidget", parentObject,
	0, 0,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_StartWidget.setMetaObject( metaObj );
    return metaObj;
}

void* StartWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "StartWidget" ) )
	return this;
    return QWidget::qt_cast( clname );
}

// SIGNAL clicked
void StartWidget::clicked()
{
    activate_signal( staticMetaObject()->signalOffset() + 0 );
}

bool StartWidget::qt_invoke( int _id, QUObject* _o )
{
    return QWidget::qt_invoke(_id,_o);
}

bool StartWidget::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: clicked(); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool StartWidget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool StartWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
