#include "agoraViewer.h"
#include "agoraWindow.h"
#include <fstream>
#include <math.h>
#include <qmessagebox.h>
#include <qimage.h>
#include <qfile.h>
#include <qfileinfo.h>
#include <qfiledialog.h>
#include <qaction.h>

using namespace std;
using namespace qglviewer;

AgoraViewer::AgoraViewer(QWidget* parent, const char* name)
  : QGLViewer(parent, name), computerIsBlack_(true), selectedPiece_(-1),
    playerIsComputer_(true), displayPossibleDestination_(true), animatePlays_(true), textures_(true),
    fileName("savedGame.ago"), undoIndex_(0), maxUndoIndex_(0)
{
  // Stored once and for all
  normal[0] = Vec(-1.0,  0.0, 0.0);
  normal[1] = Vec( 0.0,  1.0, 0.0);
  normal[2] = Vec( 1.0,  0.0, 0.0);
  normal[3] = Vec( 0.0, -1.0, 0.0);
  normal[4] = normal[0];

  levelIsEasy();

  QObject::connect(&kfi_[0], SIGNAL(interpolated()), this, SLOT(updateGL()));
  QObject::connect(&kfi_[0], SIGNAL(finished()), this, SLOT(simplePlay()));
}


// I n i t i a l i z a t i o n   f u n c t i o n s //

void AgoraViewer::init()
{
  initViewer();
  initSpotLight();
  initCamera();
  initGame();

  setMouseBinding(Qt::RightButton, CAMERA, ROTATE);
  setMouseBinding(Qt::LeftButton, SELECT);
}

void AgoraViewer::initSpotLight()
{
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_LIGHT1);
  glLoadIdentity();

  // Light default parameters
  const GLfloat light_ambient[4]  = {2.0, 2.0, 2.0, 1.0};
  const GLfloat light_specular[4] = {2.0, 2.0, 2.0, 1.0};
  const GLfloat light_diffuse[4]  = {2.0, 2.0, 2.0, 1.0};

  glLightf( GL_LIGHT1, GL_SPOT_EXPONENT,  2.0);
  glLightf( GL_LIGHT1, GL_SPOT_CUTOFF,    60.0);
  glLightf( GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.1);
  glLightf( GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.3);
  glLightf( GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.3);
  glLightfv(GL_LIGHT1, GL_AMBIENT,  light_ambient);
  glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse);
}

class BoardConstraint : public Constraint
{
public:
  virtual void constrainRotation(Quaternion& q, Frame * const fr)
  {
    const Vec up = fr->transformOf(Vec(0.0, 0.0, 1.0));
    Vec axis = q.axis();
    float angle = 2.0*acos(q[3]);
    if (fabs(axis*up) > fabs(axis.x))
      axis.projectOnAxis(up);
    else
      {
	angle = (axis.x > 0.0) ? angle : -angle;
	axis.setValue(fabs(axis.x), 0.0, 0.0);
	const float currentAngle = asin(fr->inverseTransformOf(Vec(0.0, 0.0, -1.0)).z);
	if (currentAngle + angle > -0.2)
	  angle = -0.2 - currentAngle; // Not too low
	if (currentAngle + angle < -M_PI/2.0)
	  angle = -M_PI/2.0 - currentAngle; // Do not pass on the other side
      }
    q = Quaternion(axis, angle);
  }
};

void AgoraViewer::initCamera()
{
  camera()->setUpVector(Vec(0.0, 0.0, 1.0));
  camera()->setPosition(Vec(-6.0, -6.0, 4.0));
  camera()->lookAt(sceneCenter());
  setSceneRadius(3.5);
  showEntireScene();
  
  // Limit camera rotation motion
  camera()->frame()->setConstraint(new BoardConstraint());
}

void AgoraViewer::initGame()
{
  agora.reinit();
  updatePiecePositions();
  blackPlay_ = false;
  gameIsOver_ = false;
}

