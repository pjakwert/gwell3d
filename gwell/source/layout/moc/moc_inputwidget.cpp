/****************************************************************************
** InputWidget meta object code from reading C++ file 'inputwidget.h'
**
** Created: Mon Oct 18 14:24:22 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../dialogs/inputwidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *InputWidget::className() const
{
    return "InputWidget";
}

QMetaObject *InputWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_InputWidget( "InputWidget", &InputWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString InputWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "InputWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString InputWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "InputWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* InputWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_signal_0[] = {
	{ "index", &static_QUType_int, 0, QUParameter::In },
	{ "value", &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"valueChanged", 2, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "valueChanged(int,double)", &signal_0, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"InputWidget", parentObject,
	0, 0,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_InputWidget.setMetaObject( metaObj );
    return metaObj;
}

void* InputWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "InputWidget" ) )
	return this;
    return QWidget::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL valueChanged
void InputWidget::valueChanged( int t0, double t1 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 0 );
    if ( !clist )
	return;
    QUObject o[3];
    static_QUType_int.set(o+1,t0);
    static_QUType_double.set(o+2,t1);
    activate_signal( clist, o );
}

bool InputWidget::qt_invoke( int _id, QUObject* _o )
{
    return QWidget::qt_invoke(_id,_o);
}

bool InputWidget::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: valueChanged((int)static_QUType_int.get(_o+1),(double)static_QUType_double.get(_o+2)); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool InputWidget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool InputWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
