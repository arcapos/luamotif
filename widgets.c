/*
 * Copyright (c) 2009 - 2012, Micro Systems Marc Balmer, CH-5073 Gipf-Oberfrick
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

/* Lua binding for Motif */

#include <stdlib.h>

#include <X11/Xdefs.h>
#include <Xm/XmAll.h>
#include <Xm/ButtonBox.h>
#include <Xm/FontS.h>
#include <Xm/Tree.h>
#include <Xm/Outline.h>
#include <Xm/IconBox.h>

#ifdef OPENGL
#include <GL/GLwMDrawA.h>
#endif

#include <lua.h>
#include <lauxlib.h>

#include "luamotif.h"

#define GadgetConstructor(W) \
static int \
lm_##W##Gadget(lua_State *L) \
{ \
	lua_pushlightuserdata(L, xm##W##GadgetClass); \
	lua_setfield(L, -2, "__widgetClass"); \
	return 1; \
}

#define WidgetConstructor(W) \
static int \
lm_##W(lua_State *L) \
{ \
	lua_pushlightuserdata(L, xm##W##WidgetClass); \
	lua_setfield(L, -2, "__widgetClass"); \
	return 1; \
}

GadgetConstructor(ArrowButton)
GadgetConstructor(Label)
GadgetConstructor(PushButton)
GadgetConstructor(Separator)
GadgetConstructor(ToggleButton)

WidgetConstructor(ArrowButton)
WidgetConstructor(BulletinBoard)
WidgetConstructor(ButtonBox)
WidgetConstructor(CascadeButton)
WidgetConstructor(Column)
WidgetConstructor(ComboBox)
WidgetConstructor(Command)
WidgetConstructor(Container)
WidgetConstructor(DataField)
WidgetConstructor(DialogShell)
WidgetConstructor(DrawingArea)
WidgetConstructor(DrawnButton)
WidgetConstructor(FileSelectionBox)
WidgetConstructor(FontSelector)
WidgetConstructor(Form)
WidgetConstructor(Frame)
WidgetConstructor(Hierarchy)
WidgetConstructor(IconBox)
WidgetConstructor(Label)
WidgetConstructor(List)
WidgetConstructor(MainWindow)
WidgetConstructor(MessageBox)
WidgetConstructor(Notebook)
WidgetConstructor(Outline)
WidgetConstructor(PanedWindow)
WidgetConstructor(PushButton)
WidgetConstructor(RowColumn)
WidgetConstructor(Scale)
WidgetConstructor(ScrollBar)
WidgetConstructor(ScrolledWindow)
WidgetConstructor(SelectionBox)
WidgetConstructor(Separator)
WidgetConstructor(SpinBox)
WidgetConstructor(TabBox)
WidgetConstructor(TabStack)
WidgetConstructor(Text)
WidgetConstructor(TextField)
WidgetConstructor(ToggleButton)
WidgetConstructor(Tree)

#ifdef OPENGL
/* Special widgets */
static int
lm_glDrawingArea(lua_State *L)
{
	lua_pushlightuserdata(L, glwMDrawingAreaWidgetClass);
	lua_setfield(L, -2, "__widgetClass");
	return 1;
}
#endif

struct luaL_Reg lm_gadgetConstructors[] = {
	{ "ArrowButtonGadget",	lm_ArrowButtonGadget },
	{ "LabelGadget",	lm_LabelGadget },
	{ "PushButtonGadget",	lm_PushButtonGadget },
	{ "SeparatorGadget",	lm_SeparatorGadget },
	{ "ToggleButtonGadget",	lm_ToggleButtonGadget },
	{ NULL,			NULL }
};

struct luaL_Reg lm_widgetConstructors[] = {
#ifdef OPENGL
	{ "glDrawingArea",	lm_glDrawingArea },
#endif
	{ "ArrowButton",	lm_ArrowButton },
	{ "BulletinBoard",	lm_BulletinBoard },
	{ "ButtonBox",		lm_ButtonBox },
	{ "CascadeButton",	lm_CascadeButton },
	{ "Column",		lm_Column },
	{ "ComboBox",		lm_ComboBox },
	{ "Command",		lm_Command },
	{ "Container",		lm_Container },
	{ "DataField",		lm_DataField },
	{ "DialogShell",	lm_DialogShell },
	{ "DrawingArea",	lm_DrawingArea },
	{ "DrawnButton",	lm_DrawnButton },
	{ "FileSelectionBox",	lm_FileSelectionBox },
	{ "FontSelector",	lm_FontSelector },
	{ "Form",		lm_Form },
	{ "Frame",		lm_Frame },
	{ "Hierarchy",		lm_Hierarchy },
	{ "IconBox",		lm_IconBox },
	{ "Label",		lm_Label },
	{ "LabelGadget",	lm_LabelGadget },
	{ "List",		lm_List },
	{ "MainWindow",		lm_MainWindow },
	{ "MessageBox",		lm_MessageBox },
	{ "Notebook",		lm_Notebook },
	{ "Outline",		lm_Outline },
	{ "PanedWindow",	lm_PanedWindow },
	{ "PushButton",		lm_PushButton },
	{ "RowColumn",		lm_RowColumn },
	{ "Scale",		lm_Scale },
	{ "ScrollBar",		lm_ScrollBar },
	{ "ScrolledWindow",	lm_ScrolledWindow },
	{ "SelectionBox",	lm_SelectionBox },
	{ "Separator",		lm_Separator },
	{ "SpinBox",		lm_SpinBox },
	{ "TabBox",		lm_TabBox },
	{ "TabStack",		lm_TabStack },
	{ "Text",		lm_Text },
	{ "TextField",		lm_TextField },
	{ "ToggleButton",	lm_ToggleButton },
	{ "Tree",		lm_Tree },
	{ NULL,			NULL }
};
