/****************************************************************************
** Table meta object code from reading C++ file 'table.h'
**
** Created: Mon Oct 18 14:32:20 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../dialogs/table.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *Table::className() const
{
    return "Table";
}

QMetaObject *Table::metaObj = 0;
static QMetaObjectCleanUp cleanUp_Table( "Table", &Table::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString Table::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Table", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString Table::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Table", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* Table::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QTable::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ 0, &static_QUType_ptr, "ViKinemCtrlItem", QUParameter::In }
    };
    static const QUMethod slot_0 = {"addRow", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ "value", &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"setCurrentValue", 1, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ "controlItem", &static_QUType_ptr, "ViKinemCtrlItem", QUParameter::In }
    };
    static const QUMethod slot_2 = {"updateItem", 1, param_slot_2 };
    static const QUParameter param_slot_3[] = {
	{ 0, &static_QUType_bool, 0, QUParameter::Out },
	{ "row", &static_QUType_int, 0, QUParameter::In },
	{ "col", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_3 = {"validateAndSet", 3, param_slot_3 };
    static const QUParameter param_slot_4[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In },
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"rowAndColChanged", 2, param_slot_4 };
    static const QMetaData slot_tbl[] = {
	{ "addRow(ViKinemCtrlItem*)", &slot_0, QMetaData::Public },
	{ "setCurrentValue(double)", &slot_1, QMetaData::Public },
	{ "updateItem(ViKinemCtrlItem*)", &slot_2, QMetaData::Public },
	{ "validateAndSet(int,int)", &slot_3, QMetaData::Private },
	{ "rowAndColChanged(int,int)", &slot_4, QMetaData::Private }
    };
    static const QUMethod signal_0 = {"valueChangedIsOK", 0, 0 };
    static const QUParameter param_signal_1[] = {
	{ 0, &static_QUType_ptr, "ViKinemCtrlItem", QUParameter::In }
    };
    static const QUMethod signal_1 = {"MinMaxValueChanged", 1, param_signal_1 };
    static const QMetaData signal_tbl[] = {
	{ "valueChangedIsOK()", &signal_0, QMetaData::Private },
	{ "MinMaxValueChanged(ViKinemCtrlItem*)", &signal_1, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"Table", parentObject,
	slot_tbl, 5,
	signal_tbl, 2,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_Table.setMetaObject( metaObj );
    return metaObj;
}

void* Table::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "Table" ) )
	return this;
    return QTable::qt_cast( clname );
}

// SIGNAL valueChangedIsOK
void Table::valueChangedIsOK()
{
    activate_signal( staticMetaObject()->signalOffset() + 0 );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL MinMaxValueChanged
void Table::MinMaxValueChanged( ViKinemCtrlItem* t0 )
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

bool Table::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: addRow((ViKinemCtrlItem*)static_QUType_ptr.get(_o+1)); break;
    case 1: setCurrentValue((double)static_QUType_double.get(_o+1)); break;
    case 2: updateItem((ViKinemCtrlItem*)static_QUType_ptr.get(_o+1)); break;
    case 3: static_QUType_bool.set(_o,validateAndSet((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2))); break;
    case 4: rowAndColChanged((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    default:
	return QTable::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool Table::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: valueChangedIsOK(); break;
    case 1: MinMaxValueChanged((ViKinemCtrlItem*)static_QUType_ptr.get(_o+1)); break;
    default:
	return QTable::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool Table::qt_property( int id, int f, QVariant* v)
{
    return QTable::qt_property( id, f, v);
}

bool Table::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
