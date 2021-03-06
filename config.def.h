/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 15;  /* horiz inner gap between windows */
static const unsigned int gappiv    = 15;  /* vert inner gap between windows */
static const unsigned int gappoh    = 15;  /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 15;  /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;   /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 35;
static const int horizpadbar        = 15;        /* horizontal padding for statusbar */
static const int vertpadbar         = 10;        /* vertical padding for statusbar */
static const char buttonbar[]           = " ";
static const char *fonts[]     = {"UbuntuMono Nerd Font:size=16:antialias=true:autohint=true",
                                  "Hack:size=14:antialias=true:autohint=true",
                                  "JoyPixels:size=14:antialias=true:autohint=true"};
static const char dmenufont[]  = "UbuntuMono Nerd Font:size=16:antialias=true:autohint=true";
static const char col_1[]  = "#121419"; /* background color of bar */
static const char col_2[]  = "#444444"; /* border color unfocused windows */
static const char col_3[]  = "#d7d7d7";
static const char col_4[]  = "#924441";
static const char col_5[]  = "#272a33";
static const char col_6[]  = "#e6e6e6";


static const char *colors[][3]        = {
        /*               fg         bg         border   */
        [SchemeNorm] = { col_3, col_1, col_2 },
        [SchemeSel]  = { col_3, col_4,  col_4 },
        [SchemeTitle]  = { col_6, col_5,  col_2  },
};

