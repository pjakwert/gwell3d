/****************************************************************************
** NameDialog meta object code from reading C++ file 'namedialog.h'
**
** Created: Wed Oct 13 20:02:03 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../dialogs/namedialog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *NameDialog::className() const
{
    return "NameDialog";
}

QMetaObject *NameDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_NameDialog( "NameDialog", &NameDialog::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString NameDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "NameDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString NameDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "NameDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* NameDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"NameDialog", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_NameDialog.setMetaObject( metaObj );
    return metaObj;
}

void* NameDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "NameDialog" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool NameDialog::qt_invoke( int _id, QUObject* _o )
{
    return QDialog::qt_invoke(_id,_o);
}

bool NameDialog::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool NameDialog::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool NameDialog::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
