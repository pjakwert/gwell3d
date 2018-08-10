////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///  class: HierListViewItem (.h)
///
///  dziedziczony od QListViewItem element listy QListView, zawierajacy dodatkowo wskaznik i adres obiektu
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "hierlistviewitem.h"


/*!
Konstruktor - rodzicem tak utworzonego w�z�a jest g��wna lista QListView.
*/
HierListViewItem::HierListViewItem(QListView *parent, QString label, const ViNTreeNode *hier) : QListViewItem(parent, label)
{
  _hier = hier;
  _address = hier->GetNodeAddress();
}


/*!
Konstruktor - rodzicem tak utworzonego w�z�a jest inny w�ze� HierListViewItem.
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
Metoda zwraca wska�nik na obiekt ViNTreeNode reprezentowany przez ten w�ze�.
*/
const ViNTreeNode* HierListViewItem::hier()
{
  return _hier;
}

/*!
Metoda zwraca adres (�cie�k�) obiektu ViNTreeNode reprezentowanego przez ten w�ze�.
*/
const ViNodeAddress HierListViewItem::address()
{
  return _address;
}

