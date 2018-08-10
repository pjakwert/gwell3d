#include "glmphmenuitem.h"

using namespace qglviewer;


// odpowiednie kolory dla rysowania bryly: t³o, normalnie, najechanej, klikniêtej
// warto¶ci pocz±tkowe
QColor GLMphMenuItem::_clearColor  = QColor( 0, 0, 0 );
QColor GLMphMenuItem::_normalColor = QColor( 79, 77, 199 );
QColor GLMphMenuItem::_overColor   = QColor( 109, 200, 43 );
QColor GLMphMenuItem::_clickColor  = QColor( 200, 80, 54 );



// funkcja tworzenia obiektów dla GLMphMenuItem traktuje obiekty klasy ViElemePolyhExt
// jak obiekty ViElemePolyh; dziêki temu nie ³aduje niepotrzebnie tekstur do pamiêci i materia³u
ViNTreeNode* itemCreateFunction( const char *className )
{
  if ( strcmp( "ViElemePolyhExt", className ) == 0 ) return new ViElemePolyh;
  return 0;
}



GLMphMenuItem::GLMphMenuItem( QWidget *parent, QString mphPath, const char *name, QGLWidget *shareWidget, WFlags f ) : QGLViewer( parent, name, shareWidget, f)
{
  _mphPath = mphPath;
  _multiPolyh = 0L;
  
  if ( QFile::exists( _mphPath ) )
  {
    ViException exception;
    switch (Vi::ReadMultiPolyh( _mphPath.ascii(), *(Kernel::scene()), &_multiPolyh, exception, itemCreateFunction))
    {
      case  0 : break;
      case -1 : //StatusBar::printStatusMsg( tr("error reading mph %1.").arg(_mphPath), "GLMphMenuItem");
                _mphPath = QString::null;
                return;
      case -2 : //StatusBar::printStatusMsg( tr("error reading mph %1.").arg(_mphPath), "GLMphMenuItem");   
                _mphPath = QString::null;
                return;
      default : _mphPath = QString::null;
                return;
    } // switch
    
    _multiPolyh->ComputeHierAllGlbVtx();
    
    QToolTip::add( this, _mphPath.section('/', -1) ); // nazwa pliku
    fitItemToScreen();
    
    _angle = 0;
    _currentColor = _normalColor; // na pocz±tku rysujemy domy¶lnym kolorem
  }
  else _mphPath = QString::null;
}




