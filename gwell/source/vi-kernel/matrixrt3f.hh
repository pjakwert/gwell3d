#ifndef MATRIXRT3F_HH
#define MATRIXRT3F_HH

/*!
 * \file matrixrt3f.hh
 * Plik zawiera definicjê macierzy MatrixRT3f.
 * \date 2004.09
 * \author Bogdan Kreczmer
 */

#include <iostream>

#ifdef __GNUG__
#pragma interface
#endif


#include "vector3f.hh"
#include "vi-utils.hh"

/*!
 *  Rozmiar kolumny macierzy transformacji.
 */
#define DH_MAXX 3
/*!
 *  Rozmiar wiersza macierzy transformacji.
 */
#define DH_MAXY 4
/*!
 *  Realizuje podnoszenie do kwadratu.
 */
#define SQR(x)     (x*x)


/*!
 * Reprezentuje jednorodn± macierz transformacji zawieraj±c±
 * wspó³czynniki z³o¿enia rotacji i translacji oraz skali.
 * Wspó³czynniki transformacji mog± byæ wyznaczone dla nastêpuj±cych
 * z³o¿eñ transformacji:
 *     \li \f$ T\circ S\circ R\f$,
 *     \li \f$ S\circ R\circ T\f$.
 *
 * Finalna postaæ transformacji reprezentowana jest przez
 * wspó³czynniki:
 * \f[
        \left[\begin{array}{cccc} 
               s_x*r_{11} & s_x*r_{12} & s_x*r_{13} & t_{14} \\
               s_y*r_{21} & s_y*r_{22} & s_y*r_{23} & t_{24} \\
               s_z*r_{31} & s_z*r_{32} & s_z*r_{33} & t_{34} \\
                0     &  0     &   0    &  1
              \end{array}\right]
   \f]
 * gdzie \f$ r_{11}, \ldots, r_{33}\f$ s± elementami podmacierzy rotacji,
 * \f$ s_x, s_y, s_z \f$ wspó³czynnikami skali dla poszczególnych osi,
 *  (tzn. odpowiednio osi \e OX, \e OY, \e OZ),
 * za¶ \f$ t_{14}, t_{24}, t_{34} \f$ jest wektorem translacji.
 */
class MatrixRT3f {

  private:
     /*!
      * Zawiera wspó³czynniki macierzy transformacji.
      */
   float     _DH[DH_MAXX][DH_MAXY];

    /*!
     * Udostêpnia zadany elemement macierzy transformacji. 
     * \param w - numer wiersza.
     * \param k - numer kolumny. 
     * \pre \f$ 0 \le w \le 2\f$, \f$ 0 \le k \le 3\f$.
     */
  float &Mx(unsigned int w, unsigned int k) { return _DH[w][k]; } 


 public:

    /*!
     * Udostêpnia zadany elemement macierzy transformacji. 
     * \param w - numer wiersza.
     * \param k - numer kolumny. 
     * \pre \f$ 0 \le w \le 2\f$, \f$ 0 \le k \le 3\f$.
     */
  float Mx(unsigned int w, unsigned int k) const { return _DH[w][k]; } 

 private:
    /*!
     * Zmienia zawarto¶æ wybranej kolumny macierzy transformacji.
     * Metoda ta operuje bezpo¶renio na elementach tablicy
     * \link MatrixH3f::_DH _DH\endlink.
     * \param no - numer kolumny,
     * \param x  - nowa warto¶æ pierwszego elementu kolumny,
     * \param y  - nowa warto¶æ drugie elementu kolumny,
     * \param z  - nowa warto¶æ trzeciego elementu kolumny.
     * \pre  \e no musi zawieraæ jedn± z warto¶ci: 0, 1, 2, 3.
     */
    void SetColumn(int no, float x, float y, float z);

    /*!
     * Zmienia zawarto¶æ wybranej kolumny macierzy transformacji.
     * Metoda ta operuje bezpo¶renio na elementach tablicy
     * \link MatrixH3f::_DH _DH\endlink.
     * \param no - numer kolumny,
     * \param Col - wektor wspó³czynników transformacji dla danej kolumny.
     * \pre  \e no musi zawieraæ jedn± z warto¶ci: 0, 1, 2, 3.
     */
    void SetColumn(int no, const Vector3f &Col)
        { SetColumn(no,Col.x,Col.y,Col.z); }