void AgoraViewer::initViewer()
{
  int count = 0;
  for (int i=0; i<6; ++i)
    for (int j=0; j<6; ++j)
      {
	float height;
	if ((i==0) || (j==0) || (i==5) || (j==5))
	  height = 6.0 * pieceHeight;
	else
	  if ((i==1) || (j==1) || (i==4) || (j==4))
	    height = 3.0 * pieceHeight;
	  else
	    height = pieceHeight;
	
	casePosition[count++] = Vec(i-2.5, j-2.5, height);
      }

  glBlendFunc(GL_SRC_ALPHA,  GL_ONE_MINUS_SRC_ALPHA);
  // Enable GL textures
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glEnable( GL_TEXTURE_2D );

  // Nice texture coordinate interpolation
  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

  const QString texFileName("wood.png");
  QImage img(texFileName);
  
  if (img.isNull())
    {
      cerr << "Unable to load wood texture from " << texFileName << endl;
      exit(1);
    }

  // 1E-3 needed. Just try with width=128 and see !
  if ( ( img.width()  != 1<<(int)(1+log(img.width() -1+1E-3) / log(2.0)) ) ||
       ( img.height() != 1<<(int)(1+log(img.height()-1+1E-3) / log(2.0))) )
    {
      cerr << "Texture dimensions are not powers of 2 in " << texFileName << endl;
      exit(1);
    }
  
  QImage glImg = QGLWidget::convertToGLFormat(img);  // flipped 32bit RGBA

  // Bind the img texture...
  glTexImage2D(GL_TEXTURE_2D, 0, 4, glImg.width(), glImg.height(), 0,
	       GL_RGBA, GL_UNSIGNED_BYTE, glImg.bits());
}




// D r a w i n g  f u n c t i o n s //

void AgoraViewer::draw()
{
  glColor3f(0.7, 0.7, 0.7);
  glDisable(GL_LIGHTING);
  if (blackPlay_)
    drawText(20, 20, "Blacks play");
  else
    drawText(20, 20, "Whites play");
  glEnable(GL_LIGHTING);

  drawAgora();
  drawAllPieces();
  if (selectedPiece_ >= 0)
    {
      highlightSelectedPiece();
      if (displayPossibleDestination_)
	drawPossibleDestinations();
    }
}

void AgoraViewer::drawAgora() const
{
  static const GLfloat pos[4] = {0.0, 0.0, 3.0, 1.0};
  const GLfloat spot_dir[3]   = {0.0, 0.0, -1.0};
  glLightfv(GL_LIGHT1, GL_POSITION, pos);
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_dir);

  glColor3f(0.5, 0.5, 0.5);
  if (textures_)
    glEnable(GL_TEXTURE_2D);
  else
    glDisable(GL_TEXTURE_2D);
  
  drawBorder(6.0, 6.0 * pieceHeight);
  drawBorder(4.0, 6.0 * pieceHeight, false, 3.0 * pieceHeight);
  drawBorder(2.0, 3.0 * pieceHeight, false, pieceHeight);

  drawRing(6.0, 6.0 * pieceHeight);
  drawRing(4.0, 3.0 * pieceHeight);
  drawRing(2.0, pieceHeight);
  drawFace(6.0, 0.0, false);
  glDisable(GL_TEXTURE_2D);

  glDisable(GL_LIGHTING);
  
  glLineWidth(3.0);
  glColor3f(0.4, 0.4, 0.4);
  drawBorderLines(6.0, 6.0 * pieceHeight);
  drawBorderLines(4.0, 6.0 * pieceHeight, false, 3.0 * pieceHeight);
  drawBorderLines(2.0, 3.0 * pieceHeight, false, pieceHeight);

  drawLeveLines(4.0, 5.0 * pieceHeight);
  drawLeveLines(4.0, 4.0 * pieceHeight);
  drawLeveLines(2.0, 2.0 * pieceHeight);
  
  glLineWidth(4.0);
  glColor3f(0.1, 0.1, 0.1);
  drawSeparatingBars(6.0, 6.0 * pieceHeight);
  drawSeparatingBars(4.0, 3.0 * pieceHeight);
  drawSeparatingBars(2.0, pieceHeight);

  glEnable(GL_LIGHTING);
}  

void AgoraViewer::drawPiece() const
{
  drawBorder(pieceSize, pieceHeight);
  drawFace(pieceSize, pieceHeight, true);
  drawFace(pieceSize, 0.0, false);

  glLineWidth(2.0);
  glDisable(GL_LIGHTING);
  glColor3f(0.4, 0.4, 0.4);
  drawBorderLines(pieceSize, pieceHeight);
  glEnable(GL_LIGHTING);
}

