/*
 * Copyright (c) 2009 - 2016, Micro Systems Marc Balmer, CH-5073 Gipf-Oberfrick
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
#ifdef __linux__
#include <bsd/string.h>
#endif

#include <X11/Xdefs.h>
#include <Xm/XmAll.h>

#include <iconv.h>
#include <lua.h>
#include <lauxlib.h>

#include "luamotif.h"

static int lm_getArgs(lua_State *L, int start, Arg **args);
static int get_type(const char *);

extern struct luaL_Reg lm_gadgetConstructors[];
extern struct luaL_Reg lm_widgetConstructors[];

extern struct str_constant motif_strings[];
extern struct int_constant motif_ints[];
extern size_t num_motif_strings(void);
extern size_t num_motif_ints(void);

static struct str_constant *typestr;

static Widget
lm_GetWidget(lua_State *L, int t)
{
	Widget w;

	if (!lua_istable(L, t))
		luaL_argerror(L, t, "table expected");

	lua_pushstring(L, "__widget");
	lua_rawget(L, t);
	w = (Widget)lua_topointer(L, -1);
	lua_pop(L, 1);

	if (w == NULL)
		luaL_argerror(L, t, "widget expected");

	return w;
}

static int
lm_CreateFileSelectionDialog(lua_State *L)
{
	Widget parent, dialog;
	const char *name;

	parent = lm_GetWidget(L, 1);

	name = luaL_checkstring(L, 2);
	dialog = XmCreateFileSelectionDialog(parent, (char *)name, NULL, 0);
	XtManageChild(dialog);
	lua_newtable(L);
	lua_pushlightuserdata(L, dialog);
	lua_setfield(L, -2, "__widget");
	luaL_getmetatable(L, WIDGET_METATABLE);
	lua_setmetatable(L, -2);

	return 1;
}

static int
lm_CreateFormDialog(lua_State *L)
{
	Widget parent, dialog;
	const char *name;

	parent = lm_GetWidget(L, 1);

	name = luaL_checkstring(L, 2);
	dialog = XmCreateFormDialog(parent, (char *)name, NULL, 0);
	XtManageChild(dialog);
	lua_newtable(L);
	lua_pushlightuserdata(L, dialog);
	lua_setfield(L, -2, "__widget");
	luaL_getmetatable(L, WIDGET_METATABLE);
	lua_setmetatable(L, -2);

	return 1;
}

static int
lm_CreateInformationDialog(lua_State *L)
{
	Widget parent, dialog;
	const char *name;

	parent = lm_GetWidget(L, 1);

	name = luaL_checkstring(L, 2);
	dialog = XmCreateInformationDialog(parent, (char *)name, NULL, 0);
	XtManageChild(dialog);
	lua_newtable(L);
	lua_pushlightuserdata(L, dialog);
	lua_setfield(L, -2, "__widget");
	luaL_getmetatable(L, WIDGET_METATABLE);
	lua_setmetatable(L, -2);

	return 1;
}

static int
lm_XmFileSelectionBoxGetChild(lua_State *L)
{
	Widget child, parent;
	int which;

	if (!lua_islightuserdata(L, 1))
		luaL_argerror(L, 1, "udata expected");

	parent = lua_touserdata(L, 1);
	which = luaL_checkinteger(L, 2);
	child = XmFileSelectionBoxGetChild(parent, which);
	lua_pushlightuserdata(L, child);
	return 1;
}

static int
lm_XmFileSelectionDoSearch(lua_State *L)
{
	Widget widget;
	XmString str;

	if (!lua_islightuserdata(L, 1))
		luaL_argerror(L, 1, "udata expected");
	if (!lua_islightuserdata(L, 2))
		luaL_argerror(L, 2, "udata expected");

	widget = lua_touserdata(L, 1);
	str = lua_touserdata(L, 2);
	XmFileSelectionDoSearch(widget, str);
	return 0;
}


static int
lm_XmMessageBoxGetChild(lua_State *L)
{
	Widget child, parent;
	int which;

	if (!lua_islightuserdata(L, 1))
		luaL_argerror(L, 1, "udata expected");

	parent = lua_touserdata(L, 1);
	which = luaL_checkinteger(L, 2);
	child = XmMessageBoxGetChild(parent, which);
	lua_pushlightuserdata(L, child);
	return 1;
}

static int
lm_ProcessTraversal(lua_State *L)
{
	Widget widget;
	int direction;

	widget = lm_GetWidget(L, 1);
	direction = luaL_checkinteger(L, 2);
	XmProcessTraversal(widget, (XmTraversalDirection)direction);
	return 0;
}

static int
lm_GetString(lua_State *L)
{
	Widget widget;
	char *txt;

	widget = lm_GetWidget(L, 1);

	txt = XmTextGetString(widget);
	if (txt == NULL)
		lua_pushnil(L);
	else
		lua_pushstring(L, txt);
	return 1;
}

static int
lm_Remove(lua_State *L)
{
	Widget widget;

	widget = lm_GetWidget(L, 1);
	XmTextRemove(widget);
	return 0;
}

static int
lm_Replace(lua_State *L)
{
	Widget widget;

	widget = lm_GetWidget(L, 1);
	XmTextReplace(widget, luaL_checkinteger(L, 2), luaL_checkinteger(L, 3),
	    (char *)luaL_checkstring(L, 4));
	return 0;
}

static int
lm_Insert(lua_State *L)
{
	Widget widget;

	widget = lm_GetWidget(L, 1);

	XmTextInsert(widget, luaL_checkinteger(L, 2),
	    (char *)luaL_checkstring(L, 3));
	return 0;
}

static int
lm_GetInsertionPosition(lua_State *L)
{
	Widget widget;

	widget = lm_GetWidget(L, 1);
	lua_pushinteger(L, XmTextGetInsertionPosition(widget));
	return 1;
}

static int
lm_GetLastPosition(lua_State *L)
{
	Widget widget;

	widget = lm_GetWidget(L, 1);
	lua_pushinteger(L, XmTextGetLastPosition(widget));
	return 1;
}

static int
lm_SetInsertionPosition(lua_State *L)
{
	Widget widget;

	widget = lm_GetWidget(L, 1);
	XmTextSetInsertionPosition(widget, luaL_checkinteger(L, 2));
	return 0;
}

static int
lm_SetMaxLength(lua_State *L)
{
	Widget widget;

	widget = lm_GetWidget(L, 1);
	XmTextSetMaxLength(widget, luaL_checkinteger(L, 2));
	return 0;
}

static int
lm_SetSelection(lua_State *L)
{
	Widget widget;

	widget = lm_GetWidget(L, 1);

	XmTextSetSelection(widget, luaL_checkinteger(L, 2),
	    luaL_checkinteger(L, 3),
	    XtLastTimestampProcessed(XtDisplay(widget)));
	return 0;
}

static int
lm_SetString(lua_State *L)
{
	Widget widget;

	widget = lm_GetWidget(L, 1);
	XmTextSetString(widget, (char *)luaL_checkstring(L, 2));
	return 0;
}

static int
lm_UpdateDisplay(lua_State *L)
{
	Widget widget;

	widget = lm_GetWidget(L, 1);
	XmUpdateDisplay(widget);
	return 0;
}

static void
lm_Callback(Widget widget, XtPointer client_data, XtPointer call_data)
{
	struct cb_data *cbd = (struct cb_data *)client_data;
	int nargs = 0;

	lua_rawgeti(cbd->L, LUA_REGISTRYINDEX, cbd->ref);
	if (cbd->obj != LUA_NOREF) {
		lua_rawgeti(cbd->L, LUA_REGISTRYINDEX, cbd->obj);
		nargs = 1;
	};

	if (!strcmp(cbd->callback_name, XmNtabSelectedCallback)) {
		XmTabStackCallbackStruct * ts_cbd =
		    (XmTabStackCallbackStruct *)call_data;

		lua_newtable(cbd->L);
		lua_pushlightuserdata(cbd->L, ts_cbd->selected_child);
		lua_setfield(cbd->L, -2, "__widget");
		luaL_getmetatable(cbd->L, WIDGET_METATABLE);
		lua_setmetatable(cbd->L, -2);
		nargs++;
	}

	if (lua_pcall(cbd->L, nargs, 0, 0))
		luaL_error(cbd->L, "error calling callback function:\n%s",
		    lua_tostring(cbd->L, -1));
}

static void
lm_DestroyCallback(Widget widget, XtPointer client_data, XtPointer call_data)
{
	struct cb_data *cbd = (struct cb_data *)client_data;

	luaL_unref(cbd->L, LUA_REGISTRYINDEX, cbd->ref);
	luaL_unref(cbd->L, LUA_REGISTRYINDEX, cbd->obj);
	free(cbd->callback_name);
	free(cbd);
}

static int
lm_AddCallback(lua_State *L)
{
	Widget w;
	const char *cb;
	struct cb_data *cbd;

	w = lm_GetWidget(L, 1);
	if (!lua_isstring(L, 2))
		luaL_argerror(L, 2, "string expected");
	if (!lua_isfunction(L, 3))
		luaL_argerror(L, 3, "function expected");

	/* XXX maybe leaks memory (e.g. when the widget is destroyed */
	cbd = malloc(sizeof(struct cb_data));
	if (cbd == NULL)
		luaL_error(L, "memory error");

	cbd->L = L;

	/* reference the function */
	cbd->ref = luaL_ref(L, LUA_REGISTRYINDEX);
	cb = lua_tostring(L, -1);
	cbd->callback_name = strdup(cb);
	XtAddCallback(w, (char *)cb, lm_Callback, cbd);
	lua_pop(L, 1);
	/* reference the widget */
	cbd->obj = luaL_ref(L, LUA_REGISTRYINDEX);
	XtAddCallback(w, XmNdestroyCallback, lm_DestroyCallback, cbd);
	return 0;
}

