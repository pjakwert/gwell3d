#include "namedialog.h"

NameDialog::NameDialog(QString title, QString info, QWidget *parent, const char *name, bool modal, WFlags fl) : QDialog(parent,name,modal,fl)
{
	this->setCaption(title);
	grid = new QGridLayout(this, 3,4, 12,5);
	 infoLabel = new QLabel(info,this);
	  QFont f = this->font();
		f.setPointSize(f.pointSize()-1);
	  infoLabel->setFont(f);
	 nameEdit = new QLineEdit(this);
	 okButton = new QPushButton(tr("OK"), this);
	 cancelButton = new QPushButton(tr("Cancel"), this);
	grid->addMultiCellWidget(infoLabel, 0,0, 0,3);
	grid->addMultiCellWidget(nameEdit, 1,1, 0,3);
	grid->addWidget(okButton, 2,1);
	grid->addWidget(cancelButton, 2,2);

	connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
	//resize(200,100);
}

NameDialog::~NameDialog()
{}

QString NameDialog::name()
{
	return nameEdit->text();
}
