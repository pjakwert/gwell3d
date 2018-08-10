////////////////////////////////////////////////////////////////////////////////
///
///  class: MaterialWidget (.cpp)
///
///  widget do edycji w�a�ciwo�ci materia�u - jedna z zak�adek w MaterialEditor
///
////////////////////////////////////////////////////////////////////////////////

#include "materialwidget.h"

#include <cellframe.h>

/*!
Makro FOR_EACH_OBJECT DO [wywo�anie metody dla ViElemePolyhExt]; END
wywo�uje metod� dla wszystkich obiekt�w klasy ViElemePolyhExt znajduj�cych si� na li�cie
_selectedList, czyli wszystkich zaznaczonych obiekt�w, dla kt�rych definiujemy materia�.
METODA OD�WIE�A OKNA WIDOKOWE w zale�no�ci od zmiennej warto�ci _dynamicPreview.
*/
#define FOR_EACH_OBJECT \
for (ViNTreeNode* _selected = _selectedList->first(); _selected; _selected = _selectedList->next()) \
{ \
  if (_selected->GetInheritorType() != IT_ELEMEPOLYH) continue; \
  ViElemePolyhExt* extEl = dynamic_cast<ViElemePolyhExt*> (_selected);

#define DO extEl->
#define END } if (_dynamicPreview) CellFrame::refresh();





MaterialWidget::MaterialWidget( QPtrList<ViNTreeNode> *selectedList, QWidget *parent, const char* name, WFlags fl ) : QWidget( parent, name, fl )
{

  _selectedList = selectedList;
  
  
  ///////////////////////////////////////////////////////////////////////////////     GUI
  frameMat = new QFrame( this, "frameMat" );
  frameMat->setFrameShape( QFrame::Box );
  frameMat->setFrameShadow( QFrame::Sunken );

  enableMatCheck = new QCheckBox( frameMat, "enableMatCheck" );
  enableMatCheck->setText( tr( "Material enabled" ) );

  dynamicPreviewCheck = new QCheckBox(frameMat, "dynamicPreview");
  dynamicPreviewCheck->setText(tr("Dynamic preview"));

  applyButtonGroup = new QButtonGroup( frameMat, "applyButtonGroup" );
  applyButtonGroup->setLineWidth( 0 );
  applyButtonGroup->setFlat( TRUE );
  applyButtonGroup->setExclusive(true);
  applyLabel = new QLabel(tr( "Apply material to" ), applyButtonGroup, "applyLabel" );

  frontRadio = new QRadioButton( applyButtonGroup, "frontRadio" );
  frontRadio->setText( tr( "front" ) );

  backRadio = new QRadioButton( applyButtonGroup, "backRadio" );
  backRadio->setText( tr( "back" ) );

  fbRadio = new QRadioButton( applyButtonGroup, "fbRadio" );
  fbRadio->setText( tr( "front and back" ) );

  matLine1 = new QFrame( frameMat, "matLine1" );
  matLine1->setFrameShape( QFrame::HLine );
  matLine1->setFrameShadow( QFrame::Sunken );
  matLine1->setFrameShape( QFrame::HLine );

  ambientBox = new ColorWidget(frameMat, tr(" AMBIENT "));
  diffuseBox = new ColorWidget(frameMat, tr(" DIFFUSE "));
  specularBox = new ColorWidget(frameMat, tr(" SPECULAR "));
  emissionBox = new ColorWidget(frameMat, tr(" EMMISION "));
  shineBox = new ShineWidget(frameMat, tr(" SHININESS ") );

  // pomniejszone czcionki
  f10.setFamily(this->font().family());
  f10.setPointSize(this->font().pointSize()-2);
  f9 = f10;
  f9.setPointSize(this->font().pointSize()-3);

  makeDefMatButton = new QPushButton( frameMat, "resetMatButton" );
  makeDefMatButton->setText( tr( "Make default" ) );
  makeDefMatButton->setFont(f10);

  resetToDefMatButton = new QPushButton( frameMat, "resetMatButton" );
  resetToDefMatButton->setText( tr( "Reset to defaults" ) );
  resetToDefMatButton->setFont(f9);

  matLine2 = new QFrame( frameMat, "matLine2" );
  matLine2->setFrameShape( QFrame::HLine );
  matLine2->setFrameShadow( QFrame::Sunken );
  matLine2->setFrameShape( QFrame::HLine );

  glMatSyntaxText = new QTextEdit( frameMat, "glMatSyntaxText" );
  glMatSyntaxText->setReadOnly( TRUE );
  glMatSyntaxText->setFont(f10);
  
  materialCombo = new QComboBox(false, frameMat, "loadMaterialCombo" );

  generateButton = new QToolButton(frameMat);
  generateButton->setFont(f9);
  generateButton->setTextLabel(tr("generate OpenGL syntax"));
  generateButton->setUsesTextLabel(true);
  generateButton->setAutoRaise(true);

  saveMatButton = new QPushButton( frameMat, "saveMatButton" );
  saveMatButton->setText( tr( "Save material as ..." ) );
  ///////////////////////////////////////////////////////////////////////////////     GUI
  
  
  
  //////////////////////////////////////////////////////////////////////////// GEOMETRIA  
  frameMat->setGeometry( QRect( 10, 10, 770, 480 ) );
  enableMatCheck->setGeometry( QRect( 10, 10, 130, 23 ) );
  dynamicPreviewCheck->setGeometry(170,10,140,20);
  applyButtonGroup->setGeometry( QRect( 370, 10, 390, 20 ) );
   applyLabel->setGeometry( QRect( 10, 0, 113, 20 ) );
   frontRadio->setGeometry( QRect( 130, 0, 50, 23 ) );
   backRadio->setGeometry( QRect( 200, 0, 50, 23 ) );
   fbRadio->setGeometry( QRect( 270, 0, 110, 23 ) );
  matLine1->setGeometry( QRect( 10, 30, 750, 20 ) );
  ambientBox->move(10, 60);
  ambientBox->resize( 150, 260 );
  diffuseBox->move(170, 60);
  diffuseBox->resize( 150, 260 );
  specularBox->move(330, 60);
  specularBox->resize( 150, 260 );
  emissionBox->move(490, 60);
  emissionBox->resize( 150, 260 );
  shineBox->move(650, 60);
  makeDefMatButton->setGeometry( QRect( 650, 280, 110, 20 ) );
  resetToDefMatButton->setGeometry( QRect( 650, 310, 110, 20 ) );
   matLine2->setGeometry( QRect( 10, 330, 750, 20 ) );
  glMatSyntaxText->setGeometry( QRect( 10, 350, 550, 100 ) );
  materialCombo->setGeometry( QRect( 570, 390, 190, 25 ) );
  generateButton->setGeometry(570,350, 190,25);
  saveMatButton->setGeometry( QRect( 570, 420, 150, 30 ) );   
  //////////////////////////////////////////////////////////////////////////// GEOMETRIA
  
  
  
  _dynamicPreview = true;                   // domyslnie podglad jest wlaczony
  dynamicPreviewCheck->setChecked(true);

  
  ////////////////////////////////////////////////////////////////////////////   connections    
  connect(enableMatCheck, SIGNAL(toggled(bool)), this, SLOT(setMaterialEnabled(bool)));
  connect(dynamicPreviewCheck, SIGNAL(toggled(bool)), this, SLOT(setDynamicPreview(bool)));
  connect(applyButtonGroup, SIGNAL(clicked(int)), this, SLOT(setApplyToFromButton(int)));

  connect(ambientBox,  SIGNAL(colorChanged(const QColor&,int)), this, SLOT(setAmbientColor(const QColor&,int)));
  connect(diffuseBox,  SIGNAL(colorChanged(const QColor&,int)), this, SLOT(setDiffuseColor(const QColor&,int)));
  connect(specularBox, SIGNAL(colorChanged(const QColor&,int)), this, SLOT(setSpecularColor(const QColor&,int)));
  connect(emissionBox, SIGNAL(colorChanged(const QColor&,int)), this, SLOT(setEmissionColor(const QColor&,int)));
  connect(shineBox, SIGNAL(shininessChanged(int)), this, SLOT(setShininess(int)));

  connect(makeDefMatButton, SIGNAL(clicked()), this, SLOT(makeMaterialDefault()));
  connect(resetToDefMatButton, SIGNAL(clicked()), this, SLOT(resetToDefaultMaterial()));

  connect(generateButton, SIGNAL(clicked()), this, SLOT(updateGLMatSyntaxText()));
  connect(materialCombo, SIGNAL(activated(int)), this, SLOT(selectMaterialFromCombo(int)));
  connect(saveMatButton, SIGNAL(clicked()), this, SLOT(saveMaterial()));
  ////////////////////////////////////////////////////////////////////////////   connections    
  
  
  // robimy kopie zapasowe materia��w obiekt�w  
  _backupMaterialList = new QPtrList<BackupStruct>; // lista materia��w do cel�w CANCEL
  
  // jeden materia� odpowiada jednemu obiektowi
  // tworzymy list� zapasow� materia��w zaznaczonych obiekt�w
  for (ViNTreeNode* _selected = _selectedList->first(); _selected; _selected = _selectedList->next())
  {
    if (_selected->GetInheritorType() != IT_ELEMEPOLYH) continue;
    ViElemePolyhExt* extEl = dynamic_cast<ViElemePolyhExt*> (_selected);
        
    Material *mat = new Material; // tworzymy nowy materia�
    *mat = *(extEl->material());  // i przepisujemy do niego stary
    
    BackupStruct *backup = new BackupStruct;
    backup->_backupMaterial         = mat;
    backup->_backupMaterialEnabled  = extEl->materialEnabled();
    backup->_backupApplyTo          = extEl->applyTo();
    
    _backupMaterialList->append(backup);
  }
  
      
  
  ///////////////////////////////////////////////////////////////////// �adowanie materia��w z dysku  
  // lista materia��w �adowana z dysku do combo
  _materialList = new QPtrList<Material>;

  // �adujemy materia�y z podkatalogu 'materials/'  
  //loadMaterials("materials"); 
  loadMaterials( Options::materialPaths()->first() );
  ///////////////////////////////////////////////////////////////////// �adowanie materia��w z dysku  
  
  
    
  // inicjujemy dialog materia�em pierwszego obiektu z listy _selectedList (je�eli jest ich kilka)
  if (!_selectedList->isEmpty())
  {
    ViNTreeNode* _selected;
    Material *mat;
    bool found=false;
    for (_selected = _selectedList->first(); _selected; _selected = _selectedList->next())
    {
      if (_selected->GetInheritorType() == IT_ELEMEPOLYH) {found=true; break;} // pierwszy lepszy viElemePolyhExt
    }

    if (found) // inicjujemy dialog warto�ciami tego obiektu
    {
      ViElemePolyhExt *extEl = dynamic_cast<ViElemePolyhExt*> (_selected);
      
      mat = extEl->material();
      
      setMaterialEnabled( extEl->materialEnabled() );
      setApplyTo        ( extEl->applyTo() );
      /// kolory
      ambientBox->setColor ( mat->ambientColorQT(),  mat->ambientAlpha() );
      diffuseBox->setColor ( mat->diffuseColorQT(),  mat->diffuseAlpha() );
      specularBox->setColor( mat->specularColorQT(), mat->specularAlpha() );
      emissionBox->setColor( mat->emissionColorQT(), mat->emissionAlpha() );
      shineBox->setShininess( mat->shininess() );
      /// /kolory

      // spr�buj rozpozna�, czy ten materia� jest kt�rym� z za�adowanych z dysku
      int ind = deduceMaterial( mat );
      if (ind != -1) materialCombo->setCurrentItem(ind); // je�eli tak - ustaw go w combo
    }
  }
}



// destruktor
MaterialWidget::~MaterialWidget()
{}



/*!
Metoda pr�buje rozpozna� czy aktualny materia� jest kt�rym� z za�adowanych z plik�w:
\return indeks na li�cie _materialList - je�eli tak,
\return -1 - je�eli nie.
*/
int MaterialWidget::deduceMaterial(const Material* material) const
{
  for (Material *mat = _materialList->first(); mat; mat = _materialList->next())
  {
    if ( (*mat) == (*material) ) return _materialList->at();
  }
  
  return -1;
}


/*!
Metoda w��cza/wy��cza wszystkie kontrolki i zaznacza checkBox-a w��czenia materia�u.
*/
void MaterialWidget::setMaterialEnabled(bool on)
{
  enableMatCheck->blockSignals(true);  // checkBox enableMaterial
   enableMatCheck->setChecked(on);
  enableMatCheck->blockSignals(false);

  dynamicPreviewCheck->setEnabled(on);
  applyButtonGroup->setEnabled(on);
  ambientBox->setEnabled(on);
  diffuseBox->setEnabled(on);
  specularBox->setEnabled(on);
  emissionBox->setEnabled(on);
  shineBox->setEnabled(on);
  makeDefMatButton->setEnabled(on);
  resetToDefMatButton->setEnabled(on);
  glMatSyntaxText->setEnabled(on);
  materialCombo->setEnabled(on);
  generateButton->setEnabled(on);
  saveMatButton->setEnabled(on);

  FOR_EACH_OBJECT DO setMaterialEnabled(on); END
}


/*!
Metoda ustawia typ �cian, dla ktorych ma by� stosowany materia�.
\param applyTo - GL_FRONT, GL_BACK lub GL_FRONT_AND_BACK.
*/
void MaterialWidget::setApplyTo(GLenum applyTo)
{
  switch (applyTo)
  {
    case GL_FRONT : {
                      frontRadio->blockSignals(true);
                      frontRadio->setChecked(true);
                      backRadio->setChecked(false);
                      fbRadio->setChecked(false);
                      frontRadio->blockSignals(false);
                      break;
                    }
    case GL_BACK  : {
                      backRadio->blockSignals(true);
                      backRadio->setChecked(true);
                      frontRadio->setChecked(false);
                      fbRadio->setChecked(false);
                      backRadio->blockSignals(false);
                      break;
                    }
    case GL_FRONT_AND_BACK  : {
                                fbRadio->blockSignals(true);
                                fbRadio->setChecked(true);
                                frontRadio->setChecked(false);
                                backRadio->setChecked(false);
                                fbRadio->blockSignals(false);
                                break;
                              }
    default : break;
  }
  FOR_EACH_OBJECT DO setApplyTo(applyTo); END
}



/*!
Metoda, w zale�no�ci od klikni�tego guzika, ustawia do jakich �cian stosowany jest materia�.
*/
void MaterialWidget::setApplyToFromButton(int num)
{
  QRadioButton *butt = dynamic_cast<QRadioButton*> (applyButtonGroup->find(num));

  if (butt->name() == frontRadio->name()) setApplyTo(GL_FRONT);
  if (butt->name() == backRadio->name()) setApplyTo(GL_BACK);
  if (butt->name() == fbRadio->name()) setApplyTo(GL_FRONT_AND_BACK);
}



/*!
Metoda ustawia edytowany materia� jako domy�lny i stosuje go do wszystkich nowo utworzonych bry�.
Mo�na go tez zastosowac do aktualnej bry�y metod� resetToDefaultMaterial().
*/
void MaterialWidget::makeMaterialDefault()
{
  GLenum apply;
  if (frontRadio->isChecked()) apply = GL_FRONT;
  if (backRadio->isChecked()) apply = GL_BACK;
  if (fbRadio->isChecked()) apply = GL_FRONT_AND_BACK;

  Material newMat = Material(
                              materialCombo->currentText(),   // nazw� materia�u bierzemy z combo
                              ambientBox->color(),
                              ambientBox->alpha(),
                              diffuseBox->color(),
                              diffuseBox->alpha(),
                              specularBox->color(),
                              specularBox->alpha(),
                              emissionBox->color(),
                              emissionBox->alpha(),
                              shineBox->shininess()
                            );
  ViElemePolyhExt::setDefaultMaterial(newMat);
}


/*!
Metoda resetuje aktualny materia� do domy�lnego.
*/
void MaterialWidget::resetToDefaultMaterial()
{
  const Material mat = ViElemePolyhExt::defaultMaterial();

  if (_dynamicPreview) _dynamicPreview = false;  // �eby niepotrzebnie nie od�wie�a� widok�w dla ka�dej zmiany
   setAmbientColor    (mat.ambientColorQT(),  mat.ambientAlpha());
   setDiffuseColor    (mat.diffuseColorQT(),  mat.diffuseAlpha());
   setSpecularColor   (mat.specularColorQT(), mat.specularAlpha());
   setEmissionColor   (mat.emissionColorQT(), mat.emissionAlpha());
   setShininess       (mat.shininess());
   
   // spr�buj okre�li� materia�
   int ind = deduceMaterial ( &mat );
   if (ind != -1) materialCombo->setCurrentItem( ind );
   
  if (dynamicPreviewCheck->isChecked()) setDynamicPreview(true);
}


////////////////////////////////////////////////////////  sloty ustawiajace kolory widgetom i obiektom
/*!
Metoda ustawia kolor ambient materia�u dla obiekt�w.
*/
void MaterialWidget::setAmbientColor(const QColor& color, int alpha)
{
  ambientBox->blockSignals(true);
   ambientBox->setColor(color, alpha);
  ambientBox->blockSignals(false);

  FOR_EACH_OBJECT DO material()->setAmbientColor(color, alpha); END
}

/*!
Metoda ustawia kolor diffuse materia�u dla obiekt�w.
*/
void MaterialWidget::setDiffuseColor(const QColor& color, int alpha)
{
  diffuseBox->blockSignals(true);
   diffuseBox->setColor(color, alpha);
  diffuseBox->blockSignals(false);

  FOR_EACH_OBJECT DO material()->setDiffuseColor(color, alpha); END
}

/*!
Metoda ustawia kolor specular materia�u dla obiekt�w.
*/
void MaterialWidget::setSpecularColor(const QColor& color, int alpha)
{
  specularBox->blockSignals(true);
   specularBox->setColor(color, alpha);
  specularBox->blockSignals(false);

  FOR_EACH_OBJECT DO material()->setSpecularColor(color, alpha); END
}

/*!
Metoda ustawia kolor emission materia�u dla obiekt�w.
*/
void MaterialWidget::setEmissionColor(const QColor& color, int alpha)
{
  emissionBox->blockSignals(true);
   emissionBox->setColor(color, alpha);
  emissionBox->blockSignals(false);

  FOR_EACH_OBJECT DO material()->setEmissionColor(color, alpha); END
}

/*!
Metoda ustawia po�yskliwo�� materia�u dla obiekt�w.
*/
void MaterialWidget::setShininess(int shininess)
{
  shineBox->blockSignals(true);
   shineBox->setShininess(shininess);
  shineBox->blockSignals(false);

  FOR_EACH_OBJECT DO material()->setShininess( shininess ); END
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////



/*!
Metoda umieszcza odpowiednie wpisy w glMatSyntaxText.
Wpis ten zawiera sk�adni� OpenGL dla materia�u.
*/
void MaterialWidget::updateGLMatSyntaxText()
{
  glMatSyntaxText->clear();

  QString s;

  s = QString("// OpenGL material");
  glMatSyntaxText->append(s);

  QColor c = ambientBox->color();
         s = QString("GLfloat mat_ambient[] = { %1, %2, %3, %4 };")
                .arg((float) c.red()/255,   0,'f',2)
                .arg((float) c.green()/255, 0,'f',2)
                .arg((float) c.blue()/255,  0,'f',2)
                .arg((float) ambientBox->alpha()/255,         0,'f',2);
  glMatSyntaxText->append(s);

  c = diffuseBox->color();
  s = QString("GLfloat mat_diffuse[] = { %1, %2, %3, %4 };")
                .arg((float) c.red()/255,   0,'f',2)
                .arg((float) c.green()/255, 0,'f',2)
                .arg((float) c.blue()/255,  0,'f',2)
                .arg((float) diffuseBox->alpha()/255,         0,'f',2);
  glMatSyntaxText->append(s);

  c = specularBox->color();
  s = QString("GLfloat mat_specular[] = { %1, %2, %3, %4 };")
                .arg((float) c.red()/255,   0,'f',2)
                .arg((float) c.green()/255, 0,'f',2)
                .arg((float) c.blue()/255,  0,'f',2)
                .arg((float) specularBox->alpha()/255,         0,'f',2);
  glMatSyntaxText->append(s);

  c = emissionBox->color();
  s = QString("GLfloat mat_emission[] = { %1, %2, %3, %4 };")
                .arg((float) c.red()/255,   0,'f',2)
                .arg((float) c.green()/255, 0,'f',2)
                .arg((float) c.blue()/255,  0,'f',2)
                .arg((float) emissionBox->alpha()/255,         0,'f',2);
  glMatSyntaxText->append(s);

  s = QString("GLfloat mat_shininess[] = { %1 };")
                .arg((float) shineBox->shininess(),   0,'f',2);
  glMatSyntaxText->append(s);

  QString apply;
   QRadioButton *butt = (QRadioButton*) applyButtonGroup->selected();
   if (butt->name() == frontRadio->name())  apply = "GL_FRONT";
   if (butt->name() == backRadio->name())   apply = "GL_BACK";
   if (butt->name() == fbRadio->name())     apply = "GL_FRONT_AND_BACK";

  s = QString("glMaterialfv( %1, GL_AMBIENT, mat_ambient);").arg(apply);
  glMatSyntaxText->append(s);
  s = QString("glMaterialfv( %1, GL_DIFFUSE, mat_diffuse);").arg(apply);
  glMatSyntaxText->append(s);
  s = QString("glMaterialfv( %1, GL_SPECULAR, mat_specular);").arg(apply);
  glMatSyntaxText->append(s);
  s = QString("glMaterialfv( %1, GL_EMISSION, mat_emission);").arg(apply);
  glMatSyntaxText->append(s);
  s = QString("glMaterialfv( %1, GL_SHININESS, mat_shininess);").arg(apply);
  glMatSyntaxText->append(s);
}




////////////////////////////////////////////////////////// metoda zapisuje aktualny materia� do pliku
/*!
Metoda zapisuje aktualny materia� do pliku.
Nazwa pliku tworzona jest z nazwy w�asnej materia�u, a je�eli taki plik istnieje - do��cza si� do nazwy
kolejne liczby i pr�buje dalej do skutku.
*/
void MaterialWidget::saveMaterial()
{
  NameDialog *nameDialog = new NameDialog(tr("Save material"), tr("Enter name for material:"), this);
  QString matName;

  if (nameDialog->exec() == QDialog::Accepted) matName = nameDialog->name(); // czy user zatwierdzi�
  else { delete nameDialog; return; } // je�eli CANCEL - wyjd�, nie zapisuj

  delete nameDialog;

  if (matName == QString::null) return; // je�eli user nie poda� nazwy - nie zapisujemy wcale (a co)

  // tworzenie dokumentu XML - doc
  QString s;
  QColor color;
  int a;

  QDomDocument doc;
  QDomElement main = doc.createElement( MATERIAL_MAIN );
  doc.appendChild(main);

  main.setAttribute(ATTR_MATERIAL_NAME, matName); // ustawiamy nazw� materia�u na podan� w dialogu

  QDomElement ambient = doc.createElement(ELEM_AMBIENT_COLOR);      //ambient
  main.appendChild(ambient);
  color = ambientBox->color();
  a = ambientBox->alpha();
  ambient.setAttribute(ATTR_RED, (GLfloat) color.red()/255);
  ambient.setAttribute(ATTR_GREEN, (GLfloat) color.green()/255);
  ambient.setAttribute(ATTR_BLUE, (GLfloat) color.blue()/255);
  ambient.setAttribute(ATTR_ALPHA, (GLfloat) a/255);

  QDomElement diffuse = doc.createElement(ELEM_DIFFUSE_COLOR);     // diffuse
  main.appendChild(diffuse);
  color = diffuseBox->color();
  a = diffuseBox->alpha();
  diffuse.setAttribute(ATTR_RED, (GLfloat) color.red()/255);
  diffuse.setAttribute(ATTR_GREEN, (GLfloat) color.green()/255);
  diffuse.setAttribute(ATTR_BLUE, (GLfloat) color.blue()/255);
  diffuse.setAttribute(ATTR_ALPHA, (GLfloat) a/255);

  QDomElement specular = doc.createElement(ELEM_SPECULAR_COLOR);    //specular
  main.appendChild(specular);
  color = specularBox->color();
  a = specularBox->alpha();
  specular.setAttribute(ATTR_RED, (GLfloat) color.red()/255);
  specular.setAttribute(ATTR_GREEN, (GLfloat) color.green()/255);
  specular.setAttribute(ATTR_BLUE, (GLfloat) color.blue()/255);
  specular.setAttribute(ATTR_ALPHA, (GLfloat) a/255);

  QDomElement emission = doc.createElement(ELEM_EMISSION_COLOR);    // emission
  main.appendChild(emission);
  color = emissionBox->color();
  a = emissionBox->alpha();
  emission.setAttribute(ATTR_RED, (GLfloat) color.red()/255);
  emission.setAttribute(ATTR_GREEN, (GLfloat) color.green()/255);
  emission.setAttribute(ATTR_BLUE, (GLfloat) color.blue()/255);
  emission.setAttribute(ATTR_ALPHA, (GLfloat) a/255);

  QDomElement shine = doc.createElement(ELEM_SHININESS);          // shininess
  main.appendChild(shine);
  shine.setAttribute(ATTR_SHININESS, shineBox->shininess());

  //// teraz zapis do pliku
  //// tworzymy plik o tej samej nazwie co nazwa materia�u, jak sie nie uda - modyfikujemy nazwe do skutku
  //QString localization = "materials/"; // zapisujemy w lokalizacji !!! UWAGA: TO MA BY� USTAWIALNE !!!
  QString localization = ( Options::materialPaths()->first() );
  if ( !localization.endsWith("/") ) localization += "/";
  QFile file( localization + matName + ".mat" );
  int i=0;
  while (file.exists()) // dodawaj liczby do skutku, a� nazwa b�dzie unikalna
  {
    file.setName( localization + matName + QString::number(i++) + ".mat" );
  }

  if (!file.open(IO_WriteOnly))  // otwarcie pliku do zapisu
  {
    QMessageBox::critical(
                          this,
                          tr("Save material"),
                          tr("Unable to save file \"%1\" in given localization:\n\"%2\".").arg(file.name()).arg(localization)
                         );
    return;
  }

  QTextStream stream(&file); // tworzymy strumie�
  stream << doc.toString();  // wysy�amy XML-a do pliku
  file.close();              // zamykamy plik

  // teraz dodajemy ten material do _materialList i combo
  const char *chr = file.name().ascii();  // ta linijka wymagana jest ze wzgl�du na op�nienie mi�dzy R/W
  readFromFile(file.name()); // to uzupe�ni _materialList i combo

  materialCombo->setCurrentItem(materialCombo->count()-1); // ustaw w combo dodany materia� jako aktualny
  
  // message do StatusBar-a
  StatusBar::printStatusMsg(tr("Material \"%1\" saved successfully in file '%2'.").arg(matName).arg(file.name()), "Material Editor");
}



/*!
Metoda �aduje wszystkie materia�y z podanego katalogu.
Materia�y maj� rozszerzenie .mat, .MAT, .Mat.
\return  1 - wszystko OK,
\return -1 - katalog nie istnieje,
\return -2 - katalog jest pusty (to nie ma znaczenia).
*/
int MaterialWidget::loadMaterials(QString path)
{
  _materialList->clear(); // wyczy�� list� materia��w
  materialCombo->clear(); // wyczy�� combo

  QDir dir(path);

  if (!dir.exists()) return -1; // katalog nie istnieje

  dir.setFilter(QDir::Files | QDir::Hidden); // interesuj� nas pliki (tak�e ukryte)
  dir.setNameFilter("*.mat *.MAT *.Mat"); // filtr
  dir.setSorting(QDir::Name); // znalezione pliki sortujemy wg nazw

  const QFileInfoList *list = dir.entryInfoList(); // lista znalezionych plik�w
  QFileInfoListIterator iter (*list); // iterator dla tej listy
  QFileInfo *fileInfo; // dane znalezionego konkretnego pliku

  QString name;
  QString msg;
  int errNo;
  
  while ((fileInfo = iter.current()) != 0)
  {
    name = dir.filePath(fileInfo->fileName());
    errNo = readFromFile(name);
    
    switch (errNo)
    {
      case -1 : msg = tr("File '%1' with material doesn't exist.").arg(name); break;
      case -2 : msg = tr("Error reading material file: '%1'.").arg(name);     break;
      case -3 : msg = tr("Error parsing material file: '%1'.").arg(name);     break;
      default : msg = QString::null; break; // dla 1 jest OK
    }
    if (msg != QString::null) StatusBar::printStatusMsg(msg, "Material Editor");
    
    ++iter;
  } // while

  return 1;
}



/*!
Metoda parsuje plik XML i dodaje wczytan� struktur� do listy matList.
\param name - nazwa pliku do odczytu.
\return 1 - wszystko OK,
\return -1 - plik nie istnieje,
\return -2 - wyst�pi� b��d odczytu z pliku,
\return -3 - wyst�pi� b��d parsowania - element nie jest wtedy wogle dodawany.
Tylko ta metoda od�wie�a comboBox z materia�ami.
*/
int MaterialWidget::readFromFile(QString name)
{
  QDomDocument doc;
  Material *mat = new Material;
  float r,g,b,a;
  bool ok;

  QFile file(name);
  if (!file.exists()) return -1;                            // plik nie istnieje
  if (!file.open(IO_ReadOnly)) return -2;                   // b��d odczytu z pliku
  if (!doc.setContent(&file)) { file.close(); return -3; } // b��d parsowania XML

  file.close();

  QDomElement main = doc.documentElement();
  if (!main.hasAttributes()) return -3;                 // brak atrybut�w - z�y XML
  if (!main.hasChildNodes()) return -3;                 // brak potomk�w
  if (main.tagName() != MATERIAL_MAIN) return -3;       // z�a nazwa w�z�a

  QDomAttr materialName = main.attributeNode(ATTR_MATERIAL_NAME); // atrybut materialName
   if (materialName.isNull()) return -3; // nie istnieje taki atrybut
  mat->setMaterialName( materialName.value() );

  QDomNode node = main.firstChild(); // w�z�y elementu Material
  while (!node.isNull())
  {
   if (node.nodeType() != QDomNode::ElementNode) return -3; // tylko elementy
   QDomElement elem = node.toElement();

   if ((elem.nodeName() != ELEM_AMBIENT_COLOR)  &&
       (elem.nodeName() != ELEM_DIFFUSE_COLOR)  &&
       (elem.nodeName() != ELEM_SPECULAR_COLOR) &&
       (elem.nodeName() != ELEM_EMISSION_COLOR) &&
       (elem.nodeName() != ELEM_SHININESS)) return -3;

   if (elem.nodeName() != ELEM_SHININESS) // dla kolor�w sprawa wygl�da tak samo, ale shininess..
   {
    QDomAttr red = elem.attributeNode(ATTR_RED);
     if (red.isNull()) return -3;
     r = red.value().toFloat(&ok);   
     if (!ok) return -3;
    QDomAttr green = elem.attributeNode(ATTR_GREEN);
     if (green.isNull()) return -3;
     g = green.value().toFloat(&ok); 
     if (!ok) return -3;
    QDomAttr blue = elem.attributeNode(ATTR_BLUE);
     if (blue.isNull()) return -3;
     b = blue.value().toFloat(&ok);
     if (!ok) return -3;
    QDomAttr alpha = elem.attributeNode(ATTR_ALPHA);
     if (alpha.isNull()) return -3;
     a = alpha.value().toFloat(&ok); 
     if (!ok) return -3;

    const GLfloat color[4] = { r, g, b, a };  // tworzymy wektor z odczytanych warto�ci

    if (elem.tagName() == ELEM_AMBIENT_COLOR)  mat->setAmbientColor ( color );
    if (elem.tagName() == ELEM_DIFFUSE_COLOR)  mat->setDiffuseColor ( color );
    if (elem.tagName() == ELEM_SPECULAR_COLOR) mat->setSpecularColor( color );
    if (elem.tagName() == ELEM_EMISSION_COLOR) mat->setEmissionColor( color );
    
   }
   else // dla shininess jest tylko jeden atrybut
   {
    QDomAttr shine = elem.attributeNode(ATTR_SHININESS);
     if (shine.isNull()) return -3;
    int sh = shine.value().toInt(&ok); 
    if (!ok) return -3;

    mat->setShininess( sh );
   }

   node = node.nextSibling();
  } // while

  _materialList->append(mat); // dodaj materia� do listy
  // aktualizuj combo
  materialCombo->insertItem(mat->materialName());            // dodaj materia� do combo

  return 1; // OK
}



/*!
Metoda aktywowana wyborem materia�u z comboBox-a.
\param index - pozycj� materia�u na li�cie _materialList (r�wnie� w comboBox).
*/
void MaterialWidget::selectMaterialFromCombo(int index)
{
  if (materialCombo->count() <= 0) return; // puste combo - wyjd�

  Material *mat = _materialList->at(index);
  if (mat == 0L) return; // nie ma takiego materia�u, index poza list�
  
  bool oldPreview = _dynamicPreview;             // je�eli od�wie�anie widok�w CellFrame jest w��czone
  if (_dynamicPreview) setDynamicPreview(false); // to na chwil� je wy��czamy
                
  ambientBox->setColor   ( mat->ambientColorQT(),  mat->ambientAlpha()  );
  diffuseBox->setColor   ( mat->diffuseColorQT(),  mat->diffuseAlpha()  );
  specularBox->setColor  ( mat->specularColorQT(), mat->specularAlpha() );
  emissionBox->setColor  ( mat->emissionColorQT(), mat->emissionAlpha() );
  shineBox->setShininess ( mat->shininess() );
  
  setDynamicPreview(oldPreview); // w��czamy ponownie i zastosowanie shininess od�wie�y widoki
}


/*!
Metoda ustawia dynamiczne wy�wietlanie zmian w materiale w widokach edycyjnych.
*/
void MaterialWidget::setDynamicPreview(bool on)
{
  _dynamicPreview = on;
  if (on) CellFrame::refresh();
}


/*!
Metoda przywraca w�a�ciwo�ci materia��w sprzed modyfikacji - UNDO.
*/
void MaterialWidget::undoMaterials()
{
  BackupStruct *backup = _backupMaterialList->first();
  Material *mat;
  Material *bakMat;
  
  for (ViNTreeNode* _selected = _selectedList->first(); _selected; _selected = _selectedList->next())
  {
    if (_selected->GetInheritorType() != IT_ELEMEPOLYH) continue;
    ViElemePolyhExt* extEl = dynamic_cast<ViElemePolyhExt*> (_selected);
    
    // odtwarzamy poprzednie materia�y
    bakMat = backup->_backupMaterial;
    mat = extEl->material();
    
    mat->setMaterialName      ( bakMat->materialName() );
    extEl->setApplyTo         ( backup->_backupApplyTo );
    extEl->setMaterialEnabled ( backup->_backupMaterialEnabled );
    mat->setAmbientColor      ( bakMat->ambientColorQT(),  bakMat->ambientAlpha());
    mat->setDiffuseColor      ( bakMat->diffuseColorQT(),  bakMat->diffuseAlpha());
    mat->setSpecularColor     ( bakMat->specularColorQT(), bakMat->specularAlpha());
    mat->setEmissionColor     ( bakMat->emissionColorQT(), bakMat->emissionAlpha());
    mat->setShininess         ( bakMat->shininess());
        
    backup = _backupMaterialList->next();
  }
}

