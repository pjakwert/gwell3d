#ifndef BINDPAIR_HH
#define BINDPAIR_HH

/*! \file bindpair.hh
 *  Plik zawiera definicjê szablonu pozwolaj±cego tworzyæ wzajemne
 *  powi±zania miêdzy dwoma obiektami o zdefiniowanych typach.
 *  Powi±zanie to umo¿liwia zachowaæ itegralno¶æ struktury danych,
 *  nawet wtedy gdy jeden z obiektów jest usuwany. W takiej sytuacji
 *  dane jego partnera s± odpowiednio aktualizowane.
 *  \author Bogdan Kreczmer
 *  \date  2004.10.05
 */



/*!
 *  Szablon pozwola tworzyæ wzajemne
 *  powi±zania miêdzy dwoma obiektami o jawnie okre¶lonych klasach.
 *  Powi±zanie to pozwala zachowanie itegralno¶ci struktury danych,
 *  nawet wtedy gdy jeden z obiektów jest usuwany. W takiej sytuacji
 *  dane jego partnera s± odpowiednio aktualizowane.
 *  \param ID - jest identyfikatorem liczbowym, który pozwala 
 *              zró¿nicowaæ typy, je¿eli zachodzi potrzeba dziedziczenia
 *              przez dan± klasê wiêcej ni¿ tylko jeden szablon \b BindPair.
 */
template <class HostType, class GuestType>
class BindPair {
  /*!
   * Obiekty tej klasy drugim "krañcem" powi±zania, które mo¿na 
   * utworzyæ za pomoc± obiektów class dziedzicz±cych szablon
   * BindPair.
   */
 friend class BindPair<GuestType,HostType>;
 private:
  /*!
   *  Operator przypisania jest uczyniony operatorem prywatnym ze wzglêdu
   *  na to, aby uniemo¿liwiæ realizacjê tej operacji.
   *  Wykonanie jej dla elementu nale¿±cego ju¿ do jakie¶ listy
   *  oznacza³oby utratê spójno¶ci struktury danych.
   */
  BindPair<HostType,GuestType> &operator = (const BindAnonPair<HostType,GuestType>&)
                                                                   { return *this; }

  /*!
   *  Operator kopiuj±cy jest uczyniony operatorem prywatnym ze wzglêdu
   *  na to, aby uniemo¿liwiæ realizacjê tej operacji.
   *  Wykonanie jej dla elementu nale¿±cego ju¿ do jakie¶ listy
   *  oznacza³oby utratê spójno¶ci struktury danych.
   */
  BindPair(const BindPair<HostType,GuestType>&) {}


  /*!
   *  Wska¼nik na obiekt, z którym zrealizowane jest 
   *  powi±zanie.
   */
  GuestType *_Partner;

 public:
  /*!
   * Tworzy powi±zanie z danym obiektem.
   * \param pPartner - wska¼nik na obiekt, z którym ma byæ
   *     zrealizowane powi±zanie. Wska¼nik ten mo¿e
   *     mieæ warto¶æ \p NULL, wówczas dzia³anie metody
   *     równowa¿ne jest wywo³aniu metody
   *     \link BindPair::Unbind Unbind\endlink
   */
  void Bind(GuestType *pPartner);

  /*!
   *  Zrywa powi±zanie miêdzy dwoma obiektami. Je¿eli nie istnieje
   *  ¿adne powi±zanie, to nie jest podejmowane jakiekolwiek 
   *  dzia³anie.
   */
  void Unbind();

  /*!
   * Udostêpnia wska¼nik na obiekt, z którym istnieje powi±zanie.
   * Wska¼nik do obiektu udostêpniany jest w trybie sta³ym.
   */
  const GuestType *GetPartner() const { return _Partner; }

  /*!
   * Udostêpnia wska¼nik na obiekt, z którym istnieje powi±zanie.
   * Wska¼nik do obiektu udostêpniany jest w trybie modyfikacji.
   */
  GuestType *UsePartner() { return _Partner; }
  /*!
   *  Tworzy obiekt i inicjalizuje go jako obiekt bez powi±zania.
   */
  BindPair() { _Partner = 0L; }
  /*!
   *  Tworzy obiekt i inicjalizuje go jako obiekt powi±zany
   *  z obiektem wskazywanym przez przekazywany za pomoc±
   *  parametru wywo³ania wska¼nik.
   *  \param  pPartner - wska¼nik na obiekt, z którym ma 
   *                     byæ zrealiwoane powi±zanie.
   */
  BindPair(const GuestType *pPartner) { _Partner = 0L;  Bind(pPartner); }
  virtual ~BindPair() { Unbind(); }
  
};

#endif
