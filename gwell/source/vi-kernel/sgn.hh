#ifndef SGN_HH
#define SGN_HH

/*!
 * \file sgn.hh
 * Definiowany tu jest akceptowalny poziom b��du dla oblicze� 
 * zmiennoprzecinkowych.
 *  Pozwala to niwelowa� b��dy, kt�re powoduj�, �e ko�cowe wyniki minimalnie
 * r�ni� si� od zera, cho� ich warto�ci powinny by� r�wne zeru.
 *
 */

/*!
 * Definiuje pr�g b��du, tzn. dwie warto�ci r�ni�ce si� o wielko�� nie 
 * wi�ksz� ni� 0.1e-8 s� traktowane jako r�wne.
 */
#define   ERROR_LEVEL   0.1e-10

/*!
 * Wzorzec tej funkji pozwala uwzgl�dni� b��dy oblicz� dla typ�w float
 * i double.
 */
template <class T>
int sgn(T x)
{ 
  return x > ERROR_LEVEL ? 1 : x < -ERROR_LEVEL ? -1 : 0; 
}

/*!
 * Przeci��enie funkcji \c sgn dla \c int zapobiega implementacji
 * wzorca \c sgn dla typu \c int. Uwzgl�dnia b��dy w operacjach
 * zmiennoprzecinkowych, co jest zb�dne dla typu \c int.
 */
inline
int sgn(int x)
{
  return x > 0 ? 1 : x < 0 ? -1 : 0;
}


/*!
 * Przeci��enie funkcji \c sgn dla \c long \c int zapobiega implementacji
 * wzorca \c sgn dla typu \c long \c int. Uwzgl�dnia b��dy w operacjach
 * zmiennoprzecinkowych, co jest zb�dne dla typu \c long \c int.
 */
inline
int sgn(long int x)
{
  return x > 0 ? 1 : x < 0 ? -1 : 0;
}

#endif
