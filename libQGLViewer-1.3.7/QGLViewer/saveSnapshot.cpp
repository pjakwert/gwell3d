/****************************************************************************

 This file is part of the QGLViewer library
 Copyright (C) 2002-2004  Gilles Debunne (Gilles.Debunne@imag.fr)
 Version 1.3.7 Release 1. Packaged on Friday April 30, 2004.

 http://artis.imag.fr/Members/Gilles.Debunne/QGLViewer

 libQGLViewer is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 libQGLViewer is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with libQGLViewer; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*****************************************************************************/

#include "qglviewer.h"

#ifndef NO_EPS_RENDER
# include "EPSInterface.h"
# include "EPSRender/EPSRender.h"
  using namespace EpsRenderer;
#endif

#include <qimage.h>
#include <qfileinfo.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qapplication.h>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qmap.h>

using namespace std;

/*! Sets the filename to use when saving snapshot with saveSnapshot(). If the filename is relative,
the current working directory <em>at the moment of the function call</em> is added.
snapshotFilename() returns the current snapshot file name. */
void QGLViewer::setSnapshotFilename(const QString& n)
{
  QFileInfo info(n);
  snapshotFilename_ = info.absFilePath();
}


#if QT_VERSION < 300

void QGLViewer::saveSnapshot(bool, bool)
{ QMessageBox::information(this, "Snapshot disabled", "Snapshot saving is not implemented with Qt version 2.3."); }

#else

////// Static global variables - local to this file //////
// List of available output file formats
static QString formats;
// Converts QFileDialog resulting format to Qt snapshotFormat_.
static QMap<QString, QString> Qtformat;
// Converts Qt snapshotFormat_ to QFileDialog menu string.
static QMap<QString, QString> FDFormatString;
// Converts snapshotFormat_ to file extension
static QMap<QString, QString> extension;

static void createFormatList()
{
  QStringList formatList = QImage::outputFormatList();
  //        cout << "Available image formats : " << endl;
  //        QStringList::Iterator it = formatList.begin();
  //        while( it != formatList.end() )
  //  	    cout << (*it++) << endl;
      
#ifndef NO_EPS_RENDER
  // We add the 3 vectorial formats to the list
  formatList += "EPS";
  formatList += "PS";
  formatList += "XFIG";
#endif
      
  // Check that the interesting formats are available and add them in "formats"
  // Unused formats : XPM XBM PBM PGM
  QStringList QtText, MenuText, Ext;
  QtText += "JPEG";	MenuText += "JPEG (*.jpg)";		Ext += "jpg";
  QtText += "PNG";	MenuText += "PNG (*.png)";		Ext += "png";
  QtText += "EPS";	MenuText += "Encapsulated Postscript (*.eps)";	Ext += "eps";
  QtText += "PS";	MenuText += "Postscript (*.ps)";	Ext += "ps";
  QtText += "XFIG";	MenuText += "XFig 3.2 (*.fig)";		Ext += "fig";
  QtText += "PPM";	MenuText += "24bit RGB Bitmap (*.ppm)";	Ext += "ppm";
  QtText += "BMP";	MenuText += "Windows Bitmap (*.bmp)";	Ext += "bmp";

  QStringList::iterator itText = QtText.begin();
  QStringList::iterator itMenu = MenuText.begin();
  QStringList::iterator itExt  = Ext.begin();
  for ( ; itText != QtText.end(); )
    {
      if (formatList.contains((*itText)))
	{
	  if (!formats.isEmpty())
	    formats += ";;";
	  formats += (*itMenu);
	  Qtformat[(*itMenu)]  = (*itText);
	  FDFormatString[(*itText)]  = (*itMenu);
	  extension[(*itText)] = (*itExt);
	}
      // Synchronize parsing
      itText++;
      itMenu++;
      itExt++;
    }
}

