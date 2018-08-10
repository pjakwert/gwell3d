/****************************************************************************
** FileWidget meta object code from reading C++ file 'filewidget.h'
**
** Created: Fri Oct 8 13:51:17 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../toolwidgets/filewidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *FileWidget::className() const
{
    return "FileWidget";
}

QMetaObject *FileWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_FileWidget( "FileWidget", &FileWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString FileWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "FileWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString FileWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "FileWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* FileWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ 0, &static_QUType_bool, 0, QUParameter::Out }
    };
    static const QUMethod slot_0 = {"newMultiPolyh", 1, param_slot_0 };
    static const QUMethod slot_1 = {"saveMultiPolyh", 0, 0 };
    static const QUMethod slot_2 = {"openMultiPolyh", 0, 0 };
    static const QUMethod slot_3 = {"exit", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "newMultiPolyh()", &slot_0, QMetaData::Private },
	{ "saveMultiPolyh()", &slot_1, QMetaData::Private },
	{ "openMultiPolyh()", &slot_2, QMetaData::Private },
	{ "exit()", &slot_3, QMetaData::Private }
    };
    static const QUParameter param_signal_0[] = {
	{ "fileName", &static_QUType_charstar, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"loadMultiPolyh", 1, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ "mp", &static_QUType_ptr, "ViMultiPolyh", QUParameter::In }
    };
    static const QUMethod signal_1 = {"setMultiPolyh", 1, param_signal_1 };
    static const QUParameter param_signal_2[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod signal_2 = {"setFileCaption", 1, param_signal_2 };
    static const QMetaData signal_tbl[] = {
	{ "loadMultiPolyh(const char*)", &signal_0, QMetaData::Private },
	{ "setMultiPolyh(ViMultiPolyh*)", &signal_1, QMetaData::Private },
	{ "setFileCaption(const QString&)", &signal_2, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"FileWidget", parentObject,
	slot_tbl, 4,
	signal_tbl, 3,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_FileWidget.setMetaObject( metaObj );
    return metaObj;
}

void* FileWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "FileWidget" ) )
	return this;
    return QWidget::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL loadMultiPolyh
void FileWidget::loadMultiPolyh( const char* t0 )
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

// SIGNAL setMultiPolyh
void FileWidget::setMultiPolyh( ViMultiPolyh* t0 )
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

// SIGNAL setFileCaption
void FileWidget::setFileCaption( const QString& t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 2, t0 );
}

bool FileWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: static_QUType_bool.set(_o,newMultiPolyh()); break;
    case 1: saveMultiPolyh(); break;
    case 2: openMultiPolyh(); break;
    case 3: exit(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool FileWidget::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: loadMultiPolyh((const char*)static_QUType_charstar.get(_o+1)); break;
    case 1: setMultiPolyh((ViMultiPolyh*)static_QUType_ptr.get(_o+1)); break;
    case 2: setFileCaption((const QString&)static_QUType_QString.get(_o+1)); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool FileWidget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool FileWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