void AgoraViewer::highlightSelectedPiece() const
{
  glEnable(GL_BLEND);
  const float s = 1.1 * piece_[selectedPiece_].scale;
  glColor4f(0.3, 0.9, 0.3, 0.3);
  glPushMatrix();
  glMultMatrixd(piece_[selectedPiece_].frame.matrix());
  glScalef(s, s, s);
  drawPiece();
  glPopMatrix();  
  glDisable(GL_BLEND);
}

void AgoraViewer::drawAllPieces(bool select) const
{
  for (int i=0; i<16; ++i)
    {
      glPushMatrix();
      glMultMatrixd(piece_[i].frame.matrix());
      glScalef(piece_[i].scale, piece_[i].scale, 1.0);
      
      if (piece_[i].isBlack)
	glColor3f(0.2, 0.2, 0.2);
      else
	glColor3f(0.9, 0.9, 0.9);

      if (select)
	glPushName(i);

      drawPiece();
      
      if (select)
	glPopName();
      
      glPopMatrix();
    }
}

void AgoraViewer::drawPossibleDestinations(bool select) const
{
  glEnable(GL_BLEND);
  glColor4f(0.3, 0.3, 0.9, 0.5);
  for (Possibles::const_iterator it=possibleDest_.begin(), end=possibleDest_.end(); it != end; ++it)
    {
      const int dest = (*it).arrivee();

      glPushMatrix();
      glTranslatef(casePosition[dest].x, casePosition[dest].y, casePosition[dest].z + 0.01);

      if (select)
	glPushName(dest);

      drawFace(0.9, 0.0, true);

      if (select)
	for (int i=0; i<16; ++i)
	  if (piece_[i].square == dest)
	    {
	      glPushMatrix();
	      glTranslatef(0.0, 0.0, piece_[i].level * pieceHeight);
	      drawPiece();
	      glPopMatrix();
	    }

      if (select)
	glPopName();
      
      glPopMatrix();
    }
  glDisable(GL_BLEND);
}

void AgoraViewer::drawBorder(float width, float height, bool out, float heightMin) const
{
  const Vec up(0.0, 0.0, 1.0);
  const float coef = sqrt(2.0) / 2.0;
  
  for (int i=0; i<4; ++i)
    {
      if (out)
	glNormal3fv(normal[i].address());
      else
	glNormal3fv((-normal[i]).address());
      
      glBegin(GL_QUADS);
      glTexCoord2f(-width*coef, heightMin);
      glVertex3fv((width/2.0*(normal[i] - normal[i+1]) + heightMin*up).address());
      glTexCoord2f(width*coef, heightMin);
      glVertex3fv((width/2.0*(normal[i] + normal[i+1]) + heightMin*up).address());
      glTexCoord2f(width*coef, height);
      glVertex3fv((width/2.0*(normal[i] + normal[i+1]) + height*up).address());
      glTexCoord2f(-width*coef,height);
      glVertex3fv((width/2.0*(normal[i] - normal[i+1]) + height*up).address());
      glEnd();
    }
}

void AgoraViewer::drawBorderLines(float width, float height, bool out, float heightMin) const
{
  const Vec up(0.0, 0.0, 1.0);

  // Avoid aliassing on inside agora
  if (!out)
    {
      heightMin += 0.01;
      width     -= 0.01;
    }
  
  for (int i=0; i<4; ++i)
    {
      glBegin(GL_LINE_LOOP);
      glVertex3fv((width/2.0*(normal[i] - normal[i+1]) + heightMin*up).address());
      glVertex3fv((width/2.0*(normal[i] + normal[i+1]) + heightMin*up).address());
      glVertex3fv((width/2.0*(normal[i] + normal[i+1]) + height*up).address());
      glVertex3fv((width/2.0*(normal[i] - normal[i+1]) + height*up).address());
      glEnd();
    }
}

void AgoraViewer::drawRing(float width, float height, float thickness) const
{
  const Vec up(0.0, 0.0, 1.0);
  const float dist1 = width/2.0;
  const float dist2 = width/2.0-thickness;
  
  glNormal3fv(up.address());
  
  for (int i=0; i<4; ++i)
    {
      const Vec dir1 = normal[i] - normal[i+1];
      const Vec dir2 = normal[i] + normal[i+1];

      glBegin(GL_QUADS);
      glTexCoord2f(dist1*dir1.x, dist1*dir1.y);
      glVertex3fv((dist1*dir1 + height*up).address());
      glTexCoord2f(dist1*dir2.x, dist1*dir2.y);
      glVertex3fv((dist1*dir2 + height*up).address());
      glTexCoord2f(dist2*dir2.x, dist2*dir2.y);
      glVertex3fv((dist2*dir2 + height*up).address());
      glTexCoord2f(dist2*dir1.x, dist2*dir1.y);
      glVertex3fv((dist2*dir1 + height*up).address());
      glEnd();
    }
}

