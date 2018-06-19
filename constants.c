/*
 * Copyright (c) 2009 - 2018, Micro Systems Marc Balmer, CH-5073 Gipf-Oberfrick
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Micro Systems Marc Balmer nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* Motif constants */

#include <X11/Xdefs.h>
#include <Xm/XmAll.h>

#ifdef OPENGL
#include <GL/GLwMDrawA.h>
#endif

#include <lua.h>
#include <lauxlib.h>

#include "luamotif.h"

struct str_constant motif_strings[] = {
#ifdef OPENGL
	{ "GLwNrgba",			GLwNrgba, BOOLEAN },
	{ "GLwNdoublebuffer",		GLwNdoublebuffer, BOOLEAN },
#endif
	{ "XmNactivateCallback",	XmNactivateCallback, FUNCTION },
	{ "XmNalignment",		XmNalignment, UCHAR },
	{ "XmNarmCallback",		XmNarmCallback, FUNCTION },
	{ "XmNarmColor",		XmNarmColor, STRING },
	{ "XmNarmPixmap",		XmNarmPixmap, STRING },
	{ "XmNautoShowCursorPosition",	XmNautoShowCursorPosition,
	    BOOLEAN },
	{ "XmNbackground",		XmNbackground, STRING },
	{ "XmNbottomAttachment",	XmNbottomAttachment, DIMENSION },
	{ "XmNbottomPosition",		XmNbottomPosition, DIMENSION },
	{ "XmNcancelCallback",		XmNcancelCallback, FUNCTION },
	{ "XmNchildHorizontalAlignment",	XmNchildHorizontalAlignment,
	    DIMENSION },
	{ "XmNchildHorizontalSpacing",	XmNchildHorizontalSpacing, DIMENSION },
	{ "XmNchildType",		XmNchildType, DIMENSION },
	{ "XmNchildVerticalAlignment",	XmNchildVerticalAlignment,
	    DIMENSION },
	{ "XmNcolumns",			XmNcolumns, DIMENSION },
	{ "XmNcursorPositionVisible",	XmNcursorPositionVisible,
	    BOOLEAN },
	{ "XmNdefaultButton",		XmNdefaultButton, CARDINAL },
	{ "XmNdefaultButtonShadowThickness", XmNdefaultButtonShadowThickness,
	    DIMENSION},
	{ "XmNdeleteResponse",		XmNdeleteResponse, DIMENSION },
	{ "XmNdialogStyle",		XmNdialogStyle, DIMENSION },
	{ "XmNdisarmCallback",		XmNdisarmCallback, FUNCTION },
	{ "XmNeditable",		XmNeditable, BOOLEAN },
	{ "XmNeditMode",		XmNeditMode, DIMENSION },
	{ "XmNfillOnArm",		XmNfillOnArm, BOOLEAN },
	{ "XmNfocusCallback",		XmNfocusCallback, FUNCTION },
	{ "XmNfractionBase",		XmNfractionBase, CARDINAL },
	{ "XmNframeChildType",		XmNframeChildType, DIMENSION },
	{ "XmNheight",			XmNheight, DIMENSION },
	{ "XmNlabelString",		XmNlabelString, STRING },
	{ "XmNleftAttachment",		XmNleftAttachment, CARDINAL },
	{ "XmNleftPosition",		XmNleftPosition, CARDINAL },
	{ "XmNmarginBottom",		XmNmarginBottom, DIMENSION },
	{ "XmNmarginLeft",		XmNmarginLeft, DIMENSION },
	{ "XmNmarginRight",		XmNmarginRight, DIMENSION },
	{ "XmNmarginTop",		XmNmarginTop, DIMENSION },
	{ "XmNmessageString",		XmNmessageString, STRING },
	{ "XmNmultiClick",		XmNmultiClick, BOOLEAN },
	{ "XmNmwmDecorations",		XmNmwmDecorations, DIMENSION },
	{ "XmNmwmFunctions",		XmNmwmFunctions, DIMENSION },
	{ "XmNnumColumns",		XmNnumColumns, DIMENSION },
	{ "XmNokCallback",		XmNokCallback, FUNCTION },
	{ "XmNpaneMaximum",		XmNpaneMaximum, DIMENSION },
	{ "XmNpaneMinimum",		XmNpaneMinimum, DIMENSION },
	{ "XmNrightAttachment",		XmNrightAttachment, CARDINAL },
	{ "XmNrightPosition",		XmNrightPosition, CARDINAL },
	{ "XmNrows",			XmNrows, DIMENSION },
	{ "XmNsashHeight",		XmNsashHeight, DIMENSION },
	{ "XmNsashWidth",		XmNsashWidth, DIMENSION },
	{ "XmNscrollingPolicy",		XmNscrollingPolicy, DIMENSION },
	{ "XmNscrollVertical",		XmNscrollVertical, BOOLEAN },
	{ "XmNshadowType",		XmNshadowType, DIMENSION },
	{ "XmNshowAsDefault",		XmNshowAsDefault, BOOLEAN },
	{ "XmNstackedEffect",		XmNstackedEffect, BOOLEAN },
	{ "XmNtabAutoSelect",		XmNtabAutoSelect, BOOLEAN },
	{ "XmNtabCornerPercent",	XmNtabCornerPercent, DIMENSION },
	{ "XmNtabSelectedCallback",	XmNtabSelectedCallback, FUNCTION },
	{ "XmNtabLabelSpacing",		XmNtabLabelSpacing, DIMENSION },
	{ "XmNtabLabelString",		XmNtabLabelString, STRING },
	{ "XmNtitle",			XmNtitle, STRING },
	{ "XmNtopAttachment",		XmNtopAttachment, CARDINAL },
	{ "XmNtopPosition",		XmNtopPosition, CARDINAL },
	{ "XmNtotalLines",		XmNtotalLines, CARDINAL },
	{ "XmNuserData",		XmNuserData, CARDINAL },
	{ "XmNvalueChangedCallback",	XmNvalueChangedCallback,
	    FUNCTION },
	{ "XmNwidth",			XmNwidth, DIMENSION },
	{ "XmNworkWindow",		XmNworkWindow, NONE },
};

size_t
num_motif_strings(void)
{
	return sizeof(motif_strings)/sizeof(motif_strings[0]);
}

struct int_constant motif_ints[] = {
	/* XmDirection */
	{ "DIRECTION_IGNORED",		XmDIRECTION_IGNORED },

	{ "RIGHT_TO_LEFT_MASK",		XmRIGHT_TO_LEFT_MASK },
	{ "LEFT_TO_RIGHT_MASK",		XmLEFT_TO_RIGHT_MASK },
	{ "HORIZONTAL_MASK",		XmHORIZONTAL_MASK },
	{ "TOP_TO_BOTTOM_MASK",		XmTOP_TO_BOTTOM_MASK },
	{ "BOTTOM_TO_TOP_MASK",		XmBOTTOM_TO_TOP_MASK },
	{ "VERTICAL_MASK",		XmVERTICAL_MASK },
	{ "PRECEDENCE_HORIZ_MASK",	XmPRECEDENCE_HORIZ_MASK },
	{ "PRECEDENCE_VERT_MASK",	XmPRECEDENCE_VERT_MASK },
	{ "PRECEDENCE_MASK",		XmPRECEDENCE_MASK },

