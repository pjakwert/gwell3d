////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///  class: HierListViewItem (.h)
///
///  dziedziczony od QListViewItem element listy QListView, zawierajacy dodatkowo wskaznik i adres obiektu
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "hierlistviewitem.h"



HierListViewItem::HierListViewItem(QListView *parent, QString label, const ViMultiPolyh *mp) : QListViewItem(parent, label)
{
  _mp = mp;
  _address = mp->GetNodeAddress();
}


HierListViewItem::HierListViewItem(HierListViewItem *parent, QString label, const ViMultiPolyh *mp) : QListViewItem(parent, label)
{
  _mp = mp;
  _address = mp->GetNodeAddress();
}


// destruktor
HierListViewItem::~HierListViewItem()
{
  
}



const ViMultiPolyh* HierListViewItem::mp()
{
  return _mp;
}


const ViNodeAddress HierListViewItem::address()
{
  return _address;
}