void AgoraViewer::drawSeparatingBars(float width, float height, float thickness) const
{
  const Vec up(0.0, 0.0, 1.0);

  height += 0.01;
  
  for (int i=0; i<4; ++i)
    {
      for (int j=1; j<width-0.9; ++j)
	{
	  glBegin(GL_LINES);
	  glVertex3fv((width/2.0*normal[i] + (j*thickness-width/2.0)*normal[i+1] + height*up).address());
	  glVertex3fv(((width/2.0-thickness)*normal[i] + (j-width/2.0)*normal[i+1] + height*up).address());
	  glEnd();
	}
    }
}

void AgoraViewer::drawLeveLines(float width, float height) const
{
  const Vec up(0.0, 0.0, 1.0);
  width -= 0.01;

  glBegin(GL_LINE_LOOP);
  
  for (int i=0; i<4; ++i)
    glVertex3fv((width/2.0*(normal[i] + normal[i+1]) + height*up).address());

  glEnd();
}

void AgoraViewer::drawFace(float width, float height, bool up) const
{
  if (up)
    glNormal3f(0.0, 0.0, 1.0);
  else
    glNormal3f(0.0, 0.0, -1.0);
  
  glBegin(GL_QUADS);
  glVertex3f(-width/2.0, -width/2.0, height);
  glVertex3f(-width/2.0,  width/2.0, height);
  glVertex3f( width/2.0,  width/2.0, height);
  glVertex3f( width/2.0, -width/2.0, height);
  glEnd();
}