	{ "RIGHT_TO_LEFT_TOP_TO_BOTTOM",	XmRIGHT_TO_LEFT_TOP_TO_BOTTOM },
	{ "LEFT_TO_RIGHT_TOP_TO_BOTTOM",	XmLEFT_TO_RIGHT_TOP_TO_BOTTOM },
	{ "RIGHT_TO_LEFT_BOTTOM_TO_TOP",	XmRIGHT_TO_LEFT_BOTTOM_TO_TOP },
	{ "LEFT_TO_RIGHT_BOTTOM_TO_TOP",	XmLEFT_TO_RIGHT_BOTTOM_TO_TOP },
	{ "TOP_TO_BOTTOM_RIGHT_TO_LEFT",	XmTOP_TO_BOTTOM_RIGHT_TO_LEFT },
	{ "TOP_TO_BOTTOM_LEFT_TO_RIGHT",	XmTOP_TO_BOTTOM_LEFT_TO_RIGHT },
	{ "BOTTOM_TO_TOP_RIGHT_TO_LEFT",	XmBOTTOM_TO_TOP_RIGHT_TO_LEFT },
	{ "BOTTOM_TO_TOP_LEFT_TO_RIGHT",	XmBOTTOM_TO_TOP_LEFT_TO_RIGHT },
	{ "TOP_TO_BOTTOM",		XmTOP_TO_BOTTOM },
	{ "BOTTOM_TO_TOP",		XmBOTTOM_TO_TOP },
	{ "RIGHT_TO_LEFT",		XmRIGHT_TO_LEFT },
	{ "LEFT_TO_RIGHT",		XmLEFT_TO_RIGHT },
	{ "DEFAULT_DIRECTION",		XmDEFAULT_DIRECTION },

	/* XmFontType */
	{ "FONT_IS_FONT",		XmFONT_IS_FONT },
	{ "FONT_IS_FONTSET",		XmFONT_IS_FONTSET },
	{ "ONT_IS_XFT",			XmFONT_IS_XFT },

	/* XmStringDirection */
	{ "STRING_DIRECTION_L_TO_R",	XmSTRING_DIRECTION_L_TO_R },
	{ "STRING_DIRECTION_R_TO_L",	XmSTRING_DIRECTION_R_TO_L },
	{ "STRING_DIRECTION_UNSET",	XmSTRING_DIRECTION_UNSET },
	{ "STRING_DIRECTION_DEFAULT",	XmSTRING_DIRECTION_DEFAULT },

	/* XmStringComponent */
	{ "STRING_COMPONENT_UNKNOWN",	XmSTRING_COMPONENT_UNKNOWN },
	{ "STRING_COMPONENT_CHARSET",	XmSTRING_COMPONENT_CHARSET },
	{ "STRING_COMPONENT_TEXT",	XmSTRING_COMPONENT_TEXT },
	{ "STRING_COMPONENT_DIRECTION",	XmSTRING_COMPONENT_DIRECTION },
	{ "STRING_COMPONENT_SEPARATOR",	XmSTRING_COMPONENT_SEPARATOR },
	{ "STRING_COMPONENT_LOCALE_TEXT",
	    XmSTRING_COMPONENT_LOCALE_TEXT },
	{ "STRING_COMPONENT_LOCALE",	XmSTRING_COMPONENT_LOCALE },
	{ "STRING_COMPONENT_WIDECHAR_TEXT",
	    XmSTRING_COMPONENT_WIDECHAR_TEXT },
	{ "STRING_COMPONENT_LAYOUT_PUSH",
	    XmSTRING_COMPONENT_LAYOUT_PUSH },
	{ "STRING_COMPONENT_LAYOUT_POP",	XmSTRING_COMPONENT_LAYOUT_POP },
	{ "STRING_COMPONENT_RENDITION_BEGIN",
	    XmSTRING_COMPONENT_RENDITION_BEGIN },
	{ "STRING_COMPONENT_RENDITION_END",
	    XmSTRING_COMPONENT_RENDITION_END },
	{ "STRING_COMPONENT_TAB",	XmSTRING_COMPONENT_TAB },
	{ "STRING_COMPONENT_FONTLIST_ELEMENT_TAG",
	    XmSTRING_COMPONENT_FONTLIST_ELEMENT_TAG },
	{ "STRING_COMPONENT_TAG",	XmSTRING_COMPONENT_TAG },
	{ "STRING_COMPONENT_END",	XmSTRING_COMPONENT_END },
	{ "STRING_COMPONENT_USER_BEGIN",	XmSTRING_COMPONENT_USER_BEGIN },
	{ "STRING_COMPONENT_USER_END",	XmSTRING_COMPONENT_USER_END },

	/* XmTextType */
	{ "CHARSET_TEXT",		XmCHARSET_TEXT },
	{ "MULTIBYTE_TEXT",		XmMULTIBYTE_TEXT },
	{ "WIDECHAR_TEXT",		XmWIDECHAR_TEXT },
	{ "NO_TEXT",			XmNO_TEXT },

	/* XmParseModel */
	{ "OUTPUT_ALL",			XmOUTPUT_ALL },
	{ "OUTPUT_BETWEEN",		XmOUTPUT_BETWEEN },
	{ "OUTPUT_BEGINNING",		XmOUTPUT_BEGINNING },
	{ "OUTPUT_END",			XmOUTPUT_END },
	{ "OUTPUT_BOTH",		XmOUTPUT_BOTH },

	/* XmIncludeStatus */
	{ "INSERT",			XmINSERT },
	{ "TERMINATE",			XmTERMINATE },
	{ "INVOKE",			XmINVOKE },

	/* XmICCEncodingStyle */
	{ "STYLE_STRING",		XmSTYLE_STRING },
	{ "STYLE_COMPOUND_TEXT",	XmSTYLE_COMPOUND_TEXT },
	{ "STYLE_TEXT",			XmSTYLE_TEXT },
	{ "STYLE_STANDARD_ICC_TEXT",	XmSTYLE_STANDARD_ICC_TEXT },
	{ "STYLE_LOCALE",		XmSTYLE_LOCALE },
	{ "STYLE_COMPOUND_STRING",	XmSTYLE_COMPOUND_STRING },

	/* XmOffsetModel */
	{ "ABSOLUTE",			XmABSOLUTE },
	{ "RELATIVE",			XmRELATIVE },

	/* XmMergeMode */
	{ "SKIP",			XmSKIP },
	{ "MERGE_REPLACE",		XmMERGE_REPLACE },
	{ "MERGE_OLD",			XmMERGE_OLD },
	{ "MERGE_NEW",			XmMERGE_NEW },
	{ "DUPLICATE",			XmDUPLICATE },

	{ "AS_IS",			XmAS_IS },
	{ "FORCE_COLOR",		XmFORCE_COLOR },

	{ "UNSPECIFIED_PIXEL",		XmUNSPECIFIED_PIXEL },
	{ "DEFAULT_SELECT_COLOR",	XmDEFAULT_SELECT_COLOR },
	{ "REVERSED_GROUND_COLORS",	XmREVERSED_GROUND_COLORS },
	{ "HIGHLIGHT_COLOR",		XmHIGHLIGHT_COLOR },

	{ "UNSPECIFIED_LOAD_MODEL",	XmUNSPECIFIED_LOAD_MODEL },
	{ "LOAD_DEFERRED",		XmLOAD_DEFERRED },
	{ "LOAD_IMMEDIATE",		XmLOAD_IMMEDIATE },

/************************************************************************
 *  Primitive Resources and define values
 ************************************************************************/

	/* size policy values  */
	{ "CHANGE_ALL",			XmCHANGE_ALL },
	{ "CHANGE_NONE",		XmCHANGE_NONE },
	{ "CHANGE_WIDTH",		XmCHANGE_WIDTH },
	{ "CHANGE_HEIGHT",		XmCHANGE_HEIGHT },

