/****************************************************************************
** TextureWidget meta object code from reading C++ file 'texturewidget.h'
**
** Created: Fri Oct 8 13:48:00 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../dialogs/texturewidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *TextureWidget::className() const
{
    return "TextureWidget";
}

QMetaObject *TextureWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_TextureWidget( "TextureWidget", &TextureWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString TextureWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "TextureWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString TextureWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "TextureWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* TextureWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "yes", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"setTextureEnabledGUI", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ "yes", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"setBlendingEnabledGUI", 1, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ "yes", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"setTextureEnabled", 1, param_slot_2 };
    static const QUParameter param_slot_3[] = {
	{ "scaleMode", &static_QUType_ptr, "QImage::ScaleMode", QUParameter::In },
	{ "apply", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_3 = {"setScaleMode", 2, param_slot_3 };
    static const QUParameter param_slot_4[] = {
	{ "yes", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"setMipmapingEnabled", 1, param_slot_4 };
    static const QUParameter param_slot_5[] = {
	{ "magFilter", &static_QUType_ptr, "GLenum", QUParameter::In },
	{ "apply", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_5 = {"setMagFilter", 2, param_slot_5 };
    static const QUParameter param_slot_6[] = {
	{ "minFilter", &static_QUType_ptr, "GLenum", QUParameter::In },
	{ "apply", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_6 = {"setMinFilter", 2, param_slot_6 };
    static const QUParameter param_slot_7[] = {
	{ "wrapS", &static_QUType_ptr, "GLenum", QUParameter::In },
	{ "apply", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_7 = {"setWrapS", 2, param_slot_7 };
    static const QUParameter param_slot_8[] = {
	{ "wrapT", &static_QUType_ptr, "GLenum", QUParameter::In },
	{ "apply", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_8 = {"setWrapT", 2, param_slot_8 };
    static const QUParameter param_slot_9[] = {
	{ "envMode", &static_QUType_ptr, "GLenum", QUParameter::In },
	{ "apply", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_9 = {"setEnvMode", 2, param_slot_9 };
    static const QUParameter param_slot_10[] = {
	{ "yes", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_10 = {"setBlendingEnabled", 1, param_slot_10 };
    static const QUParameter param_slot_11[] = {
	{ "srcFactor", &static_QUType_ptr, "GLenum", QUParameter::In },
	{ "apply", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_11 = {"setBlendSrcFactor", 2, param_slot_11 };
    static const QUParameter param_slot_12[] = {
	{ "destFactor", &static_QUType_ptr, "GLenum", QUParameter::In },
	{ "apply", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_12 = {"setBlendDestFactor", 2, param_slot_12 };
    static const QUParameter param_slot_13[] = {
	{ "yes", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_13 = {"setReflectingEnabled", 1, param_slot_13 };
    static const QUParameter param_slot_14[] = {
	{ "minW", &static_QUType_ptr, "GLfloat", QUParameter::In },
	{ "minH", &static_QUType_ptr, "GLfloat", QUParameter::In },
	{ "apply", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_14 = {"setMinWH", 3, param_slot_14 };
    static const QUParameter param_slot_15[] = {
	{ "maxW", &static_QUType_ptr, "GLfloat", QUParameter::In },
	{ "maxH", &static_QUType_ptr, "GLfloat", QUParameter::In },
	{ "apply", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_15 = {"setMaxWH", 3, param_slot_15 };
    static const QUParameter param_slot_16[] = {
	{ "on", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_16 = {"setDynamicPreview", 1, param_slot_16 };
    static const QUMethod slot_17 = {"refresh", 0, 0 };
    static const QUParameter param_slot_18[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_18 = {"setMagFilterFromCombo", 1, param_slot_18 };
    static const QUParameter param_slot_19[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_19 = {"setMinFilterFromCombo", 1, param_slot_19 };
    static const QUParameter param_slot_20[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_20 = {"setWrapSFromCombo", 1, param_slot_20 };
    static const QUParameter param_slot_21[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_21 = {"setWrapTFromCombo", 1, param_slot_21 };
    static const QUParameter param_slot_22[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_22 = {"setEnvModeFromCombo", 1, param_slot_22 };
    static const QUParameter param_slot_23[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_23 = {"setBlendSrcFactorFromCombo", 1, param_slot_23 };
    static const QUParameter param_slot_24[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_24 = {"setBlendDestFactorFromCombo", 1, param_slot_24 };
    static const QUParameter param_slot_25[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_25 = {"setScaleModeFromCombo", 1, param_slot_25 };
    static const QUParameter param_slot_26[] = {
	{ 0, &static_QUType_ptr, "float", QUParameter::In }
    };
    static const QUMethod slot_26 = {"minWHChanged", 1, param_slot_26 };
    static const QUParameter param_slot_27[] = {
	{ 0, &static_QUType_ptr, "float", QUParameter::In }
    };
    static const QUMethod slot_27 = {"maxWHChanged", 1, param_slot_27 };
    static const QUMethod slot_28 = {"openFileDialog", 0, 0 };
    static const QUMethod slot_29 = {"removeImage", 0, 0 };
    static const QUMethod slot_30 = {"makeCurrentTextureDefault", 0, 0 };
    static const QUMethod slot_31 = {"resetToDefaultTexture", 0, 0 };
    static const QUParameter param_slot_32[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_32 = {"loadTextureFromCombo", 1, param_slot_32 };
    static const QMetaData slot_tbl[] = {
	{ "setTextureEnabledGUI(bool)", &slot_0, QMetaData::Private },
	{ "setBlendingEnabledGUI(bool)", &slot_1, QMetaData::Private },
	{ "setTextureEnabled(bool)", &slot_2, QMetaData::Private },
	{ "setScaleMode(QImage::ScaleMode,bool)", &slot_3, QMetaData::Private },
	{ "setMipmapingEnabled(bool)", &slot_4, QMetaData::Private },
	{ "setMagFilter(GLenum,bool)", &slot_5, QMetaData::Private },
	{ "setMinFilter(GLenum,bool)", &slot_6, QMetaData::Private },
	{ "setWrapS(GLenum,bool)", &slot_7, QMetaData::Private },
	{ "setWrapT(GLenum,bool)", &slot_8, QMetaData::Private },
	{ "setEnvMode(GLenum,bool)", &slot_9, QMetaData::Private },
	{ "setBlendingEnabled(bool)", &slot_10, QMetaData::Private },
	{ "setBlendSrcFactor(GLenum,bool)", &slot_11, QMetaData::Private },
	{ "setBlendDestFactor(GLenum,bool)", &slot_12, QMetaData::Private },
	{ "setReflectingEnabled(bool)", &slot_13, QMetaData::Private },
	{ "setMinWH(GLfloat,GLfloat,bool)", &slot_14, QMetaData::Private },
	{ "setMaxWH(GLfloat,GLfloat,bool)", &slot_15, QMetaData::Private },
	{ "setDynamicPreview(bool)", &slot_16, QMetaData::Private },
	{ "refresh()", &slot_17, QMetaData::Private },
	{ "setMagFilterFromCombo(int)", &slot_18, QMetaData::Private },
	{ "setMinFilterFromCombo(int)", &slot_19, QMetaData::Private },
	{ "setWrapSFromCombo(int)", &slot_20, QMetaData::Private },
	{ "setWrapTFromCombo(int)", &slot_21, QMetaData::Private },
	{ "setEnvModeFromCombo(int)", &slot_22, QMetaData::Private },
	{ "setBlendSrcFactorFromCombo(int)", &slot_23, QMetaData::Private },
	{ "setBlendDestFactorFromCombo(int)", &slot_24, QMetaData::Private },
	{ "setScaleModeFromCombo(int)", &slot_25, QMetaData::Private },
	{ "minWHChanged(float)", &slot_26, QMetaData::Private },
	{ "maxWHChanged(float)", &slot_27, QMetaData::Private },
	{ "openFileDialog()", &slot_28, QMetaData::Private },
	{ "removeImage()", &slot_29, QMetaData::Private },
	{ "makeCurrentTextureDefault()", &slot_30, QMetaData::Private },
	{ "resetToDefaultTexture()", &slot_31, QMetaData::Private },
	{ "loadTextureFromCombo(int)", &slot_32, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"TextureWidget", parentObject,
	slot_tbl, 33,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_TextureWidget.setMetaObject( metaObj );
    return metaObj;
}

void* TextureWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "TextureWidget" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool TextureWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: setTextureEnabledGUI((bool)static_QUType_bool.get(_o+1)); break;
    case 1: setBlendingEnabledGUI((bool)static_QUType_bool.get(_o+1)); break;
    case 2: setTextureEnabled((bool)static_QUType_bool.get(_o+1)); break;
    case 3: setScaleMode((QImage::ScaleMode)(*((QImage::ScaleMode*)static_QUType_ptr.get(_o+1))),(bool)static_QUType_bool.get(_o+2)); break;
    case 4: setMipmapingEnabled((bool)static_QUType_bool.get(_o+1)); break;
    case 5: setMagFilter((GLenum)(*((GLenum*)static_QUType_ptr.get(_o+1))),(bool)static_QUType_bool.get(_o+2)); break;
    case 6: setMinFilter((GLenum)(*((GLenum*)static_QUType_ptr.get(_o+1))),(bool)static_QUType_bool.get(_o+2)); break;
    case 7: setWrapS((GLenum)(*((GLenum*)static_QUType_ptr.get(_o+1))),(bool)static_QUType_bool.get(_o+2)); break;
    case 8: setWrapT((GLenum)(*((GLenum*)static_QUType_ptr.get(_o+1))),(bool)static_QUType_bool.get(_o+2)); break;
    case 9: setEnvMode((GLenum)(*((GLenum*)static_QUType_ptr.get(_o+1))),(bool)static_QUType_bool.get(_o+2)); break;
    case 10: setBlendingEnabled((bool)static_QUType_bool.get(_o+1)); break;
    case 11: setBlendSrcFactor((GLenum)(*((GLenum*)static_QUType_ptr.get(_o+1))),(bool)static_QUType_bool.get(_o+2)); break;
    case 12: setBlendDestFactor((GLenum)(*((GLenum*)static_QUType_ptr.get(_o+1))),(bool)static_QUType_bool.get(_o+2)); break;
    case 13: setReflectingEnabled((bool)static_QUType_bool.get(_o+1)); break;
    case 14: setMinWH((GLfloat)(*((GLfloat*)static_QUType_ptr.get(_o+1))),(GLfloat)(*((GLfloat*)static_QUType_ptr.get(_o+2))),(bool)static_QUType_bool.get(_o+3)); break;
    case 15: setMaxWH((GLfloat)(*((GLfloat*)static_QUType_ptr.get(_o+1))),(GLfloat)(*((GLfloat*)static_QUType_ptr.get(_o+2))),(bool)static_QUType_bool.get(_o+3)); break;
    case 16: setDynamicPreview((bool)static_QUType_bool.get(_o+1)); break;
    case 17: refresh(); break;
    case 18: setMagFilterFromCombo((int)static_QUType_int.get(_o+1)); break;
    case 19: setMinFilterFromCombo((int)static_QUType_int.get(_o+1)); break;
    case 20: setWrapSFromCombo((int)static_QUType_int.get(_o+1)); break;
    case 21: setWrapTFromCombo((int)static_QUType_int.get(_o+1)); break;
    case 22: setEnvModeFromCombo((int)static_QUType_int.get(_o+1)); break;
    case 23: setBlendSrcFactorFromCombo((int)static_QUType_int.get(_o+1)); break;
    case 24: setBlendDestFactorFromCombo((int)static_QUType_int.get(_o+1)); break;
    case 25: setScaleModeFromCombo((int)static_QUType_int.get(_o+1)); break;
    case 26: minWHChanged((float)(*((float*)static_QUType_ptr.get(_o+1)))); break;
    case 27: maxWHChanged((float)(*((float*)static_QUType_ptr.get(_o+1)))); break;
    case 28: openFileDialog(); break;
    case 29: removeImage(); break;
    case 30: makeCurrentTextureDefault(); break;
    case 31: resetToDefaultTexture(); break;
    case 32: loadTextureFromCombo((int)static_QUType_int.get(_o+1)); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool TextureWidget::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool TextureWidget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool TextureWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