// Returns false is the user refused to use the filename
bool checkFileName(QString& filename, QWidget* widget, const QString& snapshotFormat_, bool overwrite)
{
  if (filename.isNull())
    return false;

  // Check that extension has been provided
  QFileInfo info(filename);
      
  if (info.extension(false).isEmpty())
    {
      // No extension given. Silently add one
      if (filename.right(1) != ".")
	filename += ".";
      filename += extension[snapshotFormat_];
      info.setFile(filename);
    }
  else if (info.extension(false) != extension[snapshotFormat_])
    {
      // Extension is not appropriate. Propose a modification
      QString modifiedName = info.dirPath() + "/" + info.baseName(true) + "." + extension[snapshotFormat_];
      QFileInfo modifInfo(modifiedName);
      int i=(QMessageBox::warning(widget,"Wrong extension",
				  info.fileName()+" has a wrong extension.\nSave as "+modifInfo.fileName()+" instead ?",
				  QMessageBox::Yes,
				  QMessageBox::No,
				  QMessageBox::Cancel));
      if (i==QMessageBox::Cancel)
	{ return false; }
	  
      if (i==QMessageBox::Yes)
	{
	  filename = modifiedName;
	  info.setFile(filename);
	}
    }
      
  if ((info.exists()) && (!overwrite))
    if (QMessageBox::warning(widget,"Overwrite file ?",
			     "File "+info.fileName()+" already exists.\nSave anyway ?",
			     QMessageBox::Yes,
			     QMessageBox::Cancel) == QMessageBox::Cancel)
      return false;

  return true;
}

#ifndef NO_EPS_RENDER
// static void drawVectorial(void* param)
void drawVectorial(void* param)
{
  ( (QGLViewer*) param )->drawVectorial();
}

// Pops-up an output option dialog box
// Returns EPSRENDER_NO_ERROR or EPSRENDER_OUT_OF_MEMORY or
// EPSRENDER_CANNOT_OPEN_FILE or EPSRENDER_FILENAME_NOT_VALID or
// -1 if action has been canceled
// TODO : add a "remove fps" checkbox
static int saveVectorialSnapshot(const QString& filename, QGLWidget* widget, const QString& snapshotFormat_)
{
  static EPSInterface* interf = NULL;
  if (!interf)
    interf = new EPSInterface(widget);

  // Configure interface according to selected snapshotFormat_
  if (snapshotFormat_ == "XFIG")
    {
      interf->TightenBBCB->setEnabled(false);
      interf->ColorBackgroundCB->setEnabled(false);
    }
  else
    {
      interf->TightenBBCB->setEnabled(true);
      interf->ColorBackgroundCB->setEnabled(true);
    }

#if (!defined(WIN32) && !defined(__APPLE__))
   interf->OptimizeVisibilityCB->setEnabled(true);
#else
   interf->OptimizeVisibilityCB->setEnabled(false);
#endif

  if (interf->exec() == QDialog::Rejected)
    return -1;

  int optimizeVisibility 	= interf->OptimizeVisibilityCB->isChecked() ? EPS_CULL_INVISIBLE_PRIMITIVES: EPS_NO_OPTIMIZATION;
  int whiteBG 			= interf->ColorBackgroundCB->isChecked() ? EPS_CLEAR_BG : EPS_DONT_CLEAR_BG;
  int blackAndWhite 		= interf->BlackAndWhiteCB->isChecked() ? EPS_BLACK_AND_WHITE: EPS_COLOR;
  int tightenBB 		= interf->TightenBBCB->isChecked() ? EPS_TIGHTEN_BBOX: EPS_NORMAL_BB;
  int sortMethod 		= 0;
  switch (interf->SortMethod->currentItem())
    {
    case 0: sortMethod = EPS_DONT_SORT; 	break;
    case 1: sortMethod = EPS_BSP; 		break;
    case 2: sortMethod = EPS_OPTIMIZED_BSP; 	break;
    default:
      qWarning("EPSInterface::saveVectorialSnapshot : Unknown SortMethod");
    }

  int EPSMode = EPS_EPS;
  if (snapshotFormat_ == "EPS")		EPSMode = EPS_EPS;
  if (snapshotFormat_ == "PS")		EPSMode = EPS_PS;
  if (snapshotFormat_ == "XFIG")	EPSMode = EPS_FIG;

  int errorCode = -1;
  static int size = 1024;
  EPSRender(size, sortMethod, filename, 
            // &widget->paintGL, (void *)NULL, 
  	    drawVectorial, (void *)widget, 
	    errorCode,
	    blackAndWhite,
 	    EPSMode,
	    optimizeVisibility,
	    whiteBG,
	    tightenBB);
  return errorCode;
}
#endif // NO_EPS_RENDER

