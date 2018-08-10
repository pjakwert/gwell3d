/****************************************************************************
** ColorWidget meta object code from reading C++ file 'colorwidget.h'
**
** Created: Wed Oct 13 20:01:50 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../dialogs/colorwidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *ColorWidget::className() const
{
    return "ColorWidget";
}

QMetaObject *ColorWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_ColorWidget( "ColorWidget", &ColorWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString ColorWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ColorWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString ColorWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ColorWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* ColorWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QGroupBox::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "color", &static_QUType_varptr, "\x0a", QUParameter::In }
    };
    static const QUMethod slot_0 = {"setColor", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ "color", &static_QUType_varptr, "\x0a", QUParameter::In },
	{ "alpha", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"setColor", 2, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ "GLcolor4fv", &static_QUType_ptr, "GLfloat", QUParameter::In }
    };
    static const QUMethod slot_2 = {"setColor", 1, param_slot_2 };
    static const QUParameter param_slot_3[] = {
	{ "unused", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_3 = {"setColorFromSliders", 1, param_slot_3 };
    static const QUParameter param_slot_4[] = {
	{ "unused", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"setSlidersFromEdits", 1, param_slot_4 };
    static const QUParameter param_slot_5[] = {
	{ "value", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_5 = {"setAlpha", 1, param_slot_5 };
    static const QUParameter param_slot_6[] = {
	{ "alpha", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_6 = {"setAlpha", 1, param_slot_6 };
    static const QUMethod slot_7 = {"openColorDialog", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "setColor(const QColor&)", &slot_0, QMetaData::Public },
	{ "setColor(const QColor&,int)", &slot_1, QMetaData::Public },
	{ "setColor(const GLfloat*)", &slot_2, QMetaData::Public },
	{ "setColorFromSliders(int)", &slot_3, QMetaData::Private },
	{ "setSlidersFromEdits(const QString&)", &slot_4, QMetaData::Private },
	{ "setAlpha(int)", &slot_5, QMetaData::Private },
	{ "setAlpha(const QString&)", &slot_6, QMetaData::Private },
	{ "openColorDialog()", &slot_7, QMetaData::Private }
    };
    static const QUParameter param_signal_0[] = {
	{ "color", &static_QUType_varptr, "\x0a", QUParameter::In },
	{ "alpha", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"colorChanged", 2, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "colorChanged(const QColor&,int)", &signal_0, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"ColorWidget", parentObject,
	slot_tbl, 8,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_ColorWidget.setMetaObject( metaObj );
    return metaObj;
}

void* ColorWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "ColorWidget" ) )
	return this;
    return QGroupBox::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL colorChanged
void ColorWidget::colorChanged( const QColor& t0, int t1 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 0 );
    if ( !clist )
	return;
    QUObject o[3];
    static_QUType_varptr.set(o+1,&t0);
    static_QUType_int.set(o+2,t1);
    activate_signal( clist, o );
}

bool ColorWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: setColor((const QColor&)*((const QColor*)static_QUType_ptr.get(_o+1))); break;
    case 1: setColor((const QColor&)*((const QColor*)static_QUType_ptr.get(_o+1)),(int)static_QUType_int.get(_o+2)); break;
    case 2: setColor((const GLfloat*)static_QUType_ptr.get(_o+1)); break;
    case 3: setColorFromSliders((int)static_QUType_int.get(_o+1)); break;
    case 4: setSlidersFromEdits((const QString&)static_QUType_QString.get(_o+1)); break;
    case 5: setAlpha((int)static_QUType_int.get(_o+1)); break;
    case 6: setAlpha((const QString&)static_QUType_QString.get(_o+1)); break;
    case 7: openColorDialog(); break;
    default:
	return QGroupBox::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool ColorWidget::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: colorChanged((const QColor&)*((const QColor*)static_QUType_ptr.get(_o+1)),(int)static_QUType_int.get(_o+2)); break;
    default:
	return QGroupBox::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool ColorWidget::qt_property( int id, int f, QVariant* v)
{
    return QGroupBox::qt_property( id, f, v);
}

bool ColorWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