	/*  unit type values  */
	{ "PIXELS",			XmPIXELS },
	{ "100TH_MILLIMETERS",		Xm100TH_MILLIMETERS },
	{ "1000TH_INCHES",		Xm1000TH_INCHES },
	{ "100TH_POINTS",		Xm100TH_POINTS },
	{ "100TH_FONT_UNITS",		Xm100TH_FONT_UNITS },
	{ "INCHES",			XmINCHES },
	{ "CENTIMETERS",		XmCENTIMETERS },
	{ "MILLIMETERS",		XmMILLIMETERS },
	{ "POINTS",			XmPOINTS },
	{ "FONT_UNITS",			XmFONT_UNITS },

	/* DeleteResponse values */
	{ "DESTROY",			XmDESTROY },
	{ "UNMAP",			XmUNMAP },
	{ "DO_NOTHING",			XmDO_NOTHING },

	{ "EXPLICIT",			XmEXPLICIT },
	{ "POINTER",			XmPOINTER },

/************************************************************************
 *  Navigation defines
 ************************************************************************/

	{ "NONE",			XmNONE },
	{ "TAB_GROUP",			XmTAB_GROUP },
	{ "STICKY_TAB_GROUP",		XmSTICKY_TAB_GROUP },
	{ "EXCLUSIVE_TAB_GROUP",	XmEXCLUSIVE_TAB_GROUP },

	{ "DYNAMIC_DEFAULT_TAB_GROUP",	XmDYNAMIC_DEFAULT_TAB_GROUP },

/************************************************************************
 * Audible warning
 ************************************************************************/

	{ "BELL",			XmBELL },

/************************************************************************
 * Input Manager defines
 ************************************************************************/

	{ "PER_SHELL",			XmPER_SHELL },
	{ "PER_WIDGET",			XmPER_WIDGET },
	{ "INHERIT_POLICY",		XmINHERIT_POLICY },

/************************************************************************
 *  Menu defines
 ************************************************************************/

	{ "NO_ORIENTATION",		XmNO_ORIENTATION },
	{ "VERTICAL",			XmVERTICAL },
	{ "HORIZONTAL",			XmHORIZONTAL },

	{ "WORK_AREA",			XmWORK_AREA },
	{ "MENU_BAR",			XmMENU_BAR },
	{ "MENU_PULLDOWN",		XmMENU_PULLDOWN },
	{ "MENU_POPUP",			XmMENU_POPUP },
	{ "MENU_OPTION",		XmMENU_OPTION },

	{ "NO_PACKING",			XmNO_PACKING },
	{ "PACK_TIGHT",			XmPACK_TIGHT },
	{ "PACK_COLUMN",		XmPACK_COLUMN },
	{ "PACK_NONE",			XmPACK_NONE },

	{ "ALIGNMENT_CONTENTS_TOP",	XmALIGNMENT_CONTENTS_TOP },
	{ "ALIGNMENT_CONTENTS_BOTTOM",	XmALIGNMENT_CONTENTS_BOTTOM },

	{ "TEAR_OFF_ENABLED",		XmTEAR_OFF_ENABLED },
	{ "TEAR_OFF_DISABLED",		XmTEAR_OFF_DISABLED },

	{ "UNPOST",			XmUNPOST },
	{ "UNPOST_AND_REPLAY",		XmUNPOST_AND_REPLAY },

	{ "LAST_POSITION",		XmLAST_POSITION },
	{ "FIRST_POSITION",		XmFIRST_POSITION },
	{ "POPUP_DISABLED",		XmPOPUP_DISABLED },
	{ "POPUP_KEYBOARD",		XmPOPUP_KEYBOARD },
	{ "POPUP_AUTOMATIC",		XmPOPUP_AUTOMATIC },
	{ "POPUP_AUTOMATIC_RECURSIVE",	XmPOPUP_AUTOMATIC_RECURSIVE },

/************************************************************************
 *  Color Selector defines
 ************************************************************************/

	{ "ListMode",			XmListMode },
	{ "ScaleMode",			XmScaleMode },

/************************************************************************
 *  Column defines
 ************************************************************************/

	{ "FILL_UNSPECIFIED",		XmFILL_UNSPECIFIED },
	{ "FILL_FLUSH",			XmFILL_FLUSH },
	{ "FILL_RAGGED",		XmFILL_RAGGED },

	{ "DISTRIBUTE_TIGHT",		XmDISTRIBUTE_TIGHT },
	{ "DISTRIBUTE_SPREAD",		XmDISTRIBUTE_SPREAD },

/************************************************************************
 *  ComboBox defines
 ************************************************************************/

	{ "COMBO_BOX",			XmCOMBO_BOX },
	{ "DROP_DOWN_COMBO_BOX",	XmDROP_DOWN_COMBO_BOX },
	{ "DROP_DOWN_LIST",		XmDROP_DOWN_LIST },

	{ "QUICK_NAVIGATE",		XmQUICK_NAVIGATE },
	{ "INVALID_MATCH_BEHAVIOR",	XmINVALID_MATCH_BEHAVIOR },

	{ "ZERO_BASED",			XmZERO_BASED },
	{ "ONE_BASED",			XmONE_BASED },

	{ "INVALID_POSITION",		XmINVALID_POSITION },

/************************************************************************
 *  Icon & Button Box defines
 ************************************************************************/
	{ "IconTop",			XmIconTop },
	{ "IconLeft",			XmIconLeft },
	{ "IconRight",			XmIconRight },
	{ "IconBottom",			XmIconBottom },
	{ "IconOnly",			XmIconOnly },
	{ "IconNone",			XmIconNone },

	{ "FillNone",			XmFillNone },
	{ "FillMajor",			XmFillMajor },
	{ "FillMinor",			XmFillMinor },
	{ "FillAll",			XmFillAll },

/************************************************************************
 * Hierarchy/Tree/Outline defines
 ************************************************************************/

	{ "AlwaysOpen",			XmAlwaysOpen },
	{ "Open",			XmOpen },
	{ "Closed",			XmClosed },
	{ "Hidden",			XmHidden },
	{ "NotInHierarchy",		XmNotInHierarchy },

	{ "TreeLadder",			XmTreeLadder },
	{ "TreeDirect",			XmTreeDirect },

	{ "TreeCompressNone",		XmTreeCompressNone },
	{ "TreeCompressLeaves",		XmTreeCompressLeaves },
	{ "TreeCompressAll",		XmTreeCompressAll },

/************************************************************************
 *  Label/Frame defines
 ************************************************************************/

	{ "ALIGNMENT_BEGINNING",	XmALIGNMENT_BEGINNING },
	{ "ALIGNMENT_CENTER",		XmALIGNMENT_CENTER },
	{ "ALIGNMENT_END",		XmALIGNMENT_END },
	{ "ALIGNMENT_UNSPECIFIED",	XmALIGNMENT_UNSPECIFIED },

	{ "ALIGNMENT_BASELINE_TOP",	XmALIGNMENT_BASELINE_TOP },
	{ "ALIGNMENT_BASELINE_BOTTOM",	XmALIGNMENT_BASELINE_BOTTOM },
	{ "ALIGNMENT_WIDGET_TOP",	XmALIGNMENT_WIDGET_TOP },
	{ "ALIGNMENT_WIDGET_BOTTOM",	XmALIGNMENT_WIDGET_BOTTOM },


/* new enum introduced in 2.0 to clear up the confusion in
   widget top/bottom attachment */

