#ifndef STREAMUTILS_HH
#define STREAMUTILS_HH

#include <iostream>

/*! \file streamutils.hh
 *  Plik zawiera nag³ówki metod operuj±cych na strumieniach znakowych.
 *
 *  \author Bogdan Kreczmer
 *  \date   2004.05.19
 *  \version  1.00.00
 */


/*!
 *  Umieszcza w strumieniu podan± ilo¶æ spacji.
 *  \param  SpaceNo - ilo¶æ spacji,
 *  \param  ostrm   - wyj¶ciowy strumieñ znakowy.
 *  \return referencjê do strumienia, który udostêpniony by³ poprzez argument
 *          \e ostrm.
 */
std::ostream &Space(std::ostream &ostrm, unsigned int SpaceNo);
#endif


