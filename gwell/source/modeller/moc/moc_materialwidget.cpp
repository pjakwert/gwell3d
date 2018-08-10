/****************************************************************************
** MaterialWidget meta object code from reading C++ file 'materialwidget.h'
**
** Created: Fri Oct 8 13:47:39 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../dialogs/materialwidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MaterialWidget::className() const
{
    return "MaterialWidget";
}

QMetaObject *MaterialWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MaterialWidget( "MaterialWidget", &MaterialWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString MaterialWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MaterialWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MaterialWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MaterialWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MaterialWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ 0, &static_QUType_int, 0, QUParameter::Out },
	{ "mat", &static_QUType_ptr, "Material", QUParameter::In }
    };
    static const QUMethod slot_0 = {"deduceMaterial", 2, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ "on", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"setMaterialEnabled", 1, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ "on", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"setDynamicPreview", 1, param_slot_2 };
    static const QUMethod slot_3 = {"makeMaterialDefault", 0, 0 };
    static const QUMethod slot_4 = {"resetToDefaultMaterial", 0, 0 };
    static const QUParameter param_slot_5[] = {
	{ "applyTo", &static_QUType_ptr, "GLenum", QUParameter::In }
    };
    static const QUMethod slot_5 = {"setApplyTo", 1, param_slot_5 };
    static const QUParameter param_slot_6[] = {
	{ "num", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_6 = {"setApplyToFromButton", 1, param_slot_6 };
    static const QUParameter param_slot_7[] = {
	{ "color", &static_QUType_varptr, "\x0a", QUParameter::In },
	{ "alpha", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_7 = {"setAmbientColor", 2, param_slot_7 };
    static const QUParameter param_slot_8[] = {
	{ "color", &static_QUType_varptr, "\x0a", QUParameter::In },
	{ "alpha", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_8 = {"setDiffuseColor", 2, param_slot_8 };
    static const QUParameter param_slot_9[] = {
	{ "color", &static_QUType_varptr, "\x0a", QUParameter::In },
	{ "alpha", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_9 = {"setSpecularColor", 2, param_slot_9 };
    static const QUParameter param_slot_10[] = {
	{ "color", &static_QUType_varptr, "\x0a", QUParameter::In },
	{ "alpha", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_10 = {"setEmissionColor", 2, param_slot_10 };
    static const QUParameter param_slot_11[] = {
	{ "shininess", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_11 = {"setShininess", 1, param_slot_11 };
    static const QUMethod slot_12 = {"updateGLMatSyntaxText", 0, 0 };
    static const QUMethod slot_13 = {"saveMaterial", 0, 0 };
    static const QUParameter param_slot_14[] = {
	{ 0, &static_QUType_int, 0, QUParameter::Out },
	{ "path", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_14 = {"loadMaterials", 2, param_slot_14 };
    static const QUParameter param_slot_15[] = {
	{ 0, &static_QUType_int, 0, QUParameter::Out },
	{ "name", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_15 = {"readFromFile", 2, param_slot_15 };
    static const QUParameter param_slot_16[] = {
	{ "index", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_16 = {"selectMaterialFromCombo", 1, param_slot_16 };
    static const QUMethod slot_17 = {"undoMaterials", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "deduceMaterial(const Material*)", &slot_0, QMetaData::Private },
	{ "setMaterialEnabled(bool)", &slot_1, QMetaData::Private },
	{ "setDynamicPreview(bool)", &slot_2, QMetaData::Private },
	{ "makeMaterialDefault()", &slot_3, QMetaData::Private },
	{ "resetToDefaultMaterial()", &slot_4, QMetaData::Private },
	{ "setApplyTo(GLenum)", &slot_5, QMetaData::Private },
	{ "setApplyToFromButton(int)", &slot_6, QMetaData::Private },
	{ "setAmbientColor(const QColor&,int)", &slot_7, QMetaData::Private },
	{ "setDiffuseColor(const QColor&,int)", &slot_8, QMetaData::Private },
	{ "setSpecularColor(const QColor&,int)", &slot_9, QMetaData::Private },
	{ "setEmissionColor(const QColor&,int)", &slot_10, QMetaData::Private },
	{ "setShininess(int)", &slot_11, QMetaData::Private },
	{ "updateGLMatSyntaxText()", &slot_12, QMetaData::Private },
	{ "saveMaterial()", &slot_13, QMetaData::Private },
	{ "loadMaterials(QString)", &slot_14, QMetaData::Private },
	{ "readFromFile(QString)", &slot_15, QMetaData::Private },
	{ "selectMaterialFromCombo(int)", &slot_16, QMetaData::Private },
	{ "undoMaterials()", &slot_17, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"MaterialWidget", parentObject,
	slot_tbl, 18,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_MaterialWidget.setMetaObject( metaObj );
    return metaObj;
}

void* MaterialWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "MaterialWidget" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool MaterialWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: static_QUType_int.set(_o,deduceMaterial((const Material*)static_QUType_ptr.get(_o+1))); break;
    case 1: setMaterialEnabled((bool)static_QUType_bool.get(_o+1)); break;
    case 2: setDynamicPreview((bool)static_QUType_bool.get(_o+1)); break;
    case 3: makeMaterialDefault(); break;
    case 4: resetToDefaultMaterial(); break;
    case 5: setApplyTo((GLenum)(*((GLenum*)static_QUType_ptr.get(_o+1)))); break;
    case 6: setApplyToFromButton((int)static_QUType_int.get(_o+1)); break;
    case 7: setAmbientColor((const QColor&)*((const QColor*)static_QUType_ptr.get(_o+1)),(int)static_QUType_int.get(_o+2)); break;
    case 8: setDiffuseColor((const QColor&)*((const QColor*)static_QUType_ptr.get(_o+1)),(int)static_QUType_int.get(_o+2)); break;
    case 9: setSpecularColor((const QColor&)*((const QColor*)static_QUType_ptr.get(_o+1)),(int)static_QUType_int.get(_o+2)); break;
    case 10: setEmissionColor((const QColor&)*((const QColor*)static_QUType_ptr.get(_o+1)),(int)static_QUType_int.get(_o+2)); break;
    case 11: setShininess((int)static_QUType_int.get(_o+1)); break;
    case 12: updateGLMatSyntaxText(); break;
    case 13: saveMaterial(); break;
    case 14: static_QUType_int.set(_o,loadMaterials((QString)static_QUType_QString.get(_o+1))); break;
    case 15: static_QUType_int.set(_o,readFromFile((QString)static_QUType_QString.get(_o+1))); break;
    case 16: selectMaterialFromCombo((int)static_QUType_int.get(_o+1)); break;
    case 17: undoMaterials(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool MaterialWidget::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool MaterialWidget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool MaterialWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
