#ifndef SGN_HH
#define SGN_HH

/*!
 * \file sgn.hh
 * Definiowany tu jest akceptowalny poziom b³êdu dla obliczeñ 
 * zmiennoprzecinkowych.
 *  Pozwala to niwelowaæ b³êdy, które powoduj±, ¿e koñcowe wyniki minimalnie
 * ró¿ni± siê od zera, choæ ich warto¶ci powinny byæ równe zeru.
 *
 */

/*!
 * Definiuje próg b³êdu, tzn. dwie warto¶ci ró¿ni±ce siê o wielko¶æ nie 
 * wiêksz± ni¿ 0.1e-8 s± traktowane jako równe.
 */
#define   ERROR_LEVEL   0.1e-10

/*!
 * Wzorzec tej funkji pozwala uwzglêdniæ b³êdy obliczñ dla typów float
 * i double.
 */
template <class T>
int sgn(T x)
{ 
  return x > ERROR_LEVEL ? 1 : x < -ERROR_LEVEL ? -1 : 0; 
}

/*!
 * Przeci±¿enie funkcji \c sgn dla \c int zapobiega implementacji
 * wzorca \c sgn dla typu \c int. Uwzglêdnia b³êdy w operacjach
 * zmiennoprzecinkowych, co jest zbêdne dla typu \c int.
 */
inline
int sgn(int x)
{
  return x > 0 ? 1 : x < 0 ? -1 : 0;
}


/*!
 * Przeci±¿enie funkcji \c sgn dla \c long \c int zapobiega implementacji
 * wzorca \c sgn dla typu \c long \c int. Uwzglêdnia b³êdy w operacjach
 * zmiennoprzecinkowych, co jest zbêdne dla typu \c long \c int.
 */
inline
int sgn(long int x)
{
  return x > 0 ? 1 : x < 0 ? -1 : 0;
}

#endif
