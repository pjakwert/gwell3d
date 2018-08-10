////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///  class: HierListViewItem (.h)
///
///  dziedziczony od QListViewItem element listy QListView, zawierajacy dodatkowo wskaznik i adres obiektu
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef HIERLISTVIEWITEM_H
#define HIERLISTVIEWITEM_H

#include <qlistview.h>

#include <kernel.h>


/*!
Klasa jest u¿ywana do reprezentacji struktury kinematycznej w postaci drzewa -
stosowana jest zamiast QListViewItem, poniewa¿ posiada dodatkowe u¿yteczne pola.
*/
class HierListViewItem : public QListViewItem
{
  public:
    HierListViewItem(QListView *parent, QString label, const ViNTreeNode *hier);
    HierListViewItem(HierListViewItem *parent, QString label, const ViNTreeNode *hier);
    ~HierListViewItem();
    const ViNTreeNode* hier();
    const ViNodeAddress address();

  private:
    const ViNTreeNode *_hier;
    ViNodeAddress _address;
};  










#endif
