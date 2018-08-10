/****************************************************************************
** GLMenuItem meta object code from reading C++ file 'glmenuitem.h'
**
** Created: Fri Oct 8 13:51:45 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../toolwidgets/glmenuitem.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *GLMenuItem::className() const
{
    return "GLMenuItem";
}

QMetaObject *GLMenuItem::metaObj = 0;
static QMetaObjectCleanUp cleanUp_GLMenuItem( "GLMenuItem", &GLMenuItem::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString GLMenuItem::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GLMenuItem", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString GLMenuItem::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GLMenuItem", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* GLMenuItem::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QGLViewer::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "pPaPolyh", &static_QUType_ptr, "ViPattePolyh", QUParameter::In }
    };
    static const QUMethod slot_0 = {"setPattePolyh", 1, param_slot_0 };
    static const QMetaData slot_tbl[] = {
	{ "setPattePolyh(const ViPattePolyh*)", &slot_0, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ "objectName", &static_QUType_charstar, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"objectSelected", 1, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "objectSelected(const char*)", &signal_0, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"GLMenuItem", parentObject,
	slot_tbl, 1,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_GLMenuItem.setMetaObject( metaObj );
    return metaObj;
}

void* GLMenuItem::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "GLMenuItem" ) )
	return this;
    return QGLViewer::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL objectSelected
void GLMenuItem::objectSelected( const char* t0 )
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

bool GLMenuItem::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: setPattePolyh((const ViPattePolyh*)static_QUType_ptr.get(_o+1)); break;
    default:
	return QGLViewer::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool GLMenuItem::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: objectSelected((const char*)static_QUType_charstar.get(_o+1)); break;
    default:
	return QGLViewer::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool GLMenuItem::qt_property( int id, int f, QVariant* v)
{
    return QGLViewer::qt_property( id, f, v);
}

bool GLMenuItem::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