static int
lm_getArgs(lua_State *L, int start, Arg **args)
{
	XmString string;
	int narg, n;
	const char *arg;

	*args = calloc(sizeof(Arg), lua_gettop(L));
	if (*args == NULL)
		luaL_error(L, "memory error");

	for (narg = 0, n = start; n <= lua_gettop(L); n++) {
		if (lua_type(L, n) != LUA_TSTRING)
			continue;
		arg = lua_tostring(L, n);
		n++;
		switch (lua_type(L, n)) {
		case LUA_TNUMBER:
			XtSetArg((*args)[narg], (String)arg, (XtArgVal)
			    (int)lua_tonumber(L, n));
			narg++;
			break;
		case LUA_TSTRING:
			/* XXX leaks memory */
			string = XmStringCreateLocalized(
			    (char *)lua_tostring(L, n));
			XtSetArg((*args)[narg], (String)arg, (XtArgVal)string);
			narg++;
			break;
		case LUA_TFUNCTION:
			break;
		case LUA_TNIL:
			break;
		case LUA_TBOOLEAN:
			XtSetArg((*args)[narg], (String)arg, (XtArgVal)
			    (int)lua_toboolean(L, n));
			narg++;
			break;
		case LUA_TTABLE:
			break;
		case LUA_TUSERDATA:
			XtSetArg((*args)[narg], (String)arg,
			    (XtArgVal)lua_topointer(L, n));
			narg++;
			break;
		case LUA_TTHREAD:
			break;
		case LUA_TLIGHTUSERDATA:
			XtSetArg((*args)[narg], (String)arg,
			    (XtArgVal)lua_topointer(L, n));
			narg++;
			break;
		default:
			break;
		}
	}
	return narg;
}

