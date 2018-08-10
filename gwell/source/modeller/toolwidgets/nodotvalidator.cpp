////////////////////////////////////////////////////////////////////////////
///
///  class: NoDotValidator (.cpp)
///
///  validator dla QLineEdit do wpisywania nazwy obiektu
///  - nie dopuszcza do wyst�powania: kropek, spacji, nawias�w okr�g�ych
///  - sprawdza, czy wpisana nazwa nie zosta�a wcze�niej nadana innej bryle
///
////////////////////////////////////////////////////////////////////////////

#include "nodotvalidator.h"


NoDotValidator::NoDotValidator(QObject *parent, const char *name) : QValidator(parent,name)
{
}


NoDotValidator::~NoDotValidator()
{
}



void NoDotValidator::fixup( QString &input ) const
{
  input.replace( QChar('.'), "_" );
  input.replace( QChar(' '), "_" );
  input.replace( QChar('['), "_" );
  input.replace( QChar(']'), "_" );
  input.replace( QChar('('), "_" );
  input.replace( QChar(')'), "_" );
  input.replace( QChar('\\'), "_" );
  input.replace( QChar('\"'), "_" );
}



// metoda znajduje duplikat podanej nazwy,
// je�eli taka nazwa ju� wyst�puje zwraca TRUE, je�eli nie - FALSE
bool NoDotValidator::findName( QString &input ) const
{
   for ( ViNTreeNode::ConPolyhIter iter = (CellFrame::multiPolyh())->ConBegin_PolyhHierList(); iter; ++iter)
   {
      QString s( iter->GetName() );
      if ( input == s ) return true;
   }
   return false;
}



QValidator::State NoDotValidator::validate( QString &input, int &pos ) const
{
  QRegExp rxp = QRegExp( "[., ()`~!@#$%^&*<>{}:;'-+=?/|]", false, false );
  if ( input.contains( rxp ) ||
       input.contains( ']' ) ||
       input.contains( '[' ) ||
       input.contains( '\"' ) ||
       input.contains( '\\' ) ||
       findName(input) ) return Invalid; else return Acceptable;
}

