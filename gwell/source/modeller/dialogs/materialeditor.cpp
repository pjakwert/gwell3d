//////////////////////////////////////////////////////////////////
///
///  class: MaterialEditor (.cpp)
///
///  dialog do edycji materialu i wlasciwosci koloru
///
//////////////////////////////////////////////////////////////////

#include "materialeditor.h"



/*!
Konstruktor:
\param tabNumber - oznacza numer zak³adki (widgetu) który ma byæ na pocz±tku wy¶wietlony:
0 : MaterialWidget (edycja materia³u)
1 : TextureWidget (edycja tekstury)
*/
MaterialEditor::MaterialEditor(int tabNumber, QPtrList<ViNTreeNode> *selectedList, QWidget *parent, const char *name, bool modal, WFlags fl) : QDialog(parent,name,modal,fl)
{
  this->setCaption(tr("Material Editor"));
//  this->setIcon();

    okButton = new QPushButton( this, "okButton" );
    okButton->setText( tr( "OK" ) );

    cancelButton = new QPushButton( this, "cancelButton" );
    cancelButton->setText( tr( "Cancel" ) );

    
    mainTabBar = new QTabWidget( this, "mainTabBar" );
    mainTabBar->setTabPosition( QTabWidget::Top );

      materialTab = new MaterialWidget( selectedList, mainTabBar, "materialTab", 0 );
      mainTabBar->insertTab( materialTab, tr( "Material" ) );
    
      textureTab = new TextureWidget( selectedList, mainTabBar, "textureTab", 0 );
      mainTabBar->insertTab( textureTab, tr( "Texture" ) );
    


//////////////////////////////////////////////////////////////////////////// GEOMETRIA
    okButton->setGeometry( QRect( 310, 545, 94, 30 ) );
    cancelButton->setGeometry( QRect( 410, 545, 94, 30 ) );
    mainTabBar->setGeometry( QRect( 10, 10, 790, 530 ) );
//////////////////////////////////////////////////////////////////////////// GEOMETRIA
        

////////////////////////////////////////////////////////////////////////////   connections
    connect(okButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(undoAllAndClose()));
////////////////////////////////////////////////////////////////////////////   connections

    
  // w zale¿no¶ci od wyboru u¿ytkownika, ustawiamy widoczn± zak³adkê
  switch (tabNumber)
  {
    case 0  : mainTabBar->setCurrentPage(0); break;
    case 1  : mainTabBar->setCurrentPage(1); break;
    default : mainTabBar->setCurrentPage(0); break; // domy¶lnie pokazujemy MaterialWidget (0)
  }
    

  //materialTab->resize(810,560); 
  this->setFixedSize(810,580);
  this->show();
}



// usuwanie widgetów jest chyba niepotrzebne
MaterialEditor::~MaterialEditor() {}


/*!
Metoda przechwytuje klawisze (obecnie nie reaguje na ¿adne).
*/
void MaterialEditor::keyPressEvent( QKeyEvent* e)
{
  e->ignore();
}

/*!
Metoda anuluje wszystkie zmiany materia³u i tekstury dla obiektów i zamyka MaterialEditor.
*/
void MaterialEditor::undoAllAndClose()
{
  materialTab->undoMaterials();
  textureTab->undoTexturing();
  close();
}
