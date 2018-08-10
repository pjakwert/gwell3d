//////////////////////////////////////////////////////////////////
///
///  class: CellFrame (.h)
///
///  okno edycyjne aplikacji
///
//////////////////////////////////////////////////////////////////

#ifndef CELLFRAME_H
#define CELLFRAME_H

#include <qwidget.h>
#include <qcolor.h>
#include <qlayout.h>
#include <qcursor.h>
#include <qptrlist.h>
#include <qsplitter.h>
#include <qobjectlist.h>
#include <qpopupmenu.h>

#include <math.h>

#include <startwidget.h>
#include <cellwidget.h>
#include <modifiers.h>
#include <light.h>
#include <options.h>
#include <fogwidget.h>
#include <kineditorro.h>

#define INFI 100


class CellFrame : public QGLViewer
{
  Q_OBJECT

  public:
    CellFrame (QWidget *parent, const char *name = 0, QGLWidget *shareWidget=0, WFlags f = 0);
    ~CellFrame() {}
    bool cameraIsMoving() { return _cameraIsMoving; }
    bool lightsAreDrawn() { return _lightsAreDrawn; }
    static void refresh();
    static QPtrList<ViMultiPolyh>* selected();
    static QPtrList<Light>* lightsList() { return _lightsList; }
    static ViScene* scene();
    static void computeScene() { _scene->ComputeGlbVtx(); }
    static bool sceneIsEmpty();
    
    static void setScene( ViScene *scene );
    static void setSelected( QPtrList<ViMultiPolyh> *selectedList );
    static void setLightsList( QPtrList<Light> *lightsList );
    static void setModifier( MModifier *modifier );
    
    static void deleteSelectedObjects();
    
  private:
    static ViScene                    *_scene;  // obiekt zlozony do wyswietlania
    static QPtrList<ViMultiPolyh>     *_selectedList;
    static MModifier                  *_modifier;
    static QPtrList<Light>            *_lightsList;
    static QPtrList<ViMultiPolyh>  nameList; // przechowuje wskazniki do obiektow i odpowiadajace im numery
    QPtrList<ViElemePolyhExt> blendedList; // lista obiektów z przezroczysto¶ci± do posortowania i  narysowania
    bool sortBlendedList();

    static const GLfloat no_material[];    // pusty wektor materia³u dla OpenGL (do resetowania)
    static const GLfloat no_shininess[];   // pusta jasno¶æ - wektor 1-elementowy
    static const GLfloat white_material[]; // materia³ o max jasno¶ci - idealny dla tekstur

    StartWidget *startWidget;  // widgety odpowiadajace za gorne menu
    CellWidget  *cellWidget;
    QPopupMenu  *popupMenu;
    QHBoxLayout *hbox;

    QString _info; // informacje wyswietlane w cellFrame
    DrawMethod  _drawMethod;
    bool    _boxesAreDrawn;
    bool    _fogEnabled;
    bool    _fpsDisplayed;
    bool    _gridIsDrawn;
    bool    _grid3DIsDrawn;
    bool    _axisIsDrawn;
    bool    _lightsAreDrawn;
    bool    _cameraIsMoving;
    int     _infoPosX;
    int     _infoPosY;

    void drawGridXZ();
    void drawGrid3D();
    void drawBoxes();
    void drawElemAxis( ViElemePolyhExt* extEl );
    void setShowFPS( bool on );
    void drawLightShape( Light* light, float scale = 1.0f );
    void drawScene( bool pushID = false );
    void drawWired   ( ViElemePolyhExt* elem, bool isSelected=false );
    void drawSolid   ( ViElemePolyhExt* elem, bool isSelected=false );
    void drawTextured( ViElemePolyhExt* elem, bool isSelected=false );
    void drawInfo();
    void setInfo( QString s, int x=-1, int y=-1 );

    static GLuint _cubeDL;
    static GLuint _squareDL;
    static GLuint _hLineDL;
    static GLuint _vLineDL;
    static void createDL(); // tworzy DisplayList dla Boxa
    void drawCube() { glCallList( _cubeDL ); }
    
    void castShadow( ViElemePolyhExt* elem, const GLfloat* lightPosition );
    void doShadowPass( ViElemePolyhExt* elem, const GLfloat* lightPosition );
    void castShadows();
    
  private slots:
    void popupAboutToShow();
    void choosedFromPopup( int );
    
  protected:
    virtual void init();
    virtual void draw();
    virtual void select(const QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void enterEvent(QEvent*);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void mouseDoubleClickEvent(QMouseEvent *);

  public slots:
    void setLight( Light* light );
    void setAllLights();
    void turnAllLights( bool on );
    void updateColorForLight( GLenum GLcolorChanged, Light* light );
    
    void setFog( FogStruct*, FogParamsEnum );
            
    void selectAll();
    void setSelectedSlot( QPtrList<ViMultiPolyh> *selectedList );
    void setCameraMoving( bool on );
    void setCameraType( qglviewer::Camera::Type type );
    void setDrawMethod( DrawMethod drawMethod );
    void showAllScene();
    void setViewDirection( int direction ); // direction jest jednym z predefiniowanych kierunkow
    void setDrawAxisXYZ( bool on );
    void setDrawGridXZ( bool on );
    void setDrawGrid3D( bool on );
    void setDrawBoxes( bool on );
    void setDrawLights( bool on );
    void maximize();

  signals:
    void setModifierFromCellFrame( MModifier::ModifierType mType );
    void userSelected( QPtrList<ViMultiPolyh> *selectedList );
};




#endif