    /*!
     * Udostêpnia wybran± kolumnê macierzy transformacji.
     * \param no - numer kolumny.
     * \pre  \e no musi zawieraæ jedn± z warto¶ci: 0, 1, 2, 3.
     * \return warto¶æ wybranej kolumny. Kolejne wspó³rzêdne zwracanego
     *         wektora odpowiadaj± nastêpuj±cym po sobie elementom kolumny. 
     */
    Vector3f GetColumn(int no) const;
   /*!
    * Udostêpnia w trybie modyfikacji element translacji sk³adowej \e x-owej
    * macierzy transformacji. W przypadku traktowania wektora translacji
    * jako transjacjê po rotacji, odpowiada on bezpo¶rednio 
    * \e x-owej sk³adowej wektora translacji.
    */
    float &UseETx() { return Mx(0,3); }
   /*!
    * Udostêpnia w trybie modyfikacji element translacji sk³adowej \e y-owej
    * macierzy transformacji. W przypadku traktowania wektora translacji
    * jako transjacjê po rotacji, odpowiada on bezpo¶rednio 
    * \e y-owej sk³adowej wektora translacji.
    */
    float &UseETy() { return Mx(1,3); }
   /*!
    * Udostêpnia w trybie modyfikacji element translacji sk³adowej \e z-owej
    * macierzy transformacji. W przypadku traktowania wektora translacji
    * jako transjacjê po rotacji, odpowiada on bezpo¶rednio 
    * \e z-owej sk³adowej wektora translacji.
    */
    float &UseETz() { return Mx(2,3); }

   /*!
    * Udostêpnia w trybie sta³ym element translacji sk³adowej \e x-owej
    * macierzy transformacji. W przypadku traktowania wektora translacji
    * jako transjacjê po rotacji, odpowiada on bezpo¶rednio 
    * \e x-owej sk³adowej wektora translacji.
    */
    float GetETx() const { return Mx(0,3); }
   /*!
    * Udostêpnia w trybie sta³ym element translacji sk³adowej \e y-owej
    * macierzy transformacji. W przypadku traktowania wektora translacji
    * jako transjacjê po rotacji, odpowiada on bezpo¶rednio 
    * \e y-owej sk³adowej wektora translacji.
    */
    float GetETy() const { return Mx(1,3); }
   /*!
    * Udostêpnia w trybie sta³ym element translacji sk³adowej \e z-owej
    * macierzy transformacji. W przypadku traktowania wektora translacji
    * jako transjacjê po rotacji, odpowiada on bezpo¶rednio 
    * \e z-owej sk³adowej wektora translacji.
    */
    float GetETz() const { return Mx(2,3); }

  /*!
   *  Wstawia do macierzy transformacji wspó³czynniki translacji
   *  wyliczane dla \e z-owej wspó³rzêdnej translacji wykonanej 
   *  przed skalowaniem i rotacj±, tzn.
   *  \f[
             R \circ S \circ T
      \f]
   *  \param Tx - wspó³rzêdna \e x-owa wektora translacji.
   *  \param Ty - wspó³rzêdna \e y-owa wektora translacji.
   *  \param Tz - wspó³rzêdna \e z-owa wektora translacji.
   */
   void SetTransZ_TBeforeR(float Tx, float Ty, float Tz)
        { Mx(2,3) = Mx(2,0)*Tx + Mx(2,1)*Ty + Mx(2,2)*Tz; }
  /*!
   *  Wstawia do macierzy transformacji wspó³czynniki translacji
   *  wyliczane dla \e y-owej wspó³rzêdnej translacji wykonanej 
   *  przed skalowaniem i rotacj±, tzn.
   *  \f[
             R \circ S \circ T
      \f]
   *  \param Tx - wspó³rzêdna \e x-owa wektora translacji.
   *  \param Ty - wspó³rzêdna \e y-owa wektora translacji.
   *  \param Tz - wspó³rzêdna \e z-owa wektora translacji.
   */
   void SetTransY_TBeforeR(float Tx, float Ty, float Tz)
        { Mx(1,3) = Mx(1,0)*Tx + Mx(1,1)*Ty + Mx(1,2)*Tz; }
  /*!
   *  Wstawia do macierzy transformacji wspó³czynniki translacji
   *  wyliczane dla \e x-owej wspó³rzêdnej translacji wykonanej 
   *  przed skalowaniem i rotacj±, tzn.
   *  \f[
             R \circ S \circ T
      \f]
   *  \param Tx - wspó³rzêdna \e x-owa wektora translacji.
   *  \param Ty - wspó³rzêdna \e y-owa wektora translacji.
   *  \param Tz - wspó³rzêdna \e z-owa wektora translacji.
   */
   void SetTransX_TBeforeR(float Tx, float Ty, float Tz)
        { Mx(0,3) = Mx(0,0)*Tx + Mx(0,1)*Ty + Mx(0,2)*Tz; }




