#ifdef __GNUG__
#pragma implementation
#endif

#include <iostream>
#include "matrixrt3f.hh"
#include "sgn.hh"


namespace Vi {

/*!
 * Oblicza wyznacznik macierzy 3x3
 * \param Row0 - (\b in) wska¼nik na tablicê jednowymiarow± zawieraj±c± 
 *               pierwszy wiersz macierzy.
 * \param Row1 - (\b in) wska¼nik na tablicê jednowymiarow± zawieraj±c± 
 *               drugi wiersz macierzy.
 * \param Row2 - (\b in) wska¼nik na tablicê jednowymiarow± zawieraj±c± 
 *               trzeci wiersz macierzy.
 * \return wyliczon± warto¶æ wyznacznika.
 */
 float ComputeDet3ByRows( float *Row0, float *Row1, float *Row2 )
 {
   return Row0[0]*Row1[1]*Row2[2] + Row0[1]*Row1[2]*Row2[0]
        + Row0[2]*Row1[0]*Row2[1] - Row0[2]*Row1[1]*Row2[1]
        - Row0[0]*Row1[2]*Row2[1] - Row0[1]*Row1[0]*Row2[2];
 }

/*!
 * Oblicza wyznacznik macierzy 3x3
 * \param Col0 - (\b in) wska¼nik na tablicê jednowymiarow± zawieraj±c± 
 *               pierwszy wiersz macierzy.
 * \param Col1 - (\b in) wska¼nik na tablicê jednowymiarow± zawieraj±c± 
 *               drugi wiersz macierzy.
 * \param Col2 - (\b in) wska¼nik na tablicê jednowymiarow± zawieraj±c± 
 *               trzeci wiersz macierzy.
 * \return wyliczon± warto¶æ wyznacznika.
 */
 inline
 float ComputeDet3ByCols( const Vector3f  &Col0, 
                          const Vector3f  &Col1,
                          const Vector3f  &Col2 
                        )
 {
   return Col0[0]*Col1[1]*Col2[2] + Col0[1]*Col1[2]*Col2[0]
        + Col0[2]*Col1[0]*Col2[1] - Col0[2]*Col1[1]*Col2[0]
        - Col0[0]*Col1[2]*Col2[1] - Col0[1]*Col1[0]*Col2[2];
 }



 /*!
  * Wyznacza rozwi±zanie równia postaci:
  * \f[
      \begin{array}{ccccccc}
        a_{11}*x_1 & + & a_{12}*x_2 & + &  a_{13}*x_3 & = & b_1 \\
        a_{21}*x_1 & + & a_{22}*x_2 & + &  a_{23}*x_3 & = & b_1 \\
        a_{31}*x_1 & + & a_{32}*x_2 & + &  a_{33}*x_3 & = & b_1 
      \end{array}
    \f]
  * \param A - (\b in) tablica wspó³czynników równania, sposób 
  *            indeksowania wspó³czynników jest zgodny z porz±dkiem
  *            indeksu elementu tablicy.
  * \param X - (\b out) wektor, do którego wpisane zostaj± wyznaczone
  *            rozwi±zania (o ile istniej±).
  * \retval true - je¶li istnieje rozwi±zanie, jego warto¶æ 
  *            dostêpna jest poprzez parametr \e X.
  * \retval false - gdy rozwi±zanie nie istnieje.
  */
 inline
 bool SolveLinearEq3( float A[3][4], Vector3f &X )
 {

   Vector3f Col1(A[0][0],A[1][0],A[2][0]);
   Vector3f Col2(A[0][1],A[1][1],A[2][1]);
   Vector3f Col3(A[0][2],A[1][2],A[2][2]);
   Vector3f Col4(A[0][3],A[1][3],A[2][3]);

   float D = ComputeDet3ByCols(Col1,Col2,Col3);
   if (!sgn(D)) { X.Set_0();  return false; }
   X.x =  ComputeDet3ByCols(Col4,Col2,Col3)/D;
   X.y =  ComputeDet3ByCols(Col1,Col4,Col3)/D;
   X.z =  ComputeDet3ByCols(Col1,Col2,Col4)/D;
   return true;
 }
}


/*!
 * Udostêpnia wektor translacji przy za³o¿eniu,
 * ¿e translacja jest wykonana po skalowaniu i rotacji, tzn
 * \f[
      T \circ R \circ S
   \f]
 */
void MatrixRT3f::GetTrans_TBeforeR(Vector3f &Trans)
{
  Vi::SolveLinearEq3(_DH,Trans);
}


