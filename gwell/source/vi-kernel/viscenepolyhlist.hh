#ifndef VISCENEPOLYHLIST_HH
#define VISCENEPOLYHLIST_HH

/*! \file viscenepolyhlist.hh
 *  Plik zawiera definicjê klasy ViScenePolyhList.
 *  Wykorzystana jest ona do tworzenia pol w klasie ViScene,
 *  s± zarz±dcami kolejek bry³ z³o¿onych nale¿±cych do danej sceny.
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
 * Klasa przewidziana jest do tworzenia pól w klasie ViScene bêd±cych
 * zarz±dcami koleki bry³ z³o¿onych (obiekty klasy ViMultiPolyh)
 * tworzonych dla danej sceny.
 */
class ViScenePolyhList: public ViNTreeNode {
   /*!
    * Metoda jest reimplementacj± metody wirtualnej z klasy 
    * \link ViNTreeNode::GetInheritorType 
    *       ViNTreeNode::GetInheritorType\endlink.
    * Warto¶æ przez ni± zwracana identyfikuje klasê pochodn±.
    * \retval IT_SCENEPOLYHLIST  (patrz opis 
    *          \link vintreenode.hh::IT_SCENEPOLYHLIST
    *                                     IT_SCENEPOLYHLIST\endlink).
    */
   virtual int GetInheritorType() const { return IT_SCENEPOLYHLIST; }
   
  /*!
   * \if brief_private_fields
   *  \brief Obrys wszystkich bry³ danej listy.
   * \endif
   *
   *  Pole reprezentuje obrys we wspó³rzêdnych globalnych
   *  wszystkich bry³ danej listy.
   */
   OutlineBox3f      _GlbOutlineBox;

  public:
   /*!
    *  Definiuje skrócon± nazwê do typu iteratora listy bry³ z³o¿onych.
    *  Iterator ten udostêpnia iterowane obiekty w trybie \b sta³ym.
    */
   typedef List<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>::ConstIterator 
                                                             ConMultiPolyhIter;
   /*!
    *  Definiuje skrócon± nazwê do typu iteratora listy bry³ z³o¿onych.
    *  Iterator ten udostêpnia iterowane obiekty w trybie \b modyfikowacji.
    */
   typedef List<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>::VariaIterator
                                                             VarMultiPolyhIter;

  /*!
   * \if brief_fileds
   *  \brief Udostêpnia obrys wszystkich bry³ danej listy.
   * \endif
   *
   * Metoda udostêpnia obrys we wspó³rzêdnych globalnych
   *  wszystkich bry³ danej listy. Obrys udostêpniany jest w trybie modyfikacji. 
   */
  OutlineBox3f  &GetOutlineBox() { return _GlbOutlineBox; }

  /*!
   * \if brief_fileds
   *  \brief Udostêpnia obrys wszystkich bry³ danej listy.
   * \endif
   *
   * Metoda udostêpnia obrys we wspó³rzêdnych globalnych
   *  wszystkich bry³ danej listy. Obrys udostêpniany jest w trybie sta³ym. 
   */
  const OutlineBox3f &GetOutlineBox() const { return _GlbOutlineBox; }

  /*!
   * Udostêpnia wska¼nik na pierwszy element listy bry³ z³o¿onych.
   * Element listy poprzez wspomniany wska¼nik dostêpny jest w trybie 
   * sta³ym.
   */
   const ViMultiPolyh *GetFirstMultiPolyh() const throw(ViException);

  /*!
   * Udostêpnia wska¼nik na pierwszy element listy bry³ z³o¿onych.
   * Element listy poprzez wspomniany wska¼nik dostêpny jest w trybie 
   * modyfikacji.
   * \exception ViException - wyj±tek jest zg³aszany z kodem b³êdu
   *     \link vierrors.hh::ERRNUM_HIER__NO_MULTI_AT_TOP
   *                        ERRNUM_HIER__NO_MULTI_AT_TOP\endlink.
   *            Wyj±tek ten jest zg³aszany w przypadku, gdy
   *    w pierwszej warstwie hierarchicznego modelu sceny znajduje siê wêze³,
   *    który jest obiektem klasy nie wyprowadzonej
   *    z klasy ViMultiPolyh. Pierwsza warstwa musi byæ zawsze list± obiektów
   *    z³o¿onych.
   */
   ViMultiPolyh *GetFirstMultiPolyh() throw(ViException)
      {return (ViMultiPolyh*)(*(const ViScenePolyhList*)this).GetFirstMultiPolyh();}