static int
lm_GetValues(lua_State *L)
{
	Arg args[1];
	Widget widget;
	int narg, n, nn, type;
	const char *arg;
	char *value;
	Cardinal card;
	XmString text;

	widget = lm_GetWidget(L, 1);

	nn = lua_gettop(L);
	for (narg = 0, n = 2; n <= nn; n++) {
		if (lua_type(L, n) != LUA_TSTRING)
			continue;

		arg = lua_tostring(L, n);
		type = get_type(arg);
		switch (type) {
		case LUA_TNUMBER:
			XtSetArg(args[0], (String)arg, &card);
			XtGetValues(widget, args, 1);
#if LUA_VERSION_NUM >= 503
			lua_pushinteger(L, card);
#else
			lua_pushnumber(L, card);
#endif
			narg++;
			break;
		case LUA_TSTRING:
			XtSetArg(args[0], (String)arg, &text);
			XtGetValues(widget, args, 1);
			XmStringGetLtoR(text, XmFONTLIST_DEFAULT_TAG, &value);
			lua_pushstring(L, value);
			XmStringFree(text);
			narg++;
			break;
		case LUA_TFUNCTION:
			break;
		case LUA_TNIL:
			break;
		case LUA_TBOOLEAN:
			break;
		case LUA_TTABLE:
			break;
		case LUA_TUSERDATA:
			break;
		case LUA_TTHREAD:
			break;
		case LUA_TLIGHTUSERDATA:
			break;
		default:
			break;
		}
	}
	return narg;
}

static int
lm_SetValues(lua_State *L)
{
	Arg *args;
	Widget widget;
	int narg;

	widget = lm_GetWidget(L, 1);
	narg = lm_getArgs(L, 2, &args);
	XtSetValues(widget, args, narg);
	free(args);
	return 0;
}

static int
lm_SetKeyboardFocus(lua_State *L)
{
	Widget subtree, descendant;

	subtree = lm_GetWidget(L, 1);
	descendant = lm_GetWidget(L, 2);
	XtSetKeyboardFocus(subtree, descendant);
	return 0;
}

static int
lm_SetWorkWindow(lua_State *L)
{
	Widget widget, work_window;

	widget = lm_GetWidget(L, 1);
	work_window = lm_GetWidget(L, 2);
	XtVaSetValues(widget, XmNworkWindow, work_window, NULL);
	return 0;
}

static int
lm_ScrollVisible(lua_State *L)
{
	Widget w, scroll_to;

	w = lm_GetWidget(L, 1);
	scroll_to = lm_GetWidget(L, 2);

	XmScrollVisible(w, scroll_to, 0, 0);
	return 0;
}

/* Return the true widget */
static int
lm_Widget(lua_State *L)
{
	Widget widget;

	widget = lm_GetWidget(L, 1);

	lua_pushlightuserdata(L, widget);

	return 1;
}

/* Return the true XtParent as a widget */
static int
lm_XtParent(lua_State *L)
{
	Widget parent, widget;

	widget = lm_GetWidget(L, 1);

	parent = XtParent(widget);

	lua_newtable(L);
	lua_pushlightuserdata(L, parent);
	lua_setfield(L, -2, "__widget");
	luaL_getmetatable(L, WIDGET_METATABLE);
	lua_setmetatable(L, -2);

	return 1;
}

/* Return the Parent in the Lua object hierarchy */
static int
lm_Parent(lua_State *L)
{
	if (!lua_istable(L, -1))
		luaL_argerror(L, -1, "table expected");

	lua_pushstring(L, "__parent");
	lua_rawget(L, -2);
	return 1;
}

