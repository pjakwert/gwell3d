/****************************************************************************
** KinematicsEditor meta object code from reading C++ file 'kineditor.h'
**
** Created: Mon Oct 11 16:31:08 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../dialogs/kineditor.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *KinematicsEditor::className() const
{
    return "KinematicsEditor";
}

QMetaObject *KinematicsEditor::metaObj = 0;
static QMetaObjectCleanUp cleanUp_KinematicsEditor( "KinematicsEditor", &KinematicsEditor::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString KinematicsEditor::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "KinematicsEditor", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString KinematicsEditor::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "KinematicsEditor", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* KinematicsEditor::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"addCtrlItem", 0, 0 };
    static const QUMethod slot_1 = {"updateView", 0, 0 };
    static const QUParameter param_slot_2[] = {
	{ 0, &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"updateView", 1, param_slot_2 };
    static const QMetaData slot_tbl[] = {
	{ "addCtrlItem()", &slot_0, QMetaData::Private },
	{ "updateView()", &slot_1, QMetaData::Private },
	{ "updateView(double)", &slot_2, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"KinematicsEditor", parentObject,
	slot_tbl, 3,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_KinematicsEditor.setMetaObject( metaObj );
    return metaObj;
}

void* KinematicsEditor::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "KinematicsEditor" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool KinematicsEditor::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: addCtrlItem(); break;
    case 1: updateView(); break;
    case 2: updateView((double)static_QUType_double.get(_o+1)); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool KinematicsEditor::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool KinematicsEditor::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool KinematicsEditor::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