   /*!
    *  Metoda dodaje do listy bry³ z³o¿onych (zarz±dzan± przez obiekt
    *  klasy ViScenePolyhList) now± bry³ê.
    *  \param pMPolyh - wska¼nik na now± bry³ê.
    *  \return wska¼nika na dodan± bry³ê.
    *  \post Nowa bry³a dodwana jest zawsze na koniec kolejki.
    *  \exception ViException - jest zg³aszany z kodem 
    *        \link vierrors.hh::ERRMSG_POLYH__IS_NODE_ALREADY
    *                     ERRMSG_POLYH__IS_NODE_ALREADY\endlink,
    *         w sytuacji, gdy nastêpuje próba dodania do sceny 
    *         bry³y z³o¿onej do listy bry³, w której jest ju¿
    *         bry³a o tej samej nazwie.
    */
   ViMultiPolyh *AddMultiPolyh(ViMultiPolyh *pMPolyh) throw(ViException);

  /*!
   * Metoda usuwa pierwsz± bry³ê z³o¿on± z danej listy i dodaje j± 
   * do innej listy.
   * \param MList - lista bry³ z³o¿onych, do której ma byæ przesuniêta
   *                pierwsza bry³a z³o¿ona z bie¿±cej listy, dla której
   *                wywo³ana jest niniejsza metoda.
   * \return wska¼nik na przesuniêty model bry³y z³o¿onej. Je¶li operacja
   *         nie powiedzie siê (np. pusta lista ¼ród³owa), to zwracany
   *         jest wska¼nik \p NULL.
   * \exception  ViException - wyj±tek jest zg³aszany z kodem b³êdu
   *     \link vierrors.hh::ERRNUM_HIER__NO_MULTI_AT_TOP
   *                        ERRNUM_HIER__NO_MULTI_AT_TOP\endlink.
   *            Wyj±tek ten jest zg³aszany w przypadku, gdy
   *    w pierwszej warstwie hierarchicznego modelu sceny znajduje siê wêze³,
   *    który jest obiektem klasy nie wyprowadzonej
   *    z klasy ViMultiPolyh. Pierwsza warstwa musi byæ zawsze list± obiektów
   *    z³o¿onych.
   */
  ViMultiPolyh *MoveFirstMultiPolyh(ViScenePolyhList & MList);

  /*!
   *  Metoda umieszcza w strukturze hierarchicznego modelu sceny dany
   *  obiekt pod wskazanym adresem. Na pierwszym poziomie (bezpo¶rednio
   *  pod korzeniem, którym jest scena) mog± znale¼æ siê obiekty klasy
   *  ViMultiPolyh lub obiekty klas posiadaj±cych jako klasê bazow±
   *  klasê ViMultiPolyh. Tworz± one listê bry³ z³o¿onych. Umieszczenie
   *  obiektu na dalszym poziomie jest interpretowane jako umieszczenie
   *  elementu w danej bryle z³o¿onej.
   *  \param pPolyh - wska¼nik na obiekt, który ma zostaæ umieszczony
   *                  w hierarchicznym modelu sceny.
   *  \param Addr - adres lokalizacji danego elementu w strukturze
   *                hierarchicznej modelu sceny.
   *  \pre Adres musi mieæ poprawn± postaæ w sensie definicji i okre¶leñ
   *       przedstawionych w opisie klasy ViNodeAddress. Ostatni± etykiet±
   *       w adresie musi byæ nazwa wêz³a udostêpnionego przez parametr
   *       \e pPolyh. Jego nazwa dostêpna jest poprzez metodê
   *    \link ViNTreeNode::IndivName ViNTreeNode::IndivName\endlink.\n
   *    W przypadku, gdy adres wskazuje miejsce bezpo¶rednio pod korzeniem,
   *    klasa danego obiektu musi byæ klas± ViMultiPolyh lub klas± pochodn±.
   * \exception ViException - jest zg³aszany z kodem b³êdu kod
   *  \link vierrors.hh::ERRNUM_HIER__TOP_NO_MULTI 
   *                                       ERRNUM_HIER__TOP_NO_MULTI\endlink
   *                  w przypadku, gdy nast±pi³a próba umieszczenia obiektu
   *                  klasy nie bêd±c± klas± pochodn± wzglêdem ViMultiPolyh
   *                  na pierwszym poziomie hierarchicznej struktury opisu.
   * \exception ViException - jest zg³aszany z kodem b³êdu kod
   *  \link vierrors.hh::ERRNUM_HIER__NO_VALID_ADDR 
   *                                       ERRNUM_HIER__NO_VALID_ADDR\endlink
   *                  w przypadku, gdy podana ¶cie¿ka w adresie docelowej
   *                  lokalizacji wêz³a nie istnieje.
   */
  void AddUsingAddress(ViNTreeNode *pPolyh, const ViNodeAddress &  Addr )
                                                            throw (ViException);

