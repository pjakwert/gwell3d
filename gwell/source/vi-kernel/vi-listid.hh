#ifndef VI_LISTID_H
#define VI_LISTID_H

/*!
 * \file vi-listid.hh
 *  Plik zawiera identyfikatory wykorzystywane przy tworzeniu 
 *  wielokrotnych list w oparciu o szablon ListItem i List.
 */

#define IDFIGURE     10
#define IDPRIMITIVE  14

/*!
 * Definiuje identyfikator dla listy, której zarz±dca znajduje siê
 * w klasie ViNTreeNode, za¶ elementem listy jest obiekt klasy
 * ViKinemCtrlItem.
 */
#define ID_KINEMCTRL_NTREENODE  1


/*!
 *  Identyfikator macierzy 
 *  \link ViNTreeNode::_Transf2ParentCoord 
 *        ViNTreeNode::_Transf2ParentCoord\endlink.
 */
#define MTXID_NODE2PARENT           1
/*!
 *  Identyfikator macierzy 
 *  \link ViElemePolyh::_Mtx_Patte2Eleme
 *        ViElemePolyh::_Mtx_Patte2Eleme\endlink.
 */
#define MTXID_PATTE2ELEME           2
/*!
 *  Identyfikator macierzy 
 *  \link ViElemePolyh::_Mtx_Eleme2Indiv
 *        ViElemePolyh::_Mtx_Eleme2Indiv\endlink.
 */
#define MTXID_ELEME2INDIV           3

#endif
