//////////////////////////////////////////////////////////////////
///
///  class: MaterialEditor (.h)
///
///  dialog do edycji materialu i wlasciwosci koloru
///
//////////////////////////////////////////////////////////////////
#ifndef MATERIAL_EDITOR_H
#define MATERIAL_EDITOR_H


#include <qdialog.h>
#include <qpixmap.h>
#include <qiconset.h>
#include <qtabwidget.h>

#include <materialwidget.h>
#include <texturewidget.h>


class MaterialWidget;
class TextureWidget;


/*!
Klasa implementuje g³ówny dialog do modyfikowania materia³u i tekstury obiektów.
*/
class MaterialEditor : public QDialog
{
  Q_OBJECT

  public:
    MaterialEditor(int tabNumber, QPtrList<ViNTreeNode> *selectedList, QWidget *parent=0, const char *name=0, bool modal=true, WFlags fl=WType_Dialog | WDestructiveClose);
    ~MaterialEditor();

  private:
    QPushButton* okButton;
    QPushButton* cancelButton;

    QTabWidget*     mainTabBar;
  
    MaterialWidget *materialTab;
    TextureWidget  *textureTab;

  protected:
    void keyPressEvent( QKeyEvent* );
  
  private slots:
    void undoAllAndClose();
};


#endif