// metoda dopasowuje parametry widoku GL, ¿eby obiekt zajmowa³ ca³± jego powierzchniê
void GLMphMenuItem::fitItemToScreen()
{
  if ( _mphPath == QString::null ) return;
  
  // wyznaczenie objetosci bryly: min i max prostopad³o¶cianu
  Vector3f minV = _multiPolyh->GlbOlnBox().Min();
  Vector3f maxV = _multiPolyh->GlbOlnBox().Max();
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



void GLMphMenuItem::setMultiPolyh( const QString& path )
{
  _mphPath = path;
  //if ( _multiPolyh != 0L ) delete _multiPolyh;
  
  if ( QFile::exists( _mphPath ) )
  {
    ViException exception;
    switch (Vi::ReadMultiPolyh( _mphPath.ascii(), *(Kernel::scene()), &_multiPolyh, exception, itemCreateFunction))
    {
      case  0 : break;
      case -1 : {
                  //StatusBar::printStatusMsg( tr("error reading mph %1.").arg(_mphPath), "GLMphMenuItem");
                  _mphPath = QString::null;
                } return;
      case -2 : {
                  //StatusBar::printStatusMsg( tr("error reading mph %1.").arg(_mphPath), "GLMphMenuItem");
                  _mphPath = QString::null;
                } return;
      default : {
                  _mphPath = QString::null;
                  return;
                }
    } // switch
    
    if ( !_multiPolyh )
    {
      _mphPath = QString::null;
      return;
    }
    
    _multiPolyh->ComputeHierAllGlbVtx();
    
    QToolTip::add( this, _mphPath.section('/', -1) ); // nazwa pliku
    fitItemToScreen();
    
    _angle = 0;
    _currentColor = _normalColor; // na pocz±tku rysujemy domy¶lnym kolorem
    updateGL();
  }
   else _mphPath = QString::null;
}




///////////////////////////////////////////////////////
//////////////////  S T A T I C 
///////////////////////////////////////////////////////
void GLMphMenuItem::setNormalColor( const QColor& color )
{
  _normalColor = color;
  updateGLForAllViewers();
}


void GLMphMenuItem::setOverColor( const QColor& color )
{
  _overColor = color;
  updateGLForAllViewers();
}


void GLMphMenuItem::setClickColor( const QColor& color )
{
  _clickColor = color;
  updateGLForAllViewers();
}


void GLMphMenuItem::setClearColor( const QColor& color )
{
  _clearColor = color;
  updateGLForAllViewers();
}
///////////////////////////////////////////////////////
//////////////////  S T A T I C 
///////////////////////////////////////////////////////




void GLMphMenuItem::init()
{
  glShadeModel( Options::shadeModel() );
  qglClearColor( _clearColor );
}



// rysowanie bryly
void GLMphMenuItem::draw()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );  
  qglColor( _currentColor );
  
  if ( _mphPath == QString::null ) return;
  
  glRotated(_angle, 0.0, 1.0, 0.0); // obrót o zadany k±t dla ³adnej animacji
  
  for (ViMultiPolyh::ConElemePolyhIter iter = _multiPolyh->ConBegin_ElemePolyh(); iter; ++iter)
  { 
     glBegin( GL_TRIANGLES );
      for ( ViElemePolyhExt::ConFaceIter faceIter = iter->ConBegin_GlbFace(); faceIter; ++faceIter )
      { // iteracja scianek
        for ( ViElemePolyhFace::ConTriaIter triIter = faceIter->ConBegin_GlbTria(); triIter; ++triIter )
        { // iteracja trojkatow
          glNormal3f(faceIter->GetNormVect().x, faceIter->GetNormVect().y, faceIter->GetNormVect().z);
          glVertex3f((*triIter).Vtx0().x, (*triIter).Vtx0().y, (*triIter).Vtx0().z);
          glVertex3f((*triIter).Vtx1().x, (*triIter).Vtx1().y, (*triIter).Vtx1().z);
          glVertex3f((*triIter).Vtx2().x, (*triIter).Vtx2().y, (*triIter).Vtx2().z);
        } // trojkaty
      } // scianki
    glEnd();
  }
}



// metoda wywolywana przez QGLViewer w celach animacji
void GLMphMenuItem::animate()
{
  _angle+=10;
  if (_angle>360) _angle=0;
}



// zdarzenia myszki: najechanie na widget, opuszczenia widgeta, klikniecie

void GLMphMenuItem::enterEvent(QEvent*)
{
  _currentColor = _overColor; // zmieniamy aktualny kolor rysowania na zaznaczenie
  startAnimation();
}



void GLMphMenuItem::leaveEvent(QEvent*)
{
  stopAnimation();
  _angle = 0;
  _currentColor = _normalColor; // ponownie rysujemy normalnie
  updateGL();
}



void GLMphMenuItem::mousePressEvent(QMouseEvent *e)
{
  if (e->button() == Qt::LeftButton) // klikniecie lewym klawiszem
  {
    _currentColor = _clickColor;
    updateGL();
    emit mphSelected( _mphPath.ascii() );
  }
  else e->ignore();
}



// odbindowanie skrotow klawiaturowych QGLViewer i dodanie wlasnych
void GLMphMenuItem::keyPressEvent(QKeyEvent *e)
{
  e->ignore();
}



// wylaczenie koleczka myszy
void GLMphMenuItem::wheelEvent(QWheelEvent *e)
{
  e->ignore();
}


// GLMenuItem pozostaje kwadratowy
void GLMphMenuItem::resizeEvent(QResizeEvent *e)
{
  int w = e->size().width();
  setFixedHeight( w );
  
  makeCurrent();
  QGLViewer::resizeGL( w, w );
}

