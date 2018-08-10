#ifndef QUARTO_H
#define QUARTO_H

#include <qvariant.h>
#include <qmainwindow.h>
#include "glview.h"
#include "piece.h"
#include <iostream>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout; 
class QPopupMenu;
class QFrame;
class QGroupBox;
class QLabel;
class QPushButton;
class QWidget;

class Quarto : public QMainWindow
{ 
  Q_OBJECT
    
public:
  Quarto( QWidget* parent = 0, const char* name = 0, WFlags fl = WType_TopLevel );
  ~Quarto();
  
  QFrame* GLFrameJeu, *GLFramePieces;
  // buttons
  QGroupBox* GameGroupBox;
  QLabel* TourDeJeuLabel, *NomLabel;
  QPushButton* ResetButton, *QuitButton;
  QPopupMenu *GagnantPopUp;
  
public slots:
  virtual void New();
  virtual void Exit();
  virtual void changeTour();
  virtual void piecePlacee();
  virtual void finDeJeu();

signals:
  void updategl();

protected:
  QVBoxLayout* QuartoLayout, *VLayout1, *VLayout2, *VLayout3;
  QHBoxLayout* MainHLayout, *HLayout1, *HLayout2, *HLayout3, *HLayout4;

  bool joueur;
  bool pieceplacee;
  int width, height;
  GLViewJeu *vuePlateau;
  GLViewPieces *vuePieces;
  SetOfPiece *setofpiece;
  virtual void init(bool);
};

#endif // QUARTO_H
