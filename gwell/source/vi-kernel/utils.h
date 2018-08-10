#ifndef UTILS_H
#define UTILS_H

/*! \file utils.h
 *  Plik zawiera nag³ówki zapowiedzi funkcji, które operuj± na ³añcuchach
 *  znakowych (w sensie jêzyka C). S± one wykorzystywane przez metody 
 *  z klasy ExtString.
 *
 *  \author Bogdan Kreczmer
 *  \date   2003.12
 *  \version  1.00.00
 */

/*!
 * Zwraca przesuniêty wska¼nik (w stosunku do argumentu polecenia)
 * na ³añcuch znaków, który wskazuje na pierwszy znak ró¿ny od znaku bia³ego.
 * \param str - wska¼nik na ci±g znaków, który mo¿e zawieraæ na pocz±tku
 *              znaki bia³e.
 * \return przesuniêty wska¼nik znaków, wskazuj±cy na pierwszy znak nie
 *         bêd±cy znakiem bia³ym.
 */
char const *SkipFrontSpace( char const * str );
/*!
 * Usuwa z ³añcucha znaków (w sensie jêzyka C) prowadz±ce znaki "bia³e".
 * \param str - (\b in/\b out) zadany ³añcuch znaków, po zadzia³aniu
 *              funkcji usuniête zostaj± z niego prowadz±ce znaki "bia³e".
 * \return wska¼nik na ³añcuch znaków po usuniêciu prowadz±cych znaków 
 *         "bia³ych".
 */
char       *RemoveBegSpace( char * str );
/*!
 * Usuwa z ³añcucha znakowego prowadz±ce znaki bia³e.
 * \param str - wska¼nik na ³añcuch, z którego maj± zostaæ usuniête
 *             prowadz±ce znaki bia³e.
 * \return wska¼nik na ³añcuch wskazywany przez parametr \e str
 */
char       *RemoveFrontSpace( char * str );
/*!
 * Usuwa z ³añcucha znakowego znaki bia³e znajduj±ce siê na jego
 * koñcu.
 * \param str - wska¼nik na ³añcuch, z którego maj± zostaæ usuniête
 *             koñcz±ce go znaki bia³e.
 * \return wska¼nik na ³añcuch wskazywany przez parametr \e str
 */
char const *RemoveEndSpace( char * const str );
/*!
 * Usuwa z ³añcucha znakowego prawadz±ce znaki bia³e oraz te które
 * znajduj±ce siê na jego koñcu.
 * \param str - wska¼nik na ³añcuch, z którego maj± zostaæ usuniête
 *             znaki bia³e.
 * \return wska¼nik na ³añcuch wskazywany przez parametr \e str
 */
char       *RemoveSpace( char * const str );
int findCopyLastNumber(char const *TaskDirName, char const* FileName);
char const *skipString( char const *str );
#endif


