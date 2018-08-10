#ifndef TABLE_H
#define TABLE_H

#include <qtable.h>
#include <qstringlist.h>

#include <kernel.h>
#include <options.h>
#include <statusbar.h>


/*!
Klasa Table reprezentuje tabelê wy¶wietlaj±c± i steruj±c± elementami interfejsu sterowania.
*/
class Table : public QTable
{
  Q_OBJECT
      
  public:
    Table( ViMultiPolyh* multiPolyh, QWidget *parent = 0, const char *name = 0 );
    ~Table() {}

  private:
    ViMultiPolyh *_multiPolyh;
    QStringList transfList;
    QStringList coordList;
    int transfTypeToIndex( Vi::TransformType tt );
    Vi::TransformType indexToTransfType( int i );
    Vi::Coord3DType indexToCoordType( int i );
        
  protected:
    void resizeEvent( QResizeEvent *e );
    
  public slots:
    void addRow( ViKinemCtrlItem* );
    void setCurrentValue( double value );
    void updateItem( ViKinemCtrlItem *controlItem );
    
  private slots:
    bool validateAndSet( int row, int col );
    void rowAndColChanged( int,int );
    
  signals:
    void valueChangedIsOK(); // sygna³ wysy³any przy zmianie warto¶ci maj±cych wp³yw na rysowanie
    void MinMaxValueChanged( ViKinemCtrlItem* ); // do knoba
    
};


#endif
