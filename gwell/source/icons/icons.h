///////////////////////////////////////////////////////////////////////////////////
///
//////////////////////     IKONY
#ifndef ICONS_H
#define ICONS_H

#include <qimage.h>

class Icons
{
  public:
    static const char** hierIcon();
    static const char** showAllSceneIcon();
    static const char** pyramidIcon();
    static const char** colorsIcon();
    static const char** textureIcon();
    static const char** coneIcon();
    static const char** asPathsIcon();
    static const char** asTreeIcon();

    static const char** undoIcon();
    static const char** selectIcon();
    static const char** moveIcon();
    static const char** rotateIcon();
    static const char** scaleIcon();
    static const char** transTextIcon();    
    static const char** rotateTextIcon();
    static const char** scaleTextIcon();
    static const char** linkIcon();
    
    static const QImage* transLightIcon();
    static const QImage* dirLightIcon();
    
    static const char** newIcon();
    static const char** openIcon();    
    static const char** saveIcon();
    static const char** exitIcon();
                
    static const char** primitivesIcon();

    static const char** cameraIcon();
    static const char** gridIcon();
    static const char** axisIcon();
    static const char** wireIcon();
    static const char** solidIcon();
    static const char** texturedIcon();
    static const char** fotoIcon();
    static const char** ballIcon();
    static const char** appleGreenIcon();
    static const QImage* appleRedIcon();
    
    static const QImage* bulbIcon();
    static const QImage* spotIcon();
    static const QImage* addIcon();
    static const QImage* deleteIcon();
    
    static const QImage* copyIcon();
    static const QImage* pasteIcon();
    static const QImage* cutIcon();
    static const QImage* transCoordsIcon();
    static const QImage* rotCoordsIcon();

  private:
    static const char* const hier_data[];
    static const char* const showAllScene_data[];
    static const char* const pyramid_data[];
    static const char* const colors_data[];
    static const char* const texture_data[];
    static const char* const cone_data[];
    static const char* const asPaths_data[];
    static const char* const asTree_data[];    
    static const char* const undo_data[];
    static const char* const move_data[];
    static const char* const rotate_data[];
    static const char* const scale_data[];
    static const char* const primitives_data[];
    static const char* const open_data[];
    static const char* const scaleText_data[];
    static const char* const rotateText_data[];
    static const char* const transText_data[];
    static const char* const link_data[];    
    static const char* const select_data[];
    static const char* const new_data[];
    static const char* const camera_data[];
    static const char* const grid_data[];
    static const char* const axis_data[];
    static const char* const wire_data[];
    static const char* const solid_data[];
    static const char* const textured_data[];
    static const char* const exit_data[];
    static const char* const foto_data[];
    static const char* const ball_data[];
    static const char* const save_data[];
    static const char* const apple_data[];
};



#endif
