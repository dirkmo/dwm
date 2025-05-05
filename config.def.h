/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 5;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int rmaster            = 1;        /* 1 means master-area is initially on the right */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "Roboto Mono:size=12" }; // see installed fonts with "fc-list"
static const char dmenufont[]       = "Roboto Mono:size=12";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_focusedborder[] = "#00bb00";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_focusedborder  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor    scratch key*/
	{ "Gimp",     NULL,       NULL,       0,            1,           -1,        0 },
	// { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1,        0 },
	{ NULL,       NULL,   "scratchpad",   0,            1,           -1,       's' },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/bash", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

/* First arg only serves to match against key in rules */
// static const char *scratchpadcmd[] = {"s", "st", "-t", "scratchpad", "-e", "pulsemixer", NULL};
static const char *scratchpadcmd[] = {"s", "alacritty", "--title", "scratchpad", "-o", "window.dimensions.columns=120", "-o", "window.dimensions.lines=50", "-e", "/usr/local/share/dwm/dwm_showkeys.sh", NULL};

#include "movestack.c"
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } }, // dmenu
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } }, // terminal
	{ MODKEY,                       XK_b,      togglebar,      {0} }, // toggle bar
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } }, // select next window in stack
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } }, // select previous window in stack
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } }, // increase number of windows in master area
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } }, // decrease number of windows in master area
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} }, // resize window: move border left
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} }, // resize window: move border right
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } }, // move window up in stack
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } }, // move window down in stack
	{ MODKEY,                       XK_Return, zoom,           {0} }, // swap master window with stack window
	{ MODKEY,                       XK_Tab,    view,           {0} }, // switch between recent tags
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} }, // kill window
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, // master/stack layout
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} }, // floating layout
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} }, // monocle layout
	{ MODKEY,                       XK_space,  setlayout,      {0} }, // switch to last layout
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} }, // toggle floating state
	{ MODKEY,                       XK_r,      togglermaster,  {0} }, // switch side of master area (left or right of screen)
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } }, // view all tags at once
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } }, // add current window to all tags
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } }, // focus previous monitor
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } }, // focus next monitor
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } }, // move window to previous monitor
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } }, // move window to next monitor
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} }, // quit DWM
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} }, // restart DWM
	{ MODKEY|ControlMask|Mod1Mask,  XK_q,      spawn,          SHCMD("/vol/config/scripts/shutdown.sh") }, // Shutdown PC
	{ MODKEY,                       XK_v,      spawn,          {.v = (const char*[]){ "brave", NULL } } }, // start Brave browser
	{ MODKEY|ShiftMask,             XK_v,      spawn,          {.v = (const char*[]){"brave", "--incognito", NULL } } }, // start Brave browser in incognito mode
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = (const char*[]){"alacritty", "-e", "dlp.sh", NULL } } },
    { MODKEY,                       XK_y,      spawn,          SHCMD("/vol/config/scripts/monitor-dual.sh")}, // enable dual-monitor
    { MODKEY|ShiftMask,             XK_y,      spawn,          SHCMD("/vol/config/scripts/monitor-single.sh")}, // enable single-monitor
	{ MODKEY,                       XK_plus,   spawn,          SHCMD("/vol/pwcb.sh")},
	{ MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("systemctl suspend")}, // suspend computer
	{ MODKEY,                       XK_dead_circumflex,  togglescratch,  {.v = scratchpadcmd } }, // show keybindings
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

