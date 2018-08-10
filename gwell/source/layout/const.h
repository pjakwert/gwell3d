///////////////////////////////////////////////////////////////////////
//
//    const (.h)
//
//    Plik naglowkowy zawierajacy stale i typy uzywane w calej aplikacji.
//
///////////////////////////////////////////////////////////////////////
#ifndef CONST_H
#define CONST_H


#define APPNAME "Gwell Layout"
#define APPDESCRIPTION "Graphical Workshop for modelling and simulating robot environments"
// wersja
#define VERSION 0.18092004

#define PI 3.14159265358979

// typ wyliczeniowy dla metod rysowania bry³
typedef enum { Wire=0, Solid=1, Textured=2 } DrawMethod;

// typ wyliczeniowy dla parametrów mg³y
typedef enum { FogEnabled=0, FogMode=1, FogDensity, FogStart, FogEnd, FogColor, FogAll } FogParamsEnum;




// numery identyfikujace i laczace poszczegolne zakladki (tabs.h) z widgetami w lewym menu (widgetstack.h)
#define FILE_TAB_ID    0
#define DRAW_TAB_ID    1
#define MODIFY_TAB_ID  2
#define OBJECTS_TAB_ID 3
#define LIGHTS_TAB_ID  4
#define FOG_TAB_ID     5
#define OPTIONS_TAB_ID 6
#define HELP_TAB_ID    7




// nazwy elementów i atrybutów materia³u w zapisie/odczycie materia³u do/z pliku XML
  // g³ówny element dokumentu XML
#define ELEMENT_PROPERTIES      "ElementProperties"
  // nazwa g³ównej sekcji materia³u
#define MATERIAL_MAIN           "Material"
  // nazwy atrybutów g³ównej sekcji
#define ATTR_MATERIAL_NAME      "materialName"
#define ATTR_MATERIAL_ENABLED   "materialEnabled"
#define ATTR_APPLY_MATERIAL_TO  "applyMaterialTo"
  // nazwy elementów
#define ELEM_AMBIENT_COLOR      "ambientColor"
#define ELEM_DIFFUSE_COLOR      "diffuseColor"
#define ELEM_SPECULAR_COLOR     "specularColor"
#define ELEM_EMISSION_COLOR     "emissionColor"
#define ELEM_SHININESS          "shininess"
  // nazwy atrybutów elementów
#define ATTR_RED                "red"
#define ATTR_GREEN              "green"
#define ATTR_BLUE               "blue"
#define ATTR_ALPHA              "alpha"
#define ATTR_SHININESS          "shininess"

// nazwy elementów i atrybutów materia³u w zapisie/odczycie tekstury do/z pliku XML
  // nazwa g³ównej sekcji
#define TEXTURE_MAIN           "Texture"
#define ATTR_TEXTURE_ENABLED   "textureEnabled"
#define ATTR_TEXTURE_REFLECT   "reflectingEnabled"

#define ELEM_IMAGE_PARAMS      "imageParameters"
#define ATTR_IMAGE_FILENAME    "fileName"
#define ATTR_IMAGE_SCALEMODE   "scaleMode"
#define ATTR_IMAGE_MIPMAPING   "mipmapingEnabled"

#define ELEM_FILTERING         "textureFiltering"
#define ATTR_FILTER_MAG        "magFilter"
#define ATTR_FILTER_MIN        "minFilter"
#define ATTR_FILTER_WRAPS      "wrapSFilter"
#define ATTR_FILTER_WRAPT      "wrapTFilter"
#define ATTR_FILTER_ENVMODE    "envModeFilter"

#define ELEM_BLENDING          "blending"
#define ATTR_BLENDING_ENABLED  "blendingEnabled"
#define ATTR_BLENDING_SRC      "blendingSrcFunc"
#define ATTR_BLENDING_DEST     "blendingDestFunc"
#define ELEM_BLENDING_COLOR    "blendingColor"
// po tym id± atrybuty ATTR_RED, ATTR_GREEN, ...

#define ELEM_TEXTURE_COORDS    "textureCoordinates"
#define ATTR_MINW              "minW"
#define ATTR_MINH              "minH"
#define ATTR_MAXW              "maxW"
#define ATTR_MAXH              "maxH"



////////////////////////////////////////// nazwy atrybutów dla sceny
#define SCENE_MAIN            "Scene"
#define ATTR_SCENE_NAME       "name"

////////////////////////////////////////// g³ówne o¶wietlenie
#define ELEM_LIGHTING         "Lighting"
#define ATTR_LIGHTING_ENABLED "isEnabled"

////////////////////////////////////////// pojedyczne ¶wiat³o
#define ELEM_LIGHT            "Light"
#define ATTR_LIGHT_NAME       "name"
#define ATTR_LIGHT_ENABLED    "isEnabled"
#define ATTR_LIGHT_TYPE       "type"
#define ATTR_LIGHT_IS         "lightIs"
#define ATTR_LIGHT_EXPONENT   "exponent"
#define ATTR_LIGHT_CUTOFF     "cutOff"
#define ATTR_LIGHT_MOVES_WITH_CAMERA "movesWithCamera"

#define ELEM_LIGHT_POSITION   "position"
#define ELEM_LIGHT_DIRECTION  "direction"
#define ATTR_X                "x"
#define ATTR_Y                "y"
#define ATTR_Z                "z"
#define ELEM_LIGHT_ATTENUATION "attenuation"
#define ATTR_LIGHT_LINEAR     "linear"
#define ATTR_LIGHT_CONSTANT   "constant"
#define ATTR_LIGHT_QUADRATIC  "quadratic"
#define ELEM_LIGHT_AMBIENT    "ambientColor"
#define ELEM_LIGHT_DIFFUSE    "diffuseColor"
#define ELEM_LIGHT_SPECULAR   "specularColor"

////////////////////////////////////////// mg³a
#define ELEM_FOG              "Fog"
#define ATTR_FOG_ENABLED      "isEnabled"
#define ATTR_FOG_MODE         "mode"
#define ATTR_FOG_DENSITY      "density"
#define ELEM_FOG_DISTANCE     "distance"
#define ATTR_FOG_START        "start"
#define ATTR_FOG_END          "end"
#define ELEM_FOG_COLOR        "color"

///////////////////////////////////////// cienie
#define ELEM_SHADOWS          "Shadows"

///////////////////////////////////////// elementy
#define ELEM_ELEMENTS         "Elements"

///////////////////////////////////////// pojedynczy elementy
#define ELEM_OBJECT           "Object"
#define ATTR_ELEM_FILENAME    "fileName"
#define ATTR_ELEM_NAME        "name"
#define ELEM_TRANS            "translation"
#define ELEM_ROT              "rotation"
#define ELEM_SCALE            "scale"


#endif
