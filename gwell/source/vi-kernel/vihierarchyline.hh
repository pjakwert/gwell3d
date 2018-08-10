#ifndef VIHIERARCHYLINE_HH
#define VIHIERARCHYLINE_HH

/*! \file vihierarchyline.hh
 *  Plik zawiera definicjê wzorca ViHierarchyLine. Pozwala on na wywo³ywanie
 *  metod zapisu i odczytu opisów bry³. Metody te wywo³ywane s± dla kolejnych
 *  klas dziedzicz±cych dan± klasê bazow±.
 *  £añcuch kolejnych wywo³añ odpowiada ¶ci¶le hierarchii dziedziczenia.
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
 *  Przestrzeñ nazw ViClassName pe³ni rolê pomocnicz± dla generowania
 *  wywo³añ metod \e WriteDescriptionTo i \e ReadDescriptionFrom
 *  definiowanych w szablonie ViHierarchyLine i klasach pochodnych
 *  dziedzicz±cych klasê ViNTreeNode. We wspomnianej przestrzeni
 *  nazw definiowane s± funkcje udostêpniaj±ce nazwy klas dziedzicz±cych
 *  klasê ViNTreeNode przy za³o¿eniu, ¿e definiowane s± one
 *  poprzez makro 
 *   \link vihierarchyline.hh::DEFPOLYHCLASS DEFPOLYHCLASS\endlink.
 *  Do funkcji tych odwo³uje siê metoda 
 *  \link ViHierarchyLine::GetClassName GetClassName\endlink z szablonu
 *  ViHierarchyLine.
 */