static int
lm_Popdown(lua_State *L)
{
	Widget widget;

	widget = lm_GetWidget(L, 1);
	XtPopdown(widget);
	return 0;
}

static int
lm_Popup(lua_State *L)
{
	Widget widget;
	int grab;

	widget = lm_GetWidget(L, 1);
	grab = luaL_checkinteger(L, 2);
	XtPopup(widget, grab);
	return 0;
}

static int
lm_Screen(lua_State *L)
{
	Widget widget;
	Screen *screen;

	widget = lm_GetWidget(L, 1);
	screen = XtScreen(widget);
	lua_pushinteger(L, screen->width);
	lua_pushinteger(L, screen->height);
	return 2;
};

static int
lm_Window(lua_State *L)
{
	Widget widget;

	widget = lm_GetWidget(L, 1);
	lua_pushinteger(L, XtWindow(widget));
	return 1;
};

static int
lm_XtSetLanguageProc(lua_State *L)
{
	XtAppContext app_context;
	XtLanguageProc proc;
	XtPointer client_data;

	if (lua_isnil(L, 1))
		app_context = NULL;
	else
		app_context = lua_touserdata(L, 1);
	if (lua_isnil(L, 2))
		proc = NULL;
	else
		proc = lua_touserdata(L, 2);
	if (lua_isnil(L, 3))
		client_data = NULL;
	else
		client_data = lua_touserdata(L, 3);
	XtSetLanguageProc(app_context, proc, client_data);
	return 0;
}

static int
lm_SetSensitive(lua_State *L)
{
	Widget widget;
	int value;

	widget = lm_GetWidget(L, 1);
	value = luaL_checkinteger(L, 2);
	XtSetSensitive(widget, value);
	return 0;
}

static int
lm_UnmanageChild(lua_State *L)
{
	Widget widget;

	widget = lm_GetWidget(L, 1);
	XtUnmanageChild(widget);
	return 0;
}

static int
lm_ManageChild(lua_State *L)
{
	Widget widget;

	widget = lm_GetWidget(L, 1);
	XtManageChild(widget);
	return 0;
}

static int
lm_Initialize(lua_State *L)
{
	Widget toplevel;
	XtAppContext *app;
	String *res, *r;
	const char *application_class;
	int argc = 0, nres, t;
	String *argv;

	res = NULL;
	argv = NULL;
	nres = 0;

	application_class = luaL_checkstring(L, 1);
	if (lua_gettop(L) > 2) {
		/* Count strings */
		t = lua_gettop(L);
		lua_pushnil(L);
		while (lua_next(L, t) != 0) {
			if (lua_type(L, -1) == LUA_TSTRING)
				nres++;
			lua_pop(L, 1);
		}
		if (nres > 2) {
			nres -= 2;
			argc = nres + 1;
			argv = calloc(nres + 2, sizeof(String));
			argv[0] = strdup("lua");
			/* Populate arguments */
			t = lua_gettop(L);
			r = &argv[1];
			lua_pushnil(L);
			while (lua_next(L, t) != 0) {
				if (lua_type(L, -1) == LUA_TSTRING && nres--)
						*r++ = strdup(lua_tostring(L,
						    -1));
				lua_pop(L, 1);
			}
			*r = NULL;
		}
		lua_pop(L, 1);
	}
	nres = 0;
	if (lua_gettop(L) > 1) {
		/* Count strings */
		t = lua_gettop(L);
		lua_pushnil(L);
		while (lua_next(L, t) != 0) {
			if (lua_type(L, -1) == LUA_TSTRING)
				nres++;
			lua_pop(L, 1);
		}
		if (nres > 0) {
			res = calloc(nres + 1, sizeof(String));

			/* Populate resources */
			t = lua_gettop(L);
			r = res;
			lua_pushnil(L);
			while (lua_next(L, t) != 0) {
				if (lua_type(L, -1) == LUA_TSTRING)
					*r++ = strdup(lua_tostring(L, -1));
				lua_pop(L, 1);
			}
			*r = NULL;
		}
	}
	if (argv == NULL) {
		argc = 0;
		argv = malloc(sizeof(String));
		argv[0] = NULL;
	}
	app = lua_newuserdata(L, sizeof(XtAppContext *));
	luaL_getmetatable(L, CONTEXT_METATABLE);
	lua_setmetatable(L, -2);

	toplevel = XtOpenApplication(app, (char *)application_class, NULL, 0,
	    &argc, argv, res, applicationShellWidgetClass, NULL, 0);

	lua_newtable(L);
	lua_pushlightuserdata(L, toplevel);
	lua_setfield(L, -2, "__widget");
	luaL_getmetatable(L, WIDGET_METATABLE);
	lua_setmetatable(L, -2);
	return 2;
}

static int
lm_MainLoop(lua_State *L)
{
	XtAppContext *app;

	app = luaL_checkudata(L, 1, CONTEXT_METATABLE);
	XtAppMainLoop(*app);
	return 0;
}

static int
lm_SetExitFlag(lua_State *L)
{
	XtAppContext *app;

	app = luaL_checkudata(L, 1, CONTEXT_METATABLE);
	XtAppSetExitFlag(*app);
	return 0;
}

