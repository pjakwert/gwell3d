TEMPLATE = app
DEPENDPATH += dialogs ../icons modifiers toolwidgets ../vi-kernel ../qwt ../common
INCLUDEPATH += . modifiers dialogs ../icons ../vi-kernel toolwidgets ../qwt ../common
LIBS += -lQGLViewer

TARGET = ../../bin/modeler

UI_DIR = ui
OBJECTS_DIR = obj
MOC_DIR = moc

TRANSLATIONS = ../../languages/modeler_lang_pl.ts
DEFAULTCODEC = ISO-8859-2

# Input
HEADERS += cellframe.h \
           cellwidget.h \
           const.h \
           kernel.h \
           light.h \
           material.h \
           options.h \
           startwidget.h \
           statusbar.h \
           helpstring.h \
           tabs.h \
           texture.h \
           toolbar.h \
           vielemepolyhext.h \
           gwellinterface.h \
           workspace.h \
           dialogs/colorwidget.h \
           dialogs/floatspinbox.h \
           dialogs/hierlistviewitem.h \
           dialogs/imagepreview.h \
           dialogs/materialeditor.h \
           dialogs/materialwidget.h \
           dialogs/namedialog.h \
           dialogs/shinewidget.h \
           dialogs/texturemanager.h \
           dialogs/textureparams.h \
           dialogs/texturewidget.h \
           dialogs/kineditor.h \
           dialogs/table.h \
           dialogs/knob.h \
           ../icons/add_icon.h \
           ../icons/apple_icon.h \
           ../icons/apple_red_icon.h \
           ../icons/aspaths_icon.h \
           ../icons/astree_icon.h \
           ../icons/axis_icon.h \
           ../icons/ball_icon.h \
           ../icons/bulb_icon.h \
           ../icons/camera_icon.h \
           ../icons/colors_icon.h \
           ../icons/cone_icon.h \
           ../icons/delete_icon.h \
           ../icons/exit_icon.h \
           ../icons/foto_icon.h \
           ../icons/grid_icon.h \
           ../icons/hier_icon.h \
           ../icons/icons.h \
           ../icons/link_icon.h \
           ../icons/move_icon.h \
           ../icons/new_icon.h \
           ../icons/open_icon.h \
           ../icons/primitives_icon.h \
           ../icons/pyramid_icon.h \
           ../icons/rotate_icon.h \
           ../icons/rotatetext_icon.h \
           ../icons/translight_icon.h \
           ../icons/dirlight_icon.h \
           ../icons/save_icon.h \
           ../icons/scale_icon.h \
           ../icons/scaletext_icon.h \
           ../icons/select_icon.h \
           ../icons/showallscene_icon.h \
           ../icons/solid_icon.h \
           ../icons/spot_icon.h \
           ../icons/texture_icon.h \
           ../icons/textured_icon.h \
           ../icons/transtext_icon.h \
           ../icons/undo_icon.h \
           ../icons/wire_icon.h \
           ../icons/copy_icon.h \
           ../icons/paste_icon.h \
           ../icons/cut_icon.h \
           ../icons/transcoords_icon.h \
           ../icons/rotcoords_icon.h \
           modifiers/m_link.h \
           modifiers/m_rot.h \
           modifiers/m_rotcoords.h \
           modifiers/m_scale.h \
           modifiers/m_select.h \
           modifiers/m_trans.h \
           modifiers/m_transcoords.h \
           modifiers/m_translightdir.h \
           modifiers/m_translightpos.h \
           modifiers/modifier.h \
           modifiers/modifiers.h \
           toolwidgets/drawwidget.h \
           toolwidgets/glmphmenu.h \
           toolwidgets/glmphmenuitem.h \
           toolwidgets/filewidget.h \
           toolwidgets/glmenu.h \
           toolwidgets/glmenuitem.h \
           toolwidgets/lightstablewidget.h \
           toolwidgets/lightswidget.h \
           toolwidgets/modifywidget.h \
           toolwidgets/nodotvalidator.h \
           toolwidgets/objectswidget.h \
           toolwidgets/optionswidget.h \
           toolwidgets/helpwidget.h \
           toolwidgets/mphpreview.h \
           toolwidgets/listview.h \
           ../common/tools.h \
           ../vi-kernel/angle.hh \
           ../vi-kernel/baseiterator.hh \
            ../vi-kernel/bexception.hh \
            ../vi-kernel/bindanonpair.hh \
            ../vi-kernel/bindpair-methods.hh \
            ../vi-kernel/bindpair.hh \
            ../vi-kernel/chaintableiterator.hh \
            ../vi-kernel/diretableiterator.hh \
            ../vi-kernel/extstring.hh \
            ../vi-kernel/halfline3f.hh \
            ../vi-kernel/inditableiterator.hh \
            ../vi-kernel/line3f.hh \
            ../vi-kernel/listque.hh \
            ../vi-kernel/matrixh3f.hh \
            ../vi-kernel/matrixrt3f.hh \
            ../vi-kernel/outlinebox3.hh \
            ../vi-kernel/outlinebox3f.hh \
            ../vi-kernel/plain3f.hh \
            ../vi-kernel/sgn.hh \
            ../vi-kernel/streamutils.hh \
            ../vi-kernel/strprintf.hh \
            ../vi-kernel/sxinterp.hh \
            ../vi-kernel/syntax-new.hh \
            ../vi-kernel/twostageiter.hh \
            ../vi-kernel/vector3.hh \
            ../vi-kernel/vector3f.hh \
            ../vi-kernel/vi-keywords.hh \
            ../vi-kernel/vi-laserbeam.hh \
            ../vi-kernel/vi-listid.hh \
            ../vi-kernel/vi-readmultipolyh.hh \
            ../vi-kernel/vi-readpattepolyhlib.hh \
            ../vi-kernel/vi-sxutils.hh \
            ../vi-kernel/vi-utils.hh \
            ../vi-kernel/viedge.hh \
            ../vi-kernel/viedgeiterator.hh \
            ../vi-kernel/vielemepolyh.hh \
            ../vi-kernel/vielemepolyhedge.hh \
            ../vi-kernel/vielemepolyhface.hh \
            ../vi-kernel/vielemepolyhfaceedge.hh \
            ../vi-kernel/vierrors.hh \
            ../vi-kernel/viexception.hh \
            ../vi-kernel/viface.hh \
            ../vi-kernel/vifaceedge.hh \
            ../vi-kernel/vihierarchyline.hh \
            ../vi-kernel/vikinemctrl.hh \
            ../vi-kernel/vimatrix3f.hh \
            ../vi-kernel/vimultipolyh.hh \
            ../vi-kernel/vinodeaddress.hh \
            ../vi-kernel/vinodedescr.hh \
            ../vi-kernel/vintreenode.hh \
            ../vi-kernel/vipatteaddress.hh \
            ../vi-kernel/vipatteliblist.hh \
            ../vi-kernel/vipattepolyh.hh \
            ../vi-kernel/vipattepolyhlib.hh \
            ../vi-kernel/viscene.hh \
            ../vi-kernel/viscenepolyhlist.hh \
            ../vi-kernel/visynxinterp.hh \
            ../vi-kernel/vitriangle3.hh \
            ../vi-kernel/vitriangle3f.hh \
            ../vi-kernel/vivalidflags.hh \
           ../qwt/qwt_dimap.h \
           ../qwt/qwt_global.h \
           ../qwt/qwt_math.h \
           ../qwt/qwt_scldraw.h \
           ../qwt/qwt_sldbase.h \
           ../qwt/qwt_drange.h \
           ../qwt/qwt_knob.h \
           ../qwt/qwt_scldiv.h \
           ../qwt/qwt_sclif.h
