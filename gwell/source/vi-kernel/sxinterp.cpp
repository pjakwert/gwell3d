#ifdef __GNUG__
#pragma implementation
#endif

#include <iomanip>
#include <cctype>
#include <iostream>
#include "sxinterp.hh"
#include "extstring.hh"

using namespace std;
using namespace Sx;


void  KeywordList::GetAllKeywords(std::string  &Keywords)
{
  const char *Comma = "";

  Keywords.clear();
  for (KeyPair *Item = First(); Item; Item = Item->Next()) {
    (Keywords += Comma) += Item->Keyword().c_str();
    Comma = ", ";
  }
}



bool KeywordList::ShouldLoopBeContinued() const
{
  if (!_CanEndAfterMeetingAll) return true;
  return !AllKeywordsWereVisited();
}



bool KeywordList::AllKeywordsWereVisited() const
{
  for (const KeyPair *Item = First(); Item; Item = Item->Next()) {
    if (!Item->GetEncounterNo()) return false;
  }
  return true;
}



void MultiStack::CreateNewKeySet(bool CanEndAfterMeetingAll)
{
  _InitNewQueue = true; AddToHead(new KeywordList(CanEndAfterMeetingAll));
}



SxInterp::SxInterp(const string &Str): istringstream(Str) 
{ 
  _LineNo = 0; 
  SetVectorSep('(',',',')');
}


MultiStack & MultiStack::operator ()(const char *Str, int ID)
{
  if (!First()) return *this;
  First()->AddToTail(new KeyPair(Str,ID));
  return *this;
}




/*!
 * Wczytuje ci±g znaków, a¿ do znaku koñca linii lub koñca strumienia.
 * \param Line - (\b out) do parametru wpisywana jest odczytana linia.
 */
void SxInterp::GetLine( std::string &Line )
{
  Line = "";
  char  c;

  while ((*this >> c).good()) {
    if (c == '\n') return;
    Line += c;
  }
}



void SxInterp::EatWhite() 
{
  char  c;
  *this >> noskipws;

  while (*this >> c) {
    if (c == '\n') { ++_LineNo; continue; }
    if (!isspace(c)) break;
  }
  this->unget();
}



int SxInterp::GetNextKeyword() // throw (Sx::Exception)
{
  char   c;
  string Word;

  EatWhite();
  if (!First()) 
    throw Sx::Exception(ERRNUM_SX__NO_KEYWORDS,ERRMSG_SX__NO_KEYWORDS);

  if (!(*this >> c)) 
    throw Sx::Exception(ERRNUM_SX__CANNOT_READ_STREAM,
                             ERRMSG_SX__CANNOT_READ_STREAM);
  if (!isalpha(c) && (c != '_')) {
     std::string   WordsSet;
     First()->GetAllKeywords(WordsSet);
     throw Sx::Exception(ERRNUM_SX__START_NO_KEYWORD,
                 (MSG(ERRMSG_SX__START_NO_KEYWORD),c,WordsSet.c_str()));
  }
  *this >> noskipws;
  
  while (good()) {
    if (!isalnum(c) && (c != '_')) { unget();  break; }
    Word += c;
    *this >> c;
  }

  if (Word.empty()) {
       std::string  WordsSet;
       First()->GetAllKeywords(WordsSet);     
       WordsSet.insert(0,"Oczekiwano wyst±pienia jednego ze s³ów kluczowych: ");
       throw Sx::Exception(ERRNUM_SX__NO_WORD,
                             (MSG(ERRMSG_SX__NO_WORD),WordsSet.c_str()));
  }

  for (KeyPair *Item = First()->First(); Item; Item = Item->Next()) {
    if (Item->Keyword() == Word) {Item->IncEncounterNo();  return Item->ID();}
  }
  std::string WordsSet;

  First()->GetAllKeywords(WordsSet);

  throw Sx::Exception(ERRNUM_SX__NO_KEYWORD,
             (MSG(ERRMSG_SX__NO_KEYWORD),Word.c_str(),WordsSet.c_str()));
}



void SxInterp::GetNum( int &Val ) // throw (Sx::Exception)
{
  EatWhite();
  if (*this >> Val) return;
  throw  Sx::Exception(ERRNUM_SX__FAIL_INT,ERRMSG_SX__FAIL_INT);
}


void SxInterp::GetNum( float &Val ) // throw (Sx::Exception)
{
  EatWhite();
  if (*this >> Val) return;
  throw  Sx::Exception(ERRNUM_SX__FAIL_FLOAT,ERRMSG_SX__FAIL_FLOAT);
}



void SxInterp::GetWord(std::string &Word, const char *WordAddChars )
{
  Word.clear();
  EatWhite();
  ExtString  Chars = "_";
  char c;

  if (WordAddChars) Chars += WordAddChars;

  while ((*this >> c)) {
    if (Word.empty()) {
       if (!isalpha(c) && !Chars.IsInString(c)) { unget();  return; }
    } else if (!isalnum(c) && !Chars.IsInString(c)) { unget();  return; }
    Word += c;
  }
}



void SxInterp::GetVector( float &Val1, float &Val2, float &Val3 ) 
                                               // throw (Sx::Exception)
{
  if (_Parenthesis_Left != -1) LookForChar(_Parenthesis_Left);
  GetNum(Val1);
  if (_Numbers_Separator != -1) LookForChar(_Numbers_Separator);
  GetNum(Val2);
  if (_Numbers_Separator != -1) LookForChar(_Numbers_Separator);
  GetNum(Val3);
  if (_Parenthesis_Right != -1) LookForChar(_Parenthesis_Right);
}



void SxInterp::LookForChar(char Ch) // throw (Sx::Exception)
{
  char c_curr;

  do {
     if (!( *this >> noskipws >> c_curr)) 
        throw Sx::Exception(ERRNUM_SX__UNEXP_END,
                            (MSG(ERRMSG_SX__UNEXP_END),Ch));
     if (c_curr == '\n')  ++_LineNo;
     if (c_curr == Ch) return;
  } while (isspace(c_curr));
  throw Sx::Exception(ERRNUM_SX__UNEXP_CHAR,
                      (MSG(ERRMSG_SX__UNEXP_CHAR),c_curr,Ch));
}
