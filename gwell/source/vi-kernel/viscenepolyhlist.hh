#ifndef VISCENEPOLYHLIST_HH
#define VISCENEPOLYHLIST_HH

/*! \file viscenepolyhlist.hh
 *  Plik zawiera definicj� klasy ViScenePolyhList.
 *  Wykorzystana jest ona do tworzenia pol w klasie ViScene,
 *  s� zarz�dcami kolejek bry� z�o�onych nale��cych do danej sceny.
 *
 *  \author  Bogdan Kreczmer
 *  \date    2004.03.27
 */



#ifdef __GNUG__
#pragma interface
#endif


#include "vintreenode.hh"
#include "outlinebox3f.hh"

class ViMultiPolyh;

/*!
 * Klasa przewidziana jest do tworzenia p�l w klasie ViScene b�d�cych
 * zarz�dcami koleki bry� z�o�onych (obiekty klasy ViMultiPolyh)
 * tworzonych dla danej sceny.
 */
class ViScenePolyhList: public ViNTreeNode {
   /*!
    * Metoda jest reimplementacj� metody wirtualnej z klasy 
    * \link ViNTreeNode::GetInheritorType 
    *       ViNTreeNode::GetInheritorType\endlink.
    * Warto�� przez ni� zwracana identyfikuje klas� pochodn�.
    * \retval IT_SCENEPOLYHLIST  (patrz opis 
    *          \link vintreenode.hh::IT_SCENEPOLYHLIST
    *                                     IT_SCENEPOLYHLIST\endlink).
    */
   virtual int GetInheritorType() const { return IT_SCENEPOLYHLIST; }
   
  /*!
   * \if brief_private_fields
   *  \brief Obrys wszystkich bry� danej listy.
   * \endif
   *
   *  Pole reprezentuje obrys we wsp�rz�dnych globalnych
   *  wszystkich bry� danej listy.
   */
   OutlineBox3f      _GlbOutlineBox;

  public:
   /*!
    *  Definiuje skr�con� nazw� do typu iteratora listy bry� z�o�onych.
    *  Iterator ten udost�pnia iterowane obiekty w trybie \b sta�ym.
    */
   typedef List<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>::ConstIterator 
                                                             ConMultiPolyhIter;
   /*!
    *  Definiuje skr�con� nazw� do typu iteratora listy bry� z�o�onych.
    *  Iterator ten udost�pnia iterowane obiekty w trybie \b modyfikowacji.
    */
   typedef List<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>::VariaIterator
                                                             VarMultiPolyhIter;

  /*!
   * \if brief_fileds
   *  \brief Udost�pnia obrys wszystkich bry� danej listy.
   * \endif
   *
   * Metoda udost�pnia obrys we wsp�rz�dnych globalnych
   *  wszystkich bry� danej listy. Obrys udost�pniany jest w trybie modyfikacji. 
   */
  OutlineBox3f  &GetOutlineBox() { return _GlbOutlineBox; }

  /*!
   * \if brief_fileds
   *  \brief Udost�pnia obrys wszystkich bry� danej listy.
   * \endif
   *
   * Metoda udost�pnia obrys we wsp�rz�dnych globalnych
   *  wszystkich bry� danej listy. Obrys udost�pniany jest w trybie sta�ym. 
   */
  const OutlineBox3f &GetOutlineBox() const { return _GlbOutlineBox; }

  /*!
   * Udost�pnia wska�nik na pierwszy element listy bry� z�o�onych.
   * Element listy poprzez wspomniany wska�nik dost�pny jest w trybie 
   * sta�ym.
   */
   const ViMultiPolyh *GetFirstMultiPolyh() const throw(ViException);

  /*!
   * Udost�pnia wska�nik na pierwszy element listy bry� z�o�onych.
   * Element listy poprzez wspomniany wska�nik dost�pny jest w trybie 
   * modyfikacji.
   * \exception ViException - wyj�tek jest zg�aszany z kodem b��du
   *     \link vierrors.hh::ERRNUM_HIER__NO_MULTI_AT_TOP
   *                        ERRNUM_HIER__NO_MULTI_AT_TOP\endlink.
   *            Wyj�tek ten jest zg�aszany w przypadku, gdy
   *    w pierwszej warstwie hierarchicznego modelu sceny znajduje si� w�ze�,
   *    kt�ry jest obiektem klasy nie wyprowadzonej
   *    z klasy ViMultiPolyh. Pierwsza warstwa musi by� zawsze list� obiekt�w
   *    z�o�onych.
   */
   ViMultiPolyh *GetFirstMultiPolyh() throw(ViException)
      {return (ViMultiPolyh*)(*(const ViScenePolyhList*)this).GetFirstMultiPolyh();}