	{ "ALIGNMENT_CHILD_TOP",	XmALIGNMENT_CHILD_TOP },
	{ "ALIGNMENT_CHILD_BOTTOM",	XmALIGNMENT_CHILD_BOTTOM },

/************************************************************************
 *  Frame defines
 ************************************************************************/

	{ "FRAME_GENERIC_CHILD",	XmFRAME_GENERIC_CHILD },
	{ "FRAME_WORKAREA_CHILD",	XmFRAME_WORKAREA_CHILD },
	{ "FRAME_TITLE_CHILD",		XmFRAME_TITLE_CHILD },

/************************************************************************
 *  ToggleButton  defines
 ************************************************************************/

	{ "N_OF_MANY",			XmN_OF_MANY },
	{ "ONE_OF_MANY",		XmONE_OF_MANY },
	{ "ONE_OF_MANY_ROUND",		XmONE_OF_MANY_ROUND },
	{ "ONE_OF_MANY_DIAMOND",	XmONE_OF_MANY_DIAMOND },

/************************************************************************
 *  Form defines
 ************************************************************************/

	{ "ATTACH_NONE",		XmATTACH_NONE },
	{ "ATTACH_FORM",		XmATTACH_FORM },
	{ "ATTACH_OPPOSITE_FORM",	XmATTACH_OPPOSITE_FORM },
	{ "ATTACH_WIDGET",		XmATTACH_WIDGET },
	{ "ATTACH_OPPOSITE_WIDGET",	XmATTACH_OPPOSITE_WIDGET },
	{ "ATTACH_POSITION",		XmATTACH_POSITION },
	{ "ATTACH_SELF",		XmATTACH_SELF },

	{ "RESIZE_NONE",		XmRESIZE_NONE },
	{ "RESIZE_GROW",		XmRESIZE_GROW },
	{ "RESIZE_ANY",			XmRESIZE_ANY },

	/* TabStack */
	/* XmTabStyle */
	{ "TABS_SQUARED",		XmTABS_SQUARED },
	{ "TABS_ROUNDED",		XmTABS_ROUNDED },
	{ "TABS_BEVELED",		XmTABS_BEVELED },

	/* XmTabMode */
	{ "TABS_BASIC",			XmTABS_BASIC },
	{ "TABS_STACKED",		XmTABS_STACKED },
	{ "TABS_STACKED_STATIC",	XmTABS_STACKED_STATIC },
	{ "TABS_SCROLLED",		XmTABS_SCROLLED },
	{ "TABS_OVERLAYED",		XmTABS_OVERLAYED },

 	/* XmTabOrientation */
	{ "TAB_ORIENTATION_DYNAMIC",	XmTAB_ORIENTATION_DYNAMIC },
	{ "TABS_RIGHT_TO_LEFT",		XmTABS_RIGHT_TO_LEFT },
	{ "TABS_LEFT_TO_RIGHT",		XmTABS_LEFT_TO_RIGHT },
	{ "TABS_TOP_TO_BOTTOM",		XmTABS_TOP_TO_BOTTOM },
	{ "TABS_BOTTOM_TO_TOP",		XmTABS_BOTTOM_TO_TOP },

	/* XmTabEdge */
	{ "TAB_EDGE_TOP_LEFT",		XmTAB_EDGE_TOP_LEFT },
	{ "TAB_EDGE_BOTTOM_RIGHT",	XmTAB_EDGE_BOTTOM_RIGHT },

	/* XmTabArrowPlacement */
	{ "TAB_ARROWS_ON_RIGHT",	XmTAB_ARROWS_ON_RIGHT },
	{ "TAB_ARROWS_ON_LEFT",		XmTAB_ARROWS_ON_LEFT },
	{ "TAB_ARROWS_SPLIT",		XmTAB_ARROWS_SPLIT },

	{ "CR_TAB_SELECTED",		XmCR_TAB_SELECTED },
	{ "CR_TAB_UNSELECTED",		XmCR_TAB_UNSELECTED },

	{ "TABS_ON_BOTTOM",		XmTABS_ON_BOTTOM },
	{ "TABS_ON_LEFT",		XmTABS_ON_LEFT },
	{ "TABS_ON_RIGHT",		XmTABS_ON_RIGHT },
	{ "TABS_ON_TOP",		XmTABS_ON_TOP },

	{ "PIXMAP_TOP",			XmPIXMAP_TOP },
	{ "PIXMAP_BOTTOM",		XmPIXMAP_BOTTOM },
	{ "PIXMAP_RIGHT",		XmPIXMAP_RIGHT },
	{ "PIXMAP_LEFT",		XmPIXMAP_LEFT },
	{ "PIXMAP_NONE",		XmPIXMAP_NONE },
	{ "PIXMAP_ONLY",		XmPIXMAP_ONLY },

	{ "TAB_VALUE_COPY",		XmTAB_VALUE_COPY },
	{ "TAB_VALUE_SHARE",		XmTAB_VALUE_SHARE },

	{ "TAB_CMP_VISUAL",		XmTAB_CMP_VISUAL },
	{ "TAB_CMP_SIZE",		XmTAB_CMP_SIZE },
	{ "TAB_CMP_EQUAL",		XmTAB_CMP_EQUAL },

/****************************************************************************
 *  Callback reasons
 ****************************************************************************/

