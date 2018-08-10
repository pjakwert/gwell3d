#include "glmenuitem.h"

using namespace qglviewer;


// odpowiednie kolory dla rysowania bryly: t³o, normalnie, najechanej, klikniêtej
// warto¶ci pocz±tkowe
QColor GLMenuItem::_clearColor  = QColor( 0, 0, 0 );      // black
QColor GLMenuItem::_normalColor = QColor( 51, 76, 229 );  // blue
QColor GLMenuItem::_overColor   = QColor( 76, 178, 51 );  // green
QColor GLMenuItem::_clickColor  = QColor( 229, 76, 51 );  // red


GLMenuItem::GLMenuItem(QWidget *parent, ViPattePolyh const *pPaPolyh, const char *name, QGLWidget *shareWidget, WFlags f) : QGLViewer(parent,name,shareWidget,f)
{
  setMouseTracking(true);
  
  setNormalColor( Options::solidColor() );
  setClearColor( Options::backgroundColor() );
  setOverColor( Options::solidColor() );
  setClickColor( Options::solidSelectedColor() );
  
  _pPaPolyh = pPaPolyh;
  QToolTip::add(this, QString( _pPaPolyh->GetName() ));
  
  fitItemToScreen();

  _angle = 0; // k±t obrotu dla animacji
  _currentColor = _normalColor; // na pocz±tku rysujemy domy¶lnym kolorem
}



GLMenuItem::~GLMenuItem()
{
}


// metoda dopasowuje parametry widoku GL, ¿eby obiekt zajmowa³ ca³± jego powierzchniê
void GLMenuItem::fitItemToScreen()
{
// wyznaczenie objetosci bryly: min i max prostopad³o¶cianu
  ViElemePolyh elem(_pPaPolyh, "item"); // tworzenie pomocniczej bry³y elementarnej
  MatrixH3f M_1;
  elem.ComputeGlbVtx(M_1);
  Vector3f minV = elem.GlbOlnBox().Min();
  Vector3f maxV = elem.GlbOlnBox().Max();
    float minX = minV.x; float minY = minV.y; float minZ = minV.z;
    float maxX = maxV.x; float maxY = maxV.y; float maxZ = maxV.z;

  // lekkie skalowanie, zeby obiekt nie zajmowal calkowicie sceny
  float sf = 0.3;
  minX-=sf*minX; minY-=sf*minY; minZ-=sf*minZ;
  maxX+=sf*maxX; maxY+=sf*maxY; maxZ+=sf*maxZ;

  Vec vMax(maxX,maxY,maxZ);
  Vec mid((minX+maxX)/2, (minY+maxY)/2, (minZ+maxZ)/2); // ¶rodek przekatnej prostopadloscianu ograniczajacego
  float r = Vec::Vec(vMax-mid).norm(); // promieñ od ¶rodka do rogu prostopad³o¶cianu

  setSceneCenter(mid); // ¶rodek sceny w ¶rodku prostopad³o¶cianu
  setSceneRadius(r);   // promieñ

  showEntireScene();   // poka¿ scenê
}



///////////////////////////////////////////////////////
//////////////////  S T A T I C 
///////////////////////////////////////////////////////
void GLMenuItem::setNormalColor( const QColor& color )
{
  _normalColor = color;
  updateGLForAllViewers();
}


void GLMenuItem::setOverColor( const QColor& color )
{
  _overColor = color;
  updateGLForAllViewers();
}


void GLMenuItem::setClickColor( const QColor& color )
{
  _clickColor = color;
  updateGLForAllViewers();
}


void GLMenuItem::setClearColor( const QColor& color )
{
  _clearColor = color;
  updateGLForAllViewers();
}
///////////////////////////////////////////////////////
//////////////////  S T A T I C 
///////////////////////////////////////////////////////



void GLMenuItem::setPattePolyh(ViPattePolyh const *pPaPolyh)
{
  _pPaPolyh = pPaPolyh;
  QToolTip::add(this, QString( _pPaPolyh->GetName() ));
  fitItemToScreen();
}



void GLMenuItem::init()
{
  glShadeModel( Options::shadeModel() );
  qglClearColor( _clearColor );
}



// rysowanie bryly
void GLMenuItem::draw()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );  
  
  qglColor( _currentColor );
  
  glRotated(_angle, 0.0, 1.0, 0.0); // obrót o zadany k±t dla ³adnej animacji
  for (ViPattePolyh::ConFaceIter faceIter = _pPaPolyh->ConBegin_Face(); faceIter; ++faceIter)
  {
    for (ViFace::ConTriaIter triIter = faceIter->ConBegin_Tria(); triIter; ++triIter)
    {
      glBegin(GL_TRIANGLES);
       glNormal3f(faceIter->GetNormVect().x, faceIter->GetNormVect().y, faceIter->GetNormVect().z);
       glVertex3f((*triIter).Vtx0().x, (*triIter).Vtx0().y, (*triIter).Vtx0().z);
       glVertex3f((*triIter).Vtx1().x, (*triIter).Vtx1().y, (*triIter).Vtx1().z);
        //glNormal3f(faceIter->GetNormVect().x, faceIter->GetNormVect().y, faceIter->GetNormVect().z);
       glVertex3f((*triIter).Vtx2().x, (*triIter).Vtx2().y, (*triIter).Vtx2().z);
        //glNormal3f(faceIter->GetNormVect().x, faceIter->GetNormVect().y, faceIter->GetNormVect().z);
      glEnd();
    }
  }
}



// metoda wywolywana przez QGLViewer w celach animacji
void GLMenuItem::animate()
{
  _angle+=10;
  if (_angle>360) _angle=0;
}



// zdarzenia myszki: najechanie na widget, opuszczenia widgeta, klikniecie

void GLMenuItem::enterEvent(QEvent*)
{
  _currentColor = _overColor; // zmieniamy aktualny kolor rysowania na zaznaczenie
  startAnimation();
}



void GLMenuItem::leaveEvent(QEvent*)
{
  stopAnimation();
  _angle=0;
  _currentColor = _normalColor; // ponownie rysujemy normalnie
  updateGL();
}



void GLMenuItem::mousePressEvent(QMouseEvent *e)
{
  if (e->button() == Qt::LeftButton) // klikniecie lewym klawiszem
  {
    _currentColor = _clickColor;
    updateGL();
    emit objectSelected( _pPaPolyh->GetName() );
  }

  if (e->button() == Qt::RightButton)  // prawy klawisz
  {
  }
}



// odbindowanie skrotow klawiaturowych QGLViewer i dodanie wlasnych
void GLMenuItem::keyPressEvent(QKeyEvent *e)
{
  e->ignore();
}



// wylaczenie koleczka myszy
void GLMenuItem::wheelEvent(QWheelEvent *e)
{
  e->ignore();
}


// GLMenuItem pozostaje kwadratowy
void GLMenuItem::resizeEvent(QResizeEvent *e)
{
  int w = e->size().width();
  setFixedHeight( w );
  
  makeCurrent();
  QGLViewer::resizeGL( w, w );
}

