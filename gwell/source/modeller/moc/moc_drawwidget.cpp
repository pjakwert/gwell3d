/****************************************************************************
** DrawWidget meta object code from reading C++ file 'drawwidget.h'
**
** Created: Sun Oct 24 14:05:57 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../toolwidgets/drawwidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *DrawWidget::className() const
{
    return "DrawWidget";
}

QMetaObject *DrawWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_DrawWidget( "DrawWidget", &DrawWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString DrawWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "DrawWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString DrawWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "DrawWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* DrawWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "objectName", &static_QUType_charstar, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"objectItemSelected", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ "mphPath", &static_QUType_charstar, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"multiPolyhSelected", 1, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ "scene", &static_QUType_ptr, "ViScene", QUParameter::In }
    };
    static const QUMethod slot_2 = {"setScene", 1, param_slot_2 };
    static const QMetaData slot_tbl[] = {
	{ "objectItemSelected(const char*)", &slot_0, QMetaData::Private },
	{ "multiPolyhSelected(const char*)", &slot_1, QMetaData::Private },
	{ "setScene(ViScene*)", &slot_2, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ "objectName", &static_QUType_charstar, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"objectSelected", 1, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ "mphPath", &static_QUType_charstar, 0, QUParameter::In },
	{ "parent", &static_QUType_ptr, "ViNTreeNode", QUParameter::In }
    };
    static const QUMethod signal_1 = {"addMultiPolyh", 2, param_signal_1 };
    static const QMetaData signal_tbl[] = {
	{ "objectSelected(const char*)", &signal_0, QMetaData::Public },
	{ "addMultiPolyh(const char*,ViNTreeNode*)", &signal_1, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"DrawWidget", parentObject,
	slot_tbl, 3,
	signal_tbl, 2,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_DrawWidget.setMetaObject( metaObj );
    return metaObj;
}

void* DrawWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "DrawWidget" ) )
	return this;
    return QWidget::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL objectSelected
void DrawWidget::objectSelected( const char* t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 0 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_charstar.set(o+1,t0);
    activate_signal( clist, o );
}

// SIGNAL addMultiPolyh
void DrawWidget::addMultiPolyh( const char* t0, ViNTreeNode* t1 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 1 );
    if ( !clist )
	return;
    QUObject o[3];
    static_QUType_charstar.set(o+1,t0);
    static_QUType_ptr.set(o+2,t1);
    activate_signal( clist, o );
}

bool DrawWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: objectItemSelected((const char*)static_QUType_charstar.get(_o+1)); break;
    case 1: multiPolyhSelected((const char*)static_QUType_charstar.get(_o+1)); break;
    case 2: setScene((ViScene*)static_QUType_ptr.get(_o+1)); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool DrawWidget::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: objectSelected((const char*)static_QUType_charstar.get(_o+1)); break;
    case 1: addMultiPolyh((const char*)static_QUType_charstar.get(_o+1),(ViNTreeNode*)static_QUType_ptr.get(_o+2)); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool DrawWidget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool DrawWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
