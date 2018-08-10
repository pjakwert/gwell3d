#ifdef __GNUG__
#pragma implementation
#endif

//=================================================================
//  Klasa napisu.
//
//  wer. 1.0.2
//       2003.04.23
//
#include <iostream>
#include <cstring>
#include <cctype>
#include <sstream>
#include "extstring.hh"

using namespace std;



string::size_type ExtString::Find_ith(const char *Str, unsigned int Idx) const
{
  if (!Str || !*Str) return string::npos;
  if (!Idx) return string::npos;

  string::size_type   Pos_i = 0; 

  for (; Idx; --Idx) {
    if ((Pos_i = find(Str,Pos_i)) == string::npos) return string::npos;   
    Pos_i += strlen(Str);
  }
  return Pos_i - strlen(Str);
}



bool ExtString::IsNewLineAtEnd() const
{
  if (empty()) return false;
  string::size_type  Len = length();
  return Len && (*this)[Len-1] == '\n';
}



/*==========================================================================
 * Sprawdza, czy od i-tej pozycji do konca lancuch zawiera tylko 
 * biale znaki.
 *     
 * Zwraca: 1 - jesli od i-tej pozycji do koñca w ³añcuchu sa tylko znaki bia³e
 *         0 - je¶li tak nie jest,
 *        -1 - je¶li podana pozycja wykracza poza ³añcuch.
 */
int ExtString::IsSpaceToEnd(size_type i) const
{
  if (i < 0 || length() <= i) return -1;
  do {
    if (!isspace(at(i))) return 0;
  } while (++i < length());
  return 1;
}


void ExtString::AddSpace(unsigned int No)
{
  for (unsigned int i=0; i < No; i++) *this += ' ';
}




string::size_type ExtString::SkipLine(string::size_type Idx) const
{
  string::size_type Idx_i = find('\n',Idx);
  if (Idx_i == string::npos) return string::npos;
  return Idx_i+1;
}



string::size_type ExtString::GoToSpaceChar(string::size_type Idx) const
{
  return find_first_of(" \t\n\0",Idx);
}


string::size_type ExtString::GoToNotSpaceChar(string::size_type Idx) const
{
  return find_first_not_of(" \t\n",Idx);
}


std::string::size_type ExtString::SkipSpace(std::string::size_type Idx,
                                            const char *           TermChars
                                           ) const
{
  if (Idx > size()) return string::npos;
  string  AllTerms(" \t\n\0");

  std::string::size_type  ChPos;
  while (*TermChars) {
    if ((ChPos = AllTerms.find(*TermChars)) == string::npos) {
      AllTerms.erase(ChPos,1);
    }
    ++TermChars;
  }
  if (AllTerms.empty()) return Idx;
  return find_first_not_of(AllTerms,Idx);
}


std::string::size_type ExtString::GetNotSpacedString(  std::string::size_type Idx,
                                                       ExtString  &       Str,
                                                       const char *       TermChars
                                                    ) const
{
  if ((Idx = SkipSpace(Idx,TermChars)) == string::npos) return string::npos;
  Str.clear();
  do {
    Str += (*this)[Idx];
    if (++Idx > size()) return true;
  } while (!isspace((*this)[Idx]));
  return Idx;
}

/*==========================================================================
 * Usuwa puste linie z konca tekstu.
 *
 * Zwraca:  true  - je¶li ³±ñcuch zosta³ zmodyfikowany.
 *          false - w przypadku przeciwnym.
 */
bool ExtString::RemoveEmptyTail()
{
  bool res = false;
  if (RemoveLastEmptyLine()) {
    res = true;
    while (RemoveLastEmptyLine());
  }
  return res;
}

/*==========================================================================
 * Usuwa puste linie z konca tekstu i znak przejscia do nowej
 * linii z konca tekstu.
 *
 * Zwraca:  true  - je¶li ³±ñcuch zosta³ zmodyfikowany.
 *          false - w przypadku przeciwnym.
 */
bool ExtString:: RemoveNewLineFromEnd()
{
  if (IsEmpty()) return false;
  if (at(length()-1) != '\n') return false;
  erase(length()-1);
  return true;
}


/*==========================================================================
 * Usuwa puste linie z konca tekstu i znak przejscia do nowej
 * linii z konca tekstu.
 *
 * Zwraca:  true  - je¶li ³±ñcuch zosta³ zmodyfikowany.
 *          false - w przypadku przeciwnym.
 */
bool ExtString::RemoveEmptyTailAndLastNL()
{
 if (IsEmpty()) return false;
 bool res1 = RemoveEmptyTail();
 bool res2 = RemoveNewLineFromEnd();
 return res1 || res2;
}




/*==========================================================================
 * Usuwa ostatnia linie jesli sklada sie ona tylko z bialych
 * znakow
 */
bool ExtString::RemoveLastEmptyLine()
{
  size_type  pos_i = 0, pos_n;
  
  if (IsEmpty()) return false;
  if (length() == 0) return false;
  if (length() == 1) {
    if (isspace(at(0))) { clear();  return true; }
    return false;
  }
  while ((pos_n = find('\n',pos_i)) != npos) {
    if (pos_n+1 >= length()) { // '\n' jest na koncu tekstu.
      break;
    }
    pos_i = pos_n + 1;
  }
  if (pos_i > 0) pos_i--;
  if (IsSpaceToEnd(pos_i) == 1) { erase(pos_i);  return true; }
  return false;
}



/*==========================================================================
 *  Kopiuje od elementu wskazanego przez pBeg
 *  kolejnych 'Size' elementow.
 */
