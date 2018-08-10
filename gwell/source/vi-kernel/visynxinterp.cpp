#ifdef __GNUG__
#pragma implementation
#endif


#include "visynxinterp.hh"
#include "viscene.hh"


const ViScene        *ViSynxInterp::_CurrScene = 0L;
const ViPatteLibList *ViSynxInterp::_PatteLibList = 0L;
ViScenePolyhList  ViSynxInterp::_PolyhList;


void ViSynxInterp::SetScene(const ViScene &Scene) 
{ 
  _CurrScene = &Scene; 
  SetPatteLibList(&Scene.GetList_PatteLibs());
}
