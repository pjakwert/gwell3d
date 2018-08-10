#ifndef GLMPHMENU_H
#define GLMPHMENU_H


#include <qlayout.h>
#include <qgrid.h>
#include <qdir.h>

#include <glmphmenuitem.h>
#include <kernel.h>


class GLMphMenu : public QWidget
{
  Q_OBJECT
  
  public:
    GLMphMenu( QWidget* parent, const QFileInfoList* fileList, int& count );
    ~GLMphMenu() {}


  private:
    QGridLayout *grid;
    QGrid       *gridzik;

  private slots:
    void multiPolyhSelected( const char* mphPath );

  signals:
    void mphSelected( const char* mphPath );
};


#endif