	{ "CR_NONE",			XmCR_NONE },
	{ "CR_HELP",			XmCR_HELP },
	{ "CR_VALUE_CHANGED",		XmCR_VALUE_CHANGED },
	{ "CR_INCREMENT",		XmCR_INCREMENT },
	{ "CR_DECREMENT",		XmCR_DECREMENT },
	{ "CR_PAGE_INCREMENT",		XmCR_PAGE_INCREMENT },
	{ "CR_PAGE_DECREMENT",		XmCR_PAGE_DECREMENT },
	{ "CR_TO_TOP",			XmCR_TO_TOP },
	{ "CR_TO_BOTTOM",		XmCR_TO_BOTTOM },
	{ "CR_DRAG",			XmCR_DRAG },
	{ "CR_ACTIVATE",		XmCR_ACTIVATE },
	{ "CR_ARM",			XmCR_ARM },
	{ "CR_DISARM",			XmCR_DISARM },
	{ "CR_MAP",			XmCR_MAP },
	{ "CR_UNMAP",			XmCR_UNMAP },
	{ "CR_FOCUS",			XmCR_FOCUS },
	{ "CR_LOSING_FOCUS",		XmCR_LOSING_FOCUS },
	{ "CR_MODIFYING_TEXT_VALUE",	XmCR_MODIFYING_TEXT_VALUE },
	{ "CR_MOVING_INSERT_CURSOR",	XmCR_MOVING_INSERT_CURSOR },
	{ "CR_EXECUTE",			XmCR_EXECUTE },
	{ "CR_SINGLE_SELECT",		XmCR_SINGLE_SELECT },
	{ "CR_MULTIPLE_SELECT",		XmCR_MULTIPLE_SELECT },
	{ "CR_EXTENDED_SELECT",		XmCR_EXTENDED_SELECT },
	{ "CR_BROWSE_SELECT",		XmCR_BROWSE_SELECT },
	{ "CR_DEFAULT_ACTION",		XmCR_DEFAULT_ACTION },
	{ "CR_CLIPBOARD_DATA_REQUEST",	XmCR_CLIPBOARD_DATA_REQUEST },
	{ "CR_CLIPBOARD_DATA_DELETE",	XmCR_CLIPBOARD_DATA_DELETE },
	{ "CR_CASCADING",		XmCR_CASCADING },
	{ "CR_OK",			XmCR_OK },
	{ "CR_CANCEL",			XmCR_CANCEL },
	{ "CR_APPLY",			XmCR_APPLY },
	{ "CR_NO_MATCH",		XmCR_NO_MATCH },
	{ "CR_COMMAND_ENTERED",		XmCR_COMMAND_ENTERED },
	{ "CR_COMMAND_CHANGED",		XmCR_COMMAND_CHANGED },
	{ "CR_EXPOSE",			XmCR_EXPOSE },
	{ "CR_RESIZE",			XmCR_RESIZE },
	{ "CR_INPUT",			XmCR_INPUT },
	{ "CR_GAIN_PRIMARY",		XmCR_GAIN_PRIMARY },
	{ "CR_LOSE_PRIMARY",		XmCR_LOSE_PRIMARY },
	{ "CR_CREATE",			XmCR_CREATE },
	{ "CR_TEAR_OFF_ACTIVATE",	XmCR_TEAR_OFF_ACTIVATE },
	{ "CR_TEAR_OFF_DEACTIVATE",	XmCR_TEAR_OFF_DEACTIVATE },
	{ "CR_OBSCURED_TRAVERSAL",	XmCR_OBSCURED_TRAVERSAL },
	{ "CR_FOCUS_MOVED",		XmCR_FOCUS_MOVED },
	{ "CR_REPOST",			XmCR_REPOST },
	{ "CR_COLLAPSED",		XmCR_COLLAPSED },
	{ "CR_EXPANDED",		XmCR_EXPANDED },
	{ "CR_SELECT",			XmCR_SELECT },
	{ "CR_DRAG_START",		XmCR_DRAG_START },
	{ "CR_NO_FONT",			XmCR_NO_FONT },
	{ "CR_NO_RENDITION",		XmCR_NO_RENDITION },
	{ "CR_POST",			XmCR_POST },
	{ "CR_SPIN_NEXT",		XmCR_SPIN_NEXT },
	{ "CR_SPIN_PRIOR",		XmCR_SPIN_PRIOR },
	{ "CR_SPIN_FIRST",		XmCR_SPIN_FIRST },
	{ "CR_SPIN_LAST",		XmCR_SPIN_LAST },
	{ "CR_PAGE_SCROLLER_INCREMENT",	XmCR_PAGE_SCROLLER_INCREMENT },
	{ "CR_PAGE_SCROLLER_DECREMENT",	XmCR_PAGE_SCROLLER_DECREMENT },
	{ "CR_MAJOR_TAB",		XmCR_MAJOR_TAB },
	{ "CR_MINOR_TAB",		XmCR_MINOR_TAB },
	{ "CR_START_JOB",		XmCR_START_JOB },
	{ "CR_END_JOB",			XmCR_END_JOB },
	{ "CR_PAGE_SETUP",		XmCR_PAGE_SETUP },
	{ "CR_PDM_NONE",		XmCR_PDM_NONE },
	{ "CR_PDM_UP",			XmCR_PDM_UP },
	{ "CR_PDM_START_ERROR",		XmCR_PDM_START_ERROR },
	{ "CR_PDM_START_VXAUTH",	XmCR_PDM_START_VXAUTH },
	{ "CR_PDM_START_PXAUTH",	XmCR_PDM_START_PXAUTH },
	{ "CR_PDM_OK",			XmCR_PDM_OK },
	{ "CR_PDM_CANCEL",		XmCR_PDM_CANCEL },
	{ "CR_PDM_EXIT_ERROR",		XmCR_PDM_EXIT_ERROR },
	{ "CR_UPDATE_SHELL",		XmCR_UPDATE_SHELL },
	{ "CR_UPDATE_TEXT",		XmCR_UPDATE_TEXT },
	{ "CR_VERIFY_TEXT",		XmCR_VERIFY_TEXT },
	{ "CR_VERIFY_TEXT_FAILED",	XmCR_VERIFY_TEXT_FAILED },
  	{ "CR_ENTER_CHILD",		XmCR_ENTER_CHILD },
	{ "CR_LEAVE_CHILD",		XmCR_LEAVE_CHILD },
	{ "CR_PROTOCOLS",		XmCR_PROTOCOLS },

/************************************************************************
 *  new ScrollBar showArrows  define
 ************************************************************************/

	{ "EACH_SIDE",			XmEACH_SIDE },
	{ "MAX_SIDE",			XmMAX_SIDE },
	{ "MIN_SIDE",			XmMIN_SIDE },

/************************************************************************
 *  Sliding mode
 ************************************************************************/

	{ "SLIDER",			XmSLIDER },
	{ "THERMOMETER",		XmTHERMOMETER },

/************************************************************************
 *  Slider Visual
 ************************************************************************/

	{ "BACKGROUND_COLOR",		XmBACKGROUND_COLOR },
	{ "FOREGROUND_COLOR",		XmFOREGROUND_COLOR },
	{ "TROUGH_COLOR",		XmTROUGH_COLOR },
 	{ "SHADOWED_BACKGROUND",	XmSHADOWED_BACKGROUND },

/************************************************************************
 *  Slider Mark
 ************************************************************************/

	{ "ETCHED_LINE",		XmETCHED_LINE },
	{ "THUMB_MARK",			XmTHUMB_MARK },
	{ "ROUND_MARK",			XmROUND_MARK },

/************************************************************************
 *  new Scale showValue
 ************************************************************************/

	{ "NEAR_SLIDER",		XmNEAR_SLIDER },
	{ "NEAR_BORDER",		XmNEAR_BORDER },

/************************************************************************
 *  new ScrolledWindow/MainWindow chidType
 ************************************************************************/

	{ "HOR_SCROLLBAR",		XmHOR_SCROLLBAR },
	{ "VERT_SCROLLBAR",		XmVERT_SCROLLBAR },
	{ "COMMAND_WINDOW",		XmCOMMAND_WINDOW },
	{ "MESSAGE_WINDOW",		XmMESSAGE_WINDOW },
	{ "SCROLL_HOR",			XmSCROLL_HOR },
	{ "SCROLL_VERT",		XmSCROLL_VERT },
	{ "NO_SCROLL",			XmNO_SCROLL },
	{ "CLIP_WINDOW",		XmCLIP_WINDOW },
	{ "GENERIC_CHILD",		XmGENERIC_CHILD },

/************************************************************************
 *  new ScrolledWindow auto drag enum
 ************************************************************************/

	{ "AUTO_DRAG_ENABLED",		XmAUTO_DRAG_ENABLED },
	{ "AUTO_DRAG_DISABLED",		XmAUTO_DRAG_DISABLED },

/************************************************************************
 *  new Display enable warp enum
 ************************************************************************/

	{ "ENABLE_WARP_ON",		XmENABLE_WARP_ON },
	{ "ENABLE_WARP_OFF",		XmENABLE_WARP_OFF },

/************************************************************************
 *  new Display enable btn1 transfer enum
 ************************************************************************/

	{ "OFF",			XmOFF },
	{ "BUTTON2_ADJUST",		XmBUTTON2_ADJUST },
	{ "BUTTON2_TRANSFER",		XmBUTTON2_TRANSFER },

/************************************************************************
 * auto_selection_type
 ************************************************************************/

	{ "AUTO_UNSET",			XmAUTO_UNSET },
	{ "AUTO_BEGIN",			XmAUTO_BEGIN },
	{ "AUTO_MOTION",		XmAUTO_MOTION },
	{ "AUTO_CANCEL",		XmAUTO_CANCEL },
	{ "AUTO_NO_CHANGE",		XmAUTO_NO_CHANGE },
	{ "AUTO_CHANGE",		XmAUTO_CHANGE },

/************************************************************************
 *  PushButton defines
 ************************************************************************/

