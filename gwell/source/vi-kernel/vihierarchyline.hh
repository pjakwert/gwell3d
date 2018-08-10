#ifndef VIHIERARCHYLINE_HH
#define VIHIERARCHYLINE_HH

/*! \file vihierarchyline.hh
 *  Plik zawiera definicj� wzorca ViHierarchyLine. Pozwala on na wywo�ywanie
 *  metod zapisu i odczytu opis�w bry�. Metody te wywo�ywane s� dla kolejnych
 *  klas dziedzicz�cych dan� klas� bazow�.
 *  �a�cuch kolejnych wywo�a� odpowiada �ci�le hierarchii dziedziczenia.
 *
 *  \author  Bogdan Kreczmer
 *  \date    2004.05.23
 */


#ifdef __GNUG__
#pragma interface
#pragma implementation
#endif

#include "vinodedescr.hh"



/*! \namespace  ViClassName
 *  Przestrze� nazw ViClassName pe�ni rol� pomocnicz� dla generowania
 *  wywo�a� metod \e WriteDescriptionTo i \e ReadDescriptionFrom
 *  definiowanych w szablonie ViHierarchyLine i klasach pochodnych
 *  dziedzicz�cych klas� ViNTreeNode. We wspomnianej przestrzeni
 *  nazw definiowane s� funkcje udost�pniaj�ce nazwy klas dziedzicz�cych
 *  klas� ViNTreeNode przy za�o�eniu, �e definiowane s� one
 *  poprzez makro 
 *   \link vihierarchyline.hh::DEFPOLYHCLASS DEFPOLYHCLASS\endlink.
 *  Do funkcji tych odwo�uje si� metoda 
 *  \link ViHierarchyLine::GetClassName GetClassName\endlink z szablonu
 *  ViHierarchyLine.
 */



/*! \def DEFPOLYHCLASS(DeriClassName, BaseClassName)
 *  Makro wykorzystywane jest do tworzenia definicji w�asnej klasy pochodnej.
 *  Zapewnia ono, �e nowa klasa b�dzie posiada�a metod�, kt�ra zwraca
 *  w�a�ciw� nazw� klasy pochodnej.
 *  \param DeriClassName - nazwa klasy pochodnej,
 *  \param BaseClassName - nazwa klasy bazowej.
 *
 *  Przyk�ad wykorzystania makra przy dziedzieczeniu klasy ViElemePolyh:
 * \code
 * DEFPOLYHCLASS(MojaBrylaElementarna,ViElemePolyh) {
 *   // ...
 *   // Dalsze deklaracje i definicje.
 *   // ...
 * };
 * \endcode
 */