  protected:
    /*!
     * Operacja mno¿enia danej macierzy przez inn± macierz (sk³adanie 
     * przekszta³ceñ). 
     * \param M - drugi argument operacji mno¿enia.
     */
    void MultiplyByMatrix(MatrixRT3f const &M);

   /*!
    * Wektor wymna¿any jest tylko przez podmacierz rotacji.
    * Wektor translacji nie jest dodawany.
    * \param V - wektor, który jest mno¿ony przez podmacierz rotacji.
    * \return wynik mono¿enia wektora \e V przez podmacierz rotacji.
    */
    Vector3f RotateOnly(const Vector3f &V) const;

  public:


    /*!
     * Operator udostêpnia zadany elemement macierzy transformacji. 
     * \param w - numer wiersza.
     * \param k - numer kolumny. 
     * \pre \f$ 0 \le w \le 2\f$, \f$ 0 \le k \le 3\f$.
     */
    float operator ()(unsigned int w, unsigned int k) const{return Mx(w,k);}


    /*!
     *  Inicjalizuje dan± macierz jako macierz jednostkow±.
     */
   void SetUnitMtx();


     /*!
      * Sprowadza warto¶æ skali transformacji do (1,1,1) aktualizuj±c
      * odpowiednio wspó³czynniki macierzy transformacji.
      */
   void Normalize();

      /*! 
       * Udostêpnia wektor wspó³czynników skali dla poszczególnuch osi.
       * \param Scale - zawiera wspó³czynniki skali odpowiednio dla
       *                osi \e OX, \e OY, \e OZ.
       */
   void GetScale(Vector3f &Scale) const;

  /*! 
   * Udostêpnia spó³czynnik skali dla osi \e OX.
   * \return wpó³czynnik skali dla osi \e OX.
   */
   float GetScaleX() const 
       { return sqrt(SQR(Mx(0,0))+SQR(Mx(1,0))+SQR(Mx(2,0))); }

  /*! 
   * Udostêpnia spó³czynnik skali dla osi \e OY.
   * \return wpó³czynnik skali dla osi \e OY.
   */
  float GetScaleY() const
      { return sqrt(SQR(Mx(0,1))+SQR(Mx(1,1))+SQR(Mx(2,1))); }

  /*! 
   * Udostêpnia spó³czynnik skali dla osi \e OZ.
   * \return wpó³czynnik skali dla osi \e OZ.
   */
   float GetScaleZ() const
      { return sqrt(SQR(Mx(0,2))+SQR(Mx(1,2))+SQR(Mx(2,2))); }

   void SetScale_TAfterR(const Vector3f &Scale);
   void SetScaleX_TAfterR(float Sx);
   void SetScaleY_TAfterR(float Sy);
   void SetScaleZ_TAfterR(float Sz);

   void SetMatrix( const Vector3f &Col1_Rot, 
                   const Vector3f &Col2_Rot,
                   const Vector3f &Col3_Rot,
                   const Vector3f &Col4_Trans
                 );


   void SetMatrix_XYZ_TBeforeR_Rad( const Vector3f &Ang, 
                                    const Vector3f &Trans=Vector3f(),
                                    const Vector3f &Scale=Vector3f(1,1,1)
	                          );

