#ifndef VISYNXINTERP_HH
#define VISYNXINTERP_HH

/*! \file visynxinterp.hh
 *  Plik zawiera definicjê klasy ViSynxInterp. Jest ona przeznaczona
 *  do u³atwienia odczytywania i interpretacji opisu bry³y.
 *  Klasa ViSynxInterp jest specjalizacj± klasy SxInterp.
 *  \author Bogdan Kreczmer
 *  \date   2004.08
 */



#ifdef __GNUG__
#pragma interface
#endif


#include <string>
#include "sxinterp.hh"
#include "viscene.hh"

/*!
 * Klasa ViSynxInterp jest specjalizacj± klasy SxInterp. Obiekty
 * klasy ViSynxInterp daj± mo¿liwo¶æ odwo³ywania siê do aktualnej
 * sceny oraz do roboczej listy bry³ (patrz pole
 * \link ViSynxInterp::_PolyhList  ViSynxInterp::_PolyhList\endlink). 
 * Lista ta wykorzystywana jest
 * przy konstruowaniu bry³y z³o¿onej w trakcie wczytywania jej opisu.
 * Je¿eli konstrukcja zostanie poprawnie zakoñczona, to modelu bry³y
 * z³o¿onej zostaje przesuniêty do listy bry³ aktualnej sceny.
 */
class ViSynxInterp: public SxInterp {
   /*!
    * Wska¼nik jest inicjalizowany przez funkcjê wczytywania 
    * bry³y z³o¿onej 
    * (patrz \link Vi::ReadMultiPolyh Vi::ReadMultiPolyh\endlink)
    * i zawiera on adres sceny, w której ma byæ
    * umieszczona bry³a. Poprzez ten wska¼nik realizowany jest
    * równie¿ do bibliotek bry³ wzorcowych,  jak te¿ pó¼niejsze
    * przeniesienie utworzonej bry³y, o ile operacja jej wczytania
    * zakoñczy siê powodzeniem.
    */
   static const ViScene        *_CurrScene;
  /*!
   *  Pole daje dostêp do listy bibliotek bry³ wzorcowych,
   *  z których maj± byæ wykorzystane do modelowania bry³
   *  elementarnych wchodz±cych w sk³ad bry³y wzorcowej.
   */
   static const ViPatteLibList *_PatteLibList;

   /*!
    * Pole wykorzystywane jest do budowania wczytywanej bry³y z³o¿onej.
    * Je¿eli operacja koñczy siê sukcesem, to utworzony model bry³y
    * przesuwany jest do w³a¶ciwej listy bry³ sceny.
    */
   static ViScenePolyhList  _PolyhList;

  public:

   /*!
    *  Udostêpnia listê bry³.
    */
   static ViScenePolyhList &GetPolyhList() { return _PolyhList; }


   /*!
    *  Inicjalizuje strumieñ wyj¶ciowy przekazanym przez parametr napisem.
    *  \param Str - zawiera napis, który ma byæ doczytany i interpretowany.
    */
   ViSynxInterp(const std::string &Str): SxInterp(Str) {}
  /*!
   * Zapisuje wska¼nik na dan± scenê, do której bêdzie mo¿na siê
   * dalej odwo³ywaæ wczytuj± poszczególne bry³y. Odwo³ania te
   * maj± miejsce np. przy inicjalizacji bry³ elementarnych i ³aczeniu
   * ich z bry³ami wzorcowymi. 
   * Metoda ta dokonuje równie¿ powi±zania  
   * listy bibliotek bry³ wzorcowych zwi±zanych z dan± scen±.
   * Powoduje to, ¿e w trakcie odczytu opisu bry³y z³o¿onej
   * i tworzenia jej przegl±dane s±  biblioteki
   * bry³ elementarnych dostêpna w danej scenie.
   * \param Scene - referencja na scenê, do której maj± odwo³ywaæ
   *           siê metody wczytuj±ce bry³y. 
   * \post Do pola \link ViSynxInterp::_CurrScene _CurrScene\endlink
   *       wpisany jest wska¼nik udostêpniony poprzez referencjê
   *       przekazan± przez parametr \e Scene.
   * Ponadto zapisuje wska¼nik do listy bibliotek bry³ elementarnych,
   * który po¶rednio dostêpny jest poprzez metodê 
   * \link ViScene::GetList_PatteLibs ViScene::GetList_PatteLibs\endlink.
   * parametru \e Scene.
   * Wspomniany wska¼nik zapisywany jest do pola 
   * \link ViSynxInterp::_PatteLibList _PatteLibList\endlink.
   */
   static void SetScene(const ViScene &Scene);
  /*!
   * Udostêpnia wska¼nik na bie¿±c± scenê. Wska¼nik ten zawarty
   * jest w polu \link ViSynxInterp::_CurrScene _CurrScene\endlink.
   * Obiekt poprzez ten wska¼nik udostêpniany jest w trybie sta³ym.
   */
   static const ViScene *GetScene() { return _CurrScene; }

  /*!
   * Zapisuje wska¼nik do listy bibliotek bry³ elementarnych.
   * Wspomniany wska¼nik zapisywany jest do pola 
   * \link ViSynxInterp::_PatteLibList _PatteLibList\endlink.
   */
   static const void  SetPatteLibList(const ViPatteLibList *PLib)
                                    { _PatteLibList = PLib; }
  /*!
   *  Udostêpnia wska¼nik do listy bibliotek bry³ wzorcowych.
   *  Wska¼nik udostêpniany jest w trybie sta³ym.
   */
   static const ViPatteLibList *GetPatteLibList()
                                    { return _PatteLibList; }

};

#endif