	{ "MULTICLICK_DISCARD",		XmMULTICLICK_DISCARD },
	{ "MULTICLICK_KEEP",		XmMULTICLICK_KEEP },

/************************************************************************
 *  DrawnButton defines
 ************************************************************************/

	{ "SHADOW_IN",			XmSHADOW_IN },
	{ "SHADOW_OUT",			XmSHADOW_OUT },

/************************************************************************
 *  Arrow defines
 ************************************************************************/

	{ "ARROW_UP",			XmARROW_UP },
	{ "ARROW_DOWN",			XmARROW_DOWN },
	{ "ARROW_LEFT",			XmARROW_LEFT },
	{ "ARROW_RIGHT",		XmARROW_RIGHT },

/************************************************************************
 *  Separator defines
 *  Note: XmINVALID_SEPARATOR_TYPE marks the last+1 separator type
 ************************************************************************/

	{ "NO_LINE",			XmNO_LINE },
	{ "SINGLE_LINE",		XmSINGLE_LINE },
	{ "DOUBLE_LINE",		XmDOUBLE_LINE },
	{ "SINGLE_DASHED_LINE",		XmSINGLE_DASHED_LINE },
	{ "DOUBLE_DASHED_LINE",		XmDOUBLE_DASHED_LINE },
	{ "SHADOW_ETCHED_IN",		XmSHADOW_ETCHED_IN },
	{ "SHADOW_ETCHED_OUT",		XmSHADOW_ETCHED_OUT },
	{ "SHADOW_ETCHED_IN_DASH",	XmSHADOW_ETCHED_IN_DASH },
	{ "SHADOW_ETCHED_OUT_DASH",	XmSHADOW_ETCHED_OUT_DASH },
	{ "INVALID_SEPARATOR_TYPE",	XmINVALID_SEPARATOR_TYPE },

	{ "PIXMAP",			XmPIXMAP },
	{ "STRING",			XmSTRING },
	{ "PIXMAP_AND_STRING",		XmPIXMAP_AND_STRING },

/************************************************************************
 *  Drag and Drop defines
 ************************************************************************/

	{ "WINDOW",			XmWINDOW },
	{ "CURSOR",			XmCURSOR },
	{ "DRAG_WINDOW",		XmDRAG_WINDOW },

/************************************************************************
 *  ScrollBar defines
 ************************************************************************/

	{ "MAX_ON_TOP",			XmMAX_ON_TOP },
	{ "MAX_ON_BOTTOM",		XmMAX_ON_BOTTOM },
	{ "MAX_ON_LEFT",		XmMAX_ON_LEFT },
	{ "MAX_ON_RIGHT",		XmMAX_ON_RIGHT },

/************************************************************************
 *									*
 * List Widget defines							*
 *									*
 ************************************************************************/

	{ "SINGLE_SELECT",		XmSINGLE_SELECT },
	{ "MULTIPLE_SELECT",		XmMULTIPLE_SELECT },
	{ "XTENDED_SELECT",		XmEXTENDED_SELECT },
	{ "BROWSE_SELECT",		XmBROWSE_SELECT },

	{ "STATIC",			XmSTATIC },
	{ "DYNAMIC",			XmDYNAMIC },
	{ "NORMAL_MODE",		XmNORMAL_MODE },
	{ "ADD_MODE",			XmADD_MODE },

/************************************************************************
 *                                                                      *
 * Container Widget defines                                             *
 *                                                                      *
 ************************************************************************/

        /* XmRAutomaticSelection */
	{ "NO_AUTO_SELECT",		XmNO_AUTO_SELECT },
	{ "AUTO_SELECT",		XmAUTO_SELECT },

        /* XmRLineStyle */
	{ "SINGLE",			XmSINGLE },

        /* XmREntryViewType */
	{ "ANY_ICON",			XmANY_ICON },

        /* XmRSpatialIncludeModel */
	{ "APPEND",			XmAPPEND },
	{ "CLOSEST",			XmCLOSEST },
	{ "FIRST_FIT",			XmFIRST_FIT },

        /* XmRLayoutType */
	{ "OUTLINE",			XmOUTLINE },
	{ "SPATIAL",			XmSPATIAL },
	{ "DETAIL",			XmDETAIL },

	/* XmNoutlineButtonPolicy */
	{ "OUTLINE_BUTTON_PRESENT",	XmOUTLINE_BUTTON_PRESENT },
	{ "OUTLINE_BUTTON_ABSENT",	XmOUTLINE_BUTTON_ABSENT },

        /* XmRSpatialPlaceStyle */
	{ "GRID",			XmGRID },
	{ "CELLS",			XmCELLS },

	/* XmRPrimaryOwnership */
	{ "OWN_NEVER",			XmOWN_NEVER },
	{ "OWN_ALWAYS",			XmOWN_ALWAYS },
	{ "OWN_MULTIPLE",		XmOWN_MULTIPLE },
	{ "OWN_POSSIBLE_MULTIPLE",	XmOWN_POSSIBLE_MULTIPLE },

        /* XmRSpatialResizeModel */
	{ "GROW_MINOR",			XmGROW_MINOR },
	{ "GROW_MAJOR",			XmGROW_MAJOR },
	{ "GROW_BALANCED",		XmGROW_BALANCED },

        /* XmRSelectionTechnique */
	{ "MARQUEE",			XmMARQUEE },
	{ "MARQUEE_EXTEND_START",	XmMARQUEE_EXTEND_START },
	{ "MARQUEE_EXTEND_BOTH",	XmMARQUEE_EXTEND_BOTH },
	{ "TOUCH_ONLY",			XmTOUCH_ONLY },
	{ "TOUCH_OVER",			XmTOUCH_OVER },

        /* XmRSpatialSnapModel */
	{ "SNAP_TO_GRID",		XmSNAP_TO_GRID },
	{ "CENTER",			XmCENTER },

        /* XmROutlineState */
	{ "COLLAPSED",			XmCOLLAPSED },
	{ "XPANDED",			XmEXPANDED },

/************************************************************************
 *                                                                      *
 * IconGadget defines                                                   *
 *                                                                      *
 ************************************************************************/

        /* XmRViewType */
	{ "LARGE_ICON",			XmLARGE_ICON },
	{ "SMALL_ICON",			XmSMALL_ICON },

        /* XmRVisualEmphasis */
	{ "SELECTED",			XmSELECTED },
	{ "NOT_SELECTED",		XmNOT_SELECTED },

/************************************************************************
 *                                                                      *
 * Notebook Widget defines                                              *
 *                                                                      *
 ************************************************************************/

	{ "UNSPECIFIED_PAGE_NUMBER",	XmUNSPECIFIED_PAGE_NUMBER },

        /* XmRBindingType */
	{ "SOLID",			XmSOLID },
	{ "SPIRAL",			XmSPIRAL },
	{ "PIXMAP_OVERLAP_ONLY",	XmPIXMAP_OVERLAP_ONLY },

        /* XmRNBChildType */
	{ "PAGE",			XmPAGE },
	{ "MAJOR_TAB",			XmMAJOR_TAB },
	{ "MINOR_TAB",			XmMINOR_TAB },
	{ "STATUS_AREA",		XmSTATUS_AREA },
	{ "PAGE_SCROLLER",		XmPAGE_SCROLLER },

/************************************************************************
 *									*
 * Spin button defines.							*
 *									*
 ************************************************************************/

	/* XmNarrowOrientation */
	{ "ARROWS_VERTICAL",		XmARROWS_VERTICAL },
	{ "ARROWS_HORIZONTAL",		XmARROWS_HORIZONTAL },