void AgoraViewer::animatePlay()
{
  float start = 0.0;
  float end = 0.8;
  int hpops = higherPieceOnPosition(play_.depart());
  int hpope = higherPieceOnPosition(play_.arrivee());

  if (hpops < 0)
    cerr << "Internal error" << endl;

  int nbKfi = 0;
  if (play_.dessus())
    {
      for (int i=0; i<16; ++i)
	if ((piece_[i].square == play_.arrivee()) && (piece_[i].isBlack != piece_[hpops].isBlack) && (piece_[hpops].isBlack != piece_[hpope].isBlack))
	  {
	    // piece_[i].isBlack = piece_[hpops].isBlack;
	    nbKfi++;
	    kfi_[nbKfi].deletePath();
	    kfi_[nbKfi].setFrame(&piece_[i].frame);
	    kfi_[nbKfi].addKeyFrame(piece_[i].frame, 0.0);
	    Frame midFrame(piece_[i].frame.position()+Vec(0.0, 0.0, 4*pieceHeight*(piece_[i].level+2)),
			   Quaternion(Vec(1.0, 0.0, 0.0), 2.0));
	    kfi_[nbKfi].addKeyFrame(midFrame, 0.3);
	    Frame endFrame(piece_[i].frame.position()+Vec(0.0, 0.0, pieceHeight),
			   Quaternion(Vec(1.0, 0.0, 0.0), M_PI));
	    kfi_[nbKfi].addKeyFrame(endFrame, 0.6);
	    start = 0.6;
	  }
    }
  else
    {
      for (int i=0; i<16; ++i)
	if (piece_[i].square == play_.arrivee())
	  {
	    nbKfi++;
	    kfi_[nbKfi].deletePath();
	    kfi_[nbKfi].setFrame(&piece_[i].frame);
	    kfi_[nbKfi].addKeyFrame(piece_[i].frame, 0.0);
	    Frame midFrame, endFrame;
	    if ((agora.ArriveeRevolution(play_)) && (piece_[i].isBlack != piece_[hpops].isBlack))
	      {
		midFrame = Frame(piece_[i].frame.position()+Vec(0.0, 0.0, 3.0*pieceHeight*(piece_[i].level+2)),
				 Quaternion(Vec(1.0, 0.0, 0.0), 2.0));
		endFrame = Frame(piece_[i].frame.position()+Vec(0.0, 0.0, 2.0*pieceHeight),
				 Quaternion(Vec(1.0, 0.0, 0.0), M_PI));

		// piece_[i].isBlack = piece_[hpops].isBlack;
	      }
	    else
	      {
		midFrame.setPosition(piece_[i].frame.position()+Vec(0.0, 0.0, 3.0*pieceHeight*(piece_[i].level+2)));
		endFrame.setPosition(piece_[i].frame.position()+Vec(0.0, 0.0, pieceHeight));
	      }
	    kfi_[nbKfi].addKeyFrame(midFrame, 0.4);
	    kfi_[nbKfi].addKeyFrame(endFrame, 1.0);
	    end = 1.0;
	  }
    }

  // Revolution on starting case
  if (agora.DepartRevolution(play_))
    for (int i=0; i<16; ++i)
      if ((piece_[i].square == play_.depart()) && (i!=hpops) && (piece_[i].isBlack == piece_[hpops].isBlack))
	{
	  nbKfi++;
	  kfi_[nbKfi].deletePath();
	  kfi_[nbKfi].setFrame(&piece_[i].frame);
	  kfi_[nbKfi].addKeyFrame(piece_[i].frame, 0.0);
	  kfi_[nbKfi].addKeyFrame(piece_[i].frame, 0.6);
	  Frame midFrame(piece_[i].frame.position()+Vec(0.0, 0.0, 3.0*pieceHeight*(piece_[i].level+2)),
			 Quaternion(Vec(1.0, 0.0, 0.0), 2.0));
	  Frame endFrame(piece_[i].frame.position()+Vec(0.0, 0.0, pieceHeight),
			 Quaternion(Vec(1.0, 0.0, 0.0), M_PI));

	  // piece_[i].isBlack = !piece_[hpops].isBlack;
	  kfi_[nbKfi].addKeyFrame(midFrame, 0.9);
	  kfi_[nbKfi].addKeyFrame(endFrame, 1.5);
	  end = 1.5;
	}

  // Selected piece
  kfi_[0].deletePath();
  kfi_[0].setFrame(&piece_[hpops].frame);
  Frame arrival;
  if ((hpope >= 0) && (play_.dessus()))
    arrival.setPosition(piece_[hpope].frame.position() + Vec(0.0, 0.0, pieceHeight));
  else
    arrival.setPosition(casePosition[play_.arrivee()]);

  Vec mid(0.5 * (piece_[hpops].frame.position() + arrival.position()));
  mid.z = max(piece_[hpops].frame.position().z, arrival.position().z) + 2.0 * pieceHeight;
  const Frame intermediate(mid, Quaternion());

  kfi_[0].addKeyFrame(piece_[higherPieceOnPosition(play_.depart())].frame, 0.0);
  kfi_[0].addKeyFrame(piece_[higherPieceOnPosition(play_.depart())].frame, start);
  kfi_[0].addKeyFrame(intermediate, start+0.3);
  kfi_[0].addKeyFrame(arrival, start+0.8);
  kfi_[0].addKeyFrame(arrival, start+end);

  for (int i=1; i<=nbKfi; ++i)
    kfi_[i].startInterpolation();
  kfi_[0].startInterpolation();
}

int AgoraViewer::higherPieceOnPosition(Position pos) const 
{
  float levelMax = -1.0;
  int res = -1;
  
  for (int i=0; i<16; ++i)
    if ((piece_[i].square == pos) && (piece_[i].level > levelMax))
      {
	res = i;
	levelMax = piece_[i].level;
      }
  return res;
}



// G a m e   I n t e r f a c e  //

void AgoraViewer::play()
{
  if (animatePlays_)
    animatePlay();
  else
    simplePlay();
}

void AgoraViewer::deselect()
{
  selectedPiece_ = -1;
  possibleDest_.clear();
}

void AgoraViewer::simplePlay()
{
  deselect();
  updateUndoHistory(true);
  agora.jouer(play_);
  updateUndoHistory(false);
  updatePiecePositions();
  blackPlay_ = !blackPlay_;
  updateGL();

  gameIsOver_ = agora.gameIsOver();
  if (gameIsOver_) 
  {
      if (agora.gameIsOver(BLACK)) 
          QMessageBox::information(this, "Whites won !", "The whites won !");
      else
          QMessageBox::information(this, "Blacks won !", "The blacks won !");
  } else if ((playerIsComputer_) && (computerIsBlack_==blackPlay_))
  {
      play_ = agora.Suggest(play_, blackPlay_, gameLevel_.computerMaxReflexionTime_, gameLevel_.computerMaxDepth_);
      play();
  }
}