static int
lm_ProcessEvent(lua_State *l)
{
	XEvent event;
	XtAppContext *app;

	app = luaL_checkudata(l, 1, CONTEXT_METATABLE);
	XtAppNextEvent(*app, &event);
	XtDispatchEvent(&event);
	return 0;
}

static void
lm_Input(XtPointer client_data, int *source, XtInputId *id)
{
	lm_callbackdata *cbd = (lm_callbackdata *)client_data;

	lua_rawgeti(cbd->L, LUA_REGISTRYINDEX, cbd->ref);
	if (lua_pcall(cbd->L, 0, 0, 0))
		luaL_error(cbd->L, "error calling input function:\n%s",
		    lua_tostring(cbd->L, -1));
	/*luaL_unref(cbd->L, LUA_REGISTRYINDEX, cbd->ref);
	free(cbd);*/
}

static int
lm_AddInput(lua_State *L)
{
	XtAppContext *app;
	XtIntervalId id;
	lm_callbackdata *cbd;
	int fd;

	app = luaL_checkudata(L, 1, CONTEXT_METATABLE);

	cbd = malloc(sizeof(lm_callbackdata));
	cbd->L = L;
	cbd->ref = luaL_ref(L, LUA_REGISTRYINDEX);
	fd = luaL_checkinteger(L, -1);
	lua_pop(L, 1);
	id = XtAppAddInput(*app, fd, (XtPointer)XtInputReadMask, lm_Input, cbd);
	lua_pushinteger(L, id);
	return 1;
}

static int
lm_RemoveInput(lua_State *L)
{
	XtRemoveInput(lua_tointeger(L, 1));
	return 0;
}

static void
lm_Interval(XtPointer client_data, XtIntervalId *ignored)
{
	lm_callbackdata *cbd = (lm_callbackdata *)client_data;

	lua_rawgeti(cbd->L, LUA_REGISTRYINDEX, cbd->ref);
	if (lua_pcall(cbd->L, 0, 0, 0))
		luaL_error(cbd->L, "error calling timeout function:\n%s",
		    lua_tostring(cbd->L, -1));
	luaL_unref(cbd->L, LUA_REGISTRYINDEX, cbd->ref);
	free(cbd);
}

static int
lm_AddTimeOut(lua_State *L)
{
	XtAppContext *app;
	XtIntervalId id;
	lm_callbackdata *cbd;
	unsigned long interval;

	app = luaL_checkudata(L, 1, CONTEXT_METATABLE);

	cbd = malloc(sizeof(lm_callbackdata));
	cbd->L = L;
	cbd->ref = luaL_ref(L, LUA_REGISTRYINDEX);
	interval = luaL_checkinteger(L, -1);
	lua_pop(L, 1);
	id = XtAppAddTimeOut(*app, interval, lm_Interval, cbd);
	lua_pushinteger(L, id);
	return 1;
}

static int
lm_RemoveTimeOut(lua_State *L)
{
	XtRemoveTimeOut(luaL_checkinteger(L, 1));
	return 0;
}

static int
type_compare(const void *r1, const void *r2)
{
	struct str_constant *s1, *s2;

	s1 = (struct str_constant *)r1;
	s2 = (struct str_constant *)r2;

	return strcmp(s1->value, s2->value);
}

static int
get_type(const char *string)
{
	struct str_constant *constant, key;
	int type = LUA_TNIL;

	if (typestr == NULL) {
		typestr = motif_strings;
		qsort(&motif_strings[0],
		    num_motif_strings(),
		    sizeof(motif_strings[0]), type_compare);
	}
	key.value = string;
	constant = bsearch(&key, &motif_strings[0],
	    num_motif_strings(),
	    sizeof(motif_strings[0]), type_compare);
	if (constant)
		type = constant->type;
	return type;
}

static void
lm_set_info(lua_State *L) {
	lua_pushliteral(L, "_COPYRIGHT");
	lua_pushliteral(L, "Copyright (C) 2009 - 2016 micro systems "
	    "marc balmer");
	lua_settable(L, -3);
	lua_pushliteral(L, "_DESCRIPTION");
	lua_pushliteral(L, "Motif binding for Lua");
	lua_settable(L, -3);
	lua_pushliteral(L, "_VERSION");
	lua_pushliteral(L, "Motif 1.2.0");
	lua_settable(L, -3);
}

static void
lm_register(lua_State *L, struct luaL_Reg *reg)
{
	while (reg->name != NULL) {
		lua_pushcfunction(L, reg->func);
		lua_setfield(L, -2, reg->name);
		reg++;
	}
}

static int
lm_index(lua_State *L)
{
	const char *nam;

	nam = lua_tostring(L, -1);
	lua_rawget(L, -2);
	if (lua_type(L, -1) == LUA_TNIL) {
		if (lua_getmetatable(L, -2)) {
			lua_pushstring(L, nam);
			lua_rawget(L, -2);
			/* XXX if no function found, try attributes */
		}
	}
	return 1;
}