	/* XmNarrowLayout */
	{ "ARROWS_END",			XmARROWS_END },
	{ "ARROWS_BEGINNING",		XmARROWS_BEGINNING },
	{ "RROWS_SPLIT",		XmARROWS_SPLIT },
	{ "ARROWS_FLAT_END",		XmARROWS_FLAT_END },
	{ "ARROWS_FLAT_BEGINNING",	XmARROWS_FLAT_BEGINNING },

	/* XmNarrowSensitivity and XmNdefaultArrowSensitivity */
	/* Please note that these arrows form the proper values
	   for a bit mask. */
	{ "RROWS_INSENSITIVE",		XmARROWS_INSENSITIVE },
	{ "ARROWS_INCREMENT_SENSITIVE",	XmARROWS_INCREMENT_SENSITIVE },
	{ "ARROWS_DECREMENT_SENSITIVE",	XmARROWS_DECREMENT_SENSITIVE },
	{ "ARROWS_SENSITIVE",		XmARROWS_SENSITIVE },
	{ "ARROWS_DEFAULT_SENSITIVITY",	XmARROWS_DEFAULT_SENSITIVITY },

	/* XmNpositionType */
	{ "POSITION_INDEX",		XmPOSITION_INDEX },
	{ "POSITION_VALUE",		XmPOSITION_VALUE },

	/* XmNspinButtonChildType */
	{ "NUMERIC",			XmNUMERIC },

	/* Return values for Xm[Simple]SpinBoxValidatePosition */
	{ "VALID_VALUE",		XmVALID_VALUE },
	{ "CURRENT_VALUE",		XmCURRENT_VALUE },
	{ "MAXIMUM_VALUE",		XmMAXIMUM_VALUE },
	{ "MINIMUM_VALUE",		XmMINIMUM_VALUE },
	{ "INCREMENT_VALUE",		XmINCREMENT_VALUE },

/************************************************************************
 *									*
 * Scrolled Window defines.						*
 *									*
 ************************************************************************/

	{ "VARIABLE",			XmVARIABLE },
	{ "CONSTANT",			XmCONSTANT },
	{ "RESIZE_IF_POSSIBLE",		XmRESIZE_IF_POSSIBLE },

	{ "AUTOMATIC",			XmAUTOMATIC },
	{ "APPLICATION_DEFINED",	XmAPPLICATION_DEFINED },

	{ "AS_NEEDED",			XmAS_NEEDED },

	{ "TOP_LEFT",			XmTOP_LEFT },
	{ "BOTTOM_LEFT",		XmBOTTOM_LEFT },
	{ "TOP_RIGHT",			XmTOP_RIGHT },
	{ "BOTTOM_RIGHT",		XmBOTTOM_RIGHT },

/************************************************************************
 *									*
 * MainWindow Resources                                                 *
 *									*
 ************************************************************************/

	{ "COMMAND_ABOVE_WORKSPACE"	,XmCOMMAND_ABOVE_WORKSPACE },
	{ "COMMAND_BELOW_WORKSPACE",	XmCOMMAND_BELOW_WORKSPACE },

/************************************************************************
 *									*
 * Text Widget defines							*
 *									*
 ************************************************************************/

	{ "MULTI_LINE_EDIT",		XmMULTI_LINE_EDIT },
	{ "SINGLE_LINE_EDIT",		XmSINGLE_LINE_EDIT },

	/* XmTextDirection */
	{ "TEXT_FORWARD",		XmTEXT_FORWARD },
	{ "TEXT_BACKWARD",		XmTEXT_BACKWARD },

	{ "FMT_8_BIT",			XmFMT_8_BIT },
	{ "FMT_16_BIT",			XmFMT_16_BIT },

	/* XmTextScanType */
	{ "SELECT_POSITION",		XmSELECT_POSITION },
	{ "SELECT_WHITESPACE",		XmSELECT_WHITESPACE },
	{ "SELECT_WORD",		XmSELECT_WORD },
	{ "SELECT_LINE",		XmSELECT_LINE },
	{ "SELECT_ALL",			XmSELECT_ALL },
	{ "SELECT_PARAGRAPH",		XmSELECT_PARAGRAPH },
	{ "SELECT_OUT_LINE",		XmSELECT_OUT_LINE },

	/* XmHighlightMode */
	{ "HIGHLIGHT_NORMAL",		XmHIGHLIGHT_NORMAL },
	{ "HIGHLIGHT_SELECTED",		XmHIGHLIGHT_SELECTED },
	{ "HIGHLIGHT_SECONDARY_SELECTED",
	    XmHIGHLIGHT_SECONDARY_SELECTED },
	{ "SEE_DETAIL",			XmSEE_DETAIL },

	{ "COPY_FAILED",		XmCOPY_FAILED },
	{ "COPY_SUCCEEDED",		XmCOPY_SUCCEEDED },
	{ "COPY_TRUNCATED",		XmCOPY_TRUNCATED },

/************************************************************************
 *									*
 *  DIALOG defines..  BulletinBoard and things common to its subclasses *
 *          CommandBox    MessageBox    Selection    FileSelection      *
 *									*
 ************************************************************************/

	/* child type defines for Xm...GetChild() */
	{ "DIALOG_NONE",		XmDIALOG_NONE },
	{ "DIALOG_APPLY_BUTTON",	XmDIALOG_APPLY_BUTTON },
	{ "DIALOG_CANCEL_BUTTON",	XmDIALOG_CANCEL_BUTTON },
	{ "DIALOG_DEFAULT_BUTTON",	XmDIALOG_DEFAULT_BUTTON },
	{ "DIALOG_OK_BUTTON",		XmDIALOG_OK_BUTTON },
	{ "DIALOG_FILTER_LABEL",	XmDIALOG_FILTER_LABEL },
	{ "DIALOG_FILTER_TEXT",		XmDIALOG_FILTER_TEXT },
	{ "DIALOG_HELP_BUTTON",		XmDIALOG_HELP_BUTTON },
	{ "DIALOG_LIST",		XmDIALOG_LIST },
	{ "DIALOG_LIST_LABEL",		XmDIALOG_LIST_LABEL },
	{ "DIALOG_MESSAGE_LABEL",	XmDIALOG_MESSAGE_LABEL },
	{ "DIALOG_SELECTION_LABEL",	XmDIALOG_SELECTION_LABEL },
	{ "DIALOG_SYMBOL_LABEL",	XmDIALOG_SYMBOL_LABEL },
	{ "DIALOG_TEXT",		XmDIALOG_TEXT },
	{ "DIALOG_SEPARATOR",		XmDIALOG_SEPARATOR },
	{ "DIALOG_DIR_LIST",		XmDIALOG_DIR_LIST },
	{ "DIALOG_DIR_LIST_LABEL",	XmDIALOG_DIR_LIST_LABEL },

	{ "DIALOG_HISTORY_LIST",	XmDIALOG_HISTORY_LIST },
	{ "DIALOG_PROMPT_LABEL",	XmDIALOG_PROMPT_LABEL },
	{ "DIALOG_VALUE_TEXT",		XmDIALOG_VALUE_TEXT },
	{ "DIALOG_COMMAND_TEXT",	XmDIALOG_COMMAND_TEXT },
	{ "DIALOG_FILE_LIST",		XmDIALOG_FILE_LIST },
	{ "DIALOG_FILE_LIST_LABEL",	XmDIALOG_FILE_LIST_LABEL },

