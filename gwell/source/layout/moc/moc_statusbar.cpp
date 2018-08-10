/****************************************************************************
** StatusBar meta object code from reading C++ file 'statusbar.h'
**
** Created: Wed Oct 13 20:00:56 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../statusbar.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *StatusBar::className() const
{
    return "StatusBar";
}

QMetaObject *StatusBar::metaObj = 0;
static QMetaObjectCleanUp cleanUp_StatusBar( "StatusBar", &StatusBar::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString StatusBar::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "StatusBar", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString StatusBar::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "StatusBar", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* StatusBar::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QTextEdit::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ 0, &static_QUType_int, 0, QUParameter::Out }
    };
    static const QUMethod slot_0 = {"writeAllToFile", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ 0, &static_QUType_int, 0, QUParameter::Out },
	{ "fileName", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"writeAllToFile", 2, param_slot_1 };
    static const QUMethod slot_2 = {"copyToClipboard", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "writeAllToFile()", &slot_0, QMetaData::Public },
	{ "writeAllToFile(QString)", &slot_1, QMetaData::Public },
	{ "copyToClipboard()", &slot_2, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"StatusBar", parentObject,
	slot_tbl, 3,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_StatusBar.setMetaObject( metaObj );
    return metaObj;
}

void* StatusBar::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "StatusBar" ) )
	return this;
    return QTextEdit::qt_cast( clname );
}

bool StatusBar::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: static_QUType_int.set(_o,writeAllToFile()); break;
    case 1: static_QUType_int.set(_o,writeAllToFile((QString)static_QUType_QString.get(_o+1))); break;
    case 2: copyToClipboard(); break;
    default:
	return QTextEdit::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool StatusBar::qt_emit( int _id, QUObject* _o )
{
    return QTextEdit::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool StatusBar::qt_property( int id, int f, QVariant* v)
{
    return QTextEdit::qt_property( id, f, v);
}

bool StatusBar::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
