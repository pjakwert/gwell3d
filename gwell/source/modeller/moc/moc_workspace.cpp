/****************************************************************************
** Workspace meta object code from reading C++ file 'workspace.h'
**
** Created: Fri Oct 8 13:46:56 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../workspace.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *Workspace::className() const
{
    return "Workspace";
}

QMetaObject *Workspace::metaObj = 0;
static QMetaObjectCleanUp cleanUp_Workspace( "Workspace", &Workspace::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString Workspace::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Workspace", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString Workspace::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Workspace", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* Workspace::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "selected", &static_QUType_ptr, "QPtrList<ViNTreeNode>", QUParameter::In }
    };
    static const QUMethod slot_0 = {"userSelected", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ "mType", &static_QUType_ptr, "MModifier::ModifierType", QUParameter::In }
    };
    static const QUMethod slot_1 = {"modifierChangedFromCellFrame", 1, param_slot_1 };
    static const QUMethod slot_2 = {"structureChanged", 0, 0 };
    static const QUParameter param_slot_3[] = {
	{ "multiPolyh", &static_QUType_ptr, "ViMultiPolyh", QUParameter::In }
    };
    static const QUMethod slot_3 = {"setMultiPolyh", 1, param_slot_3 };
    static const QUParameter param_slot_4[] = {
	{ "lightsList", &static_QUType_ptr, "QPtrList<Light>", QUParameter::In }
    };
    static const QUMethod slot_4 = {"setLightsList", 1, param_slot_4 };
    static const QUParameter param_slot_5[] = {
	{ "light", &static_QUType_ptr, "Light", QUParameter::In }
    };
    static const QUMethod slot_5 = {"setLight", 1, param_slot_5 };
    static const QUParameter param_slot_6[] = {
	{ "yes", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_6 = {"setLightingEnabled", 1, param_slot_6 };
    static const QUParameter param_slot_7[] = {
	{ 0, &static_QUType_ptr, "GLenum", QUParameter::In },
	{ 0, &static_QUType_ptr, "Light", QUParameter::In }
    };
    static const QUMethod slot_7 = {"updateLightColor", 2, param_slot_7 };
    static const QUParameter param_slot_8[] = {
	{ "selected", &static_QUType_ptr, "QPtrList<ViNTreeNode>", QUParameter::In }
    };
    static const QUMethod slot_8 = {"setSelected", 1, param_slot_8 };
    static const QUParameter param_slot_9[] = {
	{ "modifier", &static_QUType_ptr, "MModifier", QUParameter::In }
    };
    static const QUMethod slot_9 = {"setModifier", 1, param_slot_9 };
    static const QUMethod slot_10 = {"refresh", 0, 0 };
    static const QUParameter param_slot_11[] = {
	{ "yes", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_11 = {"setCameraIsMovingForAll", 1, param_slot_11 };
    static const QUMethod slot_12 = {"showEntireSceneForAll", 0, 0 };
    static const QUParameter param_slot_13[] = {
	{ "on", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_13 = {"showGridForAll", 1, param_slot_13 };
    static const QUParameter param_slot_14[] = {
	{ "on", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_14 = {"showAxisForAll", 1, param_slot_14 };
    static const QUParameter param_slot_15[] = {
	{ "on", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_15 = {"showLightsForAll", 1, param_slot_15 };
    static const QUParameter param_slot_16[] = {
	{ "direction", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_16 = {"viewDirectionChangedForAll", 1, param_slot_16 };
    static const QUParameter param_slot_17[] = {
	{ "type", &static_QUType_ptr, "DrawMethod", QUParameter::In }
    };
    static const QUMethod slot_17 = {"setViewTypeForAll", 1, param_slot_17 };
    static const QUParameter param_slot_18[] = {
	{ "type", &static_QUType_ptr, "qglviewer::Camera::Type", QUParameter::In }
    };
    static const QUMethod slot_18 = {"setProjTypeForAll", 1, param_slot_18 };
    static const QMetaData slot_tbl[] = {
	{ "userSelected(QPtrList<ViNTreeNode>*)", &slot_0, QMetaData::Private },
	{ "modifierChangedFromCellFrame(MModifier::ModifierType)", &slot_1, QMetaData::Private },
	{ "structureChanged()", &slot_2, QMetaData::Private },
	{ "setMultiPolyh(ViMultiPolyh*)", &slot_3, QMetaData::Public },
	{ "setLightsList(QPtrList<Light>*)", &slot_4, QMetaData::Public },
	{ "setLight(Light*)", &slot_5, QMetaData::Public },
	{ "setLightingEnabled(bool)", &slot_6, QMetaData::Public },
	{ "updateLightColor(GLenum,Light*)", &slot_7, QMetaData::Public },
	{ "setSelected(QPtrList<ViNTreeNode>*)", &slot_8, QMetaData::Public },
	{ "setModifier(MModifier*)", &slot_9, QMetaData::Public },
	{ "refresh()", &slot_10, QMetaData::Public },
	{ "setCameraIsMovingForAll(bool)", &slot_11, QMetaData::Public },
	{ "showEntireSceneForAll()", &slot_12, QMetaData::Public },
	{ "showGridForAll(bool)", &slot_13, QMetaData::Public },
	{ "showAxisForAll(bool)", &slot_14, QMetaData::Public },
	{ "showLightsForAll(bool)", &slot_15, QMetaData::Public },
	{ "viewDirectionChangedForAll(int)", &slot_16, QMetaData::Public },
	{ "setViewTypeForAll(DrawMethod)", &slot_17, QMetaData::Public },
	{ "setProjTypeForAll(qglviewer::Camera::Type)", &slot_18, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ "mType", &static_QUType_ptr, "MModifier::ModifierType", QUParameter::In }
    };
    static const QUMethod signal_0 = {"setModifierFromCellFrame", 1, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ "selected", &static_QUType_ptr, "QPtrList<ViNTreeNode>", QUParameter::In }
    };
    static const QUMethod signal_1 = {"userSelectedObject", 1, param_signal_1 };
    static const QUMethod signal_2 = {"mphStructureChanged", 0, 0 };
    static const QMetaData signal_tbl[] = {
	{ "setModifierFromCellFrame(MModifier::ModifierType)", &signal_0, QMetaData::Public },
	{ "userSelectedObject(QPtrList<ViNTreeNode>*)", &signal_1, QMetaData::Public },
	{ "mphStructureChanged()", &signal_2, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"Workspace", parentObject,
	slot_tbl, 19,
	signal_tbl, 3,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_Workspace.setMetaObject( metaObj );
    return metaObj;
}

void* Workspace::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "Workspace" ) )
	return this;
    return QWidget::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL setModifierFromCellFrame
void Workspace::setModifierFromCellFrame( MModifier::ModifierType t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 0 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_ptr.set(o+1,&t0);
    activate_signal( clist, o );
}

// SIGNAL userSelectedObject
void Workspace::userSelectedObject( QPtrList<ViNTreeNode>* t0 )
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

// SIGNAL mphStructureChanged
void Workspace::mphStructureChanged()
{
    activate_signal( staticMetaObject()->signalOffset() + 2 );
}

bool Workspace::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: userSelected((QPtrList<ViNTreeNode>*)static_QUType_ptr.get(_o+1)); break;
    case 1: modifierChangedFromCellFrame((MModifier::ModifierType)(*((MModifier::ModifierType*)static_QUType_ptr.get(_o+1)))); break;
    case 2: structureChanged(); break;
    case 3: setMultiPolyh((ViMultiPolyh*)static_QUType_ptr.get(_o+1)); break;
    case 4: setLightsList((QPtrList<Light>*)static_QUType_ptr.get(_o+1)); break;
    case 5: setLight((Light*)static_QUType_ptr.get(_o+1)); break;
    case 6: setLightingEnabled((bool)static_QUType_bool.get(_o+1)); break;
    case 7: updateLightColor((GLenum)(*((GLenum*)static_QUType_ptr.get(_o+1))),(Light*)static_QUType_ptr.get(_o+2)); break;
    case 8: setSelected((QPtrList<ViNTreeNode>*)static_QUType_ptr.get(_o+1)); break;
    case 9: setModifier((MModifier*)static_QUType_ptr.get(_o+1)); break;
    case 10: refresh(); break;
    case 11: setCameraIsMovingForAll((bool)static_QUType_bool.get(_o+1)); break;
    case 12: showEntireSceneForAll(); break;
    case 13: showGridForAll((bool)static_QUType_bool.get(_o+1)); break;
    case 14: showAxisForAll((bool)static_QUType_bool.get(_o+1)); break;
    case 15: showLightsForAll((bool)static_QUType_bool.get(_o+1)); break;
    case 16: viewDirectionChangedForAll((int)static_QUType_int.get(_o+1)); break;
    case 17: setViewTypeForAll((DrawMethod)(*((DrawMethod*)static_QUType_ptr.get(_o+1)))); break;
    case 18: setProjTypeForAll((qglviewer::Camera::Type)(*((qglviewer::Camera::Type*)static_QUType_ptr.get(_o+1)))); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool Workspace::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: setModifierFromCellFrame((MModifier::ModifierType)(*((MModifier::ModifierType*)static_QUType_ptr.get(_o+1)))); break;
    case 1: userSelectedObject((QPtrList<ViNTreeNode>*)static_QUType_ptr.get(_o+1)); break;
    case 2: mphStructureChanged(); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool Workspace::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool Workspace::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
