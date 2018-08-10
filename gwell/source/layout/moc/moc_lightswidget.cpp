/****************************************************************************
** LightsWidget meta object code from reading C++ file 'lightswidget.h'
**
** Created: Wed Oct 13 20:04:22 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../toolwidgets/lightswidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *LightsWidget::className() const
{
    return "LightsWidget";
}

QMetaObject *LightsWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_LightsWidget( "LightsWidget", &LightsWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString LightsWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "LightsWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString LightsWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "LightsWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* LightsWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "on", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"lightsToggled", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ "light", &static_QUType_ptr, "Light", QUParameter::In }
    };
    static const QUMethod slot_1 = {"currentLightChanged", 1, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ "light", &static_QUType_ptr, "Light", QUParameter::In }
    };
    static const QUMethod slot_2 = {"lightParamsChanged", 1, param_slot_2 };
    static const QUParameter param_slot_3[] = {
	{ 0, &static_QUType_varptr, "\x0a", QUParameter::In },
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_3 = {"updateLightForWorkspace", 2, param_slot_3 };
    static const QUParameter param_slot_4[] = {
	{ "yes", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"setAllParamsEnabled", 1, param_slot_4 };
    static const QUMethod slot_5 = {"updateWorkspace", 0, 0 };
    static const QUParameter param_slot_6[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_6 = {"setLightTypeFromCombo", 1, param_slot_6 };
    static const QUMethod slot_7 = {"setAllParamsFromEdits", 0, 0 };
    static const QUParameter param_slot_8[] = {
	{ "yes", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_8 = {"setMovingWithCamera", 1, param_slot_8 };
    static const QUParameter param_slot_9[] = {
	{ "mType", &static_QUType_ptr, "MModifier::ModifierType", QUParameter::In },
	{ "v", &static_QUType_ptr, "Vector3f", QUParameter::In }
    };
    static const QUMethod slot_9 = {"updateData", 2, param_slot_9 };
    static const QUParameter param_slot_10[] = {
	{ 0, &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_10 = {"transLightToggled", 1, param_slot_10 };
    static const QUParameter param_slot_11[] = {
	{ 0, &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_11 = {"changeDirToggled", 1, param_slot_11 };
    static const QUMethod slot_12 = {"disableModifiers", 0, 0 };
    static const QUMethod slot_13 = {"turnModifiersButtonsOff", 0, 0 };
    static const QUParameter param_slot_14[] = {
	{ "mType", &static_QUType_ptr, "MModifier::ModifierType", QUParameter::In }
    };
    static const QUMethod slot_14 = {"setModifier", 1, param_slot_14 };
    static const QUParameter param_slot_15[] = {
	{ "yes", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_15 = {"enableLighting", 1, param_slot_15 };
    static const QUMethod slot_16 = {"clearAllLights", 0, 0 };
    static const QUParameter param_slot_17[] = {
	{ "light", &static_QUType_ptr, "Light", QUParameter::In }
    };
    static const QUMethod slot_17 = {"addLight", 1, param_slot_17 };
    static const QMetaData slot_tbl[] = {
	{ "lightsToggled(bool)", &slot_0, QMetaData::Private },
	{ "currentLightChanged(Light*)", &slot_1, QMetaData::Private },
	{ "lightParamsChanged(Light*)", &slot_2, QMetaData::Private },
	{ "updateLightForWorkspace(const QColor&,int)", &slot_3, QMetaData::Private },
	{ "setAllParamsEnabled(bool)", &slot_4, QMetaData::Private },
	{ "updateWorkspace()", &slot_5, QMetaData::Private },
	{ "setLightTypeFromCombo(int)", &slot_6, QMetaData::Private },
	{ "setAllParamsFromEdits()", &slot_7, QMetaData::Private },
	{ "setMovingWithCamera(bool)", &slot_8, QMetaData::Private },
	{ "updateData(MModifier::ModifierType,Vector3f)", &slot_9, QMetaData::Private },
	{ "transLightToggled(bool)", &slot_10, QMetaData::Private },
	{ "changeDirToggled(bool)", &slot_11, QMetaData::Private },
	{ "disableModifiers()", &slot_12, QMetaData::Public },
	{ "turnModifiersButtonsOff()", &slot_13, QMetaData::Public },
	{ "setModifier(MModifier::ModifierType)", &slot_14, QMetaData::Public },
	{ "enableLighting(bool)", &slot_15, QMetaData::Public },
	{ "clearAllLights()", &slot_16, QMetaData::Public },
	{ "addLight(Light*)", &slot_17, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ "yes", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"setLightingEnabled", 1, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ "light", &static_QUType_ptr, "GLenum", QUParameter::In },
	{ "yes", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod signal_1 = {"setLightEnabled", 2, param_signal_1 };
    static const QUParameter param_signal_2[] = {
	{ 0, &static_QUType_ptr, "Light", QUParameter::In }
    };
    static const QUMethod signal_2 = {"setLight", 1, param_signal_2 };
    static const QUParameter param_signal_3[] = {
	{ 0, &static_QUType_ptr, "QPtrList<Light>", QUParameter::In }
    };
    static const QUMethod signal_3 = {"setLightsList", 1, param_signal_3 };
    static const QUParameter param_signal_4[] = {
	{ "GLwhichColor", &static_QUType_ptr, "GLenum", QUParameter::In },
	{ "_currentLight", &static_QUType_ptr, "Light", QUParameter::In }
    };
    static const QUMethod signal_4 = {"updateLightColor", 2, param_signal_4 };
    static const QUParameter param_signal_5[] = {
	{ "modifier", &static_QUType_ptr, "MModifier", QUParameter::In }
    };
    static const QUMethod signal_5 = {"sendModifier", 1, param_signal_5 };
    static const QUMethod signal_6 = {"setDefaultModifier", 0, 0 };
    static const QMetaData signal_tbl[] = {
	{ "setLightingEnabled(bool)", &signal_0, QMetaData::Protected },
	{ "setLightEnabled(GLenum,bool)", &signal_1, QMetaData::Protected },
	{ "setLight(Light*)", &signal_2, QMetaData::Protected },
	{ "setLightsList(QPtrList<Light>*)", &signal_3, QMetaData::Protected },
	{ "updateLightColor(GLenum,Light*)", &signal_4, QMetaData::Protected },
	{ "sendModifier(MModifier*)", &signal_5, QMetaData::Protected },
	{ "setDefaultModifier()", &signal_6, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"LightsWidget", parentObject,
	slot_tbl, 18,
	signal_tbl, 7,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_LightsWidget.setMetaObject( metaObj );
    return metaObj;
}

void* LightsWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "LightsWidget" ) )
	return this;
    return QWidget::qt_cast( clname );
}

// SIGNAL setLightingEnabled
void LightsWidget::setLightingEnabled( bool t0 )
{
    activate_signal_bool( staticMetaObject()->signalOffset() + 0, t0 );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL setLightEnabled
void LightsWidget::setLightEnabled( GLenum t0, bool t1 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 1 );
    if ( !clist )
	return;
    QUObject o[3];
    static_QUType_ptr.set(o+1,&t0);
    static_QUType_bool.set(o+2,t1);
    activate_signal( clist, o );
}

// SIGNAL setLight
void LightsWidget::setLight( Light* t0 )
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

// SIGNAL setLightsList
void LightsWidget::setLightsList( QPtrList<Light>* t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 3 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_ptr.set(o+1,t0);
    activate_signal( clist, o );
}

// SIGNAL updateLightColor
void LightsWidget::updateLightColor( GLenum t0, Light* t1 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 4 );
    if ( !clist )
	return;
    QUObject o[3];
    static_QUType_ptr.set(o+1,&t0);
    static_QUType_ptr.set(o+2,t1);
    activate_signal( clist, o );
}

// SIGNAL sendModifier
void LightsWidget::sendModifier( MModifier* t0 )
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

// SIGNAL setDefaultModifier
void LightsWidget::setDefaultModifier()
{
    activate_signal( staticMetaObject()->signalOffset() + 6 );
}

bool LightsWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: lightsToggled((bool)static_QUType_bool.get(_o+1)); break;
    case 1: currentLightChanged((Light*)static_QUType_ptr.get(_o+1)); break;
    case 2: lightParamsChanged((Light*)static_QUType_ptr.get(_o+1)); break;
    case 3: updateLightForWorkspace((const QColor&)*((const QColor*)static_QUType_ptr.get(_o+1)),(int)static_QUType_int.get(_o+2)); break;
    case 4: setAllParamsEnabled((bool)static_QUType_bool.get(_o+1)); break;
    case 5: updateWorkspace(); break;
    case 6: setLightTypeFromCombo((int)static_QUType_int.get(_o+1)); break;
    case 7: setAllParamsFromEdits(); break;
    case 8: setMovingWithCamera((bool)static_QUType_bool.get(_o+1)); break;
    case 9: updateData((MModifier::ModifierType)(*((MModifier::ModifierType*)static_QUType_ptr.get(_o+1))),(Vector3f)(*((Vector3f*)static_QUType_ptr.get(_o+2)))); break;
    case 10: transLightToggled((bool)static_QUType_bool.get(_o+1)); break;
    case 11: changeDirToggled((bool)static_QUType_bool.get(_o+1)); break;
    case 12: disableModifiers(); break;
    case 13: turnModifiersButtonsOff(); break;
    case 14: setModifier((MModifier::ModifierType)(*((MModifier::ModifierType*)static_QUType_ptr.get(_o+1)))); break;
    case 15: enableLighting((bool)static_QUType_bool.get(_o+1)); break;
    case 16: clearAllLights(); break;
    case 17: addLight((Light*)static_QUType_ptr.get(_o+1)); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool LightsWidget::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: setLightingEnabled((bool)static_QUType_bool.get(_o+1)); break;
    case 1: setLightEnabled((GLenum)(*((GLenum*)static_QUType_ptr.get(_o+1))),(bool)static_QUType_bool.get(_o+2)); break;
    case 2: setLight((Light*)static_QUType_ptr.get(_o+1)); break;
    case 3: setLightsList((QPtrList<Light>*)static_QUType_ptr.get(_o+1)); break;
    case 4: updateLightColor((GLenum)(*((GLenum*)static_QUType_ptr.get(_o+1))),(Light*)static_QUType_ptr.get(_o+2)); break;
    case 5: sendModifier((MModifier*)static_QUType_ptr.get(_o+1)); break;
    case 6: setDefaultModifier(); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool LightsWidget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool LightsWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