void AgoraViewer::reactToSelection(int selected, bool onTop)
{
  if (selectedPiece_ >= 0)
    {
      if (selected >= 0)
	{
	  bool playOnTopIsValid = false;
	  bool playPrisonnerIsValid = false;
	  Play playOnTop, playPrisonner;
	  for (Possibles::const_iterator it=possibleDest_.begin(), end=possibleDest_.end(); it != end; ++it)
	    if (((*it).depart() == piece_[selectedPiece_].square) && ((int)((*it).arrivee()) == selected))
	      if ((*it).dessus())
		{
		  playOnTopIsValid = true;
		  playOnTop = (*it);
		}
	      else
		{
		  playPrisonnerIsValid = true;
		  playPrisonner = (*it);
		}

	  if (playOnTopIsValid)
	    if (playPrisonnerIsValid)
	      play_ = (onTop) ? playOnTop : playPrisonner;
	    else
	      play_ = playOnTop;
	  else
	    if (playPrisonnerIsValid)
	      play_ = playPrisonner;
	    else
	      cerr << "Internal error : invalid play in reactToSelection." << endl;
	  
	  play();
	}
      else
	deselect();
    }
  else
    // New piece selection. Color must correspond to current player
    if ((selected >= 0) && (piece_[selected].isBlack == blackPlay_))
      {
	// Search for the piece at highest level on this heap
	selectedPiece_ = higherPieceOnPosition(piece_[selected].square);
        agora.CoupsVoisins( possibleDest_, piece_[selectedPiece_].square );
      }
}

void AgoraViewer::select(const QMouseEvent* e)
{
  if (gameIsOver_)
    return;
  
  // Make openGL context current
  makeCurrent();
  
  const int SENSITIVITY = 4;
  const int NB_HITS_MAX = 50;
  
  // Prepare the selection mode
  static GLuint hits[NB_HITS_MAX];
  
  glSelectBuffer(NB_HITS_MAX, hits);
  glRenderMode(GL_SELECT);
  glInitNames();

  // Loads the matrices
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT,viewport);
  gluPickMatrix(static_cast<GLdouble>(e->x()), static_cast<GLdouble>(viewport[3] - e->y()), SENSITIVITY, SENSITIVITY, viewport);

  // loadProjectionMatrix() first resets the GL_PROJECTION matrix with a glLoadIdentity.
  // Give false as a parameter in order to prevent this and to combine the matrices.
  camera()->loadProjectionMatrix(false);

  camera()->loadModelViewMatrix();
  
  // Render scene with objects ids
  if (selectedPiece_ >= 0)
    drawPossibleDestinations(true);
  else
    drawAllPieces(true);
  glFlush();

  // Get the results
  GLint nb_hits = glRenderMode(GL_RENDER);
  
  // Interpret results
  unsigned int zMin = UINT_MAX;
  int id = -1;
  for (int i=0; i<nb_hits; ++i)
    if (hits[i*4+1] < zMin)
      {
	zMin = hits[i*4+1];
	id = hits[i*4+3];
      }

  reactToSelection(id, e->state() == Qt::NoButton);
}

void AgoraViewer::updatePiecePositions()
{
  int nb = 0;
  for (int i=0; i<36; ++i)
    {
      Pile p = agora[i];
      bool topIsBlack = agora.couleur(p);
      for (int j=0; j<agora.taille(p); ++j)
	{
	  if (j == agora.uns(p))
	    topIsBlack = !topIsBlack;
	  
	  piece_[nb].square = i;
	  piece_[nb].isBlack = topIsBlack;
	  piece_[nb].level = agora.taille(p)-1-j;
	  piece_[nb].frame.setPosition(casePosition[i] + Vec(0.0, 0.0, pieceHeight * piece_[nb].level));
	  piece_[nb].frame.setOrientation(Quaternion());
	  piece_[nb].scale = 1.0 - 0.1*(agora.taille(p)-j-1)/(float)agora.taille(p);
	  nb++;
	}
    }
  if (nb > 16)
    cerr << "More than 16 pieces in the Agora !!!" << endl;
}




