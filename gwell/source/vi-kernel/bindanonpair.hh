#ifndef BINDANONPAIR_HH
#define BINDANONPAIR_HH

/*! \file bindanonpair.hh
 *  Plik zawiera definicj� szablonu pozwolaj�cego tworzy� wzajemne
 *  powi�zania mi�dzy dwoma obiektami o nieokre�lonych klasach.
 *  Powi�zanie to umo�liwia zachowa� itegralno�� struktury danych,
 *  nawet wtedy gdy jeden z obiekt�w jest usuwany. W takiej sytuacji
 *  dane jego partnera s� odpowiednio aktualizowane.
 *  \author Bogdan Kreczmer
 *  \date  2004.10.05
 */

/*!
 *  Szablon pozwola tworzy� wzajemne
 *  powi�zania mi�dzy dwoma obiektami o niezdefiniowanych jawnie
 *  (anonimowych) klasach.
 *  Powi�zanie to pozwala zachowanie itegralno�ci struktury danych,
 *  nawet wtedy gdy jeden z obiekt�w jest usuwany. W takiej sytuacji
 *  dane jego partnera s� odpowiednio aktualizowane.
 *  \param ID - jest identyfikatorem liczbowym, kt�ry pozwala 
 *              zr�nicowa� typy, je�eli zachodzi potrzeba dziedziczenia
 *              przez dan� klas� wi�cej ni� tylko jeden szablon \b BindAnonPair.
 */
template <int ID = 0>
class BindAnonPair {
 private:
  /*!
   *  Operator przypisania jest uczyniony operatorem prywatnym ze wzgl�du
   *  na to, aby uniemo�liwi� realizacj� tej operacji.
   *  Wykonanie jej dla elementu nale��cego ju� do jakie� listy
   *  oznacza�oby utrat� sp�jno�ci struktury danych.
   */
  BindAnonPair<0> &operator = (const BindAnonPair<0>&) { return *this; }

  /*!
   *  Operator kopiuj�cy jest uczyniony operatorem prywatnym ze wzgl�du
   *  na to, aby uniemo�liwi� realizacj� tej operacji.
   *  Wykonanie jej dla elementu nale��cego ju� do jakie� listy
   *  oznacza�oby utrat� sp�jno�ci struktury danych.
   */
  BindAnonPair(const BindAnonPair<0>&) {}
  
  /*!
   *  Wska�nik na obiekt, z kt�rym zrealizowane jest 
   *  powi�zanie.
   */
  BindAnonPair<ID> *_Partner;

 public:
  /*!
   * Tworzy powi�zanie z danym obiektem.
   * \param pPartner - wska�nik na obiekt, z kt�rym ma by�
   *     zrealizowane powi�zanie. Wska�nik ten mo�e
   *     mie� warto�� \p NULL, w�wczas dzia�anie metody
   *     r�wnowa�ne jest wywo�aniu metody
   *     \link BindAnonPair::Unbind Unbind\endlink
   */
  void Bind(BindAnonPair<ID> *pPartner) 
    { 
       Unbind(); 
       if (!pPartner) return;
       pPartner->BindAnonPair<ID>::Unbind(); 
       _Partner = (BindAnonPair<ID>*) pPartner;
       pPartner->BindAnonPair<ID>::_Partner = this;
    }
  /*!
   *  Zrywa powi�zanie mi�dzy dwoma obiektami. Je�eli nie istnieje
   *  �adne powi�zanie, to nie jest podejmowane jakiekolwiek 
   *  dzia�anie.
   */
  void Unbind() 
    { 
      if (!_Partner) return;
      _Partner->BindAnonPair<ID>::_Partner = 0L; 
      _Partner = 0L; 
    }
  /*!
   * Udost�pnia wska�nik na obiekt, z kt�rym istnieje powi�zanie.
   * Wska�nik do obiektu udost�pniany jest w trybie sta�ym.
   */
  const BindAnonPair<ID> *GetPartner() const { return _Partner; }
  /*!
   *  Tworzy obiekt i inicjalizuje go jako obiekt bez powi�zania.
   */
  BindAnonPair() { _Partner = 0L; }
  /*!
   *  Tworzy obiekt i inicjalizuje go jako obiekt powi�zany
   *  z obiektem wskazywanym przez przekazywany za pomoc�
   *  parametru wywo�ania wska�nik.
   *  \param  pPartner - wska�nik na obiekt, z kt�rym ma 
   *                     by� zrealiwoane powi�zanie.
   */
  BindAnonPair(const BindAnonPair<ID> *pPartner) 
       { _Partner = 0L;  Bind(pPartner); }
  virtual ~BindAnonPair() { Unbind(); }
  
};


#endif
