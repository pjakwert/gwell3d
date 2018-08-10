#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <qlistview.h>
#include <qtoolbutton.h>
#include <qpopupmenu.h>
#include <kineditor.h>
#include <cellframe.h>

class ListView : public QListView
{
  Q_OBJECT
  
  public:
    ListView( QWidget* parent, QToolButton* treeViewButton, const char * name = 0, WFlags f = 0 );
    ~ListView() {}
    void expandAll();
    void collapseAll();
    
  private:
    QPopupMenu *popup;
    QToolButton *_treeViewButton;
    
  private slots:
    void popupAboutToShow();
    void choosedFromPopup( int id );
  
  protected:
    void contentsMousePressEvent( QMouseEvent *e );
    
};


#endif
