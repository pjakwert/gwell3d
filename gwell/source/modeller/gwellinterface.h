///////////////////////////////////////////////////////////////////////
//
//    class: GwellInterface (.h)
//
//    Kompletny interfejs Gwell.
//
///////////////////////////////////////////////////////////////////////

#ifndef GWELLINTERFACE_H
#define GWELLINTERFACE_H


#include <qsplitter.h>
#include <qmessagebox.h>
#include <qtooltip.h>

#include <const.h>
#include <workspace.h>
#include <tabs.h>
#include <qhbox.h>
#include <toolbar.h>
#include <statusbar.h>
#include <kernel.h>
#include <icons.h>


/*!
Klasa stanowi g³ówny widget aplikacji.
*/
class GwellInterface : public QWidget
{
  Q_OBJECT;

  public:
    GwellInterface(QWidget *parent = 0, char *name = 0, WFlags fl = 0);
    ~GwellInterface() {}
   
  private:
    Kernel      *kernel;             // GLOWNY OBIEKT ZARZADZAJACY CALA STRUKTURA VI-KERNEL

    ToolBar     *toolbar;            // okno z narzedziami
    Tabs        *tabBar;             // gorne zakladki
    StatusBar   *statusBar;          // dolny pasek statusu
    Workspace   *workSpace;          // 4 okna edycyjne

    QGridLayout *grid;
    QSplitter   *splitter8;          // splittery
    QSplitter   *splitter7;
    QSplitter   *splitter6;
    int         _toolWidth;          // szerokosc tego okna

  protected:
    virtual void resizeEvent(QResizeEvent *e);
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void closeEvent(QCloseEvent *e);
};





#endif
