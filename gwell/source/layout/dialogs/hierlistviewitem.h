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


class HierListViewItem : public QListViewItem
{
  public:
    HierListViewItem(QListView *parent, QString label, const ViMultiPolyh *mp);
    HierListViewItem(HierListViewItem *parent, QString label, const ViMultiPolyh *mp);
    ~HierListViewItem();
    const ViMultiPolyh* mp();
    const ViNodeAddress address();

  private:
    const ViMultiPolyh *_mp;
    ViNodeAddress _address;
};  










#endif
