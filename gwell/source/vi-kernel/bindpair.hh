#ifndef BINDPAIR_HH
#define BINDPAIR_HH

/*! \file bindpair.hh
 *  Plik zawiera definicj� szablonu pozwolaj�cego tworzy� wzajemne
 *  powi�zania mi�dzy dwoma obiektami o zdefiniowanych typach.
 *  Powi�zanie to umo�liwia zachowa� itegralno�� struktury danych,
 *  nawet wtedy gdy jeden z obiekt�w jest usuwany. W takiej sytuacji
 *  dane jego partnera s� odpowiednio aktualizowane.
 *  \author Bogdan Kreczmer
 *  \date  2004.10.05
 */



/*!
 *  Szablon pozwola tworzy� wzajemne
 *  powi�zania mi�dzy dwoma obiektami o jawnie okre�lonych klasach.
 *  Powi�zanie to pozwala zachowanie itegralno�ci struktury danych,
 *  nawet wtedy gdy jeden z obiekt�w jest usuwany. W takiej sytuacji
 *  dane jego partnera s� odpowiednio aktualizowane.
 *  \param ID - jest identyfikatorem liczbowym, kt�ry pozwala 
 *              zr�nicowa� typy, je�eli zachodzi potrzeba dziedziczenia
 *              przez dan� klas� wi�cej ni� tylko jeden szablon \b BindPair.
 */
template <class HostType, class GuestType>
class BindPair {
  /*!
   * Obiekty tej klasy drugim "kra�cem" powi�zania, kt�re mo�na 
   * utworzy� za pomoc� obiekt�w class dziedzicz�cych szablon
   * BindPair.
   */
 friend class BindPair<GuestType,HostType>;
 private:
  /*!
   *  Operator przypisania jest uczyniony operatorem prywatnym ze wzgl�du
   *  na to, aby uniemo�liwi� realizacj� tej operacji.
   *  Wykonanie jej dla elementu nale��cego ju� do jakie� listy
   *  oznacza�oby utrat� sp�jno�ci struktury danych.
   */
  BindPair<HostType,GuestType> &operator = (const BindAnonPair<HostType,GuestType>&)
                                                                   { return *this; }

  /*!
   *  Operator kopiuj�cy jest uczyniony operatorem prywatnym ze wzgl�du
   *  na to, aby uniemo�liwi� realizacj� tej operacji.
   *  Wykonanie jej dla elementu nale��cego ju� do jakie� listy
   *  oznacza�oby utrat� sp�jno�ci struktury danych.
   */
  BindPair(const BindPair<HostType,GuestType>&) {}


  /*!
   *  Wska�nik na obiekt, z kt�rym zrealizowane jest 
   *  powi�zanie.
   */
  GuestType *_Partner;

 public:
  /*!
   * Tworzy powi�zanie z danym obiektem.
   * \param pPartner - wska�nik na obiekt, z kt�rym ma by�
   *     zrealizowane powi�zanie. Wska�nik ten mo�e
   *     mie� warto�� \p NULL, w�wczas dzia�anie metody
   *     r�wnowa�ne jest wywo�aniu metody
   *     \link BindPair::Unbind Unbind\endlink
   */
  void Bind(GuestType *pPartner);

  /*!
   *  Zrywa powi�zanie mi�dzy dwoma obiektami. Je�eli nie istnieje
   *  �adne powi�zanie, to nie jest podejmowane jakiekolwiek 
   *  dzia�anie.
   */
  void Unbind();

  /*!
   * Udost�pnia wska�nik na obiekt, z kt�rym istnieje powi�zanie.
   * Wska�nik do obiektu udost�pniany jest w trybie sta�ym.
   */
  const GuestType *GetPartner() const { return _Partner; }

  /*!
   * Udost�pnia wska�nik na obiekt, z kt�rym istnieje powi�zanie.
   * Wska�nik do obiektu udost�pniany jest w trybie modyfikacji.
   */
  GuestType *UsePartner() { return _Partner; }
  /*!
   *  Tworzy obiekt i inicjalizuje go jako obiekt bez powi�zania.
   */
  BindPair() { _Partner = 0L; }
  /*!
   *  Tworzy obiekt i inicjalizuje go jako obiekt powi�zany
   *  z obiektem wskazywanym przez przekazywany za pomoc�
   *  parametru wywo�ania wska�nik.
   *  \param  pPartner - wska�nik na obiekt, z kt�rym ma 
   *                     by� zrealiwoane powi�zanie.
   */
  BindPair(const GuestType *pPartner) { _Partner = 0L;  Bind(pPartner); }
  virtual ~BindPair() { Unbind(); }
  
};

#endif