/*!
 * Wstawia now± skalê dla osi \e OX przyjmuj±c, ¿e aktualne wspó³czynniki
 * macierzy przekszta³cenia jednorodnego odpowiadaj± przypadkowi,
 * gdy translacja jest realizowana po rotacji. W takim przypadku
 * operacja nie powoduje zmiany czwartej kolumny macierzy transformacji,
 * która w tej interpretacji odpowiada bezpo¶rednio wektorowi translacji.
 * \param Sx - (\b in) wspó³czynnik skali dla osi \e OX.
 * \pre Wspó³czynnik skali nie mo¿e byæ równy 0.
 *      Je¿eli dla danej osi wcze¶niej wspó³czynnik skali by³ ustawiony
 *      na warto¶æ 0, to przeskalowanie nie jest realizowane.
 */
void MatrixRT3f::SetScaleX_TAfterR(float Sx)
{
  if (float OldSx = GetScaleX()) {
    Mx(0,0) *= (Sx/OldSx);
    Mx(1,0) *= (Sx/OldSx);
    Mx(2,0) *= (Sx/OldSx);
  }
}



/*!
 * Wstawia now± skalê dla osi \e OY przyjmuj±c, ¿e aktualne wspó³czynniki
 * macierzy przekszta³cenia jednorodnego odpowiadaj± przypadkowi,
 * gdy translacja jest realizowana po rotacji. W takim przypadku
 * operacja nie powoduje zmiany czwartej kolumny macierzy transformacji,
 * która w tej interpretacji odpowiada bezpo¶rednio wektorowi translacji.
 * \param Sy - (\b in) wspó³czynnik skali dla osi \e OY.
 * \pre Wspó³czynnik skali nie mo¿e byæ równy 0.
 *      Je¿eli dla danej osi wcze¶niej wspó³czynnik skali by³ ustawiony
 *      na warto¶æ 0, to przeskalowanie nie jest realizowane.
 */
void MatrixRT3f::SetScaleY_TAfterR(float Sy)
{
  if (float OldSy = GetScaleY()) {
    Mx(0,1) *= (Sy/OldSy);
    Mx(1,1) *= (Sy/OldSy);
    Mx(2,1) *= (Sy/OldSy);
  }
}



/*!
 * Wstawia now± skalê dla osi \e OZ przyjmuj±c, ¿e aktualne wspó³czynniki
 * macierzy przekszta³cenia jednorodnego odpowiadaj± przypadkowi,
 * gdy translacja jest realizowana po rotacji. W takim przypadku
 * operacja nie powoduje zmiany czwartej kolumny macierzy transformacji,
 * która w tej interpretacji odpowiada bezpo¶rednio wektorowi translacji.
 * \param Sz - (\b in) wspó³czynnik skali dla osi \e OZ.
 * \pre Wspó³czynnik skali nie mo¿e byæ równy 0.
 *      Je¿eli dla danej osi wcze¶niej wspó³czynnik skali by³ ustawiony
 *      na warto¶æ 0, to przeskalowanie nie jest realizowane.
 */
void MatrixRT3f::SetScaleZ_TAfterR(float Sz)
{
  if (float OldSz = GetScaleZ()) {
    Mx(0,2) *= (Sz/OldSz);
    Mx(1,2) *= (Sz/OldSz);
    Mx(2,2) *= (Sz/OldSz);
  }
}


/*!
 * Wstawia now± skalê przyjmuj±c, ¿e aktualne wspó³czynniki
 * macierzy przekszta³cenia jednorodnego odpowiadaj± przypadkowi,
 * gdy translacja jest realizowana po rotacji. W takim przypadku
 * operacja nie powoduje zmiany czwartej kolumny macierzy transformacji,
 * która w tej interpretacji odpowiada bezpo¶rednio wektorowi translacji.
 * \param Scale - (\b in) wektor nowych wspó³czynników skali wzglêdem
 *               poszczególnych
 *               osi, tzn. \e OX, \e OY, \e OZ.
 * \pre ¯aden ze wspó³czynników skali nie mo¿e byæ równy 0.
 */
void MatrixRT3f::SetScale_TAfterR(const Vector3f &Scale)
{
  SetScaleX_TAfterR(Scale.x);
  SetScaleY_TAfterR(Scale.y);
  SetScaleZ_TAfterR(Scale.z);
}


/*!
 *  \brief Dodaje do wektora translacji wykonanej po rotacji.
 *
 *  Dodaje zadan± warto¶æ do wektora translacji wykonanej po rotacji.
 *  \param dT - dodawany wektor dodatkowego przsuniêcia do aktualnego
 *              wektora translacji.
 */
void MatrixRT3f::AddTrans_TAfterR(Vector3f const &dT)
{
  UseETx() += dT.x;  UseETy() += dT.y;  UseETz() += dT.z;
}


/*!
 * Metoda oblicza wyznacznik danej macierzy (traktowanej jako macierz) --
 * transformacji jednorodnej.
 */
float MatrixRT3f::Det() const
{
 return (Mx(0,0)*Mx(1,1)-Mx(0,1)*Mx(1,0))*Mx(2,2)+
        (Mx(0,1)*Mx(1,2)-Mx(1,1)*Mx(0,2))*Mx(2,0)+
        (Mx(1,0)*Mx(0,2)-Mx(1,2)*Mx(0,0))*Mx(2,1);
}



