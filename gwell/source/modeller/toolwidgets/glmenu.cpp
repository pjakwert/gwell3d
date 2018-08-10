#include "glmenu.h"



GLMenu::GLMenu(QWidget *parent, ViPattePolyhLib const *lib, const char *name, WFlags fl) : QWidget(parent,name,fl)
{
  setMouseTracking(true);
  //setPaletteBackgroundColor(QColor(0, 0, 0));
  setPaletteBackgroundColor( Options::backgroundColor() );

  _lib = lib;                         // nazwa ladowanej biblioteki
  _libName = _lib->GetLibName();

  // ³adowanie bry³ elementarnych i umieszczanie w siatce menu
  grid = new QGridLayout(this, 2,1, 0,0);

  gridzik = new QGrid(3, this); // w tym gridzie bêd± 3 kolumny GLMenuItem-s
  GLMenuItem *item;
  for (ViPattePolyhLib::ConPatteIter iter = _lib->ConBegin_NormPatte(); iter; iter++) // umieszczamy elementy w menu
  {
    item = new GLMenuItem(gridzik, iter);
    connect(item, SIGNAL(objectSelected(const char*)), this, SLOT(objectItemSelected(const char*)));
  }
  grid->addWidget(gridzik,0,0);

  QSpacerItem *spacer = new QSpacerItem(10,10, QSizePolicy::Expanding, QSizePolicy::Expanding);
  grid->addItem(spacer,1,0);

}

  


GLMenu::~GLMenu()
{
}


// zwraca nazwe biblioteki, ktorej elementy wyswietla
const char *GLMenu::libName()
{
  return _libName;
}


// SLOT przekazuje dalej sygnal z GLMenuItem o wybranym obiekcie
void GLMenu::objectItemSelected(const char *objectName)
{
  emit objectSelected(objectName);
}




