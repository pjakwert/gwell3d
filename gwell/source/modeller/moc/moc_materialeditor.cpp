/****************************************************************************
** MaterialEditor meta object code from reading C++ file 'materialeditor.h'
**
** Created: Fri Oct 8 13:47:26 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../dialogs/materialeditor.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MaterialEditor::className() const
{
    return "MaterialEditor";
}

QMetaObject *MaterialEditor::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MaterialEditor( "MaterialEditor", &MaterialEditor::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString MaterialEditor::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MaterialEditor", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MaterialEditor::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MaterialEditor", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MaterialEditor::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"undoAllAndClose", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "undoAllAndClose()", &slot_0, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"MaterialEditor", parentObject,
	slot_tbl, 1,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_MaterialEditor.setMetaObject( metaObj );
    return metaObj;
}

void* MaterialEditor::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "MaterialEditor" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool MaterialEditor::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: undoAllAndClose(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool MaterialEditor::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool MaterialEditor::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool MaterialEditor::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