   void SetMatrix_XYZ_TAfterR_Rad( const Vector3f &Ang, 
                                   const Vector3f &Trans=Vector3f(),
                                   const Vector3f &Scale=Vector3f(1,1,1)
	                         );
  /*!
   *  Wyznacza macierz transformacji w reprezentacji \e XYZ (tzn. pierwszy
   *  obrót wzglêdem osi \f$ OX\f$, drugi wzglêdem osi \f$ OY'\f$,
   *  trzeci wzglêdem osi \f$ OZ''\f$). Macierz wyznaczana jest dla
   *  translacji wykonanej po skalowaniu i rotacji, tzn
   *  \f[
               T\circ R \circ S.
      \f]
   *  \param Ang - (\b in) zawiera warto¶ci k±tów odpowiednio obrotu
   *             wzglêdem osi \f$ OX\f$, \f$ OY'\f$, \f$ OZ''\f$.
   *             Warto¶ci k±tów wyra¿one s± w radianach.
   *  \param Trans - (\b in) wektor translacji,
   *  \param Scale - (\b in) wektor wspó³czynników skali wzglêdem
   *                  poszczególnych
   *                  osi odpowiednio  osi \f$ OX\f$, \f$ OY\f$, \f$ OZ\f$.
   *  \post Zostaje wyznaczona macierz transformacji za¶ zostaj± zapamiêtane
   *        w odpowiednich polach.
   */
  void SetMatrix_XYZ_TAfterR_Deg( const Vector3f &Ang, 
                                   const Vector3f &Trans=Vector3f(),
                                   const Vector3f &Scale=Vector3f(1,1,1)
		                 )
           { SetMatrix_XYZ_TAfterR_Rad(compute_deg2rad(Ang),Trans,Scale); }

  void  SetMatrix_Euler_TAfterR_Rad( const Vector3f &Ang, 
                                      const Vector3f &Trans=Vector3f(),
                                      const Vector3f &Scale=Vector3f(1,1,1)
                                    );

  void  SetMatrix_Euler_TBeforeR_Rad( const Vector3f &Ang, 
                                       const Vector3f &Trans=Vector3f(),
                                       const Vector3f &Scale=Vector3f(1,1,1)
                                     );


  /*!
   *  Wyznacza macierz transformacji w reprezentacji k±tów Eulera
   *  (tzn. pierwszy
   *  obrót wzglêdem osi \f$ OZ\f$, drugi wzglêdem osi \f$ OY'\f$,
   *  trzeci wzglêdem osi \f$ OZ''\f$). Macierz wyznaczana jest dla
   *  translacji wykonanej po skalowaniu i rotacji, tzn
   *  \f[
              T\circ R \circ S.
      \f]
   *  \param Ang - (\b in) zawiera warto¶ci k±tów odpowiednio obrotu
   *             wzglêdem osi \f$ OZ\f$, \f$ OY'\f$, \f$ OZ''\f$.
   *             Warto¶ci k±tów wyra¿one s± w stopniach.
   *  \param Trans - (\b in) wektor translacji,
   *  \param Scale - (\b in) wektor wspó³czynników skali wzglêdem
   *                  poszczególnych
   *                  osi odpowiednio  osi \f$ OX\f$, \f$ OY\f$, \f$ OZ\f$.
   *  \post Zostaje wyznaczona macierz transformacji za¶ zostaj± zapamiêtane
   *        w odpowiednich polach.
   */
  void  SetMatrix_Euler_TAfterR_Deg( const Vector3f &Ang, 
                                      const Vector3f &Trans=Vector3f(),
                                      const Vector3f &Scale=Vector3f(1,1,1)
		                    )
          { SetMatrix_Euler_TAfterR_Rad(compute_deg2rad(Ang),Trans,Scale); }


  void SetRotMtx_Euler_Rad( const Vector3f &Ang, const Vector3f &Scale );
  void SetRotMtx_XYZ_Rad( const Vector3f  &Ang, const Vector3f &Scale );