/*!
 * Metoda wyznacza macierz transformacji odwrotnej (rozumianej jako macierzy
 * przekszta³cenia jednorodnego) do danej macierzy.
 * \param FOut - (\b out) po wykonaniu operacji parametr zawiera 
 *              wspó³czynniki macierzy odwrotnej, o ile obliczenie
 *              takiej macierzy okaza³o siê byæ mo¿liwe.
 * \retval false - je¶li wyznacznie macierzy odwrotnej nie jest mo¿liwe (gdy
 *             przekszta³cenie osobliwe).
 *        \e FOut - obiekt nie ulega zmianie.
 *
 * \retval true  - gdy macierz przekszta³cenia odwrotnego zosta³a
 *                 wyznaczona.
 *        \e FOut - zawiera wynik obliczeñ, tzn. macierz przekszta³cenia 
 *                odwrotnego do danej macierzy.
 */
bool MatrixRT3f::InvertMtx(MatrixRT3f &FOut) const
{
 float s = Det();

 if (!sgn(s)) return false;

 FOut.Mx(0,0)=(Mx(1,1)*Mx(2,2)-Mx(1,2)*Mx(2,1))/s;
 FOut.Mx(0,1)=-(Mx(0,1)*Mx(2,2)-Mx(0,2)*Mx(2,1))/s;
 FOut.Mx(0,2)=(Mx(0,1)*Mx(1,2)-Mx(0,2)*Mx(1,1))/s;
 FOut.Mx(0,3)=-((Mx(0,1)*Mx(1,2)-Mx(0,2)*Mx(1,1))*Mx(2,3)+
             (Mx(0,3)*Mx(1,1)-Mx(0,1)*Mx(1,3))*Mx(2,2)+
             (Mx(0,2)*Mx(1,3)-Mx(0,3)*Mx(1,2))*Mx(2,1))/s;
 FOut.Mx(1,0)=-(Mx(1,0)*Mx(2,2)-Mx(1,2)*Mx(2,0))/s;
 FOut.Mx(1,1)=(Mx(0,0)*Mx(2,2)-Mx(0,2)*Mx(2,0))/s;
 FOut.Mx(1,2)=-(Mx(0,0)*Mx(1,2)-Mx(0,2)*Mx(1,0))/s;
 FOut.Mx(1,3)=((Mx(0,0)*Mx(1,2)-Mx(0,2)*Mx(1,0))*Mx(2,3)+
            (Mx(0,3)*Mx(1,0)-Mx(0,0)*Mx(1,3))*Mx(2,2)+
            (Mx(0,2)*Mx(1,3)-Mx(0,3)*Mx(1,2))*Mx(2,0))/s;
 FOut.Mx(2,0)=(Mx(1,0)*Mx(2,1)-Mx(1,1)*Mx(2,0))/s;
 FOut.Mx(2,1)=-(Mx(0,0)*Mx(2,1)-Mx(0,1)*Mx(2,0))/s;
 FOut.Mx(2,2)=(Mx(0,0)*Mx(1,1)-Mx(0,1)*Mx(1,0))/s;
 FOut.Mx(2,3)=-((Mx(0,0)*Mx(1,1)-Mx(0,1)*Mx(1,0))*Mx(2,3)+
            (Mx(0,3)*Mx(1,0)-Mx(0,0)*Mx(1,3))*Mx(2,1)+
            (Mx(0,1)*Mx(1,3)-Mx(0,3)*Mx(1,1))*Mx(2,0))/s;
 return true;
}



/*============================================================================
 * Operator mno¿enia wektora przez macierzy. Transformacja wspó³rzêdnych
 * wektora.
 */
Vector3f MatrixRT3f::operator * (Vector3f const &VA) const
{
 float s;
 Vector3f  VOut;

 for(int i=0;i<=2;i++) {
       s=0;
       for(int k=0;k<=2;k++) s=s+Mx(i,k)*VA[k];
       VOut[i]=s+Mx(i,3);
    }
 return VOut;
}



#define FT_ERROR  1.0e-04

// Trzeba to zoptymalizowac.
/*=========================================================================
 * Operacja mno¿enia danej macierzy przez inn± macierz (sk³adanie prze- 
 * kszta³ceñ). Parametry macierzy nie s± aktualizowane. Powoduje to ich 
 * uniewa¿nienie.
 */