  /*!
   * Udostêpnia wêze³ z hierarchicznego modelu sceny na podstawie adresu
   * tego¿ wêz³a w ca³ej strukturze.
   * \param  Addr - adres wêz³a. Jego sk³adnia musi byæ zgodna z wymaganiami
   *                przedstaionymi w opisie klasy ViNodeAddress.
   * \return wska¼nik znalezionego wêz³a. Wska¼nik na wêze³ udostêpniany jest
   *         jest w trybie sta³ym. Je¶li danemu adresowi nie odpowiada\
   *         ¿aden wêze³, wówczas zwracana jest warto¶æ \p NULL. 
   */
  const ViNTreeNode *GetNodeUsingAddress( const ViNodeAddress & Addr ) const;


  /*!
   * Udostêpnia wêze³ z hierarchicznego modelu sceny na podstawie adresu
   * tego¿ wêz³a w ca³ej strukturze.
   * \param  Addr - adres wêz³a. Jego sk³adnia musi byæ zgodna z wymaganiami
   *                przedstaionymi w opisie klasy ViNodeAddress.
   * \return wska¼nik znalezionego wêz³a. Wska¼nik na wêze³ udostêpniany jest
   *         jest w trybie modyfikacji. Je¶li danemu adresowi nie odpowiada\
   *         ¿aden wêze³, wówczas zwracana jest warto¶æ \p NULL. 
   */
  ViNTreeNode *GetNodeUsingAddress( const ViNodeAddress & Addr )
    {
      return (ViNTreeNode*)
                ((const ViScenePolyhList*)this)->GetNodeUsingAddress(Addr);
    }

  /*!
   *  Sprawdza czy dany adres wskazuje istniej±c± ¶cie¿kê w modelu danej
   *  sceny. 
   *  \param  Addr - (\b in) zawiera adres, który ma byæ sprawdzony.
   *  \retval true - je¶li adres ma poprawn± postaæ dla danego modelu (
   *              tzn. pod wzglêdem syntaktycznym, jak te¿ semantycznym).
   *  \retval false - w przypadku przeciwnym.
   */
  bool IsAddressValid(const ViNodeAddress & Addr) const 
                                          { return GetNodeUsingAddress(Addr); }

   /*!
    * \if brief_public_methods
    *  \brief Wylicza wspó³rzêdne globalne.
    * \endif
    *
    *  Wylicza wspó³rzêdne globalne dla wszystkich bry³ wchodz±cych w sk³ad
    *  danej listy obiektów.
    *  Wyliczane s± równie¿ dane pomocnicze (wektory 
    *  normalne ¶cianek, obrysy bry³ elementarnych i z³o¿onych).
    *  Wyznacza równie¿ obrys wszystkich bry³ danej listy.
    */
  void ComputeGlbVtx();

  /*!
   *  Kasuje zawarto¶æ listy bry³ z³o¿onych.
   */
  void DeletePolyhList() 
         { List<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>::CancelList(); }

   /*!
    * Tworzy iterator do przegl±dania bry³ z³o¿onych danej nale¿±cych
    * do listy. Iterowane obiekty udostêpniane s± w trybie \e sta³ym.
    */
   ConMultiPolyhIter ConBegin_MultiPolyh() const 
          { return  List<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>::Begin(); }
   /*!
    * Tworzy iterator do przegl±dania bry³ z³o¿onych danej nale¿±cych
    * do listy. Iterowane obiekty udostêpniane s± w trybie \e modyfikacji.
    */
   VarMultiPolyhIter VarBegin_MultiPolyh() 
          { return  List<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>::Begin(); }

   ~ViScenePolyhList() {}
};

#endif
