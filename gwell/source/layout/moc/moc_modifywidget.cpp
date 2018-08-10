/****************************************************************************
** ModifyWidget meta object code from reading C++ file 'modifywidget.h'
**
** Created: Wed Oct 13 20:04:37 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../toolwidgets/modifywidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *ModifyWidget::className() const
{
    return "ModifyWidget";
}

QMetaObject *ModifyWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_ModifyWidget( "ModifyWidget", &ModifyWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString ModifyWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ModifyWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString ModifyWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ModifyWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* ModifyWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"buttonClicked", 0, 0 };
    static const QUParameter param_slot_1[] = {
	{ "name", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"setName", 1, param_slot_1 };
    static const QUMethod slot_2 = {"setTrans", 0, 0 };
    static const QUMethod slot_3 = {"setRot", 0, 0 };
    static const QUMethod slot_4 = {"setScale", 0, 0 };
    static const QUMethod slot_5 = {"fitScale", 0, 0 };
    static const QUParameter param_slot_6[] = {
	{ "on", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_6 = {"setDeg", 1, param_slot_6 };
    static const QUParameter param_slot_7[] = {
	{ "on", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_7 = {"setRad", 1, param_slot_7 };
    static const QUParameter param_slot_8[] = {
	{ "mType", &static_QUType_ptr, "MModifier::ModifierType", QUParameter::In },
	{ "v", &static_QUType_ptr, "Vector3f", QUParameter::In }
    };
    static const QUMethod slot_8 = {"updateData", 2, param_slot_8 };
    static const QUParameter param_slot_9[] = {
	{ "yes", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_9 = {"enableInput", 1, param_slot_9 };
    static const QUMethod slot_10 = {"setDefaultModifier", 0, 0 };
    static const QUParameter param_slot_11[] = {
	{ "mType", &static_QUType_ptr, "MModifier::ModifierType", QUParameter::In }
    };
    static const QUMethod slot_11 = {"setModifier", 1, param_slot_11 };
    static const QUParameter param_slot_12[] = {
	{ "selectedList", &static_QUType_ptr, "QPtrList<ViMultiPolyh>", QUParameter::In }
    };
    static const QUMethod slot_12 = {"setSelected", 1, param_slot_12 };
    static const QMetaData slot_tbl[] = {
	{ "buttonClicked()", &slot_0, QMetaData::Private },
	{ "setName(const QString&)", &slot_1, QMetaData::Private },
	{ "setTrans()", &slot_2, QMetaData::Private },
	{ "setRot()", &slot_3, QMetaData::Private },
	{ "setScale()", &slot_4, QMetaData::Private },
	{ "fitScale()", &slot_5, QMetaData::Private },
	{ "setDeg(bool)", &slot_6, QMetaData::Private },
	{ "setRad(bool)", &slot_7, QMetaData::Private },
	{ "updateData(MModifier::ModifierType,Vector3f)", &slot_8, QMetaData::Private },
	{ "enableInput(bool)", &slot_9, QMetaData::Private },
	{ "setDefaultModifier()", &slot_10, QMetaData::Public },
	{ "setModifier(MModifier::ModifierType)", &slot_11, QMetaData::Public },
	{ "setSelected(QPtrList<ViMultiPolyh>*)", &slot_12, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ "modifier", &static_QUType_ptr, "MModifier", QUParameter::In }
    };
    static const QUMethod signal_0 = {"sendModifier", 1, param_signal_0 };
    static const QUMethod signal_1 = {"modifierChoosed", 0, 0 };
    static const QUMethod signal_2 = {"nameChanged", 0, 0 };
    static const QMetaData signal_tbl[] = {
	{ "sendModifier(MModifier*)", &signal_0, QMetaData::Public },
	{ "modifierChoosed()", &signal_1, QMetaData::Public },
	{ "nameChanged()", &signal_2, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"ModifyWidget", parentObject,
	slot_tbl, 13,
	signal_tbl, 3,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_ModifyWidget.setMetaObject( metaObj );
    return metaObj;
}

void* ModifyWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "ModifyWidget" ) )
	return this;
    return QWidget::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL sendModifier
void ModifyWidget::sendModifier( MModifier* t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 0 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_ptr.set(o+1,t0);
    activate_signal( clist, o );
}

// SIGNAL modifierChoosed
void ModifyWidget::modifierChoosed()
{
    activate_signal( staticMetaObject()->signalOffset() + 1 );
}

// SIGNAL nameChanged
void ModifyWidget::nameChanged()
{
    activate_signal( staticMetaObject()->signalOffset() + 2 );
}

bool ModifyWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: buttonClicked(); break;
    case 1: setName((const QString&)static_QUType_QString.get(_o+1)); break;
    case 2: setTrans(); break;
    case 3: setRot(); break;
    case 4: setScale(); break;
    case 5: fitScale(); break;
    case 6: setDeg((bool)static_QUType_bool.get(_o+1)); break;
    case 7: setRad((bool)static_QUType_bool.get(_o+1)); break;
    case 8: updateData((MModifier::ModifierType)(*((MModifier::ModifierType*)static_QUType_ptr.get(_o+1))),(Vector3f)(*((Vector3f*)static_QUType_ptr.get(_o+2)))); break;
    case 9: enableInput((bool)static_QUType_bool.get(_o+1)); break;
    case 10: setDefaultModifier(); break;
    case 11: setModifier((MModifier::ModifierType)(*((MModifier::ModifierType*)static_QUType_ptr.get(_o+1)))); break;
    case 12: setSelected((QPtrList<ViMultiPolyh>*)static_QUType_ptr.get(_o+1)); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool ModifyWidget::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: sendModifier((MModifier*)static_QUType_ptr.get(_o+1)); break;
    case 1: modifierChoosed(); break;
    case 2: nameChanged(); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool ModifyWidget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool ModifyWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