void MatrixRT3f::MultiplyByMatrix(MatrixRT3f const &FB)
{
 int   i,j,k;
 float s;
 float Tab[DH_MAXY];
 
   for(i=0; i < DH_MAXX; i++)
    {
       for(j=0; j < DH_MAXX; j++) // Tu MA BYC DH_MAXX a nie DH_MAXY
         {
           s=0;
           for(k=0; k < DH_MAXX; k++) s=s+Mx(i,k)*FB.Mx(k,j);
           Tab[j]= fabs(s) > FT_ERROR ? s : 0;
         }
      s=0;
      for (k=0;k<=2;k++) s=s+Mx(i,k)*FB.Mx(k,3);
      s += Mx(i,3);
      Tab[3] = fabs(s) > FT_ERROR ? s : 0;
      memcpy(_DH[i],Tab, sizeof(float)*DH_MAXY);
    }
}


Vector3f MatrixRT3f::RotateOnly(const Vector3f &V) const
{
 Vector3f  V_out;

 for(int i=0;i<=2;i++) {
      V_out[i]=0;
      for(int k=0;k<=2;k++) V_out[i]=V_out[i]+Mx(i,k)*V[k];
    }
 return V_out;
}



/*!
 *  Wstawia do macierzy transformacji wspó³czynniki translacji
 *  wyliczane dla translacji wykonanej przed skalowaniem i rotacj±,
 *  tzn.
 *  \f[
           R \circ S \circ T
      \f]
 *  \param Tx - (\b in) wspó³rzêdna \e x-owa wektora translacji.
 *  \param Ty - (\b in) wspó³rzêdna \e y-owa wektora translacji.
 *  \param Tz - (\b in) wspó³rzêdna \e z-owa wektora translacji.
 */
void MatrixRT3f::SetTrans_TBeforeR(float Tx, float Ty, float Tz)
{
  SetTransX_TBeforeR(Tx,Ty,Tz);
  SetTransY_TBeforeR(Tx,Ty,Tz);
  SetTransZ_TBeforeR(Tx,Ty,Tz);
}



/*============================================================================
 * Metoda dokonuje normalizacji macierzy rotacji (bez kolumny translacji).
 * Sprowadza w ten sposób wspó³czynniki skali wzd³u¿ osi OX, OY, OZ do 
 * warto¶ci 1. 
 */
void MatrixRT3f::Normalize()
{
 Vector3f Scale;

 GetScale(Scale);

 for(int i=0;i<=2;i++)
     for(int j=0;j<=2;j++) Mx(j,i)=Mx(j,i)/Scale[i];
}



/*!
 *  Metoda udostêpnia warto¶ci k±tów Eulera i skali.
 *  Wielko¶ci te s± jednocze¶nie udostêpniane, gdy¿ wyliczenie
 *  k±tów wymaga wcze¶niejszego wyliczenia skali.
 *  \param Angle - (\b out) wektor zawiera warto¶ci k±tów Eulera,
 *           kolejne wspó³rzêdne odpowiadaj± k±tom: 
 *           \f$ \varphi, \theta, \psi\f$. 
 *  \param Scale - (\b out) zawiera warto¶ci wspó³czynników skali
 *   odpowiednio
 *           dla osi \e OX, \e OY, \e OZ.
 *  \retval 0 - je¶li k±ty i skala s± jednoznacznie wyznaczone.
 *  \retval 1 - gdy k±t \f$\theta\f$ rÓwny jest \e 0 lub \f$ \Pi\f$
 *               (lub dowolnej wielokrotno¶ci k±ta \f$\Pi\f$) warto¶ci
 *               k±tów \f$\varphi\f$ oraz \f$\psi\f$ nie mog± byæ
 *               jednoznacznie
 *               wyznaczone. Obliczona mo¿e byæ jedynie suma tych k±tów,
 *               która jest podstawiana jako warto¶æ k±ta
 *               \f$\psi\f$, za¶ \e 0 jako warto¶æ k±ta \f$\theta\f$.
 *  \retval 2 - gdy warto¶æ wspó³czynnika skali przynajmniej 
 *               dla jednej z osi
 *               równa jest \e 0. W takiej przypadku nie s± obliczane
 *               warto¶ci k±tów, podstawiona zostaje jedynie warto¶æ 0.
 */