/* tagging */
static const char *tags[] = { " ", " ", "", "", "", "嗢", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	/*{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },*/
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
/*#include "fibonacci.c"*/
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
    { "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define CMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]    = { "dmenu_run", "-p", "Run: ", NULL };
static const char *dmenucmd2[]    = { "rofi", "-show", "drun", NULL };
static const char *termcmd[]     = { "alacritty", NULL };
static const char *termcmd2[]     = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };
static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "alsa_output.pci-0000_29_00.4.analog-stereo", "+5%",     NULL };
static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "alsa_output.pci-0000_29_00.4.analog-stereo", "-5%",     NULL };
static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute",   "alsa_output.pci-0000_29_00.4.analog-stereo", "toggle",  NULL };
#include <X11/XF86keysym.h>
static Key keys[] = {
    /* modifier                     key        function        argument */
    
    { ControlMask,     	            XK_space,      spawn,                  {.v = dmenucmd } },
    { Mod1Mask,                     XK_space,      spawn,                  {.v = dmenucmd2 } },
    { MODKEY,                       XK_Return,     spawn,                  {.v = termcmd } },
    { Mod1Mask,                     XK_s,          togglescratch,          {.v = scratchpadcmd } },
    { Mod1Mask,                     XK_Return,     spawn,                  {.v = termcmd2 } },
    { MODKEY|Mod1Mask,              XK_u,          incrgaps,               {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,    XK_u,          incrgaps,               {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_i,          incrigaps,              {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,    XK_i,          incrigaps,              {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_o,          incrogaps,              {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,    XK_o,          incrogaps,              {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_6,          incrihgaps,             {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,    XK_6,          incrihgaps,             {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_7,          incrivgaps,             {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,    XK_7,          incrivgaps,             {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_8,          incrohgaps,             {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,    XK_8,          incrohgaps,             {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_9,          incrovgaps,             {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,    XK_9,          incrovgaps,             {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_0,          togglegaps,             {0} },
    { MODKEY|Mod1Mask|ShiftMask,    XK_0,          defaultgaps,            {0} },
    { MODKEY,                       XK_b,          togglebar,              {0} },
    { MODKEY|ShiftMask,             XK_j,          rotatestack,            {.i = +1 } },
    { MODKEY|ShiftMask,             XK_k,          rotatestack,            {.i = -1 } },
    { MODKEY,                       XK_j,          focusstack,             {.i = +1 } },
    { MODKEY,                       XK_k,          focusstack,             {.i = -1 } },
    { MODKEY,                       XK_i,          incnmaster,             {.i = +1 } },
    { MODKEY,                       XK_d,          incnmaster,             {.i = -1 } },
    { MODKEY,                       XK_h,          setmfact,               {.f = -0.05} },
    { MODKEY,                       XK_l,          setmfact,               {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_Return,     zoom,                   {0} },
    { MODKEY,                       XK_Tab,        view,                   {0} },
    { MODKEY,                       XK_q,          killclient,             {0} },
    { MODKEY,                       XK_t,          setlayout,              {.v = &layouts[0]} },
    { MODKEY,                       XK_f,          setlayout,              {.v = &layouts[1]} },
    { MODKEY,                       XK_m,          setlayout,              {.v = &layouts[2]} },
    { MODKEY,                       XK_u,          setlayout,              {.v = &layouts[3]} },
    { MODKEY,                       XK_o,          setlayout,              {.v = &layouts[4]} },
    { MODKEY,                       XK_r,          setlayout,              {.v = &layouts[5]} },
    { MODKEY|ControlMask,           XK_r,          setlayout,              {.v = &layouts[6]} },
    { MODKEY,                       XK_s,          setlayout,              {.v = &layouts[7]} },
    { MODKEY|ShiftMask,             XK_s,          setlayout,              {.v = &layouts[8]} },
    { MODKEY|ShiftMask,             XK_t,          setlayout,              {.v = &layouts[9]} },
    { MODKEY|Mod1Mask,              XK_f,          setlayout,              {.v = &layouts[10]} },
    { MODKEY|ShiftMask,             XK_m,          setlayout,              {.v = &layouts[11]} },
    { MODKEY|ShiftMask,             XK_u,          setlayout,              {.v = &layouts[12]} },
    { MODKEY|ShiftMask,             XK_o,          setlayout,              {.v = &layouts[13]} },
    { MODKEY,                       XK_c,          setlayout,              {.v = &layouts[14]} },
    { MODKEY,                       XK_Tab,        cyclelayout,            {.i = -1 } },
    { MODKEY|ShiftMask,             XK_Tab,        cyclelayout,            {.i = +1 } },
    { MODKEY,                       XK_space,      setlayout,              {0} },
    { MODKEY|ShiftMask,             XK_space,      togglefloating,         {0} },
    { MODKEY|ShiftMask,             XK_f,          togglefullscr,          {0} },
    { MODKEY,                       XK_0,          view,                   {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,          tag,                    {.ui = ~0 } },
    { MODKEY,                       XK_comma,      focusmon,               {.i = -1 } },
    { MODKEY,                       XK_period,     focusmon,               {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,      tagmon,                 {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period,     tagmon,                 {.i = +1 } },
    TAGKEYS(                        XK_1,                                  0)
    TAGKEYS(                        XK_2,                                  1)
    TAGKEYS(                        XK_3,                                  2)
    TAGKEYS(                        XK_4,                                  3)
    TAGKEYS(                        XK_5,                                  4)
    TAGKEYS(                        XK_6,                                  5)
    TAGKEYS(                        XK_7,                                  6)
    TAGKEYS(                        XK_8,                                  7)
    TAGKEYS(                        XK_9,                                  8)
    { MODKEY|ShiftMask,             XK_q,          quit,                   {0} },
    { MODKEY|ShiftMask,             XK_r,          quit,                   {1} }, 
    
    /* Volume & Media Keys */
    
    { 0,                            XF86XK_AudioLowerVolume, spawn,        {.v = downvol } },
    { 0,                            XF86XK_AudioMute, spawn,               {.v = mutevol } },
    { 0,                            XF86XK_AudioRaiseVolume, spawn,        {.v = upvol   } },
   
    { 0, XF86XK_AudioPrev,          spawn,         SHCMD("playerctl previous") },
    { 0, XF86XK_AudioNext,          spawn,         SHCMD("playerctl next") },
    { 0, XF86XK_AudioPlay,          spawn,         SHCMD("playerctl play-pause") },
    
    /* Apps Launched with Alt + KEY */
    
    { Mod1Mask|ShiftMask,       XK_b,       spawn,      CMD("firefox") },
    { Mod1Mask|ShiftMask,       XK_d,       spawn,      CMD("gnome-disks") },
    { Mod1Mask|ShiftMask,       XK_m,       spawn,      CMD("gnome-system-monitor") },
    { Mod1Mask|ShiftMask,       XK_k,       spawn,      CMD("kate") },
    { Mod1Mask,                 XK_e,       spawn,      CMD("pcmanfm") },
    { Mod1Mask,                 XK_t,       spawn,      CMD("thunar") },	
    { Mod1Mask,                 XK_g,       spawn,      CMD("gthumb") },
    { Mod1Mask|ShiftMask,       XK_p,       spawn,      CMD("pavucontrol") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
    { ClkButton,		    0,		        Button1,	    spawn,		    {.v = dmenucmd } },
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

