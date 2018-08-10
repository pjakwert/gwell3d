#ifndef GLVIEW_H
#define GLVIEW_H

#include <qgl.h>
#include <QGLViewer/qglviewer.h>
#include <iostream>
#include "jeu.h"
#include "piece.h"

/*
 * Classe generique pour les fenetres OpenGl
 */
class GLView : public QGLViewer
{
  Q_OBJECT
public:
  GLView( QWidget* parent, const char* name ): QGLViewer( parent, name ) {}

  virtual void init();
  virtual void setPieces(SetOfPiece *sop) { setofpiece=sop; };

signals:
  void update();

protected:
  virtual void select(const QMouseEvent* e);
  virtual void drawWithId() {};
  virtual void applySelection(int) {};
  virtual void keyPressEvent(QKeyEvent *) {};

  SetOfPiece *setofpiece;
  
private:
  GLuint texture_bois;
};



// Classe fille pour la vue des pieces a selectionner
class GLViewPieces : public GLView
{
  Q_OBJECT
public:
  GLViewPieces( QWidget* parent, const char* name ): GLView( parent, name ) {}

protected:
  virtual void draw();
  virtual void init();

  virtual void drawWithId() { draw(); };
  virtual void applySelection(int);

signals:
  void changeJoueur();
};



// Classe fille pour la vue du plateau de jeu
class GLViewJeu : public GLView
{
  Q_OBJECT

public:
  GLViewJeu( QWidget* parent, const char* name ): GLView( parent, name ) {}
  ~GLViewJeu() { glDeleteLists(plateau, 1); }

  void reset() { jeu.init(); }
  
protected :
  virtual void draw();
  virtual void init();

  virtual void drawWithId();
  virtual void applySelection(int);

signals:
  void piecePlacee();
  void endGame();

private:
  GLuint plateau;
  Jeu jeu;

  void makePlateau();
};

#endif // GLVIEW_H