static int
lm_newindex(lua_State *L)
{
	Arg args[1];
	Widget widget;
	lm_callbackdata *cbd;
	XmString s;
	int narg, n;
	const char *nam;
	char *nm;

	nam = lua_tostring(L, -2);

	lua_pushstring(L, "__widget");
	lua_rawget(L, 1);
	widget = (Widget)lua_topointer(L, -1);
	lua_pop(L, 1);

	if (lua_type(L, -1) == LUA_TTABLE) {
		lua_pushvalue(L, -1);
		lua_pushstring(L, nam);
		lua_rawset(L, 1);
	}

	if (widget != NULL) {
		narg = 0;
		switch (lua_type(L, -1)) {
		case LUA_TSTRING:
			nm = strdup(nam);
			s = XmStringCreateLocalized(
			    (String)lua_tostring(L, -1));
			XtSetArg(args[narg], nm, (XtArgVal)s);
			narg++;
			break;
		case LUA_TNUMBER:
			nm = strdup(nam);
#if LUA_VERSION_NUM >= 503
			XtSetArg(args[narg], nm, (XtArgVal)
			    lua_tointeger(L, -1));
#else
			XtSetArg(args[narg], nm, (XtArgVal)
			    (int)lua_tonumber(L, -1));
#endif
			narg++;
			break;
		case LUA_TBOOLEAN:
			nm = strdup(nam);
			XtSetArg(args[narg], nm, (XtArgVal)
			    (int)lua_toboolean(L, -1));
			narg++;
			break;
		case LUA_TFUNCTION:
			/* XXX maybe leaks memory */
			cbd = malloc(sizeof(struct cb_data));
			if (cbd == NULL)
				luaL_error(L, "memory error");
			cbd->L = L;
			lua_pushvalue(L, -1);
			cbd->ref = luaL_ref(L, LUA_REGISTRYINDEX);
			lua_pushvalue(L, -3);
			cbd->obj = luaL_ref(L, LUA_REGISTRYINDEX);
			cbd->callback_name = strdup(nam);
			XtAddCallback(widget, nam, lm_Callback, cbd);
			XtAddCallback(widget, XmNdestroyCallback,
			    lm_DestroyCallback, cbd);
			break;
		}
		if (narg > 0) {
			XtSetValues(widget, args, narg);
			for (n = 0; n < narg; n++)
				free(args[n].name);
		}
	}
	return 0;
}

#define MAXARGS 64

static Widget
GetTopShell(Widget w)
{
	while (w && !XtIsWMShell(w))
		w = XtParent(w);
	return w;
}

