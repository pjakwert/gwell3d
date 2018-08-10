/****************************************************************************
** Kernel meta object code from reading C++ file 'kernel.h'
**
** Created: Sat Oct 9 20:00:00 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../kernel.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *Kernel::className() const
{
    return "Kernel";
}

QMetaObject *Kernel::metaObj = 0;
static QMetaObjectCleanUp cleanUp_Kernel( "Kernel", &Kernel::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString Kernel::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Kernel", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString Kernel::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Kernel", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* Kernel::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QObject::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "objectName", &static_QUType_charstar, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"addPattePolyh", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ "pathToMph", &static_QUType_charstar, 0, QUParameter::In },
	{ "parent", &static_QUType_ptr, "ViNTreeNode", QUParameter::In }
    };
    static const QUMethod slot_1 = {"addMultiPolyh", 2, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ "fileName", &static_QUType_charstar, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"loadMultiPolyh", 1, param_slot_2 };
    static const QMetaData slot_tbl[] = {
	{ "addPattePolyh(const char*)", &slot_0, QMetaData::Public },
	{ "addMultiPolyh(const char*,ViNTreeNode*)", &slot_1, QMetaData::Public },
	{ "loadMultiPolyh(const char*)", &slot_2, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ "scene", &static_QUType_ptr, "ViScene", QUParameter::In }
    };
    static const QUMethod signal_0 = {"sendScene", 1, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ "multiPolyh", &static_QUType_ptr, "ViMultiPolyh", QUParameter::In }
    };
    static const QUMethod signal_1 = {"sendMultiPolyh", 1, param_signal_1 };
    static const QUParameter param_signal_2[] = {
	{ "selectedList", &static_QUType_ptr, "QPtrList<ViNTreeNode>", QUParameter::In }
    };
    static const QUMethod signal_2 = {"sendSelected", 1, param_signal_2 };
    static const QUParameter param_signal_3[] = {
	{ 0, &static_QUType_varptr, "\x04", QUParameter::In }
    };
    static const QUMethod signal_3 = {"sendPrimitiveList", 1, param_signal_3 };
    static const QMetaData signal_tbl[] = {
	{ "sendScene(ViScene*)", &signal_0, QMetaData::Public },
	{ "sendMultiPolyh(ViMultiPolyh*)", &signal_1, QMetaData::Public },
	{ "sendSelected(QPtrList<ViNTreeNode>*)", &signal_2, QMetaData::Public },
	{ "sendPrimitiveList(QStringList*)", &signal_3, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"Kernel", parentObject,
	slot_tbl, 3,
	signal_tbl, 4,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_Kernel.setMetaObject( metaObj );
    return metaObj;
}

void* Kernel::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "Kernel" ) )
	return this;
    return QObject::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL sendScene
void Kernel::sendScene( ViScene* t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 0 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_ptr.set(o+1,t0);
    activate_signal( clist, o );
}

// SIGNAL sendMultiPolyh
void Kernel::sendMultiPolyh( ViMultiPolyh* t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 1 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_ptr.set(o+1,t0);
    activate_signal( clist, o );
}

// SIGNAL sendSelected
void Kernel::sendSelected( QPtrList<ViNTreeNode>* t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 2 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_ptr.set(o+1,t0);
    activate_signal( clist, o );
}

// SIGNAL sendPrimitiveList
void Kernel::sendPrimitiveList( QStringList* t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 3 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_varptr.set(o+1,t0);
    activate_signal( clist, o );
}

bool Kernel::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: addPattePolyh((const char*)static_QUType_charstar.get(_o+1)); break;
    case 1: addMultiPolyh((const char*)static_QUType_charstar.get(_o+1),(ViNTreeNode*)static_QUType_ptr.get(_o+2)); break;
    case 2: loadMultiPolyh((const char*)static_QUType_charstar.get(_o+1)); break;
    default:
	return QObject::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool Kernel::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: sendScene((ViScene*)static_QUType_ptr.get(_o+1)); break;
    case 1: sendMultiPolyh((ViMultiPolyh*)static_QUType_ptr.get(_o+1)); break;
    case 2: sendSelected((QPtrList<ViNTreeNode>*)static_QUType_ptr.get(_o+1)); break;
    case 3: sendPrimitiveList((QStringList*)static_QUType_varptr.get(_o+1)); break;
    default:
	return QObject::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool Kernel::qt_property( int id, int f, QVariant* v)
{
    return QObject::qt_property( id, f, v);
}

bool Kernel::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
