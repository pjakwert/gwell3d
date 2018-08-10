#ifndef GLMENU_H
#define GLMENU_H

#include <qlayout.h>
#include <qgrid.h>

#include <glmenuitem.h>
#include <kernel.h>


class GLMenu : public QWidget
{
  Q_OBJECT

  public:
    GLMenu(QWidget *parent, ViPattePolyhLib const *lib, const char *name=0, WFlags fl=0);
    ~GLMenu();
    const char *libName();

  private:
    ViPattePolyhLib const *_lib;
    const char *_libName;
    QGridLayout *grid;
    QGrid *gridzik;

  private slots:
    void objectItemSelected(const char* objectName);

  signals:
    void objectSelected(const char* objectName);
};


#endif
