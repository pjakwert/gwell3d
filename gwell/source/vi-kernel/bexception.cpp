#ifdef __GNUG__
# pragma implementation
#endif

#include <iostream>
#include "bexception.hh"

using namespace std;

namespace Ba {

  StrPrintf  Exception::_TmpMsg;
  //  std::string Exception::_ErrorMsg = "";

  Exception::Exception(int Err, const char *Msg, int AuxID) 
        { 
	  //	  std::cerr << "WYJATEK" << std::endl;
          _ErrorMsg = (Msg ? Msg : "");  _ErrorID = Err;  _ErrAuxID = AuxID; 
	  //	  std::cerr << "Koniec" << endl;
        }


}
