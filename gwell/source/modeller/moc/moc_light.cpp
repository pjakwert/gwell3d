/****************************************************************************
** Light meta object code from reading C++ file 'light.h'
**
** Created: Fri Oct 8 13:45:57 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../light.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *Light::className() const
{
    return "Light";
}

QMetaObject *Light::metaObj = 0;
static QMetaObjectCleanUp cleanUp_Light( "Light", &Light::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString Light::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Light", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString Light::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Light", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* Light::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QObject::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "lightType", &static_QUType_ptr, "LightType", QUParameter::In }
    };
    static const QUMethod slot_0 = {"setLightType", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ "yes", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"setSpotlight", 1, param_slot_1 };
    static const QUMethod slot_2 = {"setName", 0, 0 };
    static const QUParameter param_slot_3[] = {
	{ "lightName", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_3 = {"setName", 1, param_slot_3 };
    static const QUParameter param_slot_4[] = {
	{ "yes", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"setEnabled", 1, param_slot_4 };
    static const QUParameter param_slot_5[] = {
	{ "position", &static_QUType_ptr, "Vector3f", QUParameter::In }
    };
    static const QUMethod slot_5 = {"setPosition", 1, param_slot_5 };
    static const QUParameter param_slot_6[] = {
	{ "color", &static_QUType_varptr, "\x0a", QUParameter::In }
    };
    static const QUMethod slot_6 = {"setAmbientColor", 1, param_slot_6 };
    static const QUParameter param_slot_7[] = {
	{ "color", &static_QUType_varptr, "\x0a", QUParameter::In },
	{ "alpha", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_7 = {"setAmbientColor", 2, param_slot_7 };
    static const QUParameter param_slot_8[] = {
	{ "ambientColor", &static_QUType_ptr, "GLfloat", QUParameter::In }
    };
    static const QUMethod slot_8 = {"setAmbientColor", 1, param_slot_8 };
    static const QUParameter param_slot_9[] = {
	{ "color", &static_QUType_varptr, "\x0a", QUParameter::In }
    };
    static const QUMethod slot_9 = {"setDiffuseColor", 1, param_slot_9 };
    static const QUParameter param_slot_10[] = {
	{ "color", &static_QUType_varptr, "\x0a", QUParameter::In },
	{ "alpha", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_10 = {"setDiffuseColor", 2, param_slot_10 };
    static const QUParameter param_slot_11[] = {
	{ "diffuseColor", &static_QUType_ptr, "GLfloat", QUParameter::In }
    };
    static const QUMethod slot_11 = {"setDiffuseColor", 1, param_slot_11 };
    static const QUParameter param_slot_12[] = {
	{ "color", &static_QUType_varptr, "\x0a", QUParameter::In }
    };
    static const QUMethod slot_12 = {"setSpecularColor", 1, param_slot_12 };
    static const QUParameter param_slot_13[] = {
	{ "color", &static_QUType_varptr, "\x0a", QUParameter::In },
	{ "alpha", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_13 = {"setSpecularColor", 2, param_slot_13 };
    static const QUParameter param_slot_14[] = {
	{ "specularColor", &static_QUType_ptr, "GLfloat", QUParameter::In }
    };
    static const QUMethod slot_14 = {"setSpecularColor", 1, param_slot_14 };
    static const QUParameter param_slot_15[] = {
	{ "yes", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_15 = {"setMovingWithCamera", 1, param_slot_15 };
    static const QUParameter param_slot_16[] = {
	{ "spotDirection", &static_QUType_ptr, "Vector3f", QUParameter::In }
    };
    static const QUMethod slot_16 = {"setSpotDirection", 1, param_slot_16 };
    static const QUParameter param_slot_17[] = {
	{ "spotExponent", &static_QUType_ptr, "GLfloat", QUParameter::In }
    };
    static const QUMethod slot_17 = {"setSpotExponent", 1, param_slot_17 };
    static const QUParameter param_slot_18[] = {
	{ "spotCutOff", &static_QUType_ptr, "GLfloat", QUParameter::In }
    };
    static const QUMethod slot_18 = {"setSpotCutOffAngle", 1, param_slot_18 };
    static const QUParameter param_slot_19[] = {
	{ "ca", &static_QUType_ptr, "GLfloat", QUParameter::In }
    };
    static const QUMethod slot_19 = {"setConstantAttenuation", 1, param_slot_19 };
    static const QUParameter param_slot_20[] = {
	{ "la", &static_QUType_ptr, "GLfloat", QUParameter::In }
    };
    static const QUMethod slot_20 = {"setLinearAttenuation", 1, param_slot_20 };
    static const QUParameter param_slot_21[] = {
	{ "qa", &static_QUType_ptr, "GLfloat", QUParameter::In }
    };
    static const QUMethod slot_21 = {"setQuadraticAttenuation", 1, param_slot_21 };
    static const QUMethod slot_22 = {"reset", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "setLightType(LightType)", &slot_0, QMetaData::Public },
	{ "setSpotlight(bool)", &slot_1, QMetaData::Public },
	{ "setName()", &slot_2, QMetaData::Public },
	{ "setName(QString)", &slot_3, QMetaData::Public },
	{ "setEnabled(bool)", &slot_4, QMetaData::Public },
	{ "setPosition(Vector3f)", &slot_5, QMetaData::Public },
	{ "setAmbientColor(const QColor&)", &slot_6, QMetaData::Public },
	{ "setAmbientColor(const QColor&,int)", &slot_7, QMetaData::Public },
	{ "setAmbientColor(const GLfloat*)", &slot_8, QMetaData::Public },
	{ "setDiffuseColor(const QColor&)", &slot_9, QMetaData::Public },
	{ "setDiffuseColor(const QColor&,int)", &slot_10, QMetaData::Public },
	{ "setDiffuseColor(const GLfloat*)", &slot_11, QMetaData::Public },
	{ "setSpecularColor(const QColor&)", &slot_12, QMetaData::Public },
	{ "setSpecularColor(const QColor&,int)", &slot_13, QMetaData::Public },
	{ "setSpecularColor(const GLfloat*)", &slot_14, QMetaData::Public },
	{ "setMovingWithCamera(bool)", &slot_15, QMetaData::Public },
	{ "setSpotDirection(Vector3f)", &slot_16, QMetaData::Public },
	{ "setSpotExponent(GLfloat)", &slot_17, QMetaData::Public },
	{ "setSpotCutOffAngle(GLfloat)", &slot_18, QMetaData::Public },
	{ "setConstantAttenuation(GLfloat)", &slot_19, QMetaData::Public },
	{ "setLinearAttenuation(GLfloat)", &slot_20, QMetaData::Public },
	{ "setQuadraticAttenuation(GLfloat)", &slot_21, QMetaData::Public },
	{ "reset()", &slot_22, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"Light", parentObject,
	slot_tbl, 23,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_Light.setMetaObject( metaObj );
    return metaObj;
}

void* Light::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "Light" ) )
	return this;
    return QObject::qt_cast( clname );
}

bool Light::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: setLightType((LightType)(*((LightType*)static_QUType_ptr.get(_o+1)))); break;
    case 1: setSpotlight((bool)static_QUType_bool.get(_o+1)); break;
    case 2: setName(); break;
    case 3: setName((QString)static_QUType_QString.get(_o+1)); break;
    case 4: setEnabled((bool)static_QUType_bool.get(_o+1)); break;
    case 5: setPosition((Vector3f)(*((Vector3f*)static_QUType_ptr.get(_o+1)))); break;
    case 6: setAmbientColor((const QColor&)*((const QColor*)static_QUType_ptr.get(_o+1))); break;
    case 7: setAmbientColor((const QColor&)*((const QColor*)static_QUType_ptr.get(_o+1)),(int)static_QUType_int.get(_o+2)); break;
    case 8: setAmbientColor((const GLfloat*)static_QUType_ptr.get(_o+1)); break;
    case 9: setDiffuseColor((const QColor&)*((const QColor*)static_QUType_ptr.get(_o+1))); break;
    case 10: setDiffuseColor((const QColor&)*((const QColor*)static_QUType_ptr.get(_o+1)),(int)static_QUType_int.get(_o+2)); break;
    case 11: setDiffuseColor((const GLfloat*)static_QUType_ptr.get(_o+1)); break;
    case 12: setSpecularColor((const QColor&)*((const QColor*)static_QUType_ptr.get(_o+1))); break;
    case 13: setSpecularColor((const QColor&)*((const QColor*)static_QUType_ptr.get(_o+1)),(int)static_QUType_int.get(_o+2)); break;
    case 14: setSpecularColor((const GLfloat*)static_QUType_ptr.get(_o+1)); break;
    case 15: setMovingWithCamera((bool)static_QUType_bool.get(_o+1)); break;
    case 16: setSpotDirection((Vector3f)(*((Vector3f*)static_QUType_ptr.get(_o+1)))); break;
    case 17: setSpotExponent((GLfloat)(*((GLfloat*)static_QUType_ptr.get(_o+1)))); break;
    case 18: setSpotCutOffAngle((GLfloat)(*((GLfloat*)static_QUType_ptr.get(_o+1)))); break;
    case 19: setConstantAttenuation((GLfloat)(*((GLfloat*)static_QUType_ptr.get(_o+1)))); break;
    case 20: setLinearAttenuation((GLfloat)(*((GLfloat*)static_QUType_ptr.get(_o+1)))); break;
    case 21: setQuadraticAttenuation((GLfloat)(*((GLfloat*)static_QUType_ptr.get(_o+1)))); break;
    case 22: reset(); break;
    default:
	return QObject::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool Light::qt_emit( int _id, QUObject* _o )
{
    return QObject::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool Light::qt_property( int id, int f, QVariant* v)
{
    return QObject::qt_property( id, f, v);
}

bool Light::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
