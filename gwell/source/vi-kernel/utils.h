#ifndef UTILS_H
#define UTILS_H

/*! \file utils.h
 *  Plik zawiera nag��wki zapowiedzi funkcji, kt�re operuj� na �a�cuchach
 *  znakowych (w sensie j�zyka C). S� one wykorzystywane przez metody 
 *  z klasy ExtString.
 *
 *  \author Bogdan Kreczmer
 *  \date   2003.12
 *  \version  1.00.00
 */

/*!
 * Zwraca przesuni�ty wska�nik (w stosunku do argumentu polecenia)
 * na �a�cuch znak�w, kt�ry wskazuje na pierwszy znak r�ny od znaku bia�ego.
 * \param str - wska�nik na ci�g znak�w, kt�ry mo�e zawiera� na pocz�tku
 *              znaki bia�e.
 * \return przesuni�ty wska�nik znak�w, wskazuj�cy na pierwszy znak nie
 *         b�d�cy znakiem bia�ym.
 */
char const *SkipFrontSpace( char const * str );
/*!
 * Usuwa z �a�cucha znak�w (w sensie j�zyka C) prowadz�ce znaki "bia�e".
 * \param str - (\b in/\b out) zadany �a�cuch znak�w, po zadzia�aniu
 *              funkcji usuni�te zostaj� z niego prowadz�ce znaki "bia�e".
 * \return wska�nik na �a�cuch znak�w po usuni�ciu prowadz�cych znak�w 
 *         "bia�ych".
 */
char       *RemoveBegSpace( char * str );
/*!
 * Usuwa z �a�cucha znakowego prowadz�ce znaki bia�e.
 * \param str - wska�nik na �a�cuch, z kt�rego maj� zosta� usuni�te
 *             prowadz�ce znaki bia�e.
 * \return wska�nik na �a�cuch wskazywany przez parametr \e str
 */
char       *RemoveFrontSpace( char * str );
/*!
 * Usuwa z �a�cucha znakowego znaki bia�e znajduj�ce si� na jego
 * ko�cu.
 * \param str - wska�nik na �a�cuch, z kt�rego maj� zosta� usuni�te
 *             ko�cz�ce go znaki bia�e.
 * \return wska�nik na �a�cuch wskazywany przez parametr \e str
 */
char const *RemoveEndSpace( char * const str );
/*!
 * Usuwa z �a�cucha znakowego prawadz�ce znaki bia�e oraz te kt�re
 * znajduj�ce si� na jego ko�cu.
 * \param str - wska�nik na �a�cuch, z kt�rego maj� zosta� usuni�te
 *             znaki bia�e.
 * \return wska�nik na �a�cuch wskazywany przez parametr \e str
 */
char       *RemoveSpace( char * const str );
int findCopyLastNumber(char const *TaskDirName, char const* FileName);
char const *skipString( char const *str );
#endif


