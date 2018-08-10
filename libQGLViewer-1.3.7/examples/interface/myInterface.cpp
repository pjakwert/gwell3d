/****************************************************************************
** Form implementation generated from reading ui file 'myInterface.ui'
**
** Created: Tue Sep 23 12:38:27 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "myInterface.h"

#include <qvariant.h>
#include <qcheckbox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "interface.h"
static const char* const image0_data[] = { 
"22 22 203 2",
"Qt c None",
".f c #292c10",
".b c #293010",
".c c #293018",
".a c #313018",
"a3 c #313429",
"b# c #313820",
".W c #393829",
"#I c #393831",
"bi c #393c20",
"bg c #393c29",
"#o c #393c31",
"bf c #394020",
"bh c #394029",
"## c #413c31",
"#A c #413c39",
".D c #414431",
".E c #414818",
".# c #414820",
".n c #414839",
".d c #414c20",
"#S c #4a4839",
"#. c #4a4841",
"a4 c #4a4c39",
".V c #4a4c41",
"#n c #525541",
".U c #52554a",
"be c #525d20",
"b. c #525d29",
"#z c #5a554a",
".9 c #5a594a",
".C c #5a5952",
"#H c #5a5d41",
"#u c #5a5d4a",
"#t c #5a5d52",
"#0 c #5a614a",
".T c #5a6152",
"#8 c #625d52",
"aX c #626152",
"#m c #62654a",
"aD c #626552",
"aN c #62694a",
"aF c #626952",
".S c #62695a",
".o c #626d29",
".e c #626d31",
"#E c #626d41",
"ar c #626d4a",
"bd c #627129",
".m c #6a695a",
"af c #6a6d4a",
".8 c #6a6d52",
".R c #6a6d62",
"an c #6a7141",
"ae c #6a714a",
"a5 c #6a7531",
"#9 c #6a7541",
"a2 c #6a7920",
"aq c #737552",
"#s c #737939",
"#1 c #737941",
"aj c #737952",
"aJ c #737d31",
"#M c #737d39",
"ba c #738120",
"az c #738129",
"#R c #738131",
"bc c #738520",
"a7 c #738529",
".B c #7b7973",
".A c #7b7d73",
".H c #7b8173",
"aU c #7b8531",
"#7 c #7b8539",
"aV c #7b8939",
".Q c #7b8941",
"a9 c #7b8d20",
"#y c #7b8d31",
".z c #83817b",
"aa c #838562",
".l c #83857b",
"aK c #838962",
".y c #83896a",
"aT c #838d31",
"#v c #839139",
"aY c #839529",
"aO c #839541",
"#2 c #839920",
"aS c #839931",
"aW c #839d20",
"#a c #8b8983",
"#4 c #8b8d73",
".g c #8b8d83",
".k c #8b9183",
"#F c #8b9952",
"#h c #8ba120",
"bb c #8ba518",
"#f c #8ba520",
"#g c #8ba529",
"#l c #8baa18",
"a1 c #8bae08",
"a8 c #8bae10",
".p c #949183",
".j c #94918b",
".h c #94958b",
".x c #94996a",
"a6 c #94a520",
"#i c #94a529",
".7 c #94aa20",
"ax c #94aa29",
"aG c #94aa39",
"aR c #94ae18",
"ag c #94b210",
"#D c #94b218",
".G c #9c9994",
".s c #9c9d8b",
".r c #9c9d94",
".i c #9c9d9c",
"#V c #9ca17b",
"#N c #9ca573",
"aC c #9cae41",
"#3 c #9cb220",
"a# c #9cb229",
".P c #9cb239",
"a0 c #9cb610",
"#r c #9cb618",
"aZ c #9cba08",
"aI c #9cba10",
"a. c #9cba18",
"aM c #9cba20",
"aQ c #9cbe08",
"#Q c #9cbe10",
"#G c #9cc210",
".X c #a4a194",
"#b c #a4a594",
"aA c #a4b262",
"aE c #a4ba39",
"ay c #a4be10",
"#j c #a4be31",
"#x c #a4c210",
"av c #a4c239",
".6 c #a4c610",
"#L c #a4c618",
".F c #acaea4",
".q c #acaeac",
"#B c #acb294",
"ai c #acbe4a",
".w c #acbe6a",
"am c #acc239",
"#w c #acc610",
"aL c #acc629",
"ad c #acc639",
"#q c #acca20",
"#Z c #acca29",
"aP c #acce29",
"#e c #acce31",
".O c #b4ca41",
"as c #b4ca5a",
"#k c #b4ce29",
".2 c #b4ce31",
"aw c #b4ce39",
"aH c #b4ce4a",
"ap c #b4ce52",
".3 c #b4d239",
".4 c #b4d241",
".v c #bdca7b",
"ao c #bdce62",
".5 c #bdd241",
".1 c #bdd24a",
"au c #bdd252",
"aB c #bdd64a",
"#U c #bdd652",
"#Y c #bdd65a",
".t c #c5caa4",
".u c #c5ce8b",
".I c #c5ceac",
".N c #c5d65a",
"at c #c5d662",
"ah c #c5d67b",
"#P c #c5da5a",
".M c #c5da62",
".0 c #c5da6a",
"#K c #c5de6a",
".L c #cdde7b",
"#T c #cdde8b",
"#O c #cde27b",
"al c #cde283",
"#J c #d5daa4",
"#p c #d5e283",
"#d c #d5e28b",
"ab c #d5e2a4",
"#X c #d5e68b",
".K c #d5e694",
"#5 c #dee2b4",
"ak c #dee694",
"#C c #dee69c",
".J c #dee6ac",
".Z c #deeaa4",
"#W c #deeaac",
"ac c #e6eaac",
"#c c #e6eabd",
"#6 c #e6eeac",
".Y c #eeeec5",
"QtQtQt.#.a.b.c.b.a.b.c.b.a.b.c.b.a.b.dQtQtQt",
"Qt.e.f.g.h.i.h.j.k.j.k.j.k.j.g.g.l.m.n.b.oQt",
"Qt.b.p.q.r.g.p.s.t.u.v.w.x.y.z.A.B.m.C.D.cQt",
".E.g.F.G.H.s.I.J.K.L.M.N.O.P.Q.R.S.T.U.V.W.#",
".a.h.r.z.X.Y.Z.0.1.2.3.4.5.2.6.7.8.9.9#.##.b",
".f.i#a#b#c#d#e.6#f#g#h#i#j#k.6.6#l#m#n.V#o.c",
".c.h.X#c#p#q#r#s#t#u#t#u#m#v#w#x#x#y#z#.#A.b",
".f.j#B#C.2#D#E#t.9#t.9#F.Q#t#y#x#G#r#H#.#I.b",
".a.j#J#K#L#M#t#u#t#u#N#O#P.Q#t#f.6#Q#R#S#A.b",
".f.j#T#U#D#t.9#t.9#V#W#X#Y#Z#0#1#G#x#2#.#I.c",
".c.j#d.1#3#u#t#u#4#5#6.L.1#7#8#9#x#Qa.#.#o.b",
".f.j.L#Pa##t.9aaabac#d.Madae.9af#D#xag#.#I.b",
".a.jah.Mai#uaj.Lakal.0.5.3amaean.6#Q.7#S#A.b",
".f.jao.Mapaqarasatauavaw.4.1avax#Gayaz#.#I.c",
".c.kaA.1aBaCaDaeaE.QaFaGaH.5.2#x#xaIaJ#.#o.b",
".f.gaKaL#q#qaMaN.9#t.9#taOaP#x#xaQaR#H#.#I.b",
".a.l.BaS.6#x.6a.aTaUaV#7ax#x#x#QayagaW#S#I.b",
".f.m.SaXaY#x#G#x#G.6#G#x#QayaZaIaIa0a1a2a3.c",
".da4.C.U.9a5a6#Q#x#Q#x#Q#QaI#ha7a0a8a9b.b#.#",
"Qt.b.D.V#S.V#S.eba#lbbbbbc.ea4#.bda9bebf.fQt",
"Qt.o.cbg###o#A#o#A#o#o#o#A#o#o#I#Ibhbi.b.dQt",
"QtQtQt.#.f.c.f.b.f.c.f.b.f.c.f.b.f.c.EQtQtQt"};


/* 
 *  Constructs a myInterface which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
myInterface::myInterface( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    QPixmap image0( ( const char** ) image0_data );
    if ( !name )
	setName( "Form1" );
    resize( 673, 438 ); 
    setCaption( trUtf8( "Form1" ) );
    Form1Layout = new QGridLayout( this, 1, 1, 6, 2, "Form1Layout"); 

    Viewer1 = new Viewer( this, "Viewer1" );

    Form1Layout->addMultiCellWidget( Viewer1, 0, 0, 0, 5 );

    CheckBox1 = new QCheckBox( this, "CheckBox1" );
    CheckBox1->setText( trUtf8( "FPS" ) );

    Form1Layout->addWidget( CheckBox1, 1, 0 );

    CheckBox3 = new QCheckBox( this, "CheckBox3" );
    CheckBox3->setText( trUtf8( "Axis" ) );

    Form1Layout->addWidget( CheckBox3, 1, 2 );

    PushButton1 = new QPushButton( this, "PushButton1" );
    PushButton1->setText( trUtf8( "Quit" ) );

    Form1Layout->addWidget( PushButton1, 1, 5 );

    CheckBox2 = new QCheckBox( this, "CheckBox2" );
    CheckBox2->setText( trUtf8( "Grid" ) );

    Form1Layout->addWidget( CheckBox2, 1, 1 );

    // signals and slots connections
    connect( CheckBox1, SIGNAL( toggled(bool) ), Viewer1, SLOT( setDisplayFPS(bool) ) );
    connect( CheckBox2, SIGNAL( toggled(bool) ), Viewer1, SLOT( setDrawGrid(bool) ) );
    connect( CheckBox3, SIGNAL( toggled(bool) ), Viewer1, SLOT( setDrawAxis(bool) ) );
    connect( Viewer1, SIGNAL(  axisDrawn(bool)  ), CheckBox3, SLOT( setChecked(bool) ) );
    connect( Viewer1, SIGNAL(  gridDrawn(bool)  ), CheckBox2, SLOT( setChecked(bool) ) );
    connect( Viewer1, SIGNAL(  fpsDisplayed(bool)  ), CheckBox1, SLOT( setChecked(bool) ) );
    connect( PushButton1, SIGNAL( released() ), this, SLOT( close() ) );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
myInterface::~myInterface()
{
    // no need to delete child widgets, Qt does it all for us
}

