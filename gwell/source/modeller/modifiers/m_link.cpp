//////////////////////////////////////////////////////////////////
///
///  class: LinkModifier (.cpp)
///
///  klasa modyfikatora laczenia obiektow
///
//////////////////////////////////////////////////////////////////

#include "m_link.h"

#define HasDescendants() IsDescendant()


LinkModifier::LinkModifier(QCursor cursor) : MModifier(cursor) {}


LinkModifier::~LinkModifier() {}


MModifier::ModifierType LinkModifier::type()
{
  return M_LINK;
}




// wszystkie elementy listy selectedList staja sie potomkami ostatniego elementu tej listy
void LinkModifier::mousePressEvent(QMouseEvent *e, qglviewer::Camera *camera, QPtrList<ViNTreeNode> *selectedList)
{
  ViNTreeNode *dest = selectedList->last();

  selectedList->removeLast();

  bool found;
  QString src;
  QString dst = dest->NodeName();
  
  // wszystkie zaznaczone obiekty dopinamy do ostatniego na liscie (nowego ich rodzica)
  for (ViNTreeNode *_selected = selectedList->first(); _selected; _selected = selectedList->next())
  {
   // trzeba sprawdzic czy nie bedzie rekursji - czy podpinany obiekt nie jest juz rodzicem dest-a
   // iteruj potomkow _selected-a i szukaj tam dest-a, jezeli jest - NIE PODPINAJ
   found = false;

   if (!_selected->HasDescendants()) found = false; // _selected nie ma potomkow, wiec mozna go podpiac bez obaw
   else // posiada potomkow - sprawdzamy
   {
     for (ViNTreeNode::ConPolyhIter iter = _selected->ConBegin_PolyhHierList(); iter; ++iter)
     {
      if (iter == dest) { // dest jest potomkiem selected-a
                          found = true;
                          src = _selected->NodeName();
                          break;
                        }
     }
   }

   if (!found) // jezeli nie znalazl - wszystko OK - dodaj
   {
      // przeksztalc macierze zeby transformacja podpinanego obiektu nie ulegla zmianie
      // _selected->SetMtx2ParentCoord(result);

      // znalezc taka Mtx2ParentCoord zeby Mtx2RootCoord nie ulegla zmianie
      
       /*
       MatrixH3f Mx;                                                            // obecna macierz 2glb
       MatrixH3f m2scene;                                                       // do sceny
       MatrixH3f m2root;                                                        // do zlozonego
       MatrixH3f m2parent;                                                      // do rodzica
       MatrixH3f m2indiv = ((ViElemePolyhExt*) _selected)->Mtx2IndivCoord();    // transformacja ukl. wsp.
       MatrixH3f m2elem  = ((ViElemePolyhExt*) _selected)->Mtx2ElemeCoord();    // wzorzec -> bryla elem.

       _selected->GetMtxRoot2GlbCoord(m2scene);
       */
      
      
      _selected->MoveBranchTo(dest); 
   }
   else // jezeli znalazl - pokaz informacje
   {
     QMessageBox::critical(
                            qApp->mainWidget(),
                            tr("Link object to another"),
                            tr("Unable to link object \"%1\" to object \"%2\".\n"
                            "\"%3\" is already a parent of \"%4\".").arg(src).arg(dst).arg(src).arg(dst)
                          );
   }
  }

  selectedList->clear();
  selectedList->append(dest); // na liscie pozostaje tylko obiekt docelowy
}




void LinkModifier::mouseMoveEvent(QMouseEvent *e, qglviewer::Camera *camera, QString &info)
{
}





void LinkModifier::mouseReleaseEvent(QMouseEvent *e)
{
}

