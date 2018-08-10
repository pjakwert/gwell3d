////////////////////////////////////////////////////////////////////////////
///
///  class: NoDotValidator (.h)
///
///  validator dla QLineEdit do wpisywania nazwy obiektu
///  - nie dopuszcza do wyst�powania: kropek, spacji, nawias�w okr�g�ych
///  - sprawdza, czy wpisana nazwa nie zosta�a wcze�niej nadana innej bryle
///
////////////////////////////////////////////////////////////////////////////
#ifndef NODOTVALIDATOR_H
#define NODOTVALIDATOR_H

#include <qstring.h>
#include <qvalidator.h>
#include <cellframe.h>


class NoDotValidator : public QValidator
{
  public:
    NoDotValidator(QObject *parent, const char *name=0);
    ~NoDotValidator();
    virtual void fixup(QString &input) const;
    virtual State validate(QString &input, int &pos) const;
    
  private:
    bool findName( QString &input ) const;
};




#endif
