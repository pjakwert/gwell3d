#ifndef STREAMUTILS_HH
#define STREAMUTILS_HH

#include <iostream>

/*! \file streamutils.hh
 *  Plik zawiera nag��wki metod operuj�cych na strumieniach znakowych.
 *
 *  \author Bogdan Kreczmer
 *  \date   2004.05.19
 *  \version  1.00.00
 */


/*!
 *  Umieszcza w strumieniu podan� ilo�� spacji.
 *  \param  SpaceNo - ilo�� spacji,
 *  \param  ostrm   - wyj�ciowy strumie� znakowy.
 *  \return referencj� do strumienia, kt�ry udost�pniony by� poprzez argument
 *          \e ostrm.
 */
std::ostream &Space(std::ostream &ostrm, unsigned int SpaceNo);
#endif


