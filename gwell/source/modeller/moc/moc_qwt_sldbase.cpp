/****************************************************************************
** QwtSliderBase meta object code from reading C++ file 'qwt_sldbase.h'
**
** Created: Fri Oct 8 13:53:49 2004
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.2   edited Apr 19 11:34 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../../qwt/qwt_sldbase.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *QwtSliderBase::className() const
{
    return "QwtSliderBase";
}

QMetaObject *QwtSliderBase::metaObj = 0;
static QMetaObjectCleanUp cleanUp_QwtSliderBase( "QwtSliderBase", &QwtSliderBase::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString QwtSliderBase::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "QwtSliderBase", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString QwtSliderBase::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "QwtSliderBase", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* QwtSliderBase::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "val", &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"setValue", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ "val", &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"fitValue", 1, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ "steps", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"incValue", 1, param_slot_2 };
    static const QMetaData slot_tbl[] = {
	{ "setValue(double)", &slot_0, QMetaData::Public },
	{ "fitValue(double)", &slot_1, QMetaData::Public },
	{ "incValue(int)", &slot_2, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ "value", &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"valueChanged", 1, param_signal_0 };
    static const QUMethod signal_1 = {"sliderPressed", 0, 0 };
    static const QUMethod signal_2 = {"sliderReleased", 0, 0 };
    static const QUParameter param_signal_3[] = {
	{ "value", &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod signal_3 = {"sliderMoved", 1, param_signal_3 };
    static const QMetaData signal_tbl[] = {
	{ "valueChanged(double)", &signal_0, QMetaData::Public },
	{ "sliderPressed()", &signal_1, QMetaData::Public },
	{ "sliderReleased()", &signal_2, QMetaData::Public },
	{ "sliderMoved(double)", &signal_3, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"QwtSliderBase", parentObject,
	slot_tbl, 3,
	signal_tbl, 4,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_QwtSliderBase.setMetaObject( metaObj );
    return metaObj;
}

void* QwtSliderBase::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "QwtSliderBase" ) )
	return this;
    if ( !qstrcmp( clname, "QwtDblRange" ) )
	return (QwtDblRange*)this;
    return QWidget::qt_cast( clname );
}

// SIGNAL valueChanged
void QwtSliderBase::valueChanged( double t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 0, t0 );
}

// SIGNAL sliderPressed
void QwtSliderBase::sliderPressed()
{
    activate_signal( staticMetaObject()->signalOffset() + 1 );
}

// SIGNAL sliderReleased
void QwtSliderBase::sliderReleased()
{
    activate_signal( staticMetaObject()->signalOffset() + 2 );
}

// SIGNAL sliderMoved
void QwtSliderBase::sliderMoved( double t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 3, t0 );
}

bool QwtSliderBase::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: setValue((double)static_QUType_double.get(_o+1)); break;
    case 1: fitValue((double)static_QUType_double.get(_o+1)); break;
    case 2: incValue((int)static_QUType_int.get(_o+1)); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool QwtSliderBase::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: valueChanged((double)static_QUType_double.get(_o+1)); break;
    case 1: sliderPressed(); break;
    case 2: sliderReleased(); break;
    case 3: sliderMoved((double)static_QUType_double.get(_o+1)); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool QwtSliderBase::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool QwtSliderBase::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
