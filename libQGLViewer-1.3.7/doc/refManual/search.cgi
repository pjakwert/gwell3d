#!/bin/sh
DOXYSEARCH=/disc/www/scripts/DOXYGEN/doxysearch
DOXYPATH=/disc/www/IMAGIS/Membres/Gilles.Debunne/CODE/QGLViewer/refManual 
if [ -f $DOXYSEARCH ]
then
  $DOXYSEARCH $DOXYPATH
else
  echo "Content-Type: text/html"
  echo ""
  echo "<h2>Error: $DOXYSEARCH not found. Check cgi script!</h2>"
fi
