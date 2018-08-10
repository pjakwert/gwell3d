/****************************************************************************
** OptionsWidget meta object code from reading C++ file 'optionswidget.h'
**
** Created: Fri Oct 8 13:52:56 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../toolwidgets/optionswidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *OptionsWidget::className() const
{
    return "OptionsWidget";
}

QMetaObject *OptionsWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_OptionsWidget( "OptionsWidget", &OptionsWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString OptionsWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "OptionsWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString OptionsWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "OptionsWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* OptionsWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"refresh", 0, 0 };
    static const QUMethod slot_1 = {"chooseDirectory", 0, 0 };
    static const QUMethod slot_2 = {"chooseColor", 0, 0 };
    static const QUParameter param_slot_3[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_3 = {"shadeChanged", 1, param_slot_3 };
    static const QUParameter param_slot_4[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"corrChanged", 1, param_slot_4 };
    static const QUParameter param_slot_5[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_5 = {"decChanged", 1, param_slot_5 };
    static const QUParameter param_slot_6[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_6 = {"langChanged", 1, param_slot_6 };
    static const QUParameter param_slot_7[] = {
	{ "path", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_7 = {"fillLangCombo", 1, param_slot_7 };
    static const QUParameter param_slot_8[] = {
	{ "fileName", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_8 = {"setTranslator", 1, param_slot_8 };
    static const QUMethod slot_9 = {"saveSettings", 0, 0 };
    static const QUMethod slot_10 = {"restoreSettings", 0, 0 };
    static const QUMethod slot_11 = {"resetToDefaults", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "refresh()", &slot_0, QMetaData::Private },
	{ "chooseDirectory()", &slot_1, QMetaData::Private },
	{ "chooseColor()", &slot_2, QMetaData::Private },
	{ "shadeChanged(int)", &slot_3, QMetaData::Private },
	{ "corrChanged(int)", &slot_4, QMetaData::Private },
	{ "decChanged(int)", &slot_5, QMetaData::Private },
	{ "langChanged(int)", &slot_6, QMetaData::Private },
	{ "fillLangCombo(const QString&)", &slot_7, QMetaData::Private },
	{ "setTranslator(const QString&)", &slot_8, QMetaData::Private },
	{ "saveSettings()", &slot_9, QMetaData::Private },
	{ "restoreSettings()", &slot_10, QMetaData::Private },
	{ "resetToDefaults()", &slot_11, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"OptionsWidget", parentObject,
	slot_tbl, 12,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_OptionsWidget.setMetaObject( metaObj );
    return metaObj;
}

void* OptionsWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "OptionsWidget" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool OptionsWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: refresh(); break;
    case 1: chooseDirectory(); break;
    case 2: chooseColor(); break;
    case 3: shadeChanged((int)static_QUType_int.get(_o+1)); break;
    case 4: corrChanged((int)static_QUType_int.get(_o+1)); break;
    case 5: decChanged((int)static_QUType_int.get(_o+1)); break;
    case 6: langChanged((int)static_QUType_int.get(_o+1)); break;
    case 7: fillLangCombo((const QString&)static_QUType_QString.get(_o+1)); break;
    case 8: setTranslator((const QString&)static_QUType_QString.get(_o+1)); break;
    case 9: saveSettings(); break;
    case 10: restoreSettings(); break;
    case 11: resetToDefaults(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool OptionsWidget::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool OptionsWidget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool OptionsWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