   /*!
    *  Metoda dodaje do listy bry� z�o�onych (zarz�dzan� przez obiekt
    *  klasy ViScenePolyhList) now� bry��.
    *  \param pMPolyh - wska�nik na now� bry��.
    *  \return wska�nika na dodan� bry��.
    *  \post Nowa bry�a dodwana jest zawsze na koniec kolejki.
    *  \exception ViException - jest zg�aszany z kodem 
    *        \link vierrors.hh::ERRMSG_POLYH__IS_NODE_ALREADY
    *                     ERRMSG_POLYH__IS_NODE_ALREADY\endlink,
    *         w sytuacji, gdy nast�puje pr�ba dodania do sceny 
    *         bry�y z�o�onej do listy bry�, w kt�rej jest ju�
    *         bry�a o tej samej nazwie.
    */
   ViMultiPolyh *AddMultiPolyh(ViMultiPolyh *pMPolyh) throw(ViException);

  /*!
   * Metoda usuwa pierwsz� bry�� z�o�on� z danej listy i dodaje j� 
   * do innej listy.
   * \param MList - lista bry� z�o�onych, do kt�rej ma by� przesuni�ta
   *                pierwsza bry�a z�o�ona z bie��cej listy, dla kt�rej
   *                wywo�ana jest niniejsza metoda.
   * \return wska�nik na przesuni�ty model bry�y z�o�onej. Je�li operacja
   *         nie powiedzie si� (np. pusta lista �r�d�owa), to zwracany
   *         jest wska�nik \p NULL.
   * \exception  ViException - wyj�tek jest zg�aszany z kodem b��du
   *     \link vierrors.hh::ERRNUM_HIER__NO_MULTI_AT_TOP
   *                        ERRNUM_HIER__NO_MULTI_AT_TOP\endlink.
   *            Wyj�tek ten jest zg�aszany w przypadku, gdy
   *    w pierwszej warstwie hierarchicznego modelu sceny znajduje si� w�ze�,
   *    kt�ry jest obiektem klasy nie wyprowadzonej
   *    z klasy ViMultiPolyh. Pierwsza warstwa musi by� zawsze list� obiekt�w
   *    z�o�onych.
   */
  ViMultiPolyh *MoveFirstMultiPolyh(ViScenePolyhList & MList);

  /*!
   *  Metoda umieszcza w strukturze hierarchicznego modelu sceny dany
   *  obiekt pod wskazanym adresem. Na pierwszym poziomie (bezpo�rednio
   *  pod korzeniem, kt�rym jest scena) mog� znale�� si� obiekty klasy
   *  ViMultiPolyh lub obiekty klas posiadaj�cych jako klas� bazow�
   *  klas� ViMultiPolyh. Tworz� one list� bry� z�o�onych. Umieszczenie
   *  obiektu na dalszym poziomie jest interpretowane jako umieszczenie
   *  elementu w danej bryle z�o�onej.
   *  \param pPolyh - wska�nik na obiekt, kt�ry ma zosta� umieszczony
   *                  w hierarchicznym modelu sceny.
   *  \param Addr - adres lokalizacji danego elementu w strukturze
   *                hierarchicznej modelu sceny.
   *  \pre Adres musi mie� poprawn� posta� w sensie definicji i okre�le�
   *       przedstawionych w opisie klasy ViNodeAddress. Ostatni� etykiet�
   *       w adresie musi by� nazwa w�z�a udost�pnionego przez parametr
   *       \e pPolyh. Jego nazwa dost�pna jest poprzez metod�
   *    \link ViNTreeNode::IndivName ViNTreeNode::IndivName\endlink.\n
   *    W przypadku, gdy adres wskazuje miejsce bezpo�rednio pod korzeniem,
   *    klasa danego obiektu musi by� klas� ViMultiPolyh lub klas� pochodn�.
   * \exception ViException - jest zg�aszany z kodem b��du kod
   *  \link vierrors.hh::ERRNUM_HIER__TOP_NO_MULTI 
   *                                       ERRNUM_HIER__TOP_NO_MULTI\endlink
   *                  w przypadku, gdy nast�pi�a pr�ba umieszczenia obiektu
   *                  klasy nie b�d�c� klas� pochodn� wzgl�dem ViMultiPolyh
   *                  na pierwszym poziomie hierarchicznej struktury opisu.
   * \exception ViException - jest zg�aszany z kodem b��du kod
   *  \link vierrors.hh::ERRNUM_HIER__NO_VALID_ADDR 
   *                                       ERRNUM_HIER__NO_VALID_ADDR\endlink
   *                  w przypadku, gdy podana �cie�ka w adresie docelowej
   *                  lokalizacji w�z�a nie istnieje.
   */
  void AddUsingAddress(ViNTreeNode *pPolyh, const ViNodeAddress &  Addr )
                                                            throw (ViException);