static Widget
lm_CreateWidgetHierarchy(lua_State *L, int parentObj, Widget parent,
    const char *name)
{
	Arg args[MAXARGS];
	WidgetClass class;
	Widget widget;
	XmString s;
#if 0
	iconv_t cd;
#endif
	struct cb_data *cbd;
#if 0
	int data = -1;
	size_t len, inbytesleft, outbytesleft;
#endif
	char nam[64], *nm;
	int n, narg, t;
	char *utf8_s;
#if 0
	char *utf8_s, *iso_s;
	char *inbuf, *outbuf;
#endif
	widget = NULL;
	narg = 0;

	lua_pushstring(L, "__widgetClass");
	lua_rawget(L, -2);
	class = (WidgetClass)lua_topointer(L, -1);
	lua_pop(L, 1);

	if (class != NULL) {
		t = lua_gettop(L);
		lua_pushnil(L);
		while (lua_next(L, t) != 0) {
			switch (lua_type(L, -2)) {
			case LUA_TSTRING:
				strlcpy(nam, lua_tostring(L, -2), sizeof nam);
				break;
			case LUA_TNUMBER:
				snprintf(nam, sizeof nam, "%.f",
				    lua_tonumber(L, -2));
				break;
			default:
				strlcpy(nam, name, sizeof nam);
			}

			switch (lua_type(L, -1)) {
			case LUA_TSTRING:
				utf8_s = (char *)lua_tostring(L, -1);
#if 0
				len = strlen(iso_s) * 2 + 1;
				utf8_s = malloc(len);

				cd = iconv_open("UTF-8", "ISO-8859-1");
				inbytesleft = strlen(iso_s);
				outbytesleft = len;
				inbuf = iso_s;
				outbuf = utf8_s;
				bzero(utf8_s, len);
				iconv(cd, (const char**)&inbuf, &inbytesleft,
				    &outbuf, &outbytesleft);
				iconv_close(cd);
#endif
				nm = strdup(nam);
				/* XXX ugly, ugliest... */
				if (strcmp(nam, "value") &&
				    strcmp(nam, "title")) {
					s = XmStringCreateLocalized(utf8_s);
					XtSetArg(args[narg], nm, (XtArgVal)s);
				} else
					XtSetArg(args[narg], nm, utf8_s);
				narg++;
				break;
			case LUA_TNUMBER:
				nm = strdup(nam);
#if LUA_VERSION_NUM >= 503
				XtSetArg(args[narg], nm, (XtArgVal)
				    lua_tointeger(L, -1));
#else
				XtSetArg(args[narg], nm, (XtArgVal)
				    (int)lua_tonumber(L, -1));
#endif
				narg++;
				break;
			case LUA_TBOOLEAN:
				nm = strdup(nam);
				XtSetArg(args[narg], nm, (XtArgVal)
				    (int)lua_toboolean(L, -1));
				narg++;
				break;
			}
			lua_pop(L, 1);
		}
	}

	if (class == xmDialogShellWidgetClass)
		widget = XtCreatePopupShell(name, class, GetTopShell(parent),
		    args, narg);
	else if (class == xmBulletinBoardWidgetClass)
		widget = XmCreateBulletinBoard(parent, (String)name, args, narg);
	else if (class != NULL)
		widget = XtCreateWidget(name, class, parent, args, narg);
	if (widget != NULL) {
		lua_pushlightuserdata(L, widget);
		lua_setfield(L, -2, "__widget");
		luaL_getmetatable(L, WIDGET_METATABLE);
		lua_setmetatable(L, -2);
	}

	t = lua_gettop(L);
	lua_pushnil(L);
	while (lua_next(L, t) != 0) {
		switch (lua_type(L, -2)) {
		case LUA_TSTRING:
			strlcpy(nam, lua_tostring(L, -2), sizeof nam);
			break;
		case LUA_TNUMBER:
			snprintf(nam, sizeof n, "%.f", lua_tonumber(L, -2));
			break;
		default:
			strlcpy(nam, name, sizeof nam);
		}

		switch (lua_type(L, -1)) {
		case LUA_TTABLE:
			if (widget == NULL)
				lm_CreateWidgetHierarchy(L, t, parent, nam);
			else
				lm_CreateWidgetHierarchy(L, t, widget, nam);
			break;
		case LUA_TFUNCTION:
			if (widget == NULL)
				break;

			/* XXX maybe leaks memory */
			cbd = malloc(sizeof(struct cb_data));
			if (cbd == NULL)
				luaL_error(L, "memory error");
			cbd->L = L;
			lua_pushvalue(L, -1);
			cbd->ref = luaL_ref(L, LUA_REGISTRYINDEX);
			lua_pushvalue(L, t);
			cbd->obj = luaL_ref(L, LUA_REGISTRYINDEX);
			cbd->callback_name = strdup(nam);
			XtAddCallback(widget, nam, lm_Callback, cbd);
			XtAddCallback(widget, XmNdestroyCallback,
			    lm_DestroyCallback, cbd);
			break;
		}
		lua_pop(L, 1);
	}
	for (n = 0; n < narg; n++)
		free(args[n].name);
	if (parentObj > 0) {
		lua_pushvalue(L, parentObj);
		lua_setfield(L, -2, "__parent");
	}
	if (widget)
		XtManageChild(widget);
	return widget;
}

static int
lm_DestroyWidgetHierarchy(lua_State *L)
{
	Widget widget;
	int t;

	widget = NULL;

	lua_getfield(L, -1, "__widget");
	widget = (Widget)lua_topointer(L, -1);
	lua_pop(L, 1);

	if (lua_type(L, -1) == LUA_TTABLE) {
		lua_pushnil(L);
		lua_setfield(L, -2, "__parent");

		t = lua_gettop(L);
		lua_pushnil(L);
		while (lua_next(L, t) != 0) {
			if (lua_type(L, -1) == LUA_TTABLE)
				lm_DestroyWidgetHierarchy(L);
			lua_pop(L, 1);
		}
	}
	if (widget != NULL) {
		XtDestroyWidget(widget);
		lua_pushnil(L);
		lua_setfield(L, -2, "__widget");
	}
	return 0;
}

static int
lm_Realize(lua_State *L)
{
	Widget toplevel;
	char nam[64];
	void *table;
	int t;

	toplevel = lm_GetWidget(L, 1);
	if (!lua_istable(L, 2))
		luaL_argerror(L, 2, "table expected");

	if (lua_gettop(L) == 3) {
		if (!lua_isstring(L, 3))
			luaL_argerror(L, 3, "string expected");
		strlcpy(nam, lua_tostring(L, 3), sizeof nam);
		lua_pop(L, 1);
	} else {
		table = (void *)lua_topointer(L, 2);
		strlcpy(nam, "toplevel", sizeof nam);

#if LUA_VERSION_NUM >= 502
		lua_pushglobaltable(L);
		t = lua_gettop(L);
#else
		t = LUA_GLOBALSINDEX;
#endif
		lua_pushnil(L);
		while (lua_next(L, t) != 0) {
			if (lua_topointer(L, -1) == table) {
				switch (lua_type(L, -2)) {
				case LUA_TSTRING:
					strlcpy(nam, lua_tostring(L, -2),
					    sizeof nam);
					break;
				case LUA_TNUMBER:
					snprintf(nam, sizeof nam, "%.f",
					    lua_tonumber(L, -2));
					break;
				}
			}
			lua_pop(L, 1);
		}
#if LUA_VERSION_NUM >= 502
		lua_pop(L, 1);
#endif
	}
	lm_CreateWidgetHierarchy(L, 0, toplevel, nam);
	XtRealizeWidget(toplevel);
	return 0;
}