int  MatrixRT3f::GetEuler_Angles_Scale( Vector3f &Angle, 
                                         Vector3f &Scale
                                       ) const
{
 GetScale(Scale);
 if (!(Scale.x && Scale.y && Scale.z)) { Angle.Set_0(); return 2; }

 float  cosThe = Mx(2,2)/Scale[2];
 float  sinThe_cosPsi_S2 = -Mx(0,2); 
 float  sinThe_sinPsi_S2 = Mx(1,2);
 float  cosPhi_sinThe_S0 = Mx(2,0);
 float  sinPhi_sinThe_S1 = Mx(2,1);
 float &Psi = Angle.z;
 float &The = Angle.y;
 float &Phi = Angle.x;

 if (!sgn(fabs(cosThe)-1)) {
     The = atan2(0,cosThe);
     Phi = 0;
     Psi = atan2(Mx(0,1),Mx(1,1));
     return 1;
 }

 float C_s = -Mx(2,0)*Mx(0,2)/Scale[0] - Mx(2,1)*Mx(1,2)/Scale[1];
 float S_s = Mx(2,0)*Mx(1,2)/Scale[0] - Mx(2,1)*Mx(0,2)/Scale[1];
 float C_d = -Mx(2,0)*Mx(0,2)/Scale[0] + Mx(2,1)*Mx(1,2)/Scale[1];
 float S_d = Mx(2,0)*Mx(1,2)/Scale[0] + Mx(2,1)*Mx(0,2)/Scale[1];

 float S_pp = atan2(S_s,C_s); // Suma    psi + phi
 float D_pp = atan2(S_d,C_d); // Roznica psi - phi

 Phi = (S_pp - D_pp)/2;
 Psi = (S_pp + D_pp)/2;
 
 float sinPsi = sin(Psi);
 float cosPsi = cos(Psi);

 if (fabs(cosPsi) > fabs(sinPsi)) The = atan2(-Mx(0,2)/cosPsi,Mx(2,2));
                             else The = atan2(Mx(1,2)/sinPsi,Mx(2,2));
 return 0;
}




/*!
 *  Metoda udostêpnia warto¶ci k±tów rotacji przy za³o¿eniu,
 *  ¿e s± one reprezentowne przez k±ty obrotu wokó³ osi
 *  \f$ OX\f$, \f$ OY'\f$, \f$ OZ''\f$, oraz skali.
 *  Wielko¶ci te s± jednocze¶nie udostêpniane, gdy¿ wyliczenie
 *  k±tów wymaga wcze¶niejszego wyliczenia skali.
 *  \param Angle - (\b out) wektor zawiera warto¶ci k±tów obrotu
 *           wzglêdem osi  \f$ OX\f$, \f$ OY'\f$, \f$ OZ''\f$.
 *  \param Scale - (\b out) zawiera warto¶ci wspó³czynników skali
 *   odpowiednio
 *           dla osi \e OX, \e OY, \e OZ.
 *  \retval 0 - je¶li k±ty i skala s± jednoznacznie wyznaczone.
 *  \retval 2 - gdy warto¶æ wspó³czynnika skali przynajmniej 
 *               dla jednej z osi
 *               równa jest \e 0. W takiej przypadku nie s± obliczane
 *               warto¶ci k±tów, podstawiona zostaje jedynie warto¶æ 0.
 */
int  MatrixRT3f::GetXYZ_Angles_Scale( Vector3f &Angle, 
                                      Vector3f &Scale
                                    ) const
{
  GetScale(Scale);
  if (!(Scale.x && Scale.y && Scale.z)) { Angle.Set_0(); return 2; }


  if (sgn(fabs(Mx(2,0)/Scale[0])-1)) {
     float C_s = Mx(0,0)*Mx(2,2)/Scale[2]+Mx(1,0)*Mx(2,1)/Scale[1];
     float S_s = Mx(0,0)*Mx(2,1)/Scale[1]-Mx(1,0)*Mx(2,2)/Scale[2];
     float C_d = Mx(0,0)*Mx(2,2)/Scale[2]-Mx(1,0)*Mx(2,1)/Scale[1];
     float S_d = Mx(0,0)*Mx(2,1)/Scale[1]+Mx(1,0)*Mx(2,2)/Scale[2];
     float S_gp = atan2(S_s,C_s);  // Suma katow: gamma + psi
     float D_gp = atan2(S_d,C_d);  // Roznica katow: gamma - psi

     Angle[0] = (S_gp+D_gp)/2;  // Kat gamma
     Angle[2] = (S_gp-D_gp)/1;
     float cos_x_gamma = cos(Angle[0]);
     float sin_x_gamma = sin(Angle[0]);
     Angle[1] = fabs(cos_x_gamma) > fabs(sin_x_gamma)  ? 
                    atan2(Mx(2,0)/Scale[0],Mx(2,2)/(Scale[2]*cos_x_gamma)) :
                    atan2(Mx(2,0)/Scale[0],Mx(2,1)/(Scale[2]*sin_x_gamma));
     return 0;
  }
  // Przypadke nie jest jednoznacznie okreslony. Mozna jedynie
  // wyznaczyc sume katow  phi (OZ) i gamma (OX)
  Angle[1] = atan2(Mx(2,0)/Scale[0],0);  // theta ~ k*PI
  Angle[2] = atan2(Mx(0,1),Mx(1,1));   // phi
  Angle[0] = 0;
  return 1;
}




void MatrixRT3f::SetColumn(int nr, float x, float y, float z)
{
  Mx(0,nr) = x;
  Mx(1,nr) = y;
  Mx(2,nr) = z; 
};


Vector3f MatrixRT3f::GetColumn(int no) const
{
  return Vector3f(Mx(0,no),Mx(1,no),Mx(2,no));
};



