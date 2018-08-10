/****************************************************************************
** ObjectsWidget meta object code from reading C++ file 'objectswidget.h'
**
** Created: Fri Oct 8 13:52:40 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../toolwidgets/objectswidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *ObjectsWidget::className() const
{
    return "ObjectsWidget";
}

QMetaObject *ObjectsWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_ObjectsWidget( "ObjectsWidget", &ObjectsWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString ObjectsWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ObjectsWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString ObjectsWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ObjectsWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* ObjectsWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"buildTree", 0, 0 };
    static const QUMethod slot_1 = {"buildPaths", 0, 0 };
    static const QUParameter param_slot_2[] = {
	{ "buttonID", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"viewToggled", 1, param_slot_2 };
    static const QUMethod slot_3 = {"showSelectedList", 0, 0 };
    static const QUMethod slot_4 = {"buildSelectedList", 0, 0 };
    static const QUParameter param_slot_5[] = {
	{ "item", &static_QUType_ptr, "QListViewItem", QUParameter::In }
    };
    static const QUMethod slot_5 = {"setAddrEditPath", 1, param_slot_5 };
    static const QUParameter param_slot_6[] = {
	{ "selectedList", &static_QUType_ptr, "QPtrList<ViNTreeNode>", QUParameter::In }
    };
    static const QUMethod slot_6 = {"setSelectedList", 1, param_slot_6 };
    static const QUParameter param_slot_7[] = {
	{ "root", &static_QUType_ptr, "ViMultiPolyh", QUParameter::In }
    };
    static const QUMethod slot_7 = {"setRoot", 1, param_slot_7 };
    static const QUMethod slot_8 = {"update", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "buildTree()", &slot_0, QMetaData::Private },
	{ "buildPaths()", &slot_1, QMetaData::Private },
	{ "viewToggled(int)", &slot_2, QMetaData::Private },
	{ "showSelectedList()", &slot_3, QMetaData::Private },
	{ "buildSelectedList()", &slot_4, QMetaData::Private },
	{ "setAddrEditPath(QListViewItem*)", &slot_5, QMetaData::Private },
	{ "setSelectedList(QPtrList<ViNTreeNode>*)", &slot_6, QMetaData::Public },
	{ "setRoot(ViMultiPolyh*)", &slot_7, QMetaData::Public },
	{ "update()", &slot_8, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ "selectedList", &static_QUType_ptr, "QPtrList<ViNTreeNode>", QUParameter::In }
    };
    static const QUMethod signal_0 = {"selectionChanged", 1, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "selectionChanged(QPtrList<ViNTreeNode>*)", &signal_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"ObjectsWidget", parentObject,
	slot_tbl, 9,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_ObjectsWidget.setMetaObject( metaObj );
    return metaObj;
}

void* ObjectsWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "ObjectsWidget" ) )
	return this;
    return QWidget::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL selectionChanged
void ObjectsWidget::selectionChanged( QPtrList<ViNTreeNode>* t0 )
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

bool ObjectsWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: buildTree(); break;
    case 1: buildPaths(); break;
    case 2: viewToggled((int)static_QUType_int.get(_o+1)); break;
    case 3: showSelectedList(); break;
    case 4: buildSelectedList(); break;
    case 5: setAddrEditPath((QListViewItem*)static_QUType_ptr.get(_o+1)); break;
    case 6: setSelectedList((QPtrList<ViNTreeNode>*)static_QUType_ptr.get(_o+1)); break;
    case 7: setRoot((ViMultiPolyh*)static_QUType_ptr.get(_o+1)); break;
    case 8: update(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool ObjectsWidget::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: selectionChanged((QPtrList<ViNTreeNode>*)static_QUType_ptr.get(_o+1)); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool ObjectsWidget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool ObjectsWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