static int
lm_Unrealize(lua_State *L)
{
	Widget w;

	w = lm_GetWidget(L, 1);
	XtUnrealizeWidget(w);

	return 0;
}

int
luaopen_motif(lua_State *L)
{
	int n;

	struct luaL_Reg luamotif[] = {
		{ "AddInput",			lm_AddInput },
		{ "Realize",			lm_Realize },
		{ "Unrealize",			lm_Unrealize },
		{ "Initialize",			lm_Initialize },
		{ "RemoveInput",		lm_RemoveInput },
		{ "RemoveTimeOut",		lm_RemoveTimeOut },
		{ "SetLanguageProc",		lm_XtSetLanguageProc },
		{ NULL, NULL }
	};
	struct luaL_Reg luaapp[] = {
		{ "__index",			lm_index },
		{ "__newindex",			lm_newindex },

		{ "CreateInformationDialog",	lm_CreateInformationDialog },
		{ "CreateFileSelectionDialog",	lm_CreateFileSelectionDialog },
		{ "CreateFormDialog",		lm_CreateFormDialog },
		{ "FileSelectionBoxGetChild",	lm_XmFileSelectionBoxGetChild },
		{ "FileSelectionDoSearch",	lm_XmFileSelectionDoSearch },
		{ "MessageBoxGetChild",		lm_XmMessageBoxGetChild },

		/* Managing, Xt */
		{ "SetSensitive",		lm_SetSensitive },
		{ "ManageChild",		lm_ManageChild },
		{ "UnmanageChild",		lm_UnmanageChild },
		{ "Screen",			lm_Screen },
		{ "Window",			lm_Window },
		{ "Parent",			lm_Parent },
		{ "XtParent",			lm_XtParent },
		{ "Widget",			lm_Widget },
		{ "Popup",			lm_Popup },
		{ "Popdown",			lm_Popdown },
		{ "UpdateDisplay",		lm_UpdateDisplay },
		{ "ProcessTraversal",		lm_ProcessTraversal },
		{ "AddCallback",		lm_AddCallback },
		{ "Destroy",			lm_DestroyWidgetHierarchy },
		{ "GetValues",			lm_GetValues },
		{ "SetValues",			lm_SetValues },
		{ "SetKeyboardFocus",		lm_SetKeyboardFocus },
		{ "SetWorkWindow",		lm_SetWorkWindow },
		{ "ScrollVisible",		lm_ScrollVisible },

		/* XmText */
		{ "GetString",			lm_GetString },
		{ "SetString",			lm_SetString },
		{ "Remove",			lm_Remove },
		{ "Replace",			lm_Replace },
		{ "Insert",			lm_Insert },
		{ "GetInsertionPosition",	lm_GetInsertionPosition },
		{ "GetLastPosition",		lm_GetLastPosition },
		{ "SetInsertionPosition",	lm_SetInsertionPosition },
		{ "SetMaxLenght",		lm_SetMaxLength },
		{ "SetSelection",		lm_SetSelection },
		{ NULL,				NULL }
	};
	struct luaL_Reg luaXtApp[] = {
		{ "AddInput",			lm_AddInput },
		{ "AddTimeOut",			lm_AddTimeOut },
		{ "MainLoop",			lm_MainLoop },
		{ "SetExitFlag",		lm_SetExitFlag },
		{ "ProcessEvent",		lm_ProcessEvent },
		{ NULL,				NULL }
	};
#if LUA_VERSION_NUM >= 502
	luaL_newlib(L, luamotif);
#else
	luaL_register(L, "motif", luamotif);
#endif
	lm_set_info(L);
	lm_register(L, lm_widgetConstructors);
	lm_register(L, lm_gadgetConstructors);

	for (n = 0; n < num_motif_strings(); n++) {
		lua_pushstring(L, motif_strings[n].value);
		lua_setfield(L, -2, motif_strings[n].name);
	};
	for (n = 0; n < num_motif_ints(); n++) {
		lua_pushinteger(L, motif_ints[n].value);
		lua_setfield(L, -2, motif_ints[n].name);
	};

	/* The Widget metatable */
	if (luaL_newmetatable(L, WIDGET_METATABLE)) {
#if LUA_VERSION_NUM >= 502
		luaL_setfuncs(L, luaapp, 0);
#else
		luaL_register(L, NULL, luaapp);
#endif
		lua_pushliteral(L, "__metatable");
		lua_pushliteral(L, "must not access this metatable");
		lua_settable(L, -3);
	}
	lua_pop(L, 1);

	/* The Xt application context metatable */
	if (luaL_newmetatable(L, CONTEXT_METATABLE)) {
#if LUA_VERSION_NUM >= 502
		luaL_setfuncs(L, luaXtApp, 0);
#else
		luaL_register(L, NULL, luaXtApp);
#endif
		lua_pushliteral(L, "__index");
		lua_pushvalue(L, -2);
		lua_settable(L, -3);

		lua_pushliteral(L, "__metatable");
		lua_pushliteral(L, "must not access this metatable");
		lua_settable(L, -3);
	}
	lua_pop(L, 1);

	return 1;
}
