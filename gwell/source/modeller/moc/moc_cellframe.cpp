/****************************************************************************
** CellFrame meta object code from reading C++ file 'cellframe.h'
**
** Created: Fri Oct 8 13:45:22 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../cellframe.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *CellFrame::className() const
{
    return "CellFrame";
}

QMetaObject *CellFrame::metaObj = 0;
static QMetaObjectCleanUp cleanUp_CellFrame( "CellFrame", &CellFrame::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString CellFrame::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "CellFrame", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString CellFrame::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "CellFrame", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* CellFrame::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QGLViewer::staticMetaObject();
    static const QUMethod slot_0 = {"popupAboutToShow", 0, 0 };
    static const QUParameter param_slot_1[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"choosedFromPopup", 1, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ "light", &static_QUType_ptr, "Light", QUParameter::In }
    };
    static const QUMethod slot_2 = {"setLight", 1, param_slot_2 };
    static const QUMethod slot_3 = {"setAllLights", 0, 0 };
    static const QUParameter param_slot_4[] = {
	{ "on", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"turnAllLights", 1, param_slot_4 };
    static const QUParameter param_slot_5[] = {
	{ "GLcolorChanged", &static_QUType_ptr, "GLenum", QUParameter::In },
	{ "light", &static_QUType_ptr, "Light", QUParameter::In }
    };
    static const QUMethod slot_5 = {"updateColorForLight", 2, param_slot_5 };
    static const QUMethod slot_6 = {"selectAll", 0, 0 };
    static const QUParameter param_slot_7[] = {
	{ "selectedList", &static_QUType_ptr, "QPtrList<ViNTreeNode>", QUParameter::In }
    };
    static const QUMethod slot_7 = {"setSelectedSlot", 1, param_slot_7 };
    static const QUParameter param_slot_8[] = {
	{ "on", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_8 = {"setCameraMoving", 1, param_slot_8 };
    static const QUParameter param_slot_9[] = {
	{ "type", &static_QUType_ptr, "qglviewer::Camera::Type", QUParameter::In }
    };
    static const QUMethod slot_9 = {"setCameraType", 1, param_slot_9 };
    static const QUParameter param_slot_10[] = {
	{ "drawMethod", &static_QUType_ptr, "DrawMethod", QUParameter::In }
    };
    static const QUMethod slot_10 = {"setDrawMethod", 1, param_slot_10 };
    static const QUMethod slot_11 = {"showAllScene", 0, 0 };
    static const QUParameter param_slot_12[] = {
	{ "direction", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_12 = {"setViewDirection", 1, param_slot_12 };
    static const QUParameter param_slot_13[] = {
	{ "on", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_13 = {"setDrawAxisXYZ", 1, param_slot_13 };
    static const QUParameter param_slot_14[] = {
	{ "on", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_14 = {"setDrawGridXZ", 1, param_slot_14 };
    static const QUParameter param_slot_15[] = {
	{ "on", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_15 = {"setDrawGrid3D", 1, param_slot_15 };
    static const QUParameter param_slot_16[] = {
	{ "on", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_16 = {"setDrawLights", 1, param_slot_16 };
    static const QUMethod slot_17 = {"maximize", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "popupAboutToShow()", &slot_0, QMetaData::Private },
	{ "choosedFromPopup(int)", &slot_1, QMetaData::Private },
	{ "setLight(Light*)", &slot_2, QMetaData::Public },
	{ "setAllLights()", &slot_3, QMetaData::Public },
	{ "turnAllLights(bool)", &slot_4, QMetaData::Public },
	{ "updateColorForLight(GLenum,Light*)", &slot_5, QMetaData::Public },
	{ "selectAll()", &slot_6, QMetaData::Public },
	{ "setSelectedSlot(QPtrList<ViNTreeNode>*)", &slot_7, QMetaData::Public },
	{ "setCameraMoving(bool)", &slot_8, QMetaData::Public },
	{ "setCameraType(qglviewer::Camera::Type)", &slot_9, QMetaData::Public },
	{ "setDrawMethod(DrawMethod)", &slot_10, QMetaData::Public },
	{ "showAllScene()", &slot_11, QMetaData::Public },
	{ "setViewDirection(int)", &slot_12, QMetaData::Public },
	{ "setDrawAxisXYZ(bool)", &slot_13, QMetaData::Public },
	{ "setDrawGridXZ(bool)", &slot_14, QMetaData::Public },
	{ "setDrawGrid3D(bool)", &slot_15, QMetaData::Public },
	{ "setDrawLights(bool)", &slot_16, QMetaData::Public },
	{ "maximize()", &slot_17, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ "mType", &static_QUType_ptr, "MModifier::ModifierType", QUParameter::In }
    };
    static const QUMethod signal_0 = {"setModifierFromCellFrame", 1, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ "selectedList", &static_QUType_ptr, "QPtrList<ViNTreeNode>", QUParameter::In }
    };
    static const QUMethod signal_1 = {"userSelected", 1, param_signal_1 };
    static const QUMethod signal_2 = {"mphStructureChanged", 0, 0 };
    static const QMetaData signal_tbl[] = {
	{ "setModifierFromCellFrame(MModifier::ModifierType)", &signal_0, QMetaData::Public },
	{ "userSelected(QPtrList<ViNTreeNode>*)", &signal_1, QMetaData::Public },
	{ "mphStructureChanged()", &signal_2, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"CellFrame", parentObject,
	slot_tbl, 18,
	signal_tbl, 3,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_CellFrame.setMetaObject( metaObj );
    return metaObj;
}

void* CellFrame::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "CellFrame" ) )
	return this;
    return QGLViewer::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL setModifierFromCellFrame
void CellFrame::setModifierFromCellFrame( MModifier::ModifierType t0 )
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

// SIGNAL userSelected
void CellFrame::userSelected( QPtrList<ViNTreeNode>* t0 )
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
void CellFrame::mphStructureChanged()
{
    activate_signal( staticMetaObject()->signalOffset() + 2 );
}

bool CellFrame::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: popupAboutToShow(); break;
    case 1: choosedFromPopup((int)static_QUType_int.get(_o+1)); break;
    case 2: setLight((Light*)static_QUType_ptr.get(_o+1)); break;
    case 3: setAllLights(); break;
    case 4: turnAllLights((bool)static_QUType_bool.get(_o+1)); break;
    case 5: updateColorForLight((GLenum)(*((GLenum*)static_QUType_ptr.get(_o+1))),(Light*)static_QUType_ptr.get(_o+2)); break;
    case 6: selectAll(); break;
    case 7: setSelectedSlot((QPtrList<ViNTreeNode>*)static_QUType_ptr.get(_o+1)); break;
    case 8: setCameraMoving((bool)static_QUType_bool.get(_o+1)); break;
    case 9: setCameraType((qglviewer::Camera::Type)(*((qglviewer::Camera::Type*)static_QUType_ptr.get(_o+1)))); break;
    case 10: setDrawMethod((DrawMethod)(*((DrawMethod*)static_QUType_ptr.get(_o+1)))); break;
    case 11: showAllScene(); break;
    case 12: setViewDirection((int)static_QUType_int.get(_o+1)); break;
    case 13: setDrawAxisXYZ((bool)static_QUType_bool.get(_o+1)); break;
    case 14: setDrawGridXZ((bool)static_QUType_bool.get(_o+1)); break;
    case 15: setDrawGrid3D((bool)static_QUType_bool.get(_o+1)); break;
    case 16: setDrawLights((bool)static_QUType_bool.get(_o+1)); break;
    case 17: maximize(); break;
    default:
	return QGLViewer::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool CellFrame::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: setModifierFromCellFrame((MModifier::ModifierType)(*((MModifier::ModifierType*)static_QUType_ptr.get(_o+1)))); break;
    case 1: userSelected((QPtrList<ViNTreeNode>*)static_QUType_ptr.get(_o+1)); break;
    case 2: mphStructureChanged(); break;
    default:
	return QGLViewer::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool CellFrame::qt_property( int id, int f, QVariant* v)
{
    return QGLViewer::qt_property( id, f, v);
}

bool CellFrame::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
