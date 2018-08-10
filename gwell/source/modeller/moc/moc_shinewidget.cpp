/****************************************************************************
** ShineWidget meta object code from reading C++ file 'shinewidget.h'
**
** Created: Fri Oct 8 13:47:55 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../dialogs/shinewidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *ShineWidget::className() const
{
    return "ShineWidget";
}

QMetaObject *ShineWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_ShineWidget( "ShineWidget", &ShineWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString ShineWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ShineWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString ShineWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ShineWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* ShineWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QGroupBox::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "shininess", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"setShininess", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ "unused", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"setShine", 1, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ "unused", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"setShine", 1, param_slot_2 };
    static const QMetaData slot_tbl[] = {
	{ "setShininess(int)", &slot_0, QMetaData::Public },
	{ "setShine(int)", &slot_1, QMetaData::Private },
	{ "setShine(const QString&)", &slot_2, QMetaData::Private }
    };
    static const QUParameter param_signal_0[] = {
	{ "shininess", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"shininessChanged", 1, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "shininessChanged(int)", &signal_0, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"ShineWidget", parentObject,
	slot_tbl, 3,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_ShineWidget.setMetaObject( metaObj );
    return metaObj;
}

void* ShineWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "ShineWidget" ) )
	return this;
    return QGroupBox::qt_cast( clname );
}

// SIGNAL shininessChanged
void ShineWidget::shininessChanged( int t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 0, t0 );
}

bool ShineWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: setShininess((int)static_QUType_int.get(_o+1)); break;
    case 1: setShine((int)static_QUType_int.get(_o+1)); break;
    case 2: setShine((const QString&)static_QUType_QString.get(_o+1)); break;
    default:
	return QGroupBox::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool ShineWidget::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: shininessChanged((int)static_QUType_int.get(_o+1)); break;
    default:
	return QGroupBox::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool ShineWidget::qt_property( int id, int f, QVariant* v)
{
    return QGroupBox::qt_property( id, f, v);
}

bool ShineWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
