/* See LICENSE file for copyright and license details. */

/* Appearance */
static const unsigned int borderpx  = 1; /* border pixel of windows */
static const unsigned int snap      = 32; /* snap pixel */
static const unsigned int gappih    = 20; /* horiz inner gap between windows */
static const unsigned int gappiv    = 20; /* vert inner gap between windows */
static const unsigned int gappoh    = 20; /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 20; /* vert outer gap between windows and screen edge */
static const int swallowfloating    = 0; /* 1 means swallow floating windows by default */
static const int smartgaps          = 0; /* 1 means no outer gap when there is only one window */
static const int showbar            = 1; /* 0 means no bar */
static const int topbar             = 1; /* 0 means bottom bar */
static const char *fonts[]          = {
	"SauceCodePro Nerd Font Mono:size=12",
	"Noto Sans CJK JP:size=12"
};

	/* "FontAwesome:pixelsize=12:antialias=true:autohint=true",*/
	/* "JoyPixels:pixelsize=12:antialias=true:autohint=true"*/
static char dmenufont[]             = "SauceCodePro Nerd Font Mono:size=10";
static char normbgcolor[]           = "#000000";
static char normbordercolor[]       = "#000000";
static char normfgcolor[]           = "#00e897";
static char selfgcolor[]            = "#000000";
static char selbordercolor[]        = "#00e897";
static char selbgcolor[]            = "#00e897";
static unsigned int baralpha        = 0xb3;
/* static unsigned int borderalpha     = 0x00; */
static char *colors[][3] = {
	/*               fg           bg           border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd0[] = {"st", "-n", "spterm", "-f", "SauceCodePro Nerd Font Mono:size=14", "-g", "120x36", NULL };
const char *spcmd1[] = {"st", "-n", "spquicknote", "-g", "68x24", "-e", "quicknote", NULL };

static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd0},
	{"spquicknote", spcmd1},
};

/* tagging */
/* Kanji 1-9 */
static const char *tags[] = { "\u4E00", "\u4E8C", "\u4E09", "\u56DB", "\u4E94", "\u516D", "\u4E03", "\u2F0B", "\u4E5D" };

static const Rule rules[] = {
	/* class    instance      title       	 tags mask    isfloating   isterminal  noswallow  monitor */
	{ "Gimp",     NULL,       NULL,       	    1 << 7,       0,           0,         0,        -1 },
	{ "St",       NULL,       NULL,       	    0,            0,           1,         0,        -1 },
	{ NULL,       NULL,       "Event Tester",   0,            0,           0,         1,        -1 },
	{ NULL,      "spterm",			NULL,      	    SPTAG(0),     1,           1,         0,        -1 },
	{ NULL,      "spquicknote",	NULL,      	    SPTAG(1),     1,           1,         0,        -1 },
};

/* layout(s) */
/* factor of master area size [0.05..0.95] */
static const float mfact     = 0.50;
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
#define MODKEY Mod4Mask /* windows key */
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
	/* Toggle dropdown terminal */
	{ MODKEY,											XK_apostrophe,	togglescratch,	{.ui = 0} },
	/* Toggle dropdown diary */
	{ MODKEY|AltMask,							XK_apostrophe,	togglescratch,	{.ui = 4} },
	{ MODKEY|AltMask|ShiftMask,		XK_apostrophe,	spawn, SHCMD("st -e journal open") },
	/* Previous track */
	{ MODKEY,							XK_comma,	spawn, SHCMD("mpc prev") },
	/* Restart track */
	{ MODKEY|ShiftMask,		XK_comma,	spawn, SHCMD("mpc seek 0%") },

	/* Decrease volume */
	{ MODKEY,													XK_minus,	spawn, SHCMD("volumewrap dec") },
	{ MODKEY|ShiftMask,								XK_minus,	spawn, SHCMD("volumewrap min") },
	/* Decrease music volume */
	{ MODKEY|AltMask,									XK_minus,	spawn, SHCMD("mpcvolumewrap dec") },
	{ MODKEY|AltMask|ShiftMask,				XK_minus,	spawn, SHCMD("mpcvolumewrap min") },
	/* Decrease brightness level */
	{ MODKEY|ControlMask,							XK_minus,	spawn, SHCMD("backlightwrap dec") },
	{ MODKEY|ControlMask|ShiftMask,		XK_minus,	spawn, SHCMD("backlightwrap min") },
	/* Increase volume */
	{ MODKEY,													XK_equal,	spawn, SHCMD("volumewrap inc") },
	{ MODKEY|ShiftMask,								XK_equal,	spawn, SHCMD("volumewrap max") },
	/* Increase music volume */
	{ MODKEY|AltMask,									XK_equal,	spawn, SHCMD("mpcvolumewrap inc") },
	{ MODKEY|AltMask|ShiftMask,				XK_equal,	spawn, SHCMD("mpcvolumewrap max") },
	/* Increase brightness level */
	{ MODKEY|ControlMask,							XK_equal,	spawn, SHCMD("backlightwrap inc") },
	{ MODKEY|ControlMask|ShiftMask,		XK_equal,	spawn, SHCMD("backlightwrap max") },
	/* Launch taskwarrior tui */
	{ MODKEY,													XK_grave,	spawn, SHCMD("st -e taskwarrior-tui") },
	/* Switch between previous tag */
	{ MODKEY,							XK_Tab,		view,		{0} },
	{ MODKEY,							XK_bracketleft,		spawn, SHCMD("mpc seek -10") },
	{ MODKEY|ShiftMask,		XK_bracketleft,		spawn, SHCMD("mpc seek -60") },
	{ MODKEY,							XK_bracketright,	spawn, SHCMD("mpc seek +10") },
	{ MODKEY|ShiftMask,		XK_bracketright,	spawn, SHCMD("mpc seek +60") },
	{ MODKEY,							XK_backslash,			view, {0} },
	/* { MODKEY|ShiftMask,		XK_backslash,		spawn,		SHCMD("") }, */
	{ MODKEY,							XK_semicolon,		shiftview,		{ .i = 1 } },
	{ MODKEY|ShiftMask,		XK_semicolon,		shifttag,			{ .i = 1 } },
	/* Spawn terminal */
	{ MODKEY,							XK_Return,	spawn,	{.v = termcmd } },
	/* Next track */
	{ MODKEY,							XK_period,	spawn,		SHCMD("mpc next") },
	/* Toggle playlist looping */
	{ MODKEY|ShiftMask,		XK_period,	spawn,		SHCMD("mpc repeat") },
	/* Make window master (or switch with 2nd) */
	{ MODKEY,							XK_space,		zoom,						{0} },
	/* Make window float */
	{ MODKEY|ShiftMask,		XK_space,		togglefloating,	{0} },
	/* Launch music menu, search for single track */
	{ MODKEY,													XK_slash, spawn, SHCMD("dmenu_mpd --track") },
	/* Launch music menu, search for album then title */
	{ MODKEY|ShiftMask,								XK_slash, spawn, SHCMD("dmenu_mpd --longplayer") },
	/* Launch music menu, jump to song in playlist */
	{ MODKEY|ControlMask,							XK_slash, spawn, SHCMD("dmenu_mpd --jump") },
	/* Launch music menu, search for playlist */
	{ MODKEY|AltMask,									XK_slash, spawn, SHCMD("dmenu_mpd --playlist") },
	/* Launch music menu, search for artist, then album, then title */
	{ MODKEY|ControlMask|ShiftMask,		XK_slash, spawn, SHCMD("dmenu_mpd --artist") },
	/* Toggle gaps */
	{ MODKEY,											XK_a,	togglegaps,		{0} },
	/* Gaps to default value */
	{ MODKEY|ShiftMask,						XK_a,	defaultgaps,	{0} },
	/* Pick color on screen */
	{ MODKEY|ControlMask,					XK_a, spawn, SHCMD("pickcolor") },
	/* Launch anki */
	{ MODKEY|AltMask,							XK_a, spawn, SHCMD("anki") },
	/* Prep anki fields */
	{ MODKEY|AltMask|ShiftMask,		XK_a, spawn, SHCMD("st -e nvim ~/dc/anki/blank.html") },
	/* Toggle statusbar */
	{ MODKEY,							XK_b,		togglebar,	{0} },
	/* Restart statusbar */
	{ MODKEY|ControlMask,	XK_b,		spawn, SHCMD("killall -q dwmblocks; setsid dwmblocks &") },
	/* Launch bluetooth menu */
	{ MODKEY|AltMask,			XK_b,		spawn, SHCMD("dmenu_bluetooth") },
	/* Launch clipboard manager */
	{ MODKEY,							XK_c,	spawn, SHCMD("dmenu_clip") },
	/* Toggle window compositor */
	{ MODKEY|AltMask,			XK_c,	spawn, SHCMD("compositortoggle") },
	/* Launch app launcher */
	{ MODKEY,							XK_d,	spawn, SHCMD("dmenu_run") },
	/* Launch discord */
	{ MODKEY|AltMask,			XK_d,	spawn, SHCMD("discord") },
	/* Launch neomutt */
	{ MODKEY,							XK_e, spawn, SHCMD("st -e neomutt; pkill -RTMIN+2 dwmblocks") },
	/* Sync mailbox */
	{ MODKEY|ControlMask,	XK_e, spawn, SHCMD("syncmail") },
	/* Launch emoji picker */
	{ MODKEY|AltMask,			XK_e, spawn, SHCMD("dmenu_emoji") },
	/* Launch abook */
	/* { MODKEY|ShiftMask,		XK_e,		spawn, 	SHCMD("st -e abook -C ~/.config/abook/abookrc --datafile ~/.config/abook/addressbook") }, */
	/* Fullscreen mode */
	{ MODKEY,							XK_f,		togglefullscr,	{0} },
	/* Floating mode */
	{ MODKEY|ShiftMask,		XK_f,		setlayout,	{.v = &layouts[8]} },
	/* Spawn file browser */
	{ MODKEY|ControlMask,	XK_f,		spawn,	SHCMD("st -e \"$FILE_BROWSER\"") },
	/* Go to left tag */
	{ MODKEY,							XK_g,		shiftview,	{ .i = -1 } },
	/* Send window to left tag */
	{ MODKEY|ShiftMask,		XK_g,		shifttag,	{ .i = -1 } },
	/* Increase width of master window */
	{ MODKEY,							XK_h,		setmfact,	{.f = -0.05} },
	/* Center master window */
	{ MODKEY,							XK_i,		setlayout, {.v = &layouts[6]} },
	/* Center and float master window */
	{ MODKEY|ShiftMask,		XK_i,		setlayout, {.v = &layouts[7]} },
	/* J and K are automatically bound above in STACKEYS */
	/* Decrease width of master window */
	{ MODKEY,							XK_l,		setmfact,	{.f = +0.05} },
	/* Launch ncmpcpp */
	{ MODKEY,										XK_m,			spawn,		SHCMD("st -e ncmpcpp") },
	/* Mute audio toggle */
	{ MODKEY|ShiftMask,					XK_m,			spawn,		SHCMD("volumewrap toggle") },
	/* Launch usb mounter */
	{ MODKEY|AltMask,						XK_m,			spawn,		SHCMD("dmenu_mount") },
	/* Launch usb unmounter */
	{ MODKEY|AltMask|ShiftMask,	XK_m,			spawn,		SHCMD("dmenu_umount") },
	/* Toggle dropdown quicknote */
	{ MODKEY,								XK_n,		togglescratch,	{.ui = 1} },
	/* Open vimwiki */
	{ MODKEY|ShiftMask,			XK_n,		spawn,	SHCMD("st -e nvim -c VimwikiIndex") },
	/* Launch newsboat */
	{ MODKEY|AltMask,				XK_n,		spawn,	SHCMD("st -e newsboat") },
	/* Restart network manager */
	{ MODKEY|ControlMask,		XK_n,		spawn,	SHCMD("renetwork") },
	/* Increase/decrease the number of master windows */
	{ MODKEY,								XK_o,		incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,			XK_o,		incnmaster,     {.i = -1 } },
	/* Toggle pause */
	{ MODKEY,												XK_p,	spawn, SHCMD("mpc toggle") },
	/* Force pause mpd and all mpv videos */
	{ MODKEY|ShiftMask,							XK_p,	spawn, SHCMD("mpc pause ; pauseallmpv") },
	/* Take screenshot */
	{ MODKEY|AltMask,								XK_p,	spawn, SHCMD("screenshot") },
	/* Take screenshot of focused window */
	{ MODKEY|AltMask|ShiftMask,			XK_p,	spawn, SHCMD("screenshot --focused") },
	/* Take screenshot of selected region */
	{ MODKEY|AltMask|ControlMask,		XK_p,	spawn, SHCMD("sleep 0.2; screenshot --select") },
	/* Close/kill window */
	{ MODKEY,																	XK_q,					killclient,	{0} },
	/* Reload dwm */
	{ MODKEY|ControlMask|ShiftMask,						XK_q,	spawn,	SHCMD("pkill -1 dwm; echo") },
	/* Logout */
	{ MODKEY|AltMask|ShiftMask,								XK_q,	spawn,	SHCMD("pkill dwm") },
	/* Shutdown */
	{ MODKEY|AltMask|ControlMask,							XK_q,	spawn,	SHCMD("shutdown now") },
	/* Reboot */
	{ MODKEY|AltMask|ControlMask|ShiftMask,		XK_q,	spawn,	SHCMD("reboot") },
	/* Launch resource manager (htop)) */
	{ MODKEY,							XK_r,		spawn,		SHCMD("st -f 'SauceCodePro Nerd Font Mono:size=14' -e htop") },
	/* Remap keys */
	{ MODKEY|ShiftMask,		XK_r,		spawn,		SHCMD("remapkeys") },
	/* Window toggle sticky */
	{ MODKEY,							XK_s,		togglesticky,	{0} },
	/* Toggle screenkey */
	{ MODKEY|AltMask,			XK_s,		spawn,			SHCMD("screenkeytoggle") },
	/* Tiling mode */
	{ MODKEY,							XK_t,		setlayout,	{.v = &layouts[0]} },
	/* Bottom stack mode */
	{ MODKEY|ShiftMask,		XK_t,		setlayout,	{.v = &layouts[1]} },
	/* Launch torrent client */
	{ MODKEY|AltMask,			XK_t,		spawn,			SHCMD("teams") },
	/* Launch torrent client */
	{ MODKEY|ControlMask,	XK_t,		spawn,			SHCMD("st -e tremc") },
	/* Deck mode */
	{ MODKEY,							XK_u,		setlayout,	{.v = &layouts[4]} },
	/* Monocle mode */
	{ MODKEY|ShiftMask,		XK_u,		setlayout,	{.v = &layouts[5]} },
	/* V is automatically bound above in STACKKEYS */
	/* Launch browser */
	{ MODKEY,							XK_w,	spawn, SHCMD("$BROWSER") },
	{ MODKEY|AltMask,			XK_w,	spawn, SHCMD("firefox-developer-edition") },
	/* Launch nmtui */
	{ MODKEY|ShiftMask,		XK_w,	spawn, SHCMD("st -e sudo nmtui") },
	/* Launch pulsemixer */
	{ MODKEY|AltMask,			XK_x,	spawn, SHCMD("st -e pulsemixer") },
	/* Fibonacci spiral mode */
	{ MODKEY,							XK_y,		setlayout,	{.v = &layouts[2]} },
	/* Dwindle mode */
	{ MODKEY|ShiftMask,		XK_y,		setlayout,	{.v = &layouts[3]} },
	/* Increase/decrease gaps */
	{ MODKEY,							XK_z,		incrgaps,	{.i = +3 } },
	{ MODKEY|ShiftMask,		XK_z,		incrgaps,	{.i = -3 } },
	/* Launch password manager */
	{ MODKEY|AltMask,			XK_z,		spawn, SHCMD("dmenu_pass") },

	{ MODKEY,			XK_Left,	focusmon,	{.i = -1 } },
	{ MODKEY|ShiftMask,		XK_Left,	tagmon,		{.i = -1 } },
	{ MODKEY,			XK_Right,	focusmon,	{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_Right,	tagmon,		{.i = +1 } },

	{ MODKEY,			XK_Page_Up,	shiftview,	{ .i = -1 } },
	{ MODKEY|ShiftMask,		XK_Page_Up,	shifttag,	{ .i = -1 } },
	{ MODKEY,			XK_Page_Down,	shiftview,	{ .i = +1 } },
	{ MODKEY|ShiftMask,		XK_Page_Down,	shifttag,	{ .i = +1 } },
	{ MODKEY,			XK_Insert,	spawn,		SHCMD("notify-send \"Clipboard contents:\" \"$(xclip -o -selection clipboard)\"") },
	/* Select screen/display to use */
	{ MODKEY,			XK_F3,		spawn,		SHCMD("displayselect") },
	{ MODKEY,			XK_F11,		spawn,		SHCMD("mpv --no-cache --no-osc --no-input-default-bindings --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },
	{ MODKEY,			XK_F12,		xrdb,		{.v = NULL } },

	{ 0, XF86XK_Calculator,		spawn,		SHCMD("st -e bc -l") },
	{ 0, XF86XK_Sleep,		spawn,		SHCMD("sudo -A zzz") },
	{ 0, XF86XK_ScreenSaver,	spawn,		SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
	/* { 0, XF86XK_Battery,		spawn,		SHCMD("") }, */
	{ 0, XF86XK_Launch1,		spawn,		SHCMD("xset dpms force off") },
	{ 0, XF86XK_TouchpadToggle,	spawn,		SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOff,	spawn,		SHCMD("synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOn,		spawn,		SHCMD("synclient TouchpadOff=0") },

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