// F i l e  m e n u   f u n c t i o n s
void AgoraViewer::load()
{
  fileName = QFileDialog::getOpenFileName("", "Agora files (*.ago);;All files (*)", this);
  
  // In case of Cancel
  if (fileName.isEmpty())
    return;

  std::ifstream f(fileName.latin1());
  f >> agora;
  f >> undoIndex_ >> maxUndoIndex_;
  history_.clear();
  for (unsigned int i=0; i<maxUndoIndex_; ++i)
    {
      Undo u;
      f >> u.pos1 >> u.pos2 >> u.before1 >> u.before2 >> u.after1 >> u.after2;
      history_.push_back(u);
    }
  f.close();

  blackPlay_ = undoIndex_%2 == 1;
  
  updatePiecePositions();
  deselect();
}

void AgoraViewer::save()
{
  std::ofstream f(fileName.latin1());
  f << agora;
  // save undo history
  f << undoIndex_ << " " << maxUndoIndex_ << endl;
  for (std::vector<Undo>::iterator it=history_.begin(), end=history_.end(); it != end; ++it)
    f << (*it).pos1 << " " << (*it).pos2 << " "
      << (*it).before1 << " " << (*it).before2 << " "
      << (*it).after1 << " " << (*it).after2 << endl;
  f.close();
}

void AgoraViewer::saveAs()
{
  fileName = QFileDialog::getSaveFileName("", "Agora files (*.ago);;All files (*)", this, fileName.latin1());

  QFileInfo fi(fileName);
  
  if (fi.extension().isEmpty())
    {
      fileName += ".ago";
      fi.setFile(fileName);
    }
    
  if (fi.exists())
    if (QMessageBox::warning(this ,"Existing file",
			     "File "+fi.fileName()+" already exists.\nSave anyway ?",
			     QMessageBox::Yes,
			     QMessageBox::Cancel) == QMessageBox::Cancel)
      return;

  if (!fi.isWritable())  // CHECK THIS
    {
      QMessageBox::warning(this ,"Cannot save", "File "+fi.fileName()+" is not writeable.");
      return;
    }
  
  save();
}


// U n d o   a n d   R e do
AgoraViewer::Undo::Undo(const Play& play, const Agora_t& agora)
{
  pos1    = play.depart();
  pos2    = play.arrivee();
  before1 = agora[pos1];
  before2 = agora[pos2];
}

void AgoraViewer::updateUndoHistory(bool before)
{
  if (before)
    {
      if (undoIndex_ < history_.size())
	history_[undoIndex_] = Undo(play_, agora);
      else
	history_.push_back(Undo(play_, agora));
    }
  else
    {
      history_[undoIndex_].after1 = agora[play_.depart()];
      history_[undoIndex_].after2 = agora[play_.arrivee()];
      undoIndex_++;
      maxUndoIndex_ = undoIndex_;
    }
}

void AgoraViewer::undo()
{
  if (undoIndex_ > 0)
    undoIndex_--;
  else
    return;
  
  agora.remettre(history_[undoIndex_].pos1, history_[undoIndex_].before1,
		 history_[undoIndex_].pos2, history_[undoIndex_].before2);
  updatePiecePositions();
  blackPlay_ = !blackPlay_;
  updateGL();
}

void AgoraViewer::redo()
{
  if (undoIndex_ >= maxUndoIndex_)
    {
      QMessageBox::warning(this, "No more redo", "No more redo is possible");
      return;
    }
  
  agora.remettre(history_[undoIndex_].pos1, history_[undoIndex_].after1,
		 history_[undoIndex_].pos2, history_[undoIndex_].after2);
  undoIndex_++;
  updatePiecePositions();
  blackPlay_ = !blackPlay_;
  updateGL();
}

void AgoraViewer::help()
{
  QMessageBox::information(this, " A g o r a", "Rules of Agora\nNot yet available, please browse the web.");
}

void AgoraViewer::about()
{
  QMessageBox::about(this, " A g o r a", "A g o r a\nCreated by Gilles Debunne and Jean-Guillaume Dumas\nVersion 1.0 - June 2003");
}

void AgoraViewer::togglePlayAgainstComputer(bool on)
{
  playerIsComputer_ = on;

  // Disable menu items
  AgoraWindow* window = dynamic_cast<AgoraWindow*>(parent()->parent());
  if (!window)
    {
      qWarning("Unable to disable menu items");
      return;
    }
  window->levelActionGroup->setEnabled(on);
  window->computerBlackAction->setEnabled(on);
}
