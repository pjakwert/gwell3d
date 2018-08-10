/****************************************************************************
** KinematicsEditorRO meta object code from reading C++ file 'kineditorro.h'
**
** Created: Mon Oct 18 14:24:55 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../dialogs/kineditorro.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *KinematicsEditorRO::className() const
{
    return "KinematicsEditorRO";
}

QMetaObject *KinematicsEditorRO::metaObj = 0;
static QMetaObjectCleanUp cleanUp_KinematicsEditorRO( "KinematicsEditorRO", &KinematicsEditorRO::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString KinematicsEditorRO::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "KinematicsEditorRO", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString KinematicsEditorRO::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "KinematicsEditorRO", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* KinematicsEditorRO::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"updateView", 0, 0 };
    static const QUParameter param_slot_1[] = {
	{ 0, &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"updateView", 1, param_slot_1 };
    static const QMetaData slot_tbl[] = {
	{ "updateView()", &slot_0, QMetaData::Private },
	{ "updateView(double)", &slot_1, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"KinematicsEditorRO", parentObject,
	slot_tbl, 2,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_KinematicsEditorRO.setMetaObject( metaObj );
    return metaObj;
}

void* KinematicsEditorRO::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "KinematicsEditorRO" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool KinematicsEditorRO::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: updateView(); break;
    case 1: updateView((double)static_QUType_double.get(_o+1)); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool KinematicsEditorRO::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool KinematicsEditorRO::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool KinematicsEditorRO::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
