#ifndef BINDANONPAIR_HH
#define BINDANONPAIR_HH

/*! \file bindanonpair.hh
 *  Plik zawiera definicjê szablonu pozwolaj±cego tworzyæ wzajemne
 *  powi±zania miêdzy dwoma obiektami o nieokre¶lonych klasach.
 *  Powi±zanie to umo¿liwia zachowaæ itegralno¶æ struktury danych,
 *  nawet wtedy gdy jeden z obiektów jest usuwany. W takiej sytuacji
 *  dane jego partnera s± odpowiednio aktualizowane.
 *  \author Bogdan Kreczmer
 *  \date  2004.10.05
 */

/*!
 *  Szablon pozwola tworzyæ wzajemne
 *  powi±zania miêdzy dwoma obiektami o niezdefiniowanych jawnie
 *  (anonimowych) klasach.
 *  Powi±zanie to pozwala zachowanie itegralno¶ci struktury danych,
 *  nawet wtedy gdy jeden z obiektów jest usuwany. W takiej sytuacji
 *  dane jego partnera s± odpowiednio aktualizowane.
 *  \param ID - jest identyfikatorem liczbowym, który pozwala 
 *              zró¿nicowaæ typy, je¿eli zachodzi potrzeba dziedziczenia
 *              przez dan± klasê wiêcej ni¿ tylko jeden szablon \b BindAnonPair.
 */
template <int ID = 0>
class BindAnonPair {
 private:
  /*!
   *  Operator przypisania jest uczyniony operatorem prywatnym ze wzglêdu
   *  na to, aby uniemo¿liwiæ realizacjê tej operacji.
   *  Wykonanie jej dla elementu nale¿±cego ju¿ do jakie¶ listy
   *  oznacza³oby utratê spójno¶ci struktury danych.
   */
  BindAnonPair<0> &operator = (const BindAnonPair<0>&) { return *this; }

  /*!
   *  Operator kopiuj±cy jest uczyniony operatorem prywatnym ze wzglêdu
   *  na to, aby uniemo¿liwiæ realizacjê tej operacji.
   *  Wykonanie jej dla elementu nale¿±cego ju¿ do jakie¶ listy
   *  oznacza³oby utratê spójno¶ci struktury danych.
   */
  BindAnonPair(const BindAnonPair<0>&) {}
  
  /*!
   *  Wska¼nik na obiekt, z którym zrealizowane jest 
   *  powi±zanie.
   */
  BindAnonPair<ID> *_Partner;

 public:
  /*!
   * Tworzy powi±zanie z danym obiektem.
   * \param pPartner - wska¼nik na obiekt, z którym ma byæ
   *     zrealizowane powi±zanie. Wska¼nik ten mo¿e
   *     mieæ warto¶æ \p NULL, wówczas dzia³anie metody
   *     równowa¿ne jest wywo³aniu metody
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
   *  Zrywa powi±zanie miêdzy dwoma obiektami. Je¿eli nie istnieje
   *  ¿adne powi±zanie, to nie jest podejmowane jakiekolwiek 
   *  dzia³anie.
   */
  void Unbind() 
    { 
      if (!_Partner) return;
      _Partner->BindAnonPair<ID>::_Partner = 0L; 
      _Partner = 0L; 
    }
  /*!
   * Udostêpnia wska¼nik na obiekt, z którym istnieje powi±zanie.
   * Wska¼nik do obiektu udostêpniany jest w trybie sta³ym.
   */
  const BindAnonPair<ID> *GetPartner() const { return _Partner; }
  /*!
   *  Tworzy obiekt i inicjalizuje go jako obiekt bez powi±zania.
   */
  BindAnonPair() { _Partner = 0L; }
  /*!
   *  Tworzy obiekt i inicjalizuje go jako obiekt powi±zany
   *  z obiektem wskazywanym przez przekazywany za pomoc±
   *  parametru wywo³ania wska¼nik.
   *  \param  pPartner - wska¼nik na obiekt, z którym ma 
   *                     byæ zrealiwoane powi±zanie.
   */
  BindAnonPair(const BindAnonPair<ID> *pPartner) 
       { _Partner = 0L;  Bind(pPartner); }
  virtual ~BindAnonPair() { Unbind(); }
  
};


#endif