/*! Saves a snapshot of the current image displayed by the widget. If no snapshot filename is defined
  (see snapshotFilename()) or if \p automatic is \c false, a file dialog is opened to ask for the
  filename.

  Saving formats are those available in the Qt installation, plus some vectorial formats (EPS, PS,
  XFIG). See setSnapshotFormat().

  Some artifacts may appear when displaying the PS and EPS result. Simply remove the anti-alias
  option in ghostview to get the correct display. Printed output will be fine. The libEPSRender
  library was written by Cyril Soler (Cyril.Soler@imag.fr).
  
  When \p automatic is \c true (default is \c false), the filename is set to \c NAME-NUMBER, where
  \c NAME is snapshotFilename() and \c NUMBER is snapshotCounter(). The snapshotCounter() is
  incremented. This is useful to create videos from your application:
  \code
  init() { resize(720, 576); } // PAL DV format (use 720x480 for NTSC DV)

  draw() {
    scene.draw();
    
    if (makeMovie)
      saveSnapshot(true, true); // Warning, overwrite mode
  }
  \endcode
  Then call draw() in a loop (for instance using animate() and/or a camera() KeyFrameInterpolator
  replay) to create your image sequence.

  If you want to create a Quicktime VR panoramic sequence, simply use code like this:
  \code
  void Viewer::createQuicktime()
  {
    const int nbImages = 36;
    for (int i=0; i<nbImages; ++i)
      {
        camera()->setOrientation(2.0*M_PI/nbImages, 0.0); // Theta-Phi orientation
        showEntireScene();
        updateGL();  // calls draw(), which saveSnapshot() as above
      }
  }
  \endcode

  When \p overwrite is set to false (default), a pop-up window asks for confirmation (when \p
  automatic is \c false) or the snapshotCounter() is incremented until a non-existing file name is
  found (when \p automatic is \c true). */
void QGLViewer::saveSnapshot(bool automatic, bool overwrite)
{
  if (formats.isEmpty())
    createFormatList();

  // We save snapshot BEFORE all the rest, because X11 is lost otherwise, especially
  // with remote display.  
  static QImage snapshot;
  snapshot = grabFrameBuffer(true); 

  // Ask for file name
  if (snapshotFilename().isEmpty() || !automatic)
    {
      QString selectedFormat = FDFormatString[snapshotFormat_];
      QString filename = QFileDialog::getSaveFileName(snapshotFilename(), formats,
						      this, "Save Snapshot dialog",
						      "Choose a file", &selectedFormat);
      snapshotFormat_ = Qtformat[selectedFormat];
      
      if (checkFileName(filename, this, snapshotFormat_, overwrite))
	setSnapshotFilename(filename);
      else
	return;
    }

  // Determine file name in automatic mode
  QFileInfo final(snapshotFilename());

  if (final.extension().isEmpty())
    final.setFile(final.filePath() + "." + extension[snapshotFormat_]);

  // In automatic mode, names have a number appended
  if (automatic)
    {
      const QString baseName = final.baseName();
      QString count;
      count.sprintf("%.04d", snapshotCounter_++); 
      final.setFile(final.dirPath()+"/" + baseName + "-" + count + "." + final.extension());

      if (!overwrite)
	while (final.exists())
	  {
	    count.sprintf("%.04d", snapshotCounter_++); 
	    final.setFile(final.dirPath() + "/"+baseName + "-" + count + "." + final.extension());
	  }
    }

  bool saveOK;
#ifndef NO_EPS_RENDER
  if ( (snapshotFormat_ == "EPS") || (snapshotFormat_ == "PS") || (snapshotFormat_ == "XFIG") )
    {
      // Vectorial snapshot
      int res = saveVectorialSnapshot(final.filePath(), this, snapshotFormat_);
      if (res == -1) // CANCEL
	return;
      else
	saveOK = (res == EPSRENDER_NO_ERROR) ? true : false;
    }
  else
#endif
    saveOK = snapshot.save(final.filePath(), snapshotFormat_);

  if (saveOK)
    {
      if (!automatic)
	if ( (snapshotFormat_ == "EPS") || (snapshotFormat_ == "PS") || (snapshotFormat_ == "XFIG") )
	  QMessageBox::information(this, "Snapshot saved", "Snapshot successfully saved in\n"+final.filePath());
    }
  else
    QMessageBox::warning(this, "Snapshot problem", "Unable to save snapshot in\n"+final.filePath());
}


#endif // QT_VERSION < 300
