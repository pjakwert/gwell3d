////////////////////////////////////////////////////////////////////////////////
///
///  class: MaterialWidget (.cpp)
///
///  widget do edycji w³a¶ciwo¶ci materia³u - jedna z zak³adek w MaterialEditor
///
////////////////////////////////////////////////////////////////////////////////

#include "materialwidget.h"

#include <cellframe.h>

/*!
Makro FOR_EACH_OBJECT DO [wywo³anie metody dla ViElemePolyhExt]; END
wywo³uje metodê dla wszystkich obiektów klasy ViElemePolyhExt znajduj±cych siê na li¶cie
_selectedList, czyli wszystkich zaznaczonych obiektów, dla których definiujemy materia³.
METODA OD¦WIE¯A OKNA WIDOKOWE w zale¿no¶ci od zmiennej warto¶ci _dynamicPreview.
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
  
  
  // robimy kopie zapasowe materia³ów obiektów  
  _backupMaterialList = new QPtrList<BackupStruct>; // lista materia³ów do celów CANCEL
  
  // jeden materia³ odpowiada jednemu obiektowi
  // tworzymy listê zapasow± materia³ów zaznaczonych obiektów
  for (ViNTreeNode* _selected = _selectedList->first(); _selected; _selected = _selectedList->next())
  {
    if (_selected->GetInheritorType() != IT_ELEMEPOLYH) continue;
    ViElemePolyhExt* extEl = dynamic_cast<ViElemePolyhExt*> (_selected);
        
    Material *mat = new Material; // tworzymy nowy materia³
    *mat = *(extEl->material());  // i przepisujemy do niego stary
    
    BackupStruct *backup = new BackupStruct;
    backup->_backupMaterial         = mat;
    backup->_backupMaterialEnabled  = extEl->materialEnabled();
    backup->_backupApplyTo          = extEl->applyTo();
    
    _backupMaterialList->append(backup);
  }
  
      
  
  ///////////////////////////////////////////////////////////////////// ³adowanie materia³ów z dysku  
  // lista materia³ów ³adowana z dysku do combo
  _materialList = new QPtrList<Material>;

  // ³adujemy materia³y z podkatalogu 'materials/'  
  //loadMaterials("materials"); 
  loadMaterials( Options::materialPaths()->first() );
  ///////////////////////////////////////////////////////////////////// ³adowanie materia³ów z dysku  
  
  
    
  // inicjujemy dialog materia³em pierwszego obiektu z listy _selectedList (je¿eli jest ich kilka)
  if (!_selectedList->isEmpty())
  {
    ViNTreeNode* _selected;
    Material *mat;
    bool found=false;
    for (_selected = _selectedList->first(); _selected; _selected = _selectedList->next())
    {
      if (_selected->GetInheritorType() == IT_ELEMEPOLYH) {found=true; break;} // pierwszy lepszy viElemePolyhExt
    }

    if (found) // inicjujemy dialog warto¶ciami tego obiektu
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

      // spróbuj rozpoznaæ, czy ten materia³ jest którym¶ z za³adowanych z dysku
      int ind = deduceMaterial( mat );
      if (ind != -1) materialCombo->setCurrentItem(ind); // je¿eli tak - ustaw go w combo
    }
  }
}



// destruktor
MaterialWidget::~MaterialWidget()
{}



/*!
Metoda próbuje rozpoznaæ czy aktualny materia³ jest którym¶ z za³adowanych z plików:
\return indeks na li¶cie _materialList - je¿eli tak,
\return -1 - je¿eli nie.
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
Metoda w³±cza/wy³±cza wszystkie kontrolki i zaznacza checkBox-a w³±czenia materia³u.
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
Metoda ustawia typ ¶cian, dla ktorych ma byæ stosowany materia³.
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
Metoda, w zale¿no¶ci od klikniêtego guzika, ustawia do jakich ¶cian stosowany jest materia³.
*/
void MaterialWidget::setApplyToFromButton(int num)
{
  QRadioButton *butt = dynamic_cast<QRadioButton*> (applyButtonGroup->find(num));

  if (butt->name() == frontRadio->name()) setApplyTo(GL_FRONT);
  if (butt->name() == backRadio->name()) setApplyTo(GL_BACK);
  if (butt->name() == fbRadio->name()) setApplyTo(GL_FRONT_AND_BACK);
}



