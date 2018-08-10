/****************************************************************************
** FileWidget meta object code from reading C++ file 'filewidget.h'
**
** Created: Wed Oct 13 20:03:56 2004
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
    static const QUMethod slot_0 = {"newScene", 1, param_slot_0 };
    static const QUMethod slot_1 = {"saveScene", 0, 0 };
    static const QUMethod slot_2 = {"openScene", 0, 0 };
    static const QUMethod slot_3 = {"exit", 0, 0 };
    static const QUParameter param_slot_4[] = {
	{ 0, &static_QUType_int, 0, QUParameter::Out },
	{ "fileName", &static_QUType_QString, 0, QUParameter::InOut }
    };
    static const QUMethod slot_4 = {"saveSceneToFile", 2, param_slot_4 };
    static const QUParameter param_slot_5[] = {
	{ 0, &static_QUType_int, 0, QUParameter::Out },
	{ "fileName", &static_QUType_QString, 0, QUParameter::InOut }
    };
    static const QUMethod slot_5 = {"loadSceneFromFile", 2, param_slot_5 };
    static const QUParameter param_slot_6[] = {
	{ 0, &static_QUType_int, 0, QUParameter::Out },
	{ "elem", &static_QUType_ptr, "QDomElement", QUParameter::In }
    };
    static const QUMethod slot_6 = {"readLighting", 2, param_slot_6 };
    static const QUParameter param_slot_7[] = {
	{ 0, &static_QUType_int, 0, QUParameter::Out },
	{ "elem", &static_QUType_ptr, "QDomElement", QUParameter::In }
    };
    static const QUMethod slot_7 = {"readFog", 2, param_slot_7 };
    static const QUParameter param_slot_8[] = {
	{ 0, &static_QUType_int, 0, QUParameter::Out },
	{ "elem", &static_QUType_ptr, "QDomElement", QUParameter::In }
    };
    static const QUMethod slot_8 = {"readElements", 2, param_slot_8 };
    static const QMetaData slot_tbl[] = {
	{ "newScene()", &slot_0, QMetaData::Private },
	{ "saveScene()", &slot_1, QMetaData::Private },
	{ "openScene()", &slot_2, QMetaData::Private },
	{ "exit()", &slot_3, QMetaData::Private },
	{ "saveSceneToFile(QString&)", &slot_4, QMetaData::Private },
	{ "loadSceneFromFile(QString&)", &slot_5, QMetaData::Private },
	{ "readLighting(QDomElement)", &slot_6, QMetaData::Private },
	{ "readFog(QDomElement)", &slot_7, QMetaData::Private },
	{ "readElements(QDomElement)", &slot_8, QMetaData::Private }
    };
    static const QUParameter param_signal_0[] = {
	{ "fileName", &static_QUType_charstar, 0, QUParameter::In },
	{ "name", &static_QUType_charstar, 0, QUParameter::In },
	{ "trans", &static_QUType_ptr, "Vector3f", QUParameter::In },
	{ "rotDeg", &static_QUType_ptr, "Vector3f", QUParameter::In },
	{ "scale", &static_QUType_ptr, "Vector3f", QUParameter::In }
    };
    static const QUMethod signal_0 = {"addMultiPolyh", 5, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ "scene", &static_QUType_ptr, "ViScene", QUParameter::In }
    };
    static const QUMethod signal_1 = {"setScene", 1, param_signal_1 };
    static const QUParameter param_signal_2[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod signal_2 = {"setFileCaption", 1, param_signal_2 };
    static const QUParameter param_signal_3[] = {
	{ 0, &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod signal_3 = {"setLightingEnabled", 1, param_signal_3 };
    static const QUMethod signal_4 = {"clearAllLights", 0, 0 };
    static const QUParameter param_signal_5[] = {
	{ "light", &static_QUType_ptr, "Light", QUParameter::In }
    };
    static const QUMethod signal_5 = {"addLight", 1, param_signal_5 };
    static const QUMethod signal_6 = {"updateFog", 0, 0 };
    static const QMetaData signal_tbl[] = {
	{ "addMultiPolyh(const char*,const char*,const Vector3f&,const Vector3f&,const Vector3f&)", &signal_0, QMetaData::Private },
	{ "setScene(ViScene*)", &signal_1, QMetaData::Private },
	{ "setFileCaption(const QString&)", &signal_2, QMetaData::Private },
	{ "setLightingEnabled(bool)", &signal_3, QMetaData::Private },
	{ "clearAllLights()", &signal_4, QMetaData::Private },
	{ "addLight(Light*)", &signal_5, QMetaData::Private },
	{ "updateFog()", &signal_6, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"FileWidget", parentObject,
	slot_tbl, 9,
	signal_tbl, 7,
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

// SIGNAL addMultiPolyh
void FileWidget::addMultiPolyh( const char* t0, const char* t1, const Vector3f& t2, const Vector3f& t3, const Vector3f& t4 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 0 );
    if ( !clist )
	return;
    QUObject o[6];
    static_QUType_charstar.set(o+1,t0);
    static_QUType_charstar.set(o+2,t1);
    static_QUType_ptr.set(o+3,&t2);
    static_QUType_ptr.set(o+4,&t3);
    static_QUType_ptr.set(o+5,&t4);
    activate_signal( clist, o );
}

// SIGNAL setScene
void FileWidget::setScene( ViScene* t0 )
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

// SIGNAL setLightingEnabled
void FileWidget::setLightingEnabled( bool t0 )
{
    activate_signal_bool( staticMetaObject()->signalOffset() + 3, t0 );
}

// SIGNAL clearAllLights
void FileWidget::clearAllLights()
{
    activate_signal( staticMetaObject()->signalOffset() + 4 );
}

// SIGNAL addLight
void FileWidget::addLight( Light* t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 5 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_ptr.set(o+1,t0);
    activate_signal( clist, o );
}

// SIGNAL updateFog
void FileWidget::updateFog()
{
    activate_signal( staticMetaObject()->signalOffset() + 6 );
}

bool FileWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: static_QUType_bool.set(_o,newScene()); break;
    case 1: saveScene(); break;
    case 2: openScene(); break;
    case 3: exit(); break;
    case 4: static_QUType_int.set(_o,saveSceneToFile((QString&)static_QUType_QString.get(_o+1))); break;
    case 5: static_QUType_int.set(_o,loadSceneFromFile((QString&)static_QUType_QString.get(_o+1))); break;
    case 6: static_QUType_int.set(_o,readLighting((QDomElement)(*((QDomElement*)static_QUType_ptr.get(_o+1))))); break;
    case 7: static_QUType_int.set(_o,readFog((QDomElement)(*((QDomElement*)static_QUType_ptr.get(_o+1))))); break;
    case 8: static_QUType_int.set(_o,readElements((QDomElement)(*((QDomElement*)static_QUType_ptr.get(_o+1))))); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool FileWidget::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: addMultiPolyh((const char*)static_QUType_charstar.get(_o+1),(const char*)static_QUType_charstar.get(_o+2),(const Vector3f&)*((const Vector3f*)static_QUType_ptr.get(_o+3)),(const Vector3f&)*((const Vector3f*)static_QUType_ptr.get(_o+4)),(const Vector3f&)*((const Vector3f*)static_QUType_ptr.get(_o+5))); break;
    case 1: setScene((ViScene*)static_QUType_ptr.get(_o+1)); break;
    case 2: setFileCaption((const QString&)static_QUType_QString.get(_o+1)); break;
    case 3: setLightingEnabled((bool)static_QUType_bool.get(_o+1)); break;
    case 4: clearAllLights(); break;
    case 5: addLight((Light*)static_QUType_ptr.get(_o+1)); break;
    case 6: updateFog(); break;
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
