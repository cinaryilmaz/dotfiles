/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* volume control buttons */
static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "0", "+5%",     NULL };
static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "0", "-5%",     NULL };
static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle",  NULL };

/* applauncher */
static const char *applaunch[] = {"/usr/local/bin/applaunch", NULL};

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#00010a";
static const char col_gray2[]       = "#456268";
static const char col_gray3[]       = "#cfcec6";
static const char col_gray4[]       = "#456268";
static const char col_cyan[]        = "#010109";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray1, col_cyan  },
};

/* tagging */
static const char *tags[] = { "A", "M", "O", "N", "G", "U", "S"};

static const Rule rules[] = {
	{ "st", NULL,       NULL,       NULL,       1,            0 }
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
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
	

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char selectcopyss[] = "maim -su | xclip -selection clipboard -t image/png";
static const char selectss[] = "maim -su ~/Screenshots/$(date +%s).png";
static const char ss[] = "maim -u ~/Screenshots/$(date +%s).png";
static const char copyss[] = "maim -u | xclip -selection clipboard -t image/png";
static const char *next[] = { "playerctl",  "next", NULL};
static const char *prev[] = { "playerctl", "previous", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       33,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             36, spawn,          {.v = termcmd } },
	{ MODKEY,                       56,      togglebar,      {0} },
	{ MODKEY,                       44,      focusstack,     {.i = +1 } },
	{ MODKEY,                       45,      focusstack,     {.i = -1 } },
	{ MODKEY,                       31,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       40,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       43,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       46,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       36, zoom,           {0} },
	{ MODKEY,                       23,    view,           {0} },
	{ MODKEY|ShiftMask,             54,      killclient,     {0} },
	{ MODKEY,                       28,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       41,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       58,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       65,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             65,  togglefloating, {0} },
	{ MODKEY,                       19,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             19,      tag,            {.ui = ~0 } },
	{ MODKEY,                       59,  focusmon,       {.i = -1 } },
	{ MODKEY,                       60, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             59,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             60, tagmon,         {.i = +1 } },
	TAGKEYS(                        10,                      0)
	TAGKEYS(                        11,                      1)
	TAGKEYS(                        12,                      2)
	TAGKEYS(                        13,                      3)
	TAGKEYS(                        14,                      4)
	TAGKEYS(                        15,                      5)
	TAGKEYS(                        16,                      6)
	TAGKEYS(                        17,                      7)
	TAGKEYS(                        18,                      8)
	{ MODKEY|ShiftMask,             24,      quit,           {0} },
	{ 0,                            122, spawn, {.v = downvol } },
	{ 0,                            121, spawn, {.v = mutevol } },
	{ 0,                            123, spawn, {.v = upvol   } },
	{ ControlMask|ShiftMask,        107, spawn, SHCMD(selectcopyss) },
	{ ControlMask,                  107, spawn, SHCMD(selectss) },
	{ ShiftMask,                    107, spawn, SHCMD(copyss) },
	{ 0,                            107, spawn, SHCMD(ss) },
   	{ 0,                            171, spawn, {.v = next } },
   	{ 0,                            173, spawn, {.v = prev } },
        {MODKEY|ControlMask, 38, spawn, {.v = applaunch}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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

