#ifndef BINDPAIR_METHODS_HH
#define BINDPAIR_METHODS_HH

/*! \file bindpair-methods.hh
 *  Plik zawiera definicj� metod szablonu pozwolaj�cego tworzy� wzajemne
 *  powi�zania mi�dzy dwoma obiektami o zdefiniowanych typach.
 *  Powi�zanie to umo�liwia zachowa� itegralno�� struktury danych,
 *  nawet wtedy gdy jeden z obiekt�w jest usuwany. W takiej sytuacji
 *  dane jego partnera s� odpowiednio aktualizowane.
 *  \author Bogdan Kreczmer
 *  \date  2004.10.05
 */


#include "bindpair.hh"

template <class HostType, class GuestType>
void BindPair<HostType,GuestType>::Bind(GuestType *pPartner) 
    { 
       Unbind(); 
       if (!pPartner) return;
       pPartner->BindPair<GuestType,HostType>::Unbind(); 
       _Partner = pPartner;
       pPartner->BindPair<GuestType,HostType>::_Partner = (HostType*) this;
    }


template <class HostType, class GuestType>
void BindPair<HostType,GuestType>::Unbind() 
    { 
      if (!_Partner) return;
      _Partner->BindPair<GuestType,HostType>::_Partner = 0L; 
      _Partner = 0L; 
    }

#endif
