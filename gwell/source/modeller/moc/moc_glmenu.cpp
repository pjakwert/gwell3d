/****************************************************************************
** GLMenu meta object code from reading C++ file 'glmenu.h'
**
** Created: Fri Oct 8 13:51:34 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../toolwidgets/glmenu.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *GLMenu::className() const
{
    return "GLMenu";
}

QMetaObject *GLMenu::metaObj = 0;
static QMetaObjectCleanUp cleanUp_GLMenu( "GLMenu", &GLMenu::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString GLMenu::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GLMenu", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString GLMenu::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GLMenu", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* GLMenu::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "objectName", &static_QUType_charstar, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"objectItemSelected", 1, param_slot_0 };
    static const QMetaData slot_tbl[] = {
	{ "objectItemSelected(const char*)", &slot_0, QMetaData::Private }
    };
    static const QUParameter param_signal_0[] = {
	{ "objectName", &static_QUType_charstar, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"objectSelected", 1, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "objectSelected(const char*)", &signal_0, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"GLMenu", parentObject,
	slot_tbl, 1,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_GLMenu.setMetaObject( metaObj );
    return metaObj;
}

void* GLMenu::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "GLMenu" ) )
	return this;
    return QWidget::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL objectSelected
void GLMenu::objectSelected( const char* t0 )
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

bool GLMenu::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: objectItemSelected((const char*)static_QUType_charstar.get(_o+1)); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool GLMenu::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: objectSelected((const char*)static_QUType_charstar.get(_o+1)); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool GLMenu::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool GLMenu::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