  /*!
   *  Nadaje nowe warto¶ci k±tom Eulera danej transformacji.
   *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
   *  skali. Zadanie k±tów powoduje jednocze¶nie odpowiednie przeliczenie
   *  wspó³czynników macierzy transformacji.
   *  \param Angles - (\b in) wektor warto¶ci k±tów Eulera.
   *      jego kolejne wspó³rzêdne odpowiadaj± k±tom \f$\varphi\f$ 
   *                     (rotacja wokó³ osi \f$ OZ\f$),
   *     \f$\theta\f$ (rotacja wokó³ osi \f$ OY'\f$),
   *     \f$\psi\f$   (rotacja wokó³ osi \f$ OZ''\f$).
   *  \param Scale - wektor wspó³czynników skali odpowiednio osi
   *          \f$ OX\f$, \f$ OY\f$, \f$ OZ\f$.
   *  \post  Zostaj± przeliczone wspó³czynniki macierzy transformacji
   *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
   *        tak aby odpowiada³y zadanym parametrom transformacji.
   */
   void SetAng_Euler_TAfterR_Rad( const Vector3f &Angles, 
                                   const Vector3f &Scale
                                 )
   { SetRotMtx_Euler_Rad(Angles,Scale); }


  float     Det() const;



  void SetTrans_TBeforeR(float Tx, float Ty, float Tz);

  /*!
   *  Wstawia do macierzy transformacji wspó³czynniki translacji
   *  wyliczane dla translacji wykonanej przed skalowaniem i rotacj±,
   *  tzn.
   *  \f[
          R \circ S \circ T
      \f]
   *  \param V - zadawany wektor translacji.
   */
  void SetTrans_TBeforeR(const Vector3f &V)
                  { SetTrans_TBeforeR(V.x,V.y,V.z); }



  void SetTrans_TAfterR(const Vector3f &Trans); 

  /*!
   * Udostêpnia wektor translacji przy za³o¿eniu, ¿e jest ona wykonywana
   * po rotacji, tzn.
   * \f[
      T \circ R \circ S
     \f]
   * \param Trans - (\b out) wpisywane s± do niego udostêpnione warto¶ci
   *                wspó³rzêdnych wektora translacji.
   */
  void GetTrans_TAfterR(Vector3f &Trans) const
                       { Trans.Set(GetETx(),GetETy(),GetETz()); }


  void GetTrans_TBeforeR(Vector3f &Trans);
  bool InvertMtx(MatrixRT3f &FOut) const;
  int  GetEuler_Angles_Scale( Vector3f &Angle, 
                              Vector3f &Scale
                            ) const;
  int  GetXYZ_Angles_Scale( Vector3f &Angle, 
                            Vector3f &Scale
                          ) const;

  void AddTrans_TAfterR(Vector3f const &dT);


   /*!
    * Operator mno¿enia macierzy przez wektor.
    * Operacja nie wp³ywa na warto¶æ pola
    */
  Vector3f  operator *  (Vector3f const &) const;

   /*!
    * Operator mno¿enia macierzy (sk³adanie transformacji) przez macierz
    * i podstawienia.
    */
  MatrixRT3f  &operator *= (MatrixRT3f const &M)
                                { MultiplyByMatrix(M);  return *this; }

   /*!
    * Operator mno¿enia macierzy (sk³adanie transformacji) przez macierz.
    */
  MatrixRT3f   operator *  (MatrixRT3f const &M) const 
                  { MatrixRT3f Res(*this);  return Res *= M; }

};


inline
void MatrixRT3f::GetScale(Vector3f &Scale) const
{
  Scale.x = GetScaleX();
  Scale.y = GetScaleY();
  Scale.z = GetScaleZ();
}


inline
void MatrixRT3f::SetUnitMtx()
{
 int x = 0;

 for (; x<DH_MAXX; x++)
    for (int y=0; y<DH_MAXY; y++) Mx(x,y)=0;
 for (x=0; x<DH_MAXX; x++) Mx(x,x)=1;
}


/*!
 * Umo¿liwia wy¶wietlenie na wyj¶ciu standardowym ca³ej macierzy
 * transformacji.
 */
std::ostream &operator << ( std::ostream &, MatrixRT3f const & );


#endif