SOURCES += cellframe.cpp \
           cellwidget.cpp \
           kernel.cpp \
           light.cpp \
           main.cpp \
           material.cpp \
           options.cpp \
           startwidget.cpp \
           statusbar.cpp \
           tabs.cpp \
           texture.cpp \
           toolbar.cpp \
           vielemepolyhext.cpp \
           gwellinterface.cpp \
           workspace.cpp \
           dialogs/colorwidget.cpp \
           dialogs/floatspinbox.cpp \
           dialogs/hierlistviewitem.cpp \
           dialogs/imagepreview.cpp \
           dialogs/materialeditor.cpp \
           dialogs/materialwidget.cpp \
           dialogs/namedialog.cpp \
           dialogs/shinewidget.cpp \
           dialogs/texturemanager.cpp \
           dialogs/textureparams.cpp \
           dialogs/texturewidget.cpp \
           dialogs/kineditor.cpp \
           dialogs/table.cpp \
           dialogs/knob.cpp \
           ../common/tools.cpp \
           ../icons/icons.cpp \
           modifiers/m_link.cpp \
           modifiers/m_rot.cpp \
           modifiers/m_rotcoords.cpp \
           modifiers/m_scale.cpp \
           modifiers/m_select.cpp \
           modifiers/m_trans.cpp \
           modifiers/m_transcoords.cpp \
           modifiers/m_translightdir.cpp \
           modifiers/m_translightpos.cpp \
           modifiers/modifier.cpp \
           toolwidgets/drawwidget.cpp \
           toolwidgets/glmphmenu.cpp \
           toolwidgets/glmphmenuitem.cpp \
           toolwidgets/filewidget.cpp \
           toolwidgets/glmenu.cpp \
           toolwidgets/glmenuitem.cpp \
           toolwidgets/lightstablewidget.cpp \
           toolwidgets/lightswidget.cpp \
           toolwidgets/modifywidget.cpp \
           toolwidgets/nodotvalidator.cpp \
           toolwidgets/objectswidget.cpp \
           toolwidgets/optionswidget.cpp \
           toolwidgets/helpwidget.cpp \
           toolwidgets/mphpreview.cpp \
           toolwidgets/listview.cpp \
           ../vi-kernel/bexception.cpp \
            ../vi-kernel/extstring.cpp \
            ../vi-kernel/getmsg.cpp \
            ../vi-kernel/halfline3f.cpp \
            ../vi-kernel/line3f.cpp \
            ../vi-kernel/matrixh3f.cpp \
            ../vi-kernel/matrixrt3f.cpp \
            ../vi-kernel/outlinebox3f.cpp \
            ../vi-kernel/plain3f.cpp \
            ../vi-kernel/streamutils.cpp \
            ../vi-kernel/strprintf.cpp \
            ../vi-kernel/sxinterp.cpp \
            ../vi-kernel/syntax-new.cpp \
            ../vi-kernel/syntax.cpp \
            ../vi-kernel/utils.cpp \
            ../vi-kernel/vi-laserbeam.cpp \
            ../vi-kernel/vi-sxutils.cpp \
            ../vi-kernel/viedge.cpp \
            ../vi-kernel/viedgeiterator.cpp \
            ../vi-kernel/vielemepolyh.cpp \
            ../vi-kernel/vielemepolyhedge.cpp \
            ../vi-kernel/vielemepolyhface.cpp \
            ../vi-kernel/vielemepolyhfaceedge.cpp \
            ../vi-kernel/viface.cpp \
            ../vi-kernel/vifaceedge.cpp \
            ../vi-kernel/vikinemctrl.cpp \
            ../vi-kernel/vimultipolyh.cpp \
            ../vi-kernel/vinodeaddress.cpp \
            ../vi-kernel/vinodedescr.cpp \
            ../vi-kernel/vintreenode.cpp \
            ../vi-kernel/vipatteaddress.cpp \
            ../vi-kernel/vipatteliblist.cpp \
            ../vi-kernel/vipattepolyh.cpp \
            ../vi-kernel/vipattepolyhlib.cpp \
            ../vi-kernel/viscene.cpp \
            ../vi-kernel/viscenepolyhlist.cpp \
            ../vi-kernel/visynxinterp.cpp \
            ../vi-kernel/hide/vi-readmultipolyh.cpp \
            ../vi-kernel/hide/vi-readpattepolyhlib.cpp \
           ../qwt/qwt_dimap.cpp \
           ../qwt/qwt_math.cpp \
           ../qwt/qwt_scldraw.cpp \
           ../qwt/qwt_sldbase.cpp \
           ../qwt/qwt_drange.cpp \
           ../qwt/qwt_knob.cpp \
           ../qwt/qwt_scldiv.cpp \
           ../qwt/qwt_sclif.cpp