  /*!
   * Udost�pnia w�ze� z hierarchicznego modelu sceny na podstawie adresu
   * tego� w�z�a w ca�ej strukturze.
   * \param  Addr - adres w�z�a. Jego sk�adnia musi by� zgodna z wymaganiami
   *                przedstaionymi w opisie klasy ViNodeAddress.
   * \return wska�nik znalezionego w�z�a. Wska�nik na w�ze� udost�pniany jest
   *         jest w trybie sta�ym. Je�li danemu adresowi nie odpowiada\
   *         �aden w�ze�, w�wczas zwracana jest warto�� \p NULL. 
   */
  const ViNTreeNode *GetNodeUsingAddress( const ViNodeAddress & Addr ) const;


  /*!
   * Udost�pnia w�ze� z hierarchicznego modelu sceny na podstawie adresu
   * tego� w�z�a w ca�ej strukturze.
   * \param  Addr - adres w�z�a. Jego sk�adnia musi by� zgodna z wymaganiami
   *                przedstaionymi w opisie klasy ViNodeAddress.
   * \return wska�nik znalezionego w�z�a. Wska�nik na w�ze� udost�pniany jest
   *         jest w trybie modyfikacji. Je�li danemu adresowi nie odpowiada\
   *         �aden w�ze�, w�wczas zwracana jest warto�� \p NULL. 
   */
  ViNTreeNode *GetNodeUsingAddress( const ViNodeAddress & Addr )
    {
      return (ViNTreeNode*)
                ((const ViScenePolyhList*)this)->GetNodeUsingAddress(Addr);
    }

  /*!
   *  Sprawdza czy dany adres wskazuje istniej�c� �cie�k� w modelu danej
   *  sceny. 
   *  \param  Addr - (\b in) zawiera adres, kt�ry ma by� sprawdzony.
   *  \retval true - je�li adres ma poprawn� posta� dla danego modelu (
   *              tzn. pod wzgl�dem syntaktycznym, jak te� semantycznym).
   *  \retval false - w przypadku przeciwnym.
   */
  bool IsAddressValid(const ViNodeAddress & Addr) const 
                                          { return GetNodeUsingAddress(Addr); }

   /*!
    * \if brief_public_methods
    *  \brief Wylicza wsp�rz�dne globalne.
    * \endif
    *
    *  Wylicza wsp�rz�dne globalne dla wszystkich bry� wchodz�cych w sk�ad
    *  danej listy obiekt�w.
    *  Wyliczane s� r�wnie� dane pomocnicze (wektory 
    *  normalne �cianek, obrysy bry� elementarnych i z�o�onych).
    *  Wyznacza r�wnie� obrys wszystkich bry� danej listy.
    */
  void ComputeGlbVtx();

  /*!
   *  Kasuje zawarto�� listy bry� z�o�onych.
   */
  void DeletePolyhList() 
         { List<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>::CancelList(); }

   /*!
    * Tworzy iterator do przegl�dania bry� z�o�onych danej nale��cych
    * do listy. Iterowane obiekty udost�pniane s� w trybie \e sta�ym.
    */
   ConMultiPolyhIter ConBegin_MultiPolyh() const 
          { return  List<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>::Begin(); }
   /*!
    * Tworzy iterator do przegl�dania bry� z�o�onych danej nale��cych
    * do listy. Iterowane obiekty udost�pniane s� w trybie \e modyfikacji.
    */
   VarMultiPolyhIter VarBegin_MultiPolyh() 
          { return  List<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>::Begin(); }

   ~ViScenePolyhList() {}
};

#endif