/*!
 *  Podstawia do macierzy transformacji wektor translacji jako 
 *  przekszta³cenie realizowane po rotacji.
 */
void MatrixRT3f::SetTrans_TAfterR(const Vector3f &Trans)
{
  Mx(0,3)=Trans[0];
  Mx(1,3)=Trans[1];
  Mx(2,3)=Trans[2];
}



/*!
 *  Wylicza podmacierz transformacji w reprezentacji \e XYZ (tzn. pierwszy
 *  obrót wzglêdem osi \f$ OX\f$, drugi wzglêdem osi \f$ OY'\f$,
 *  trzeci wzglêdem osi \f$ OZ''\f$).
 *  \param Ang - (\b in) zawiera warto¶ci k±tów odpowiednio obrotu
 *             wzglêdem osi \f$ OX\f$, \f$ OY'\f$, \f$ OZ''\f$.
 *             Warto¶ci k±tów wyra¿one s± w radianach.
 *  \param Scale - (\b in) wektor wspó³czynników skali wzglêdem
 *                  poszczególnych
 *                  osi odpowiednio  osi \f$ OX\f$, \f$ OY\f$, \f$ OZ\f$.
 *  \post Zostaje wyliczona podmacierz rotacji za¶ zostaj± zapamiêtane
 *        w odpowiednich polach.
 */
void MatrixRT3f::SetRotMtx_XYZ_Rad( const Vector3f  &Ang, 
                                    const Vector3f  &Scale 
                                  )
{
  float  sn0 = sin(Ang[0]);  // sin_gamma
  float  cs0 = cos(Ang[0]);  // cos_gamma
  float  sn1 = sin(Ang[1]);  // sin_theta
  float  cs1 = cos(Ang[1]);  // cos_theta
  float  sn2 = sin(Ang[2]);  // sin_phi
  float  cs2 = cos(Ang[2]);  // cos_phi

 Mx(0,0)=Scale[0]*cs2*cs1;
 Mx(1,0)=Scale[0]*(-sn2)*cs1;
 Mx(2,0)=Scale[0]*(sn1);
 Mx(0,1)=Scale[1]*(sn2*cs0-cs2*sn1*sn0);
 Mx(1,1)=Scale[1]*(cs2*cs0+sn2*sn1*sn0);
 Mx(2,1)=Scale[1]*sn0*cs1;
 Mx(0,2)=Scale[2]*(-sn2*sn0-cs2*sn1*cs0);
 Mx(1,2)=Scale[2]*(-cs2*sn0+cs0*sn1*sn2);
 Mx(2,2)=Scale[2]*cs0*cs1;
}


/*!
 *  Umo¿liwia bezpo¶rednie zadawanie wspó³czynników transformacji
 *  danej macierzy. Metodê tê nale¿y stosowaæ bardzo rozwa¿nie,
 *  gdy¿ wspó³czynniki transformacji nie mog± byæ dowolnymi warto¶ciami,
 *  o ile nie maj± wprowadzaæ deformacji w transformowanych bry³ach.
 *  Je¿eli wspó³czynniki nie bêd± spe³nia³y wiêzów na³o¿onych ma macierz 
 *  rotacji, to wszystkie metody wyliczaj±ce k±ty rotacji, nie
 *  bêd± zwraca³y poprawnych warto¶ci.\n
 *  Dla podmacierzy rotacji wspomniane wiêzy maj± postaæ:
 *
 \f[
            \left[\begin{array}{cccc}
               a_{11} & a_{12} &  a_{13}  & a_{14} \\
               a_{21} & a_{22} &  a_{23}  & a_{24} \\
               a_{31} & a_{32} &  a_{33}  & a_{34}\\
                   0 & 0 & 0 & 1
              \end{array}\right]       
             =
            \left[\begin{array}{cccc}
               s_xr_{11} & s_yr_{12} &  s_zr_{13}  & t_x \\
               s_xr_{21} & s_yr_{22} &  s_zr_{23}  & t_y \\
               s_xr_{31} & s_yr_{32} &  s_zr_{33}  & t_z\\
                   0 & 0 & 0 & 1
              \end{array}\right]       
 \f]
\f[
         a_{11}^2 + a_{21}^2 + a_{31}^2 = s_x
\f]
\f[
         a_{12}^2 + a_{22}^2 + a_{32}^2 = s_y
\f]
\f[
         a_{13}^2 + a_{23}^2 + a_{33}^2 = s_z
\f]
\f[
        a_{1i}a_{1j} + a_{2i}a_{2j} + a_{3i}a_{3j} = 0
\f]
 *   gdzie  \f$ i,j = 1,2,3 \f$ oraz \f$ i \ne j\f$.
 *  \param Col1_Rot - warto¶ci wspó³czynników transformacji dla pierwszej
 *                    kolumny (pierwsza kolumna podmacierzy rotacji).
 *  \param Col2_Rot - warto¶ci wspó³czynników transformacji dla drugiej
 *                    kolumny (druga kolumna podmacierzy rotacji).
 *  \param Col3_Rot - warto¶ci wspó³czynników transformacji dla drugiej
 *                    kolumny (trzecia kolumna podmacierzy rotacji).
 *  \param Col4_Trans - warto¶ci wspó³czynników transformacji dla trzeciej
 *                    kolumny (wektor translacji).
 */
