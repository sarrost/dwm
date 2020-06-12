/* See LICENSE file for copyright and license details. */

/* Appearance */
/* border pixel of windows */
static const unsigned int borderpx  = 0;
/* snap pixel */
static const unsigned int snap      = 32;
/* horiz inner gap between windows */
static const unsigned int gappih    = 10;
/* vert inner gap between windows */
static const unsigned int gappiv    = 10;
/* horiz outer gap between windows and screen edge */
static const unsigned int gappoh    = 20;
/* vert outer gap between windows and screen edge */
static const unsigned int gappov    = 20;
/* 1 means swallow floating windows by default */
static const int swallowfloating    = 0;
/* 1 means no outer gap when there is only one window */
static const int smartgaps          = 0;
/* 0 means no bar */
static const int showbar            = 1;
/* 0 means bottom bar */
static const int topbar             = 1;
static const char *fonts[]          = {
	"Hack:size=12",
	"Noto Sans CJK JP:size=12",
	"FontAwesome:pixelsize=12:antialias=true:autohint=true",
	"JoyPixels:pixelsize=12:antialias=true:autohint=true"
};
static char dmenufont[]             = "Hack:size=10";
static char normbgcolor[]           = "#00e897";
static char normbordercolor[]       = "#00e897";
static char normfgcolor[]           = "#00e897";
static char selfgcolor[]            = "#00e897";
static unsigned int baralpha        = 0xb3;
/* static unsigned int borderalpha     = OPAQUE; */
static char selbordercolor[]        = "#00e897";
static char selbgcolor[]            = "#00e897";
static char *colors[][3] = {
	/*               fg           bg           border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "spcalc", "-f", "Hack:size=16", "-g", "50x20", "-e", "bc", "-lq", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spranger",    spcmd2},
};

/* tagging */
/* Kanji 1-9 */
static const char *tags[] = { "\u4E00", "\u4E8C", "\u4E09", "\u56DB", "\u4E94", "\u516D", "\u4E03", "\u2F0B", "\u4E5D" };

static const Rule rules[] = {
	/* class    instance      title       	 tags mask    isfloating   isterminal  noswallow  monitor */
	{ "Gimp",     NULL,       NULL,       	    1 << 8,       0,           0,         0,        -1 },
	{ "St",       NULL,       NULL,       	    0,            0,           1,         0,        -1 },
	{ NULL,       NULL,       "Event Tester",   0,            0,           0,         1,        -1 },
	{ NULL,      "spterm",    NULL,       	    SPTAG(0),     1,           1,         0,        -1 },
	{ NULL,      "spcalc",    NULL,       	    SPTAG(1),     1,           1,         0,        -1 },
};

/* layout(s) */
/* factor of master area size [0.05..0.95] */
static const float mfact     = 0.55;
/* number of clients in master area */
static const int nmaster     = 1;
/* 1 means respect size hints in tiled resizals */
static const int resizehints = 1;

/* nrowgrid layout: force two clients to always split vertically */
#define FORCE_VSPLIT 1

#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
 	{ "\u611B",	tile },			/* Default: Master on left, slaves on right */
	{ "TTT",	bstack },		/* Master on top, slaves on bottom */

	{ "[@]",	spiral },		/* Fibonacci spiral */
	{ "[\\]",	dwindle },		/* Decreasing in size right and leftward */

	{ "H[]",	deck },			/* Master on left, slaves in monocle-like mode on right */
 	{ "[M]",	monocle },		/* All windows on top of eachother */

	{ "|M|",	centeredmaster },		/* Master in middle, slaves on sides */
	{ ">M>",	centeredfloatingmaster },	/* Same but master floats */

	{ "><>",	NULL },			/* no layout function means floating behavior */
	{ NULL,		NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define AltMask Mod1Mask /* meta (ALT) key */

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define STACKKEYS(MOD,ACTION) \
	/* Cycle through windows by their stack order */ \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	/* Jump to master window */ \
	{ MOD,  XK_v,   ACTION##stack,  {.i = 0 } }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };

#include <X11/XF86keysym.h>
#include "shiftview.c"

static Key keys[] = {
	/* modifier, key, function, argument */

	/* Switch tags */
	STACKKEYS(MODKEY,							focus)
	STACKKEYS(MODKEY|ShiftMask,		push)

	TAGKEYS(XK_1, 0)
	TAGKEYS(XK_2, 1)
	TAGKEYS(XK_3, 2)
	TAGKEYS(XK_4, 3)
	TAGKEYS(XK_5, 4)
	TAGKEYS(XK_6, 5)
	TAGKEYS(XK_7, 6)
	TAGKEYS(XK_8, 7)
	TAGKEYS(XK_9, 8)

	{ MODKEY,							XK_0,		view,		{.ui = ~0 } },
	{ MODKEY|ShiftMask,		XK_0,		tag,		{.ui = ~0 } },

	/* Launch help menus and task lists */
	{ MODKEY|AltMask,							XK_0, spawn,
		SHCMD("st -e nvim $SYSTEM_HELP_FILE") },
	{ MODKEY|AltMask|ShiftMask,		XK_0, spawn,
		SHCMD("st -e nvim $RICE_TASK_FILE") },
	{ MODKEY|AltMask,							XK_1, spawn,
		SHCMD("st -e nvim $NVIM_HELP_FILE") },
	{ MODKEY|AltMask,							XK_2, spawn,
		SHCMD("st -e nvim $ZSH_HELP_FILE") },
	{ MODKEY|AltMask,							XK_3, spawn,
		SHCMD("st -e nvim $VIFM_HELP_FILE") },
	{ MODKEY|AltMask,							XK_4, spawn,
		SHCMD("st -e nvim $BRAVE_HELP_FILE") },
	{ MODKEY|AltMask,							XK_5, spawn,
		SHCMD("st -e nvim $ZATHURA_HELP_FILE") },

	{ MODKEY,							XK_minus,	spawn,		SHCMD("volumewrap dec") },
	{ MODKEY|ShiftMask,		XK_minus,	spawn,		SHCMD("volumewrap min") },
	{ MODKEY,							XK_equal,	spawn,		SHCMD("volumewrap inc") },
	{ MODKEY|ShiftMask,		XK_equal,	spawn,		SHCMD("volumewrap max") },
	/* Choose to lock screen, logour, shutdown, reboot, etc. */
	{ MODKEY,							XK_BackSpace,	spawn,
		SHCMD("sysact") },
	{ MODKEY|ShiftMask,		XK_BackSpace,	spawn,
		SHCMD("sysact") },
	{ MODKEY,			XK_Tab,		view,		{0} },
	/* Close/kill window */
	{ MODKEY,																	XK_q,					killclient,	{0} },
	/* Reload dwm */
	{ MODKEY|AltMask|ShiftMask,								XK_q,	spawn,	SHCMD("pkill -1 dwm") },
	/* Logout */
	{ MODKEY|ControlMask|ShiftMask,						XK_q,	spawn,	SHCMD("pkill dwm") },
	/* Shutdown */
	{ MODKEY|AltMask|ControlMask,							XK_q,	spawn,	SHCMD("shutdown now") },
	/* Reboot */
	{ MODKEY|AltMask|ControlMask|ShiftMask,		XK_q,	spawn,	SHCMD("reboot") },
	/* Launch browser */
	{ MODKEY,							XK_w,	spawn,	SHCMD("$BROWSER") },
	/* Launch nmtui */
	{ MODKEY|ShiftMask,		XK_w,	spawn,	SHCMD("st -e sudo nmtui") },
	/* Launch neomutt */
	{ MODKEY,			XK_e,		spawn,
		SHCMD("st -e neomutt ; pkill -RTMIN+12 dwmblocks; rmdir ~/.abook") },
	/* Launch abook */
	/* { MODKEY|ShiftMask,		XK_e,		spawn, */
	/* 	SHCMD("st -e abook -C ~/.config/abook/abookrc --datafile ~/.config/abook/addressbook") }, */
	/* Launch emoji picker */
	{ MODKEY|ShiftMask,		XK_e,		spawn,		SHCMD("emoji-rofi") },
	/* Launch resource manager (bashtop) */
	{ MODKEY,							XK_r,		spawn,		SHCMD("st -e bashtop") },
	/* Launch resource manager (htop) */
	{ MODKEY|ShiftMask,		XK_r,		spawn,		SHCMD("st -e htop") },
	/* Tiling mode */
	{ MODKEY,							XK_t,	setlayout,	{.v = &layouts[0]} },
	/* Bottom stack mode */
	{ MODKEY|ShiftMask,		XK_t,	setlayout,	{.v = &layouts[1]} },
	/* Launch torrent client */
	{ MODKEY|AltMask,			XK_t,	spawn,			SHCMD("st -e transmission-remote-cli") },
	/* Fibonacci spiral mode */
	{ MODKEY,			XK_y,		setlayout,	{.v = &layouts[2]} },
	/* Dwindle mode */
	{ MODKEY|ShiftMask,		XK_y,		setlayout,	{.v = &layouts[3]} },
	/* Deck mode */
	{ MODKEY,			XK_u,		setlayout,	{.v = &layouts[4]} },
	/* Monocle mode */
	{ MODKEY|ShiftMask,		XK_u,		setlayout,	{.v = &layouts[5]} },
	/* Center master window */
	{ MODKEY,			XK_i,		setlayout,	{.v = &layouts[6]} },
	/* Center and float master window */
	{ MODKEY|ShiftMask,		XK_i,		setlayout,	{.v = &layouts[7]} },
	/* Increase/decrease the number of master windows */
	{ MODKEY,			XK_o,		incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_o,		incnmaster,     {.i = -1 } },
	/* Toggle pause */
	{ MODKEY,											XK_p,	spawn,
		SHCMD("mpc toggle") },
	/* Force pause mpd and all mpv videos */
	{ MODKEY|ShiftMask,						XK_p,	spawn,
		SHCMD("mpc pause ; pauseallmpv") },
	/* Take screenshot */
	{ MODKEY|AltMask,							XK_p,	spawn,
		SHCMD("screenshot") },
	/* Take screenshot of focused window */
	{ MODKEY|AltMask|ShiftMask,		XK_p,	spawn,
		SHCMD("screenshot --focused") },
	/* Take screenshot of selected region */
	{ MODKEY|AltMask|ControlMask,	XK_p,	spawn,
		SHCMD("sleep 0.2; screenshot --select") },
	{ MODKEY,							XK_bracketleft,		spawn,
		SHCMD("mpc seek -10") },
	{ MODKEY|ShiftMask,		XK_bracketleft,		spawn,
		SHCMD("mpc seek -60") },
	{ MODKEY,							XK_bracketright,	spawn,
		SHCMD("mpc seek +10") },
	{ MODKEY|ShiftMask,		XK_bracketright,	spawn,
		SHCMD("mpc seek +60") },
	{ MODKEY,							XK_backslash,			view,
		{0} },
	/* { MODKEY|ShiftMask,		XK_backslash,		spawn,		SHCMD("") }, */

	/* Toggle gaps */
	{ MODKEY,			XK_a,		togglegaps,	{0} },
	/* Gaps to default value */
	{ MODKEY|ShiftMask,						XK_a,	defaultgaps,	{0} },
	/* Launch anki */
	{ MODKEY|AltMask,							XK_a,	spawn,				SHCMD("anki") },
	/* Prep anki fields */
	{ MODKEY|AltMask|ShiftMask,		XK_a,	spawn,				SHCMD("st -e nvim ~/doc/anki/blank.html") },
	/* Window toggle sticky */
	{ MODKEY,							XK_s,		togglesticky,	{0} },
	{ MODKEY|AltMask,			XK_s,		spawn,				SHCMD("screenkeytoggle") },
	{ MODKEY,		XK_d,		spawn,	SHCMD("rofi -show run") },

	/* Fullscreen mode */
	{ MODKEY,			XK_f,		togglefullscr,	{0} },
	/* Floating mode */
	{ MODKEY|ShiftMask,		XK_f,		setlayout,	{.v = &layouts[8]} },
	{ MODKEY,			XK_g,		shiftview,	{ .i = -1 } },
	{ MODKEY|ShiftMask,		XK_g,		shifttag,	{ .i = -1 } },
	/* Change width of master window */
	{ MODKEY,			XK_h,		setmfact,	{.f = -0.05} },
	{ MODKEY,			XK_l,		setmfact,	{.f = +0.05} },


	/* J and K are automatically bound above in STACKEYS */
	{ MODKEY,							XK_semicolon,		shiftview,		{ .i = 1 } },
	{ MODKEY|ShiftMask,		XK_semicolon,		shifttag,			{ .i = 1 } },
	/* Toggle dropdown terminal */
	{ MODKEY,							XK_apostrophe,	togglescratch,	{.ui = 0} },
	/* Toggle dropdown calc */
	{ MODKEY|ShiftMask,		XK_apostrophe,	togglescratch,	{.ui = 1} },
	/* Spawn terminal */
	{ MODKEY,							XK_Return,	spawn,	{.v = termcmd } },
	/* Spawn Vifm */
	{ MODKEY|ShiftMask,		XK_Return,	spawn,	SHCMD("st -e vifmrun") },
	/* Increase gaps */
	{ MODKEY,							XK_z,		incrgaps,	{.i = +3 } },
	/* Decrease gaps */
	{ MODKEY|ShiftMask,		XK_z,		incrgaps,	{.i = -3 } },

	/* V is automatically bound above in STACKKEYS */

	/* Toggle statusbar */
	{ MODKEY,			XK_b,		togglebar,	{0} },
	{ MODKEY,			XK_n,		spawn,		SHCMD("st -e nvim -c VimwikiIndex") },
	/* Launch newsboat */
	{ MODKEY|ShiftMask,		XK_n,		spawn,		SHCMD("st -e newsboat; pkill -RTMIN+6 dwmblocks") },
	/* Launch ncmpcpp */
	{ MODKEY,			XK_m,		spawn,		SHCMD("st -e ncmpcpp") },
	/* Mute audio toggle */
	{ MODKEY|ShiftMask,		XK_m,		spawn,		SHCMD("volumewrap toggle") },
	/* Previous track */
	{ MODKEY,			XK_comma,	spawn,		SHCMD("mpc prev") },
	/* Restart track */
	{ MODKEY|ShiftMask,		XK_comma,	spawn,		SHCMD("mpc seek 0%") },
	/* Next track */
	{ MODKEY,			XK_period,	spawn,		SHCMD("mpc next") },
	/* Toggle playlist looping */
	{ MODKEY|ShiftMask,		XK_period,	spawn,		SHCMD("mpc repeat") },

	{ MODKEY,			XK_Left,	focusmon,	{.i = -1 } },
	{ MODKEY|ShiftMask,		XK_Left,	tagmon,		{.i = -1 } },
	{ MODKEY,			XK_Right,	focusmon,	{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_Right,	tagmon,		{.i = +1 } },

	{ MODKEY,			XK_Page_Up,	shiftview,	{ .i = -1 } },
	{ MODKEY|ShiftMask,		XK_Page_Up,	shifttag,	{ .i = -1 } },
	{ MODKEY,			XK_Page_Down,	shiftview,	{ .i = +1 } },
	{ MODKEY|ShiftMask,		XK_Page_Down,	shifttag,	{ .i = +1 } },
	{ MODKEY,			XK_Insert,	spawn,		SHCMD("notify-send \"📋 Clipboard contents:\" \"$(xclip -o -selection clipboard)\"") },

	{ MODKEY,			XK_F1,		spawn,		SHCMD("groff -mom /usr/local/share/dwm/larbs.mom -Tpdf | zathura -") },


	/* Select screen/display to use */
	{ MODKEY,			XK_F3,		spawn,		SHCMD("displayselect") },
	/* Launch pulsemixer */
	{ MODKEY|ShiftMask,			XK_v,		spawn,		SHCMD("st -e pulsemixer; kill -44 $(pidof dwmblocks)") },
	{ MODKEY,			XK_F5,		xrdb,		{.v = NULL } },
	/* Launch transmission torrent client */
	{ MODKEY,			XK_F6,		spawn,		SHCMD("torwrap") },
	{ MODKEY,			XK_F7,		spawn,		SHCMD("td-toggle") },
	{ MODKEY,			XK_F8,		spawn,		SHCMD("mailsync") },
	{ MODKEY,			XK_F9,		spawn,		SHCMD("dmenumount") },
	{ MODKEY,			XK_F10,		spawn,		SHCMD("dmenuumount") },
	{ MODKEY,			XK_F11,		spawn,		SHCMD("mpv --no-cache --no-osc --no-input-default-bindings --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },
	{ MODKEY,			XK_F12,		xrdb,		{.v = NULL } },
	/* Make window master (or switch with 2nd) */
	{ MODKEY,			XK_space,	zoom,		{0} },
	/* Make window float */
	{ MODKEY|ShiftMask,		XK_space,	togglefloating,	{0} },

	{ MODKEY,			XK_Print,	spawn,		SHCMD("dmenurecord") },
	{ MODKEY|ShiftMask,		XK_Print,	spawn,		SHCMD("dmenurecord kill") },
	{ MODKEY,			XK_Delete,	spawn,		SHCMD("dmenurecord kill") },
	{ MODKEY,			XK_Scroll_Lock,	spawn,		SHCMD("killall screenkey || screenkey &") },

	{ 0, XF86XK_AudioMute,		spawn,		SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioPrev,		spawn,		SHCMD("mpc prev") },
	{ 0, XF86XK_AudioNext,		spawn,		SHCMD("mpc next") },
	{ 0, XF86XK_AudioPause,		spawn,		SHCMD("mpc pause") },
	{ 0, XF86XK_AudioPlay,		spawn,		SHCMD("mpc play") },
	{ 0, XF86XK_AudioStop,		spawn,		SHCMD("mpc stop") },
	{ 0, XF86XK_AudioRewind,	spawn,		SHCMD("mpc seek -10") },
	{ 0, XF86XK_AudioForward,	spawn,		SHCMD("mpc seek +10") },
	{ 0, XF86XK_AudioMedia,		spawn,		SHCMD("st -e ncmpcpp") },
	{ 0, XF86XK_PowerOff,		spawn,		SHCMD("sysact") },
	{ 0, XF86XK_Calculator,		spawn,		SHCMD("st -e bc -l") },
	{ 0, XF86XK_Sleep,		spawn,		SHCMD("sudo -A zzz") },
	{ 0, XF86XK_WWW,		spawn,		SHCMD("$BROWSER") },
	{ 0, XF86XK_DOS,		spawn,		SHCMD("st") },
	{ 0, XF86XK_ScreenSaver,	spawn,		SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
	{ 0, XF86XK_TaskPane,		spawn,		SHCMD("st -e htop") },
	{ 0, XF86XK_Mail,		spawn,		SHCMD("st -e neomutt ; pkill -RTMIN+12 dwmblocks") },
	{ 0, XF86XK_MyComputer,		spawn,		SHCMD("st -e lf /") },
	/* { 0, XF86XK_Battery,		spawn,		SHCMD("") }, */
	{ 0, XF86XK_Launch1,		spawn,		SHCMD("xset dpms force off") },
	{ 0, XF86XK_TouchpadToggle,	spawn,		SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOff,	spawn,		SHCMD("synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOn,		spawn,		SHCMD("synclient TouchpadOff=0") },
	{ 0, XF86XK_MonBrightnessUp,	spawn,		SHCMD("xbacklight -inc 15") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,		SHCMD("xbacklight -dec 15") },

	/* { MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } }, */
	/* { MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } }, */
	/* { MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} }, */
	/* { MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } }, */
	/* { MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } }, */
	/* { MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } }, */
	/* { MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } }, */
	/* { MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } }, */
	/* { MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } }, */
	/* { MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } }, */
	/* { MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } }, */

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
	{ ClkStatusText,        ShiftMask,      Button3,        spawn,          SHCMD("st -e nvim ~/.local/src/dwmblocks/config.h") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        defaultgaps,	{0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,		MODKEY,		Button4,	incrgaps,	{.i = +1} },
	{ ClkClientWin,		MODKEY,		Button5,	incrgaps,	{.i = -1} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,		0,		Button4,	shiftview,	{.i = -1} },
	{ ClkTagBar,		0,		Button5,	shiftview,	{.i = 1} },
	{ ClkRootWin,		0,		Button2,	togglebar,	{0} },
};
