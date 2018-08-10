////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///  class: HierListViewItem (.h)
///
///  dziedziczony od QListViewItem element listy QListView, zawierajacy dodatkowo wskaznik i adres obiektu
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "hierlistviewitem.h"


/*!
Konstruktor - rodzicem tak utworzonego wêz³a jest g³ówna lista QListView.
*/
HierListViewItem::HierListViewItem(QListView *parent, QString label, const ViNTreeNode *hier) : QListViewItem(parent, label)
{
  _hier = hier;
  _address = hier->GetNodeAddress();
}


/*!
Konstruktor - rodzicem tak utworzonego wêz³a jest inny wêze³ HierListViewItem.
*/
HierListViewItem::HierListViewItem(HierListViewItem *parent, QString label, const ViNTreeNode *hier) : QListViewItem(parent, label)
{
  _hier = hier;
  _address = hier->GetNodeAddress();
}


// destruktor
HierListViewItem::~HierListViewItem()
{
  
}


/*!
Metoda zwraca wska¼nik na obiekt ViNTreeNode reprezentowany przez ten wêze³.
*/
const ViNTreeNode* HierListViewItem::hier()
{
  return _hier;
}

/*!
Metoda zwraca adres (¶cie¿kê) obiektu ViNTreeNode reprezentowanego przez ten wêze³.
*/
const ViNodeAddress HierListViewItem::address()
{
  return _address;
}