void MatrixRT3f::SetMatrix( const Vector3f &  Col1_Rot, 
                            const Vector3f &  Col2_Rot,
                            const Vector3f &  Col3_Rot,
                            const Vector3f &  Col4_Trans
                          )
{
  SetColumn(0,Col1_Rot);
  SetColumn(1,Col2_Rot);
  SetColumn(2,Col3_Rot);
  SetColumn(3,Col4_Trans);
}




/*!
 *  Wyliczona macierz transformacji w reprezentacji \e XYZ (tzn. pierwszy
 *  obrót wzglêdem osi \f$ OX\f$, drugi wzglêdem osi \f$ OY'\f$,
 *  trzeci wzglêdem osi \f$ OZ''\f$). Macierz wyznaczana jest dla
 *  translacji wykonanej po skalowaniu i rotacji, tzn
 *  \f[
               F = R \circ S \circ T
      \f]
 *  \param Ang - (\b in) zawiera warto¶ci k±tów odpowiednio obrotu
 *             wzglêdem osi \f$ OX\f$, \f$ OY'\f$, \f$ OZ''\f$.
 *             Warto¶ci k±tów wyra¿one s± w radianach.
 *  \param Trans - (\b in) wektor translacji,
 *  \param Scale - (\b in) wektor wspó³czynników skali wzglêdem
 *                  poszczególnych
 *                  osi odpowiednio  osi \f$ OX\f$, \f$ OY\f$, \f$ OZ\f$.
 *  \post Zostaje wyliczona macierz transformacji.
 */
void MatrixRT3f::SetMatrix_XYZ_TBeforeR_Rad( const Vector3f &Ang, 
                                              const Vector3f &Trans,
                                              const Vector3f &Scale
	                                    )
{
 SetRotMtx_XYZ_Rad(Ang,Scale);
 SetTrans_TBeforeR(Trans);
}






/*!
 *  Wyliczona macierz transformacji w reprezentacji \e XYZ (tzn. pierwszy
 *  obrót wzglêdem osi \f$ OX\f$, drugi wzglêdem osi \f$ OY'\f$,
 *  trzeci wzglêdem osi \f$ OZ''\f$). Macierz wyznaczana jest dla
 *  translacji wykonanej po skalowaniu i rotacji, tzn
 *  \f[
             F = T \circ R \circ S.
      \f]
 *  \param Ang - (\b in) zawiera warto¶ci k±tów odpowiednio obrotu
 *             wzglêdem osi \f$ OX\f$, \f$ OY'\f$, \f$ OZ''\f$.
 *             Warto¶ci k±tów wyra¿one s± w radianach.
 *  \param Trans - (\b in) wektor translacji,
 *  \param Scale - (\b in) wektor wspó³czynników skali wzglêdem
 *                  poszczególnych
 *                  osi odpowiednio  osi \f$ OX\f$, \f$ OY\f$, \f$ OZ\f$.
 *  \post Zostaje wyliczona macierz transformacji.
 */
void MatrixRT3f::SetMatrix_XYZ_TAfterR_Rad( const Vector3f &Ang, 
                                             const Vector3f &Trans,
                                             const Vector3f &Scale
	                                   )
{
 SetRotMtx_XYZ_Rad(Ang,Scale);
 SetTrans_TAfterR(Trans);
}




/*!
 *  Wyliczona macierz transformacji wykorzystuj±c reprezentacjê rotacji
 *  za pomoc± k±tów Eulera
 *  (tzn. pierwszy
 *  obrót wzglêdem osi \f$ OZ\f$, drugi wzglêdem osi \f$ OY'\f$,
 *  trzeci wzglêdem osi \f$ OZ''\f$). Macierz wyznaczana jest dla
 *  translacji wykonanej po skalowaniu i rotacji, tzn
 *  \f[
             F =  R \circ S \circ T.
      \f]
 *  \param Ang - (\b in) zawiera warto¶ci k±tów odpowiednio obrotu
 *             wzglêdem osi \f$ OZ\f$, \f$ OY'\f$, \f$ OZ''\f$.
 *             Warto¶ci k±tów wyra¿one s± w radianach.
 *  \param Trans - (\b in) wektor translacji,
 *  \param Scale - (\b in) wektor wspó³czynników skali wzglêdem
 *                  poszczególnych
 *                  osi odpowiednio  osi \f$ OX\f$, \f$ OY\f$, \f$ OZ\f$.
 *  \post Zostaje wyliczona macierz transformacji.
 */