/*! \def DEFPOLYHCLASS(DeriClassName, BaseClassName)
 *  Makro wykorzystywane jest do tworzenia definicji w³asnej klasy pochodnej.
 *  Zapewnia ono, ¿e nowa klasa bêdzie posiada³a metodê, która zwraca
 *  w³a¶ciw± nazwê klasy pochodnej.
 *  \param DeriClassName - nazwa klasy pochodnej,
 *  \param BaseClassName - nazwa klasy bazowej.
 *
 *  Przyk³ad wykorzystania makra przy dziedzieczeniu klasy ViElemePolyh:
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
 * Wzorzec ViHierarchyLine umo¿liwia wywo³ywanie metod zapisu i odczytu
 * opisu bry³. Metody te wywo³ywane s±  dla kolejnych
 *  klas dziedzicz±cych dan± klasê bazow±.
 *  £añcuch kolejnych wywo³añ odpowiada ¶ci¶le hierarchii dziedziczenia.
 *  \warning W metodzie 
 *  \link ViHierarchyLine::WriteDescripToBuff WriteDescripToBuff\endlink
 *   znajduje siê odwo³anie do metody 
 *    \link ViNTreeNode::AddDescripToBuff AddDescripToBuff\endlink.
 *    nie jest ona deklarowana w szablonie ViHierarchyLine. Jej definicja
 *    i implementacja znajduje siê w klasie ViNTreeNode.
 *    Klasa ta jest klas± bazow± dla wszystkich dalszych klas, dla których
 *    do dziedzieczenia klas bazowych wykorzystany jest szablon
 *     ViHierarchyLine.
 *  \param Derivative - nazwa klasy pochodnej,
 *  \param Base - nazwa klasy bazowej.
 *
 *  Niniejszy szablon spe³nia funkcje pomocnicze. Poprawne jego wykorzystanie
 *  umo¿liwia makro 
 *  \link vihierarchyline.hh::DEFPOLYHCLASS DEFPOLYHCLASS\endlink. 
 *  W³asne klasy wyprowadzone z klasy
 *  ViNTreeNode i z klas pochodnych 
 *  \link vielemepolyh.hh ViElemePolyh\endlink i 
 *  \link vimultipolyh.hh ViMultiPolyh\endlink
 *  nale¿y definiowaæ z wykorzystaniem wspomnianego makra.
 *
 *  Przyk³ad wykorzystania makra przy dziedzieczeniu klasy ViElemePolyh:
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
   *  Zwraca nazwê klasy pochodnej. Metoda wykorzystywana jest
   *  przez metody zapisu parametrów bry³y do oznaczania i identyfikacji
   *  poszczególnych sekcji zapisu.
   */
   const char *GetClassName() const 
      { return ViClassNames::Name((const Derivative*)this); }


  /*!
   *  Zwraca finalnej nazwê klasy danego obiektu.
   */
  virtual const char *GetFinalClassName() const
          { return ViHierarchyLine<Derivative,Base>::GetClassName(); }

  /*!
   * Metoda udostêpnia wska¼nik do klasy bazowej.
   * Wska¼nik udostêpniany jest w trybie modyfikacji.
   */
   Base * CastToBase(Derivative*) { return this; }
  /*!
   * Metoda udostêpnia wska¼nik do klasy bazowej.
   * Wska¼nik udostêpniany jest w trybie sta³ym.
   */
   const Base* CastToBase(Derivative const*) const { return this; }

   /*!
    * Metoda zapewnia wywo³anie metod zapisu do bufora
    * parametrów opisu bry³y. Wywo³ywana jest metoda 
    *  WriteDescripToBuff dla kolejnych klas znajduj±cych siê w hierarchii
    * dziedziczenia. Wspomniana metoda wywo³ywana jest najpierw dla
    * klasy bazowej. Nastêpnie wywo³ywana jest ona dla kolejnych klas
    * pochodnych.
    * \param Margin - wielko¶æ lewego marginesu, który ma byæ zachowany
    *              przy zapsie poszczególnych linii opisu parametrów 
    *              bry³y.
    * \param pNull - jest to parametr pozorny s³u¿±cy jedynie do
    *              rozró¿nienia poszczególnych metod.
    * \warning Metoda WriteDescripToBuff musi byæ implementowana w ka¿dej
    *          klasie pochodnej.\n
    *          Metoda ta musi byæ zadeklarowana jako:
    * \code
    *     bool NazwaKlasy::WriteDescriptionTo(ExtString &) { ... }
    * \endcode
    */
   void WriteDescripToBuff(unsigned int Margin, const Derivative *pNull)
                                                                     const;
  /*!
   *  Metoda inicjalizuje hierarchiczne wywo³anie metod
   *  \b WriteDescriptionTo
   *  dla poszczególnych klas w hierarchii ich dziedziczenia. 
   *  Ka¿da z tych klas musi mieæ zaimplementowan± metodê 
   *  \b WriteDescriptionTo.
   * \param Margin - wielko¶æ lewego marginesu, który ma byæ zachowany
   *              przy zapsie poszczególnych linii opisu parametrów 
   *              bry³y.
   */
   virtual void WriteAllParamToBuff(unsigned int Margin) const;

  /*!
   *  Metoda odpowiedzialna jest za wywo³anie metod interpretuj±cych
   *  zapis parametrów inicjalizacji obiektu dla klas wchodz±cych 
   *  w hierarchiê dziedziczenia klasy ViNTreeNode
   *  (w hierarchii tej pomijane s± pomocnicze szablony klas ViHierarchyLine).
   *  Wywo³ania nastêpuj± pocz±wszy do obiektu klasy bazowej, 
   *  na obiekcie klasy finalnej koñcz±c. Metoda ta odpowiedzialna
   *  jest równie¿ za wydobycie z opisu danego wêz³a (przez wêze³ rozumiany
   *  jest pojedynczy element wchodz±cy w strukturê hierarchiczn± bry³y
   *  z³o¿onej) tego opisu,
   *  który dotyczy odpowiedniej klasy.
   *  \param Descr - zawiera opis wêz³a.
   *  \exception ViException_Syntax - jest zg³aszany z kodem b³êdu w przypadku,
   *               ERRMSG_SYNTAX__NO_CLASS_DESCR, gdy w opisie danego wêz³a
   *               nie znaleziono opisu dla danej klasy.
   *          
   */
  virtual void InterpretParamDescr(const ViNodeDescr &  Descr);
  //                   throw (ViException_Syntax);
  /*!
   *  Metoda ma znaczenie pomocnicze. Tworzy ona ³añcuch hierarchii wywo³añ
   *  metod interpretacji opisów parametrów dla poszczególnych klas wchodz±cych
   *  w hierarchiczn± strukturê dziedziczenia. Jest ona równie¿ odpowiedzialna
   *  za wywo³anie metody \e InitWithDescr, która powinna byæ zdefiniowana
   *  w ka¿dej z podstawowych klas wchodz±cych w ³±ñcuch hierarchi 
   *  dziedziczenia. Metoda \e InitWithDescr odpowiedzialna jest za 
   *  interpretacjê opisu dla danej klasy i inicjalizacjê parametrów
   *  w³a¶ciwych tej klasie (z wy³±czeniem parametrów wynikaj±cych
   *  z dziedziczenia).
   *  \param Descr - (\b in) zawiera opis inicjalicji ca³ego wêz³a. W opisie 
   *           musz± znajdowaæ siê sekcje opisu inicjalizacji poszczególnych
   *           klas wchodz±cych w sk³ad hierarchii dziedziczenia
   *           klasy pochodnej, której obiektem ma byæ dany wêze³.
   *  \param pNode - ma znaczenie pomocnicze. Pozwala na rozró¿nienie 
   *           przeci±¿onej metody i jednoznacznego jej zwi±zania z dan±
   *           klas±.
   *  \exception ViException_Syntax - jest zg³aszany z kodem b³êdu w przypadku,
   *               ERRMSG_SYNTAX__NO_CLASS_DESCR, gdy w opisie danego wêz³a
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