ExtString &ExtString::Copy(char const *pBeg, unsigned int Size)
{
  assign(pBeg,Size);
  return *this;
}


/*==========================================================================
 *  Kopiuje od pierwszego wskazanego przez pBeg do ostatniego
 *  wskazanego przez pEnd. Kopiowanie realizowane jest
 *  lacznie z ostatnim znakiem wskazywanym przez pEnd.
 */
ExtString &ExtString::Copy(char const *pBeg, char const *pEnd)
{
  assign(pBeg,pEnd-pBeg+1);
  return *this;
}



/*==========================================================================
 *  Znajduje pozycje znaku znajdujacego sie za i-ty znakiem "C" 
 *  w danym ciagu. Jesli nie znajdzie to zwraca -1.
 *  Numeracja znakow rozpoczyna sie od 0.
 */
string::size_type ExtString::FindBehind_ith(char C, unsigned int Idx) const
{
  size_type  pos = 0;
  do {
    if ((pos = find(C,pos)) == npos) return npos;
    pos++;
  } while (Idx--);
  if (pos >= length()) return npos;
  return pos;
}



/*==========================================================================
 * Powoduje przekopiowanie do Trg pierwszej linii
 *        Trg - zawiera pierwsza linie
 * Zwraca  0 jesli linia nie jest pusta,
 *        -1 w przypadku przeciwnym
 */
int ExtString::ExtractFirstLineFor(ExtString &Trg, bool IncludingNL)
         const
{
  return ExtractLineFor(0,Trg,IncludingNL);
}



 
/*==========================================================================
 * Powoduje przekopiowanie do Trg linii o numerze wskazanej przez Idx
 * przy czym Idx = 0 oznacza linie nr 1, Idx = 1 linie nr 2 itd.
 *
 *        Trg - zawiera pierwsza linie
 * Zwraca 0  gdy dana linia zosta³a poprawnie wyekstrahowana,
 *       -1  gdy nie istnieje linia o takim numerze (rowniez wtedy 
 *           gdy Trg.IsNULL()..
 */
int ExtString::ExtractLineFor( unsigned int    Idx, 
                               ExtString      &Trg, 
                               bool            IncludingNL
                             ) const
{
  if (IsEmpty()) return -1;

  std::string::size_type  pos_o = 0, pos_n;
  int  SizeNL = IncludingNL ? 1 : 0;
  bool LastLine = false;

  if (Idx) {
   if ((pos_o = FindBehind_ith('\n',Idx-1)) == npos) return -1;
  }

  if ((pos_n = find('\n',pos_o)) == npos) {
      pos_n = length();     // Wskazuje nastepny znak za ostanim znakiem.
      LastLine = true;
      if (pos_n && (*this)[pos_n-1] == '\n') --pos_n;
      // Ostatnia linia wychodzi stad zawsze bez '\n'
  } else pos_n += SizeNL; // Wskazuje nastepny znak za NL (gdy SizeNL = 1).

  if (!(*this)[pos_n] && pos_o+1 == pos_n) return -1;
  Trg.assign(*this,pos_o,pos_n-pos_o);
  if (LastLine && IncludingNL) Trg += '\n';
  return 0;
}



bool ExtString::IsEmptyText() const
{
  if (IsEmpty()) return 1;
  char const *s = c_str();
  while (*++s) if (!isspace(*s)) return false;
  return true;
}


void ExtString::RemoveSpace()
{
  if (!length()) return;

  char const *s = c_str() + length() - 1;
  while (isspace(*s) && s != c_str()) s--;
  if (isspace(*s)) { clear(); return; }
  erase(s-c_str()+1);


  if (!isspace(*(s = c_str()))) return;
  if (!*s) return;
  while (isspace(*s) && *s) s++;
  replace(0,s-c_str(),"");
}



void ExtString::ToLower()
{
  char *s = (char*) c_str();
 
  if (!s) return;
  for (; *s; s++) *s = tolower(*s);
}



bool ExtString::operator == (const char *Str) const
{
  return !strcmp(c_str(),Str);
}


bool ExtString::operator == (const std::string &Str) const
{
  return (*(const std::string*)this) == (Str);
}



ExtString &ExtString::operator = (const std::string &Str)
{
  assign(Str);  return *this;
}



ExtString &ExtString::operator = (char const * const Str) 
{
  assign(Str);  return *this;
}


ExtString &ExtString::operator = (char const c) 
{
  this->string::operator=(c);  return *this;
}


ExtString::ExtString(char const *Name) 
{ 
  *this = Name; 
}


ExtString &ExtString::operator << (char const * const Str)
{
  *this += Str;  return *this;
}



ExtString &ExtString::operator << (char const c)
{
  *this += c;  return *this;
}


ExtString &ExtString::Add(const ostringstream &ostrm)
{
  return *(ExtString*)&(*this += ostrm.str().c_str());
}



#define IMPLEMENT_METHOD4EXTSTRING_LEFTSHIF(type)    \
 ExtString &ExtString::operator << (type val)        \
 {                                                   \
   ostringstream ostrm;                              \
   return Add(*(ostringstream*)&(ostrm << val));     \
 }



IMPLEMENT_METHOD4EXTSTRING_LEFTSHIF(float)
IMPLEMENT_METHOD4EXTSTRING_LEFTSHIF(double)
IMPLEMENT_METHOD4EXTSTRING_LEFTSHIF(int)
IMPLEMENT_METHOD4EXTSTRING_LEFTSHIF(unsigned int)
IMPLEMENT_METHOD4EXTSTRING_LEFTSHIF(long int)
IMPLEMENT_METHOD4EXTSTRING_LEFTSHIF(unsigned long int)
