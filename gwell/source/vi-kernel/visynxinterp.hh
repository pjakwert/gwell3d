#ifndef VISYNXINTERP_HH
#define VISYNXINTERP_HH

/*! \file visynxinterp.hh
 *  Plik zawiera definicj� klasy ViSynxInterp. Jest ona przeznaczona
 *  do u�atwienia odczytywania i interpretacji opisu bry�y.
 *  Klasa ViSynxInterp jest specjalizacj� klasy SxInterp.
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
 * Klasa ViSynxInterp jest specjalizacj� klasy SxInterp. Obiekty
 * klasy ViSynxInterp daj� mo�liwo�� odwo�ywania si� do aktualnej
 * sceny oraz do roboczej listy bry� (patrz pole
 * \link ViSynxInterp::_PolyhList  ViSynxInterp::_PolyhList\endlink). 
 * Lista ta wykorzystywana jest
 * przy konstruowaniu bry�y z�o�onej w trakcie wczytywania jej opisu.
 * Je�eli konstrukcja zostanie poprawnie zako�czona, to modelu bry�y
 * z�o�onej zostaje przesuni�ty do listy bry� aktualnej sceny.
 */
class ViSynxInterp: public SxInterp {
   /*!
    * Wska�nik jest inicjalizowany przez funkcj� wczytywania 
    * bry�y z�o�onej 
    * (patrz \link Vi::ReadMultiPolyh Vi::ReadMultiPolyh\endlink)
    * i zawiera on adres sceny, w kt�rej ma by�
    * umieszczona bry�a. Poprzez ten wska�nik realizowany jest
    * r�wnie� do bibliotek bry� wzorcowych,  jak te� p�niejsze
    * przeniesienie utworzonej bry�y, o ile operacja jej wczytania
    * zako�czy si� powodzeniem.
    */
   static const ViScene        *_CurrScene;
  /*!
   *  Pole daje dost�p do listy bibliotek bry� wzorcowych,
   *  z kt�rych maj� by� wykorzystane do modelowania bry�
   *  elementarnych wchodz�cych w sk�ad bry�y wzorcowej.
   */
   static const ViPatteLibList *_PatteLibList;

   /*!
    * Pole wykorzystywane jest do budowania wczytywanej bry�y z�o�onej.
    * Je�eli operacja ko�czy si� sukcesem, to utworzony model bry�y
    * przesuwany jest do w�a�ciwej listy bry� sceny.
    */
   static ViScenePolyhList  _PolyhList;

  public:

   /*!
    *  Udost�pnia list� bry�.
    */
   static ViScenePolyhList &GetPolyhList() { return _PolyhList; }


   /*!
    *  Inicjalizuje strumie� wyj�ciowy przekazanym przez parametr napisem.
    *  \param Str - zawiera napis, kt�ry ma by� doczytany i interpretowany.
    */
   ViSynxInterp(const std::string &Str): SxInterp(Str) {}
  /*!
   * Zapisuje wska�nik na dan� scen�, do kt�rej b�dzie mo�na si�
   * dalej odwo�ywa� wczytuj� poszczeg�lne bry�y. Odwo�ania te
   * maj� miejsce np. przy inicjalizacji bry� elementarnych i �aczeniu
   * ich z bry�ami wzorcowymi. 
   * Metoda ta dokonuje r�wnie� powi�zania  
   * listy bibliotek bry� wzorcowych zwi�zanych z dan� scen�.
   * Powoduje to, �e w trakcie odczytu opisu bry�y z�o�onej
   * i tworzenia jej przegl�dane s�  biblioteki
   * bry� elementarnych dost�pna w danej scenie.
   * \param Scene - referencja na scen�, do kt�rej maj� odwo�ywa�
   *           si� metody wczytuj�ce bry�y. 
   * \post Do pola \link ViSynxInterp::_CurrScene _CurrScene\endlink
   *       wpisany jest wska�nik udost�pniony poprzez referencj�
   *       przekazan� przez parametr \e Scene.
   * Ponadto zapisuje wska�nik do listy bibliotek bry� elementarnych,
   * kt�ry po�rednio dost�pny jest poprzez metod� 
   * \link ViScene::GetList_PatteLibs ViScene::GetList_PatteLibs\endlink.
   * parametru \e Scene.
   * Wspomniany wska�nik zapisywany jest do pola 
   * \link ViSynxInterp::_PatteLibList _PatteLibList\endlink.
   */
   static void SetScene(const ViScene &Scene);
  /*!
   * Udost�pnia wska�nik na bie��c� scen�. Wska�nik ten zawarty
   * jest w polu \link ViSynxInterp::_CurrScene _CurrScene\endlink.
   * Obiekt poprzez ten wska�nik udost�pniany jest w trybie sta�ym.
   */
   static const ViScene *GetScene() { return _CurrScene; }

  /*!
   * Zapisuje wska�nik do listy bibliotek bry� elementarnych.
   * Wspomniany wska�nik zapisywany jest do pola 
   * \link ViSynxInterp::_PatteLibList _PatteLibList\endlink.
   */
   static const void  SetPatteLibList(const ViPatteLibList *PLib)
                                    { _PatteLibList = PLib; }
  /*!
   *  Udost�pnia wska�nik do listy bibliotek bry� wzorcowych.
   *  Wska�nik udost�pniany jest w trybie sta�ym.
   */
   static const ViPatteLibList *GetPatteLibList()
                                    { return _PatteLibList; }

};

#endif