	/*  dialog style defines  */
	{ "DIALOG_MODELESS",		XmDIALOG_MODELESS },
	{ "DIALOG_PRIMARY_APPLICATION_MODAL",
	    XmDIALOG_PRIMARY_APPLICATION_MODAL },
	{ "DIALOG_FULL_APPLICATION_MODAL",
	    XmDIALOG_FULL_APPLICATION_MODAL },
	{ "DIALOG_SYSTEM_MODAL",	XmDIALOG_SYSTEM_MODAL },

/************************************************************************
 * XmSelectionBox, XmFileSelectionBox and XmCommand - misc. stuff       *
 ***********************************************************************/

	/* Defines for Selection child placement */
	{ "PLACE_TOP",			XmPLACE_TOP },
	{ "PLACE_ABOVE_SELECTION",	XmPLACE_ABOVE_SELECTION },
	{ "PLACE_BELOW_SELECTION",	XmPLACE_BELOW_SELECTION },

	/* Defines for file type mask:
	*/
	{ "FILE_DIRECTORY",		XmFILE_DIRECTORY },
	{ "FILE_REGULAR",		XmFILE_REGULAR },
	{ "FILE_ANY_TYPE",		XmFILE_ANY_TYPE },

	/* Defines for selection dialog type:
	*/
	{ "DIALOG_WORK_AREA",		XmDIALOG_WORK_AREA },
	{ "DIALOG_PROMPT",		XmDIALOG_PROMPT },
	{ "DIALOG_SELECTION",		XmDIALOG_SELECTION },
	{ "DIALOG_COMMAND",		XmDIALOG_COMMAND },
	{ "DIALOG_FILE_SELECTION",	XmDIALOG_FILE_SELECTION },

/************************************************************************
 *  XmMessageBox           stuff not common to other dialogs            *
 ***********************************************************************/

	/* defines for dialog type */
	{ "DIALOG_TEMPLATE",		XmDIALOG_TEMPLATE },
	{ "DIALOG_ERROR",		XmDIALOG_ERROR },
	{ "DIALOG_INFORMATION",		XmDIALOG_INFORMATION },
	{ "DIALOG_MESSAGE",		XmDIALOG_MESSAGE },
	{ "DIALOG_QUESTION",		XmDIALOG_QUESTION },
	{ "DIALOG_WARNING",		XmDIALOG_WARNING },
	{ "DIALOG_WORKING",		XmDIALOG_WORKING },

	/*  Traversal types  */
	/* XmVisibility */
	{ "VISIBILITY_UNOBSCURED",	XmVISIBILITY_UNOBSCURED },
	{ "VISIBILITY_PARTIALLY_OBSCURED",
	    XmVISIBILITY_PARTIALLY_OBSCURED },
	{ "VISIBILITY_FULLY_OBSCURED",	XmVISIBILITY_FULLY_OBSCURED },

	/* XmTraverseDirection */
	{ "TRAVERSE_CURRENT",		XmTRAVERSE_CURRENT },
	{ "TRAVERSE_NEXT",		XmTRAVERSE_NEXT },
	{ "TRAVERSE_PREV",		XmTRAVERSE_PREV },
	{ "TRAVERSE_HOME",		XmTRAVERSE_HOME },
	{ "TRAVERSE_NEXT_TAB_GROUP",	XmTRAVERSE_NEXT_TAB_GROUP },
	{ "TRAVERSE_PREV_TAB_GROUP",	XmTRAVERSE_PREV_TAB_GROUP },
	{ "TRAVERSE_UP",		XmTRAVERSE_UP },
	{ "TRAVERSE_DOWN",		XmTRAVERSE_DOWN },
	{ "TRAVERSE_LEFT",		XmTRAVERSE_LEFT },
	{ "TRAVERSE_RIGHT",		XmTRAVERSE_RIGHT },
	{ "TRAVERSE_GLOBALLY_FORWARD",	XmTRAVERSE_GLOBALLY_FORWARD },
	{ "TRAVERSE_GLOBALLY_BACKWARD",	XmTRAVERSE_GLOBALLY_BACKWARD },

/***********************************************************************
 *
 * SimpleMenu declarations and definitions.
 *
 ***********************************************************************/

	{ "PUSHBUTTON",			XmPUSHBUTTON },
	{ "TOGGLEBUTTON",		XmTOGGLEBUTTON },
	{ "RADIOBUTTON",		XmRADIOBUTTON },
	{ "CASCADEBUTTON",		XmCASCADEBUTTON },
	{ "SEPARATOR",			XmSEPARATOR },
	{ "DOUBLE_SEPARATOR",		XmDOUBLE_SEPARATOR },
	{ "TITLE",			XmTITLE },
	{ "CHECKBUTTON",		XmCHECKBUTTON },

/***********************************************************************
 *
 * BitmapConversionModel
 *
 ***********************************************************************/

	{ "MATCH_DEPTH",		XmMATCH_DEPTH },
	{ "DYNAMIC_DEPTH",		XmDYNAMIC_DEPTH },

/************************************************************************
 *  PrintShell defines
 ************************************************************************/

	{ "PDM_NOTIFY_FAIL",		XmPDM_NOTIFY_FAIL },
	{ "PDM_NOTIFY_SUCCESS",		XmPDM_NOTIFY_SUCCESS },

/************************************************************************
 *  MultiList defines
 ************************************************************************/

	{ "MULTILIST_FOUND",		XmMULTILIST_FOUND },
	{ "MULTILIST_NOT_FOUND",	XmMULTILIST_NOT_FOUND },

/************************************************************************
 *  DropDown defines
 ************************************************************************/

	{ "DROPDOWN_LABEL",		XmDROPDOWN_LABEL },
	{ "DROPDOWN_TEXT",		XmDROPDOWN_TEXT },
	{ "DROPDOWN_ARROW_BUTTON",	XmDROPDOWN_ARROW_BUTTON },
	{ "DROPDOWN_LIST",		XmDROPDOWN_LIST },

	/* XmNmwmDecorations */
	{ "MWM_DECOR_ALL",		MWM_DECOR_ALL },
	{ "MWM_DECOR_BORDER",		MWM_DECOR_BORDER },
	{ "MWM_DECOR_MAXIMIZE",		MWM_DECOR_MAXIMIZE },
	{ "MWM_DECOR_MENU",		MWM_DECOR_MENU },
	{ "MWM_DECOR_MINIMIZE",		MWM_DECOR_MINIMIZE },
	{ "MWM_DECOR_RESIZEH",		MWM_DECOR_RESIZEH },
	{ "MWM_DECOR_TITLE",		MWM_DECOR_TITLE },

	/* XmNmwmFunctions */
	{ "MWM_FUNC_ALL",		MWM_FUNC_ALL },
	{ "MWM_FUNC_CLOSE",		MWM_FUNC_CLOSE },
	{ "MWM_FUNC_MAXIMIZE",		MWM_FUNC_MAXIMIZE },
	{ "MWM_FUNC_MINIMIZE",		MWM_FUNC_MINIMIZE },
	{ "MWM_FUNC_MOVE",		MWM_FUNC_MOVE },
	{ "MWM_FUNC_RESIZE",		MWM_FUNC_RESIZE },

	{ "True", 			True },
	{ "False",			False },

	{ "EXTERNAL_HIGHLIGHT",		XmEXTERNAL_HIGHLIGHT },
	{ "INTERNAL_HIGHLIGHT",		XmINTERNAL_HIGHLIGHT },

	{ "GrabExclusive",		XtGrabExclusive },
	{ "GrabNone",			XtGrabNone },
};

size_t
num_motif_ints(void)
{
	return sizeof(motif_ints)/sizeof(motif_ints[0]);
}