/*!
Metoda ustawia edytowany materia³ jako domy¶lny i stosuje go do wszystkich nowo utworzonych bry³.
Mo¿na go tez zastosowac do aktualnej bry³y metod± resetToDefaultMaterial().
*/
void MaterialWidget::makeMaterialDefault()
{
  GLenum apply;
  if (frontRadio->isChecked()) apply = GL_FRONT;
  if (backRadio->isChecked()) apply = GL_BACK;
  if (fbRadio->isChecked()) apply = GL_FRONT_AND_BACK;

  Material newMat = Material(
                              materialCombo->currentText(),   // nazwê materia³u bierzemy z combo
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
Metoda resetuje aktualny materia³ do domy¶lnego.
*/
void MaterialWidget::resetToDefaultMaterial()
{
  const Material mat = ViElemePolyhExt::defaultMaterial();

  if (_dynamicPreview) _dynamicPreview = false;  // ¿eby niepotrzebnie nie od¶wie¿aæ widoków dla ka¿dej zmiany
   setAmbientColor    (mat.ambientColorQT(),  mat.ambientAlpha());
   setDiffuseColor    (mat.diffuseColorQT(),  mat.diffuseAlpha());
   setSpecularColor   (mat.specularColorQT(), mat.specularAlpha());
   setEmissionColor   (mat.emissionColorQT(), mat.emissionAlpha());
   setShininess       (mat.shininess());
   
   // spróbuj okre¶liæ materia³
   int ind = deduceMaterial ( &mat );
   if (ind != -1) materialCombo->setCurrentItem( ind );
   
  if (dynamicPreviewCheck->isChecked()) setDynamicPreview(true);
}


////////////////////////////////////////////////////////  sloty ustawiajace kolory widgetom i obiektom
/*!
Metoda ustawia kolor ambient materia³u dla obiektów.
*/
void MaterialWidget::setAmbientColor(const QColor& color, int alpha)
{
  ambientBox->blockSignals(true);
   ambientBox->setColor(color, alpha);
  ambientBox->blockSignals(false);

  FOR_EACH_OBJECT DO material()->setAmbientColor(color, alpha); END
}

/*!
Metoda ustawia kolor diffuse materia³u dla obiektów.
*/
void MaterialWidget::setDiffuseColor(const QColor& color, int alpha)
{
  diffuseBox->blockSignals(true);
   diffuseBox->setColor(color, alpha);
  diffuseBox->blockSignals(false);

  FOR_EACH_OBJECT DO material()->setDiffuseColor(color, alpha); END
}

/*!
Metoda ustawia kolor specular materia³u dla obiektów.
*/
void MaterialWidget::setSpecularColor(const QColor& color, int alpha)
{
  specularBox->blockSignals(true);
   specularBox->setColor(color, alpha);
  specularBox->blockSignals(false);

  FOR_EACH_OBJECT DO material()->setSpecularColor(color, alpha); END
}

/*!
Metoda ustawia kolor emission materia³u dla obiektów.
*/
void MaterialWidget::setEmissionColor(const QColor& color, int alpha)
{
  emissionBox->blockSignals(true);
   emissionBox->setColor(color, alpha);
  emissionBox->blockSignals(false);

  FOR_EACH_OBJECT DO material()->setEmissionColor(color, alpha); END
}

/*!
Metoda ustawia po³yskliwo¶æ materia³u dla obiektów.
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
Wpis ten zawiera sk³adniê OpenGL dla materia³u.
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




////////////////////////////////////////////////////////// metoda zapisuje aktualny materia³ do pliku
/*!
Metoda zapisuje aktualny materia³ do pliku.
Nazwa pliku tworzona jest z nazwy w³asnej materia³u, a je¿eli taki plik istnieje - do³±cza siê do nazwy
kolejne liczby i próbuje dalej do skutku.
*/
void MaterialWidget::saveMaterial()
{
  NameDialog *nameDialog = new NameDialog(tr("Save material"), tr("Enter name for material:"), this);
  QString matName;

  if (nameDialog->exec() == QDialog::Accepted) matName = nameDialog->name(); // czy user zatwierdzi³
  else { delete nameDialog; return; } // je¿eli CANCEL - wyjd¼, nie zapisuj

  delete nameDialog;

  if (matName == QString::null) return; // je¿eli user nie poda³ nazwy - nie zapisujemy wcale (a co)

  // tworzenie dokumentu XML - doc
  QString s;
  QColor color;
  int a;

  QDomDocument doc;
  QDomElement main = doc.createElement( MATERIAL_MAIN );
  doc.appendChild(main);

  main.setAttribute(ATTR_MATERIAL_NAME, matName); // ustawiamy nazwê materia³u na podan± w dialogu

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
  //// tworzymy plik o tej samej nazwie co nazwa materia³u, jak sie nie uda - modyfikujemy nazwe do skutku
  //QString localization = "materials/"; // zapisujemy w lokalizacji !!! UWAGA: TO MA BYÆ USTAWIALNE !!!
  QString localization = ( Options::materialPaths()->first() );
  if ( !localization.endsWith("/") ) localization += "/";
  QFile file( localization + matName + ".mat" );
  int i=0;
  while (file.exists()) // dodawaj liczby do skutku, a¿ nazwa bêdzie unikalna
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

  QTextStream stream(&file); // tworzymy strumieñ
  stream << doc.toString();  // wysy³amy XML-a do pliku
  file.close();              // zamykamy plik

  // teraz dodajemy ten material do _materialList i combo
  const char *chr = file.name().ascii();  // ta linijka wymagana jest ze wzglêdu na opó¼nienie miêdzy R/W
  readFromFile(file.name()); // to uzupe³ni _materialList i combo

  materialCombo->setCurrentItem(materialCombo->count()-1); // ustaw w combo dodany materia³ jako aktualny
  
  // message do StatusBar-a
  StatusBar::printStatusMsg(tr("Material \"%1\" saved successfully in file '%2'.").arg(matName).arg(file.name()), "Material Editor");
}



/*!
Metoda ³aduje wszystkie materia³y z podanego katalogu.
Materia³y maj± rozszerzenie .mat, .MAT, .Mat.
\return  1 - wszystko OK,
\return -1 - katalog nie istnieje,
\return -2 - katalog jest pusty (to nie ma znaczenia).
*/
int MaterialWidget::loadMaterials(QString path)
{
  _materialList->clear(); // wyczy¶æ listê materia³ów
  materialCombo->clear(); // wyczy¶æ combo

  QDir dir(path);

  if (!dir.exists()) return -1; // katalog nie istnieje

  dir.setFilter(QDir::Files | QDir::Hidden); // interesuj± nas pliki (tak¿e ukryte)
  dir.setNameFilter("*.mat *.MAT *.Mat"); // filtr
  dir.setSorting(QDir::Name); // znalezione pliki sortujemy wg nazw

  const QFileInfoList *list = dir.entryInfoList(); // lista znalezionych plików
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
Metoda parsuje plik XML i dodaje wczytan± strukturê do listy matList.
\param name - nazwa pliku do odczytu.
\return 1 - wszystko OK,
\return -1 - plik nie istnieje,
\return -2 - wyst±pi³ b³±d odczytu z pliku,
\return -3 - wyst±pi³ b³±d parsowania - element nie jest wtedy wogle dodawany.
Tylko ta metoda od¶wie¿a comboBox z materia³ami.
*/
int MaterialWidget::readFromFile(QString name)
{
  QDomDocument doc;
  Material *mat = new Material;
  float r,g,b,a;
  bool ok;

  QFile file(name);
  if (!file.exists()) return -1;                            // plik nie istnieje
  if (!file.open(IO_ReadOnly)) return -2;                   // b³±d odczytu z pliku
  if (!doc.setContent(&file)) { file.close(); return -3; } // b³±d parsowania XML

  file.close();

  QDomElement main = doc.documentElement();
  if (!main.hasAttributes()) return -3;                 // brak atrybutów - z³y XML
  if (!main.hasChildNodes()) return -3;                 // brak potomków
  if (main.tagName() != MATERIAL_MAIN) return -3;       // z³a nazwa wêz³a

  QDomAttr materialName = main.attributeNode(ATTR_MATERIAL_NAME); // atrybut materialName
   if (materialName.isNull()) return -3; // nie istnieje taki atrybut
  mat->setMaterialName( materialName.value() );

  QDomNode node = main.firstChild(); // wêz³y elementu Material
  while (!node.isNull())
  {
   if (node.nodeType() != QDomNode::ElementNode) return -3; // tylko elementy
   QDomElement elem = node.toElement();

   if ((elem.nodeName() != ELEM_AMBIENT_COLOR)  &&
       (elem.nodeName() != ELEM_DIFFUSE_COLOR)  &&
       (elem.nodeName() != ELEM_SPECULAR_COLOR) &&
       (elem.nodeName() != ELEM_EMISSION_COLOR) &&
       (elem.nodeName() != ELEM_SHININESS)) return -3;

   if (elem.nodeName() != ELEM_SHININESS) // dla kolorów sprawa wygl±da tak samo, ale shininess..
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

    const GLfloat color[4] = { r, g, b, a };  // tworzymy wektor z odczytanych warto¶ci

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

  _materialList->append(mat); // dodaj materia³ do listy
  // aktualizuj combo
  materialCombo->insertItem(mat->materialName());            // dodaj materia³ do combo

  return 1; // OK
}



/*!
Metoda aktywowana wyborem materia³u z comboBox-a.
\param index - pozycj± materia³u na li¶cie _materialList (równie¿ w comboBox).
*/
void MaterialWidget::selectMaterialFromCombo(int index)
{
  if (materialCombo->count() <= 0) return; // puste combo - wyjd¼

  Material *mat = _materialList->at(index);
  if (mat == 0L) return; // nie ma takiego materia³u, index poza list±
  
  bool oldPreview = _dynamicPreview;             // je¿eli od¶wie¿anie widoków CellFrame jest w³±czone
  if (_dynamicPreview) setDynamicPreview(false); // to na chwilê je wy³±czamy
                
  ambientBox->setColor   ( mat->ambientColorQT(),  mat->ambientAlpha()  );
  diffuseBox->setColor   ( mat->diffuseColorQT(),  mat->diffuseAlpha()  );
  specularBox->setColor  ( mat->specularColorQT(), mat->specularAlpha() );
  emissionBox->setColor  ( mat->emissionColorQT(), mat->emissionAlpha() );
  shineBox->setShininess ( mat->shininess() );
  
  setDynamicPreview(oldPreview); // w³±czamy ponownie i zastosowanie shininess od¶wie¿y widoki
}


/*!
Metoda ustawia dynamiczne wy¶wietlanie zmian w materiale w widokach edycyjnych.
*/
void MaterialWidget::setDynamicPreview(bool on)
{
  _dynamicPreview = on;
  if (on) CellFrame::refresh();
}


/*!
Metoda przywraca w³a¶ciwo¶ci materia³ów sprzed modyfikacji - UNDO.
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
    
    // odtwarzamy poprzednie materia³y
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