void MatrixRT3f::SetMatrix_Euler_TBeforeR_Rad( const Vector3f &Ang, 
                                               const Vector3f &Trans,
                                               const Vector3f &Scale
		                             )
{
 SetRotMtx_Euler_Rad(Ang,Scale);
 SetTrans_TBeforeR(Trans);
}





/*!
 *  Wyliczona macierz transformacji wykorzystuj±c reprezentacjê rotacji
 *  za pomoc± k±tów Eulera
 *  (tzn. pierwszy
 *  obrót wzglêdem osi \f$ OZ\f$, drugi wzglêdem osi \f$ OY'\f$,
 *  trzeci wzglêdem osi \f$ OZ''\f$). Macierz wyznaczana jest dla
 *  translacji wykonanej po skalowaniu i rotacji, tzn
 *  \f[
             F = T \circ R \circ S.
      \f]
 *  \param Ang - (\b in) zawiera warto¶ci k±tów odpowiednio obrotu
 *             wzglêdem osi \f$ OZ\f$, \f$ OY'\f$, \f$ OZ''\f$.
 *             Warto¶ci k±tów wyra¿one s± w radianach.
 *  \param Trans - (\b in) wektor translacji,
 *  \param Scale - (\b in) wektor wspó³czynników skali wzglêdem
 *                  poszczególnych
 *                  osi odpowiednio  osi \f$ OX\f$, \f$ OY\f$, \f$ OZ\f$.
 *  \post Zostaje wyliczona macierz transformacji.
 */
void MatrixRT3f::SetMatrix_Euler_TAfterR_Rad( const Vector3f &Ang, 
                                               const Vector3f &Trans,
                                               const Vector3f &Scale
		                             )
{
 SetAng_Euler_TAfterR_Rad(Ang,Scale);
 SetTrans_TAfterR(Trans);
}




std::ostream &operator << ( std::ostream &ostr, MatrixRT3f const &F )
{
  ostr << std::endl;
  std::cout << " -----------------------------" << std::endl;
  for (int ix=0; ix < DH_MAXX; ix++) {
    std::cout << "    ";
    for (int iy=0; iy < DH_MAXY; iy++) {
      std::cout << "  " << F(ix,iy);
    }
    std::cout << std::endl;
  }
  std::cout << " -----------------------------" << std::endl;
  return ostr;
}



/*!
 *  Wyznacza podmacierz rotacji przy przyjmuj±c, ¿e rotacja jest
 *  okre¶lona za pomoc± k±tów Eulera
 *  (tzn. pierwszy
 *  obrót wzglêdem osi \f$ OZ\f$, drugi wzglêdem osi \f$ OY'\f$,
 *  trzeci wzglêdem osi \f$ OZ''\f$). Wspó³czynniki macierzy wyznaczane
 *  s± przy za³o¿eniu, ¿e skalowanie realizowane jest najpierw.
 *  Wspó³czynniki translacji nie s± modyfikowane.
 *
 *  \param Ang - (\b in) zawiera warto¶ci k±tów odpowiednio obrotu
 *             wzglêdem osi \f$ OZ\f$, \f$ OY'\f$, \f$ OZ''\f$.
 *             Warto¶ci k±tów wyra¿one s± w radianach.
 *  \param Scale - (\b in) wektor wspó³czynników skali wzglêdem
 *                  poszczególnych
 *                  osi odpowiednio  osi \f$ OX\f$, \f$ OY\f$, \f$ OZ\f$.
 */
void MatrixRT3f::SetRotMtx_Euler_Rad( const Vector3f &Ang, 
                                      const Vector3f &Scale
                                    )
{
 float sinPhi = sin(Ang[0]);  // sin(phi)
 float cosPhi = cos(Ang[0]);  // cos(phi)
 float sinThe = sin(Ang[1]);  // sin(theta)
 float cosThe = cos(Ang[1]);  // cos(theta)
 float sinPsi = sin(Ang[2]);  // sin(psi)
 float cosPsi = cos(Ang[2]);  // cos(psi)


 Mx(0,0)=Scale[0]*(cosPhi*cosThe*cosPsi-sinPhi*sinPsi);
 Mx(1,0)=-(Scale[0])*(cosPhi*cosThe*sinPsi+sinPhi*cosPsi);
 Mx(2,0)=Scale[0]*cosPhi*sinThe;

 Mx(0,1)=Scale[1]*(sinPhi*cosThe*cosPsi+cosPhi*sinPsi); 
 Mx(1,1)=Scale[1]*(-sinPhi*cosThe*sinPsi+cosPhi*cosPsi);
 Mx(2,1)=Scale[1]*sinPhi*sinThe;

 Mx(0,2)=-Scale[2]*(sinThe*cosPsi); 
 Mx(1,2)=Scale[2]*sinThe*sinPsi;
 Mx(2,2)=Scale[2]*cosThe;
}

