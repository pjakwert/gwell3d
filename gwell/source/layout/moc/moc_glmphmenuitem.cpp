/****************************************************************************
** GLMphMenuItem meta object code from reading C++ file 'glmphmenuitem.h'
**
** Created: Wed Oct 13 20:03:45 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../toolwidgets/glmphmenuitem.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *GLMphMenuItem::className() const
{
    return "GLMphMenuItem";
}

QMetaObject *GLMphMenuItem::metaObj = 0;
static QMetaObjectCleanUp cleanUp_GLMphMenuItem( "GLMphMenuItem", &GLMphMenuItem::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString GLMphMenuItem::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GLMphMenuItem", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString GLMphMenuItem::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GLMphMenuItem", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* GLMphMenuItem::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QGLViewer::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "path", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"setMultiPolyh", 1, param_slot_0 };
    static const QMetaData slot_tbl[] = {
	{ "setMultiPolyh(const QString&)", &slot_0, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ "mphPath", &static_QUType_charstar, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"mphSelected", 1, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "mphSelected(const char*)", &signal_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"GLMphMenuItem", parentObject,
	slot_tbl, 1,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_GLMphMenuItem.setMetaObject( metaObj );
    return metaObj;
}

void* GLMphMenuItem::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "GLMphMenuItem" ) )
	return this;
    return QGLViewer::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL mphSelected
void GLMphMenuItem::mphSelected( const char* t0 )
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

bool GLMphMenuItem::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: setMultiPolyh((const QString&)static_QUType_QString.get(_o+1)); break;
    default:
	return QGLViewer::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool GLMphMenuItem::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: mphSelected((const char*)static_QUType_charstar.get(_o+1)); break;
    default:
	return QGLViewer::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool GLMphMenuItem::qt_property( int id, int f, QVariant* v)
{
    return QGLViewer::qt_property( id, f, v);
}

bool GLMphMenuItem::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