#define DEFPOLYHCLASS(DeriClassName, BaseClassName)                     \
 class DeriClassName;                                                   \
 namespace ViClassNames {                                               \
   inline                                                               \
   const char* Name(const  DeriClassName*) { return #DeriClassName; }   \
 };                                                                     \
class DeriClassName: public ViHierarchyLine<DeriClassName,BaseClassName>


namespace ViClassNames {
  inline
  const char* Name(const void*) { return "void"; }
};


/*!
 * Wzorzec ViHierarchyLine umo�liwia wywo�ywanie metod zapisu i odczytu
 * opisu bry�. Metody te wywo�ywane s�  dla kolejnych
 *  klas dziedzicz�cych dan� klas� bazow�.
 *  �a�cuch kolejnych wywo�a� odpowiada �ci�le hierarchii dziedziczenia.
 *  \warning W metodzie 
 *  \link ViHierarchyLine::WriteDescripToBuff WriteDescripToBuff\endlink
 *   znajduje si� odwo�anie do metody 
 *    \link ViNTreeNode::AddDescripToBuff AddDescripToBuff\endlink.
 *    nie jest ona deklarowana w szablonie ViHierarchyLine. Jej definicja
 *    i implementacja znajduje si� w klasie ViNTreeNode.
 *    Klasa ta jest klas� bazow� dla wszystkich dalszych klas, dla kt�rych
 *    do dziedzieczenia klas bazowych wykorzystany jest szablon
 *     ViHierarchyLine.
 *  \param Derivative - nazwa klasy pochodnej,
 *  \param Base - nazwa klasy bazowej.
 *
 *  Niniejszy szablon spe�nia funkcje pomocnicze. Poprawne jego wykorzystanie
 *  umo�liwia makro 
 *  \link vihierarchyline.hh::DEFPOLYHCLASS DEFPOLYHCLASS\endlink. 
 *  W�asne klasy wyprowadzone z klasy
 *  ViNTreeNode i z klas pochodnych 
 *  \link vielemepolyh.hh ViElemePolyh\endlink i 
 *  \link vimultipolyh.hh ViMultiPolyh\endlink
 *  nale�y definiowa� z wykorzystaniem wspomnianego makra.
 *
 *  Przyk�ad wykorzystania makra przy dziedzieczeniu klasy ViElemePolyh:
 * \code
 * DEFPOLYHCLASS(MojaBrylaElementarna,ViElemePolyh) {
 *   // ...
 *   // Dalsze deklaracje i definicje.
 *   // ...
 * };
 * \endcode
 */
template <class Derivative, class Base>
class  ViHierarchyLine: public Base {
  public:

  /*!
   *  Zwraca nazw� klasy pochodnej. Metoda wykorzystywana jest
   *  przez metody zapisu parametr�w bry�y do oznaczania i identyfikacji
   *  poszczeg�lnych sekcji zapisu.
   */
   const char *GetClassName() const 
      { return ViClassNames::Name((const Derivative*)this); }


  /*!
   *  Zwraca finalnej nazw� klasy danego obiektu.
   */
  virtual const char *GetFinalClassName() const
          { return ViHierarchyLine<Derivative,Base>::GetClassName(); }

  /*!
   * Metoda udost�pnia wska�nik do klasy bazowej.
   * Wska�nik udost�pniany jest w trybie modyfikacji.
   */
   Base * CastToBase(Derivative*) { return this; }
  /*!
   * Metoda udost�pnia wska�nik do klasy bazowej.
   * Wska�nik udost�pniany jest w trybie sta�ym.
   */
   const Base* CastToBase(Derivative const*) const { return this; }

   /*!
    * Metoda zapewnia wywo�anie metod zapisu do bufora
    * parametr�w opisu bry�y. Wywo�ywana jest metoda 
    *  WriteDescripToBuff dla kolejnych klas znajduj�cych si� w hierarchii
    * dziedziczenia. Wspomniana metoda wywo�ywana jest najpierw dla
    * klasy bazowej. Nast�pnie wywo�ywana jest ona dla kolejnych klas
    * pochodnych.
    * \param Margin - wielko�� lewego marginesu, kt�ry ma by� zachowany
    *              przy zapsie poszczeg�lnych linii opisu parametr�w 
    *              bry�y.
    * \param pNull - jest to parametr pozorny s�u��cy jedynie do
    *              rozr�nienia poszczeg�lnych metod.
    * \warning Metoda WriteDescripToBuff musi by� implementowana w ka�dej
    *          klasie pochodnej.\n
    *          Metoda ta musi by� zadeklarowana jako:
    * \code
    *     bool NazwaKlasy::WriteDescriptionTo(ExtString &) { ... }
    * \endcode
    */
   void WriteDescripToBuff(unsigned int Margin, const Derivative *pNull)
                                                                     const;
  /*!
   *  Metoda inicjalizuje hierarchiczne wywo�anie metod
   *  \b WriteDescriptionTo
   *  dla poszczeg�lnych klas w hierarchii ich dziedziczenia. 
   *  Ka�da z tych klas musi mie� zaimplementowan� metod� 
   *  \b WriteDescriptionTo.
   * \param Margin - wielko�� lewego marginesu, kt�ry ma by� zachowany
   *              przy zapsie poszczeg�lnych linii opisu parametr�w 
   *              bry�y.
   */
   virtual void WriteAllParamToBuff(unsigned int Margin) const;

  /*!
   *  Metoda odpowiedzialna jest za wywo�anie metod interpretuj�cych
   *  zapis parametr�w inicjalizacji obiektu dla klas wchodz�cych 
   *  w hierarchi� dziedziczenia klasy ViNTreeNode
   *  (w hierarchii tej pomijane s� pomocnicze szablony klas ViHierarchyLine).
   *  Wywo�ania nast�puj� pocz�wszy do obiektu klasy bazowej, 
   *  na obiekcie klasy finalnej ko�cz�c. Metoda ta odpowiedzialna
   *  jest r�wnie� za wydobycie z opisu danego w�z�a (przez w�ze� rozumiany
   *  jest pojedynczy element wchodz�cy w struktur� hierarchiczn� bry�y
   *  z�o�onej) tego opisu,
   *  kt�ry dotyczy odpowiedniej klasy.
   *  \param Descr - zawiera opis w�z�a.
   *  \exception ViException_Syntax - jest zg�aszany z kodem b��du w przypadku,
   *               ERRMSG_SYNTAX__NO_CLASS_DESCR, gdy w opisie danego w�z�a
   *               nie znaleziono opisu dla danej klasy.
   *          
   */
  virtual void InterpretParamDescr(const ViNodeDescr &  Descr);
  //                   throw (ViException_Syntax);
  /*!
   *  Metoda ma znaczenie pomocnicze. Tworzy ona �a�cuch hierarchii wywo�a�
   *  metod interpretacji opis�w parametr�w dla poszczeg�lnych klas wchodz�cych
   *  w hierarchiczn� struktur� dziedziczenia. Jest ona r�wnie� odpowiedzialna
   *  za wywo�anie metody \e InitWithDescr, kt�ra powinna by� zdefiniowana
   *  w ka�dej z podstawowych klas wchodz�cych w ���cuch hierarchi 
   *  dziedziczenia. Metoda \e InitWithDescr odpowiedzialna jest za 
   *  interpretacj� opisu dla danej klasy i inicjalizacj� parametr�w
   *  w�a�ciwych tej klasie (z wy��czeniem parametr�w wynikaj�cych
   *  z dziedziczenia).
   *  \param Descr - (\b in) zawiera opis inicjalicji ca�ego w�z�a. W opisie 
   *           musz� znajdowa� si� sekcje opisu inicjalizacji poszczeg�lnych
   *           klas wchodz�cych w sk�ad hierarchii dziedziczenia
   *           klasy pochodnej, kt�rej obiektem ma by� dany w�ze�.
   *  \param pNode - ma znaczenie pomocnicze. Pozwala na rozr�nienie 
   *           przeci��onej metody i jednoznacznego jej zwi�zania z dan�
   *           klas�.
   *  \exception ViException_Syntax - jest zg�aszany z kodem b��du w przypadku,
   *               ERRMSG_SYNTAX__NO_CLASS_DESCR, gdy w opisie danego w�z�a
   *               nie znaleziono opisu dla danej klasy. 
   */
   void InterpretParamDescr( const ViNodeDescr &  Descr, 
                             const Derivative *   pNode
                           ); //  throw (ViException_Syntax);
};


template <class Derivative, class Base>
inline
void ViHierarchyLine<Derivative,Base>::
         WriteDescripToBuff(unsigned int Margin, const Derivative *) const
{
  CastToBase((Derivative const*)0L)->
                           WriteDescripToBuff(Margin,(const Base *)0L);
  ExtString Buff;
  ((const Derivative*)this)->WriteDescriptionTo(Buff);
  AddDescripToBuff(Margin,Buff,
         ((const Derivative*)this)->GetClassName(),this); // Ta metoda jest z 
                                                          // ViNTreeNode.
}


template <class Derivative, class Base>
inline
void ViHierarchyLine<Derivative,Base>::
                 WriteAllParamToBuff(unsigned int Margin) const
{ 
  WriteDescripToBuff(Margin,(Derivative const*)0L); 
}


template <class Derivative, class Base>
inline
void ViHierarchyLine<Derivative,Base>::
        InterpretParamDescr(const ViNodeDescr &  Descr, const Derivative *)
{
  CastToBase((Derivative *)0L)->
                       InterpretParamDescr(Descr,(const Base *)0L);
  ExtString  ClassDescr;
  if (((Derivative *)this)->ShouldCallForClassDescr(GetClassName())) {
   if (!Descr.GetClassDescr(GetClassName(),ClassDescr)) {
     throw ViException_Syntax(ERRNUM_SYNTAX__NO_CLASS_DESCR,
                    (MSG(ERRMSG_SYNTAX__NO_CLASS_DESCR),GetClassName()));
   }
     ((Derivative *)this)->InitWithDescr(ClassDescr);
  } else {
     ((Derivative *)this)->InitWithDescr(ClassDescr);
  }
}


template <class Derivative, class Base>
inline
void ViHierarchyLine<Derivative,Base>::
                 InterpretParamDescr(const ViNodeDescr &  Descr)
{
  InterpretParamDescr(Descr,(const Derivative *) 0L);
}

#endif
