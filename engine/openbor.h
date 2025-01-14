/*
 * OpenBOR - http://www.chronocrash.com
 * -
 ----------------------------------------------------------------------
 * All rights reserved, see LICENSE in OpenBOR root for details.
 *
 * Copyright (c) 2004 - 2014 OpenBOR Team
 */

/////////////////////////////////////////////////////////////////////////////
//	Beats of Rage                                                          //
//	Side-scrolling beat-'em-up                                             //
/////////////////////////////////////////////////////////////////////////////

#ifndef OPENBOR_H
#define OPENBOR_H


/////////////////////////////////////////////////////////////////////////////

// INCS in makefile
#include	"types.h"
#include	"video.h"
#include	"vga.h"
#include	"screen.h"
#include	"transform.h"
#include	"loadimg.h"
#include	"bitmap.h"
#include	"sprite.h"
#include	"spriteq.h"
#include	"font.h"
#include	"timer.h"
#include	"rand32.h"
#include	"sblaster.h"
#include	"soundmix.h"
#include	"control.h"
#include	"draw.h"
#include	"packfile.h"
#include	"palette.h"
#include	"anigif.h"
#include    "config.h"
#include    "globals.h"
#include    "ram.h"
#include    "version.h"
#include    "savedata.h"

#ifdef SDL
#include    "gfx.h"
#endif

#ifdef WEBM
#include    "yuv.h"
#include    "vidplay.h"
#endif

/////////////////////////////////////////////////////////////////////////////

#define		DEFAULT_SHUTDOWN_MESSAGE \
			"OpenBOR " VERSION ", Compile Date: " __DATE__ "\n" \
			"Presented by the OpenBOR Team.\n" \
			"www.chronocrash.com\n"\
			"OpenBOR is the open source continuation of Beats of Rage by Senile Team.\n" \
			"\n" \
			"Special thanks to SEGA and SNK.\n\n"

#define		COMPATIBLEVERSION	0x00033748
#define		CV_SAVED_GAME		0x00033747
#define		CV_HIGH_SCORE		0x00033747
#define     GAME_SPEED          200
#define		THINK_SPEED			2
#define		COUNTER_SPEED		(GAME_SPEED*2)
#define		MAX_NAME_LEN		50 //47
#define		MAX_ENTS			150
#define		MAX_SPECIALS		8					// Added for customizable freespecials
#define     MAX_SPECIAL_INPUTS  27                  // max freespecial input steps, MAX_SPECIAL_INPUTS-1 is reserved, MAX_SPECIAL_INPUTS-2 is animation index, MAX_SPECIAL_INPUTS-3 is reserved. OX -4 , -5 , -6 , -7 , -8 , -9 , -10 also for cancels
#define		MAX_ATCHAIN			12					// max attack chain length
#define     MAX_IDLES           1                   // Idle animations.
#define     MAX_WALKS           1                   // Walk animations.
#define     MAX_BACKWALKS       1                   // Backwalk animations.
#define     MAX_UPS             1                   // Walk up animations.
#define     MAX_DOWNS           1                   // Walk down animations.
#define		MAX_ATTACKS			4					// Total number of attacks players have
#define     MAX_FOLLOWS         4					// For followup animations
#define     MAX_COLLISIONS      2                   // Collision boxes.
#define		MAX_ARG_LEN			512
#define		MAX_ALLOWSELECT_LEN	1024
#define		MAX_SELECT_LOADS   	512
#define		MAX_PAL_SIZE		1024
#define		MAX_CACHED_BACKGROUNDS 9
#define     MAX_ARG_COUNT       64
#define     MAX_ATTACK_IDS      4                   // Number of attack ID's kept to avoid single collision hitting on each update.
#define     PLATFORM_DEFAULT_X  99999

#define     LIFESPAN_DEFAULT	0x7fffffff
/*
Note: the min Z coordinate of the player is important
for several other drawing operations.
movement restirctions are here!
*/

#define		FRONTPANEL_Z		(PLAYER_MAX_Z+50)
#define     HUD_Z               (FRONTPANEL_Z+10000)
#define		HOLE_Z				(PLAYER_MIN_Z-46)
#define		SHADOW_Z			(PLAYER_MIN_Z-47)
#define		NEONPANEL_Z			(PLAYER_MIN_Z-48)
#define		SCREENPANEL_Z		(PLAYER_MIN_Z-49)
#define		PANEL_Z				(PLAYER_MIN_Z-50)
#define		MIRROR_Z			(PLAYER_MIN_Z-5)
#define		PIT_DEPTH			-250
#define		P2_STATS_DIST		180
#define		CONTACT_DIST_H		30					// Distance to make contact
#define		CONTACT_DIST_V		12
#define		GRAB_DIST			36					// Grabbing ents will be placed this far apart.
#define		GRAB_STALL			(GAME_SPEED * 8 / 10)
#define		T_WALKOFF 			2.0
#define		T_MIN_BASEMAP 		-1000
#define     T_MAX_CHECK_ALTITUDE 9999999
#define		DEFAULT_ATK_DROPV_Y 3.0
#define		DEFAULT_ATK_DROPV_X 1.2
#define		DEFAULT_ATK_DROPV_Z 0
#define		FRAME_NONE			-1	// Lot of things use frames 0+, and this value to mean they are disabled.
#define		MODEL_INDEX_NONE	-1	// No model/disabled.
#define		SAMPLE_ID_NONE	    -1	// No sound sameple/disabled.

#define		ITEM_HIDE_POSITION_Z 100000		// Weapon items in use are still in play, but we need them out of the way and unseen.
#define		MODEL_SPEED_NONE			9999999	// Many legacy calculations are set to up to override a 0 value with some default - but we would like to have a 0 option for authors. We can use this as a "didn't populate the value" instead.

#define MAP_INDEX_NONE -1

typedef enum e_ajspecial_config
{
    AJSPECIAL_KEY_SPECIAL,
    AJSPECIAL_KEY_DOUBLE,
    AJSPECIAL_KEY_ATTACK2,
    AJSPECIAL_KEY_ATTACK3,
    AJSPECIAL_KEY_ATTACK4
} e_ajspecial_config;

/*
* Caskey, Damon V.
* 2022-04-19
* 
* Screen status flags.
* Kratus (04-2022) Added the "showgo" event accessible by script
*/
typedef enum
{
    IN_SCREEN_NONE                  = 0,
    IN_SCREEN_BUTTON_CONFIG_MENU    = (1 << 0),
    IN_SCREEN_CHEAT_OPTIONS_MENU    = (1 << 1),
    IN_SCREEN_CONTROL_OPTIONS_MENU  = (1 << 2),
    IN_SCREEN_ENGINE_CREDIT         = (1 << 3),
    IN_SCREEN_GAME_OVER             = (1 << 4),
    IN_SCREEN_GAME_START_MENU       = (1 << 5),
    IN_SCREEN_HALL_OF_FAME          = (1 << 6),
    IN_SCREEN_LOAD_GAME_MENU        = (1 << 7),
    IN_SCREEN_MENU                  = (1 << 8),
    IN_SCREEN_NEW_GAME_MENU         = (1 << 9),
    IN_SCREEN_OPTIONS_MENU          = (1 << 10),
    IN_SCREEN_SELECT                = (1 << 11),
    IN_SCREEN_SHOW_COMPLETE         = (1 << 12),
    IN_SCREEN_SHOW_GO_ARROW         = (1 << 13),
    IN_SCREEN_SOUND_OPTIONS_MENU    = (1 << 14),
    IN_SCREEN_SYSTEM_OPTIONS_MENU   = (1 << 15),
    IN_SCREEN_TITLE                 = (1 << 16),
    IN_SCREEN_VIDEO_OPTIONS_MENU    = (1 << 17)
} e_screen_status;

// Caskey, Damon V.
// 2019-01-27
// 
// Flags for animation status.
typedef enum
{
	ANIMATING_REVERSE = -1,
	ANIMATING_NONE = 0,
	ANIMATING_FORWARD = 1
} e_animating;

// Caskey, Damon V.
// 2019-02-04
//
// Flags for special attack force values.
typedef enum
{
	ATTACK_FORCE_LAND_AUTO		= -1,
	ATTACK_FORCE_LAND_COMMAND	= -2
} e_attack_force;

// Caskey, Damon V.
// 2019-02-05
typedef enum
{
	AUTOKILL_NONE				= 0,
	AUTOKILL_ANIMATION_COMPLETE	= (1 << 0),
	AUTOKILL_ATTACK_HIT			= (1 << 1)
} e_autokill_state;

// Caskey, Damon V.
// 2019-02-05
typedef enum
{
	INVINCIBLE_NONE			= 0,
	INVINCIBLE_INTANGIBLE	= (1 << 0),
	INVINCIBLE_HP_MINIMUM	= (1 << 1),
	INVINCIBLE_HP_NULLIFY	= (1 << 2),
	INVINCIBLE_HP_RESET		= (1 << 3)
} e_invincible_state;

// Caskey, Damon V.
// 2019-01-25
// 
// Flags used to time update functions.
typedef enum
{
	UPDATE_MARK_NONE				= 0,
	UPDATE_MARK_CHECK_AI			= (1 << 0),
	UPDATE_MARK_CHECK_GRAVITY		= (1 << 1),
	UPDATE_MARK_CHECK_MOVE			= (1 << 2),
	UPDATE_MARK_UPDATE_ANIMATION	= (1 << 3)	
} e_update_mark;

// Caskey, Damon V.
// 2019-02-04
//
// Flags for legacy bomb projectiles.
typedef enum
{
	EXPLODE_NONE		= 0,
	EXPLODE_PREPARED	= (1 << 0),
	EXPLODE_DETONATE	= (1 << 1)
} e_explode_state;

// Caskey, Damon V.
// 2019-01-25
//
// Flags for rising state.
typedef enum
{
	RISING_NONE	= 0,
	RISING_RISE		= (1 << 0),
	RISING_ATTACK	= (1 << 1)
} e_rising_state;

/*
* Caskey, Damon V.
* 2022-04-09
* 
* Pain (hitstun) state.
*/
typedef enum
{
    IN_PAIN_NONE = 0,
    IN_PAIN_HIT = (1 << 0),
    IN_PAIN_BACK = (1 << 1),
    IN_PAIN_BLOCK = (1 << 2)
} e_inpain_state;

// PLAY/REC INPUT vars
typedef struct InputKeys
{
    u64 keys[MAX_PLAYERS];
    u64 newkeys[MAX_PLAYERS];
    u64 releasekeys[MAX_PLAYERS];
    u64 playkeys[MAX_PLAYERS];
    u32 time;
    u32 interval;
    u32 synctime;
} RecKeys;

typedef enum
{
    A_REC_STOP,
    A_REC_REC,
    A_REC_PLAY,
    A_REC_FREE,
} a_recstatus;

typedef struct PlayRecStatus {
  char filename[MAX_ARG_LEN];
  char path[MAX_ARG_LEN];
  int status; // 0 = stop / 1 = rec / 2 = play
  int begin;
  u32 starttime;
  u32 endtime;
  u32 synctime; // used to sync rec time with game time
  u32 totsynctime;
  u32 cseed;
  unsigned long seed;
  unsigned ticks;
  FILE *handle;
  RecKeys *buffer;
} a_playrecstatus;

extern a_playrecstatus *playrecstatus;

// Caskey, Damon V.
// 2019-03-29
//
// Blending options.
typedef enum
{
	BLEND_MODE_MODEL = -1,
	BLEND_MODE_NONE,
	BLEND_MODE_ALPHA,
	BLEND_MODE_ALPHA_NEGATIVE,
	BLEND_MODE_OVERLAY,
	BLEND_MODE_HARDLIGHT,
	BLEND_MODE_DODGE,
	BLEND_MODE_AVERAGE
} e_blend_mode;

// Caskey, Damon V.
// 2018-04-23
//
// Initial values for projectile spawns.
typedef enum
{
    // Use bitwise ready values here so we can cram
    // different types of data into one value.

	PROJECTILE_PRIME_NONE				= 0,

    // Source for projectiles base.
    PROJECTILE_PRIME_BASE_FLOOR         = (1 << 0),
    PROJECTILE_PRIME_BASE_Y             = (1 << 1),

    // Movement behavior on launch.
    PROJECTILE_PRIME_LAUNCH_MOVING      = (1 << 2),
    PROJECTILE_PRIME_LAUNCH_STATIONARY  = (1 << 3),
	
    // How was projectile model determined?
	PROJECTILE_PRIME_SOURCE_GLOBAL_KNIFE		= (1 << 4),		// Global "Knife".
	PROJECTILE_PRIME_SOURCE_GLOBAL_SHOT			= (1 << 5),		// Global "Shot".
	PROJECTILE_PRIME_SOURCE_GLOBAL_STAR			= (1 << 6),		// Global "Shot".
	PROJECTILE_PRIME_SOURCE_MODEL_BOMB			= (1 << 7),		// Model header property.
	PROJECTILE_PRIME_SOURCE_MODEL_KNIFE			= (1 << 8),		// Model header property.
	PROJECTILE_PRIME_SOURCE_MODEL_PSHOTNO		= (1 << 9),		// Model header property.
	PROJECTILE_PRIME_SOURCE_MODEL_STAR			= (1 << 10),	// Model header property.
	PROJECTILE_PRIME_SOURCE_PROJ_BOMB			= (1 << 11),	// Projectile bomb setting.
	PROJECTILE_PRIME_SOURCE_PROJ_FLASH			= (1 << 12),	// Projectile flash setting.
	PROJECTILE_PRIME_SOURCE_PROJ_KNIFE			= (1 << 13),	// Projectile knife/shot setting.
	PROJECTILE_PRIME_SOURCE_PROJ_STAR			= (1 << 14),	// Projectile star setting.
	PROJECTILE_PRIME_SOURCE_WEAPON_PROJECTILE	= (1 << 15)		// From a SUBTYPE_PROJECTLE weapon pickup.

} e_projectile_prime;

// Caskey, Damon V.
// 2019-12-17
// 
// Select how to launch a projectile, as a bomb or knife. 
typedef enum
{
	// Maintain order for legacy 
	// compatability (before named constants).
	PROJECTILE_TYPE_KNIFE,
	PROJECTILE_TYPE_BOMB
} e_projectile_type;

// Caskey, Damon V.
// 2019-12-17
// 
// Select using self or parent's offense factors. 
typedef enum
{
	PROJECTILE_OFFENSE_PARENT,
	PROJECTILE_OFFENSE_SELF
} e_projectile_offense;

// State of attack boxes.
typedef enum
{
    ATTACKING_NONE,
    ATTACKING_PREPARED,
    ATTACKING_ACTIVE
    // Next should be 4, 8, ... for bitwise evaluations.
} e_attacking_state;

// Caskey, Damon V.
// 2019-02-06
//
// State of blasted (thrown or hit withblasting attack).
typedef enum
{
	BLAST_NONE,
	BLAST_ATTACK,
	BLAST_TOSS
} e_blasted_state;

// State of idle
typedef enum
{
    IDLING_NONE,
    IDLING_PREPARED,
    IDLING_ACTIVE
} e_idling_state;

// State of edge.
typedef enum
{
    EDGE_NONE,
    EDGE_LEFT,
    EDGE_RIGHT
} e_edge_state;

// State of duck.
typedef enum
{
    DUCK_NONE	= 0,
    DUCK_PREPARED	= (1 << 0),
    DUCK_ACTIVE		= (1 << 1),
    DUCK_RISE		= (1 << 2)
} e_duck_state;

// Platform props
typedef enum
{
    PLATFORM_X,
    PLATFORM_Z,
    PLATFORM_UPPERLEFT,
    PLATFORM_LOWERLEFT,
    PLATFORM_UPPERRIGHT,
    PLATFORM_LOWERRIGHT,
    PLATFORM_DEPTH,
    PLATFORM_HEIGHT
} e_platform_props;

typedef enum
{
    PORTING_ANDROID,
    PORTING_DARWIN,
    PORTING_DREAMCAST,
    PORTING_GPX2,
    PORTING_LINUX,
    PORTING_OPENDINGUX,
    PORTING_PSP,
    PORTING_UNKNOWN,
    PORTING_WII,
    PORTING_WINDOWS,
    PORTING_WIZ,
    PORTING_XBOX,
    PORTING_VITA
} e_porting;

// Caskey, Damon V.
// 2019-01-08
//
// Debugging display options for end user.
typedef enum
{
	DEBUG_DISPLAY_NONE				= (1 << 0),
	DEBUG_DISPLAY_COLLISION_ATTACK	= (1 << 1),
	DEBUG_DISPLAY_COLLISION_BODY	= (1 << 2),
	DEBUG_DISPLAY_PERFORMANCE		= (1 << 3),
	DEBUG_DISPLAY_PROPERTIES		= (1 << 4),
	DEBUG_DISPLAY_RANGE				= (1 << 5)
} e_debug_display;

typedef enum
{
    SPAWN_TYPE_UNDEFINED,
    SPAWN_TYPE_BIKER,
    SPAWN_TYPE_CMD_SPAWN,
    SPAWN_TYPE_CMD_SUMMON,
	SPAWN_TYPE_DUST_DROP,
    SPAWN_TYPE_DUST_FALL,
    SPAWN_TYPE_DUST_JUMP,
    SPAWN_TYPE_DUST_LAND,
    SPAWN_TYPE_FLASH,
    SPAWN_TYPE_FLASH_SMARTBOMB,
    SPAWN_TYPE_ITEM,
    SPAWN_TYPE_LEVEL,
    SPAWN_TYPE_PLAYER_MAIN,
    SPAWN_TYPE_PLAYER_SELECT,
    SPAWN_TYPE_PROJECTILE_BOMB,
    SPAWN_TYPE_PROJECTILE_NORMAL,
    SPAWN_TYPE_PROJECTILE_STAR,
    SPAWN_TYPE_STEAM,
    SPAWN_TYPE_WEAPON
} e_spawn_type;

typedef enum
{
    PLANE_X,
    PLANE_Y,
    PLANE_Z
} e_plane;

typedef struct
{
    int x;
    int y;
    int font_index;
} s_debug_xy_msg;


// Caskey, Damon V
// 2013-12-27
//
// Key definitions.
typedef enum
{
    SDID_MOVEUP,
    SDID_MOVEDOWN,
    SDID_MOVELEFT,
    SDID_MOVERIGHT,
    SDID_ATTACK,
    SDID_ATTACK2,
    SDID_ATTACK3,
    SDID_ATTACK4,
    SDID_JUMP,
    SDID_SPECIAL,
    SDID_START,
    SDID_SCREENSHOT,
    SDID_ESC,
    SDID_COUNT // not a key ID; it's the number of key IDs
} e_key_id;


/*
* plombo (replaces previous enum by Caskey, Damon V.)
* 2021-xx-xx
*/
typedef enum
{
    FLAG_MOVEUP = (1 << SDID_MOVEUP),
    FLAG_MOVEDOWN = (1 << SDID_MOVEDOWN),
    FLAG_MOVELEFT = (1 << SDID_MOVELEFT),
    FLAG_MOVERIGHT = (1 << SDID_MOVERIGHT),
    FLAG_ATTACK = (1 << SDID_ATTACK),
    FLAG_ATTACK2 = (1 << SDID_ATTACK2),
    FLAG_ATTACK3 = (1 << SDID_ATTACK3),
    FLAG_ATTACK4 = (1 << SDID_ATTACK4),
    FLAG_JUMP = (1 << SDID_JUMP),
    FLAG_SPECIAL = (1 << SDID_SPECIAL),
    FLAG_START = (1 << SDID_START),
    FLAG_SCREENSHOT = (1 << SDID_SCREENSHOT),
    FLAG_ESC = (1 << SDID_ESC),

    FLAG_ANYBUTTON = (FLAG_START | FLAG_SPECIAL | FLAG_ATTACK | FLAG_ATTACK2 | FLAG_ATTACK3 | FLAG_ATTACK4 | FLAG_JUMP),
    FLAG_CONTROLKEYS = (FLAG_SPECIAL | FLAG_ATTACK | FLAG_ATTACK2 | FLAG_ATTACK3 | FLAG_ATTACK4 | FLAG_JUMP | FLAG_MOVEUP | FLAG_MOVEDOWN | FLAG_MOVELEFT | FLAG_MOVERIGHT),
    FLAG_FORWARD = 0x40000000,
    FLAG_BACKWARD = 0x80000000
} e_key_def;

// Caskey, Damon V.
// 2013-12-27
//
// Entity types.
typedef enum
{
	TYPE_UNDELCARED = -1,			
    TYPE_NONE		= 0,
    TYPE_PLAYER		= (1 << 0),
    TYPE_ENEMY		= (1 << 1),
    TYPE_ITEM		= (1 << 2),
    TYPE_OBSTACLE	= (1 << 3),
    TYPE_PROJECTILE	= (1 << 4),		// 2019-12-27: Projectile type for use by any entity that doesn't have all the legacy baggage.
	TYPE_STEAMER	= (1 << 5),
    TYPE_SHOT		= (1 << 6),		// 7-1-2005 type to use for player projectiles
    TYPE_TRAP		= (1 << 7),		// 7-1-2005 lets face it enemies are going to just let you storm in without setting a trap or two!
    TYPE_TEXTBOX	= (1 << 8),		// New textbox type for displaying messages
    TYPE_ENDLEVEL	= (1 << 9),		// New endlevel type that ends the level when touched
    TYPE_NPC		= (1 << 10),	// A character can be an ally or enemy.
    TYPE_PANEL		= (1 << 12),	// Fake panel, scroll with screen using model speed
	TYPE_UNKNOWN	= (1 << 13),	// Not a real type - probably means something went wrong.
	TYPE_MAX		= TYPE_UNKNOWN,	// For openbor constant check and type hack (i.e., custom hostile and candamage)
	TYPE_RESERVED	= 0x40000000    // should not use as a type
} e_entity_type;

// Caskey, Damon V.
// 2013-12-27
//
// Entity sub-types.
typedef enum
{
    SUBTYPE_NONE		= (1 << 0),
    SUBTYPE_BIKER		= (1 << 1),
    SUBTYPE_NOTGRAB		= (1 << 2),
    SUBTYPE_ARROW		= (1 << 3),		// 7-1-2005  subtype for an "enemy" that flies across the screen and dies
    SUBTYPE_TOUCH		= (1 << 4),		// ltb 1-18-05  new Item subtype for a more platformer feel.
    SUBTYPE_WEAPON		= (1 << 5),
    SUBTYPE_NOSKIP		= (1 << 6),		// Text type that can't be skipped
    SUBTYPE_FLYDIE		= (1 << 7),		// Now obstacles can be hit and fly like on Simpsons/TMNT
    SUBTYPE_BOTH		= (1 << 8),		// Used with TYPE_ENDLEVEL to force both players to reach the point before ending level
    SUBTYPE_PROJECTILE	= (1 << 9),		// New weapon projectile type that can be picked up by players/enemies
    SUBTYPE_FOLLOW		= (1 << 10),	// Used by NPC character, if set, they will try to follow players
    SUBTYPE_CHASE		= (1 << 11)		// Used by enemy always chasing you
} e_entity_type_sub;

typedef enum
{
    EXCHANGE_CONFERRER,
    EXCHANGE_RECIPIANT
} e_exchange;

//------------reserved for A.I. types-------------------------

// Caskey, Damon V
// 2013-12-27
//
// Movement behavior types.
typedef enum
{
	AIMOVE1_NONE = -1,			// No AIMOVE set.
	AIMOVE1_NORMAL = 0,			// Current default style
	AIMOVE1_CHASE = (1 << 0),		// alway move towards target, and can run to them if target is farway
	AIMOVE1_CHASEZ = (1 << 1),		// only try to get close in z direction
	AIMOVE1_CHASEX = (1 << 2),		// only try to get colse in x direction
	AIMOVE1_AVOID = (1 << 3),		// try to avoid target
	AIMOVE1_AVOIDZ = (1 << 4),		// only try to avoid target in z direction
	AIMOVE1_AVOIDX = (1 << 5),		// only try to avoid target in x direction
	AIMOVE1_WANDER = (1 << 6),		// ignore the target's position completely, wander everywhere, long idle time
	AIMOVE1_BIKER = (1 << 7),		// move like a biker
	AIMOVE1_ARROW = (1 << 8),	// fly like an arrow
	AIMOVE1_STAR = (1 << 9),	// fly like a star, subject to ground
	AIMOVE1_BOMB = (1 << 10),	// fly like a bomb, subject to ground/wall etc
	AIMOVE1_NOMOVE = (1 << 11),	// don't move at all
	MASK_AIMOVE1 = 0x0000FFFF
} e_aimove_1;

typedef enum
{
    /*
    A.I move 2 enum: Affect terrain reflect
    Damon V. Caskey
    2013-12-27
    */

    AIMOVE2_NORMAL,                         // Current default style
    AIMOVE2_IGNOREHOLES     = 0x00010000,   // don't avoid holes
    AIMOVE2_NOTARGETIDLE    = 0x00020000,   // don't move when there's no target
    MASK_AIMOVE2            = 0xFFFF0000
} e_aimove_2;

typedef enum
{
    /*
    A.I. attack1 enum: Affect attacking style.
    Damon V. Caskey
    2013-12-27
    */

    AIATTACK1_NORMAL,                   // Current default style
    AIATTACK1_LONG      = 0x00000001,   // Long range first, not used
    AIATTACK1_MELEE     = 0x00000002,   // Melee attack first, not used
    AIATTACK1_NOATTACK  = 0x00000004,   // dont attack at all
    AIATTACK1_ALWAYS    = 0x00000008,   // more aggression than default, useful for traps who don't think
    MASK_AIATTACK1      = 0x0000FFFF
} e_aiattack_1;

typedef enum
{
    /*
    A.I. attack1 enum: Affect Defending style.
    Damon V. Caskey
    2013-12-27
    */

    AIATTACK2_NORMAL,                   // Current default style, don't dodge at all
    AIATTACK2_DODGE     = 0x00010000,   // Use dodge animation to avoid attack
    AIATTACK2_DODGEMOVE = 0x00020000,   // Try to move in z direction if a jump attack is about to hit him and try to step back if a melee attack is about to hit him.
    MASK_AIATTACK2      = 0xFFFF0000
} e_aiattack_2;

typedef enum //Animations
{
    /*
    Animations enum.
    Damon V. Caskey
    2013-12-27
    */

    ANI_NONE,               // To indicate a blank or no animation at all.
    ANI_IDLE,
    ANI_WALK,
    ANI_JUMP,
    ANI_LAND,
    ANI_PAIN,
    ANI_FALL,
    ANI_RISE,
    ANI_ATTACK,
    ANI_ATTACK1,
    ANI_ATTACK2,
    ANI_ATTACK3,
    ANI_ATTACK4,			// Very important
    ANI_UPPER,
    ANI_BLOCK,				// New block animation
	ANI_BLOCKRELEASE,		// Transition out of block.
	ANI_BLOCKSTART,			// Transition to block.
    ANI_JUMPATTACK,
    ANI_JUMPATTACK2,
    ANI_GET,
    ANI_GRAB,
    ANI_BACKGRAB,			// Kratus (10-2021) Added the new backgrab animation
    ANI_VAULT,				// Kratus (10-2021) Added the new vault animation
    ANI_VAULT2,				// Kratus (10-2021) Added the new vault2 animation
    ANI_GRABATTACK,
    ANI_GRABATTACK2,
    ANI_THROW,
    ANI_SPECIAL,
    ANI_FREESPECIAL,
    ANI_SPAWN, 				// 26-12-2004 new animation added here ani_spawn
    ANI_DIE,				// 29-12-2004 new animation added here ani_die
    ANI_PICK,				// 7-1-2005 used when players select their character at the select screen
    ANI_FREESPECIAL2,
    ANI_JUMPATTACK3,
    ANI_FREESPECIAL3,
    ANI_UP,					// Mar 2, 2005 - Animation for when going up
    ANI_DOWN,				// Mar 2, 2005 - Animation for when going down
    ANI_SHOCK,				// Animation played when knocked down by shock attack
    ANI_BURN,				// Animation played when knocked down by burn attack
    ANI_SHOCKPAIN,			// Animation played when not knocked down by shock attack
    ANI_BURNPAIN,			// Animation played when not knocked down by shock attack
    ANI_GRABBED,			// Animation played when grabbed
    ANI_SPECIAL2,			// Animation played for when pressing forward special
    ANI_RUN,				// Animation played when a player is running
    ANI_RUNATTACK,			// Animation played when a player is running and presses attack
    ANI_RUNJUMPATTACK,		// Animation played when a player is running and jumps and presses attack
    ANI_ATTACKUP,			// u u animation
    ANI_ATTACKDOWN,			// d d animation
    ANI_ATTACKFORWARD,		// f f animation
    ANI_ATTACKBACKWARD,		// Used for attacking backwards
    ANI_FREESPECIAL4,		// More freespecials added
    ANI_FREESPECIAL5,		// More freespecials added
    ANI_FREESPECIAL6,		// More freespecials added
    ANI_FREESPECIAL7,		// More freespecials added
    ANI_FREESPECIAL8,		// More freespecials added
    ANI_RISEATTACK,			// Attack used for enemies when players are crowding around after knocking them down
    ANI_DODGE,				// Used for up up / down down SOR3 dodge moves for players
    ANI_ATTACKBOTH,			// Used for when a player holds down attack and presses jump
    ANI_GRABFORWARD,		// New grab attack for when a player holds down forward/attack
    ANI_GRABFORWARD2,		// New second grab attack for when a player holds down forward/attack
    ANI_JUMPFORWARD,		// Attack when a player is moving and jumps
    ANI_GRABDOWN,			// Attack when a player has grabbed an opponent and presses down/attack
    ANI_GRABDOWN2,			// Attack when a player has grabbed an opponent and presses down/attack
    ANI_GRABUP,				// Attack when a player has grabbed an opponent and presses up/attack
    ANI_GRABUP2,			// Attack when a player has grabbed an opponent and presses up/attack
    ANI_SELECT,				// Animation that is displayed at the select screen in place of idle.
	ANI_SELECTIN,			// Animation that is displayed at the select screen, when first highlighted.
	ANI_SELECTOUT,			// Animation that is displayed at the select screen, when moving to another character.
    ANI_DUCK,				// Animation that is played when pressing down in "platform" type levels
    ANI_FAINT,  			// Faint animations for players/enemys by tails
    ANI_CANT,  				// Can't animation for players(animation when mp is less than mpcost) by tails.
    ANI_THROWATTACK,		// Added for subtype projectile
    ANI_CHARGEATTACK,       // Plays when player releases attack1 after holding >= charge_time.
    ANI_JUMPCANT,
    ANI_JUMPSPECIAL,
    ANI_BURNDIE,
    ANI_SHOCKDIE,
    ANI_PAIN2,
    ANI_PAIN3,
    ANI_PAIN4,
    ANI_FALL2,
    ANI_FALL3,
    ANI_FALL4,
    ANI_DIE2,
    ANI_DIE3,
    ANI_DIE4,
    ANI_CHARGE,
    ANI_BACKWALK,
    ANI_SLEEP,
    ANI_FOLLOW1,
    ANI_FOLLOW2,
    ANI_FOLLOW3,
    ANI_FOLLOW4,
    ANI_PAIN5,
    ANI_PAIN6,
    ANI_PAIN7,
    ANI_PAIN8,
    ANI_PAIN9,
    ANI_PAIN10,
    ANI_FALL5,
    ANI_FALL6,
    ANI_FALL7,
    ANI_FALL8,
    ANI_FALL9,
    ANI_FALL10,
    ANI_DIE5,
    ANI_DIE6,
    ANI_DIE7,
    ANI_DIE8,
    ANI_DIE9,
    ANI_DIE10,
    ANI_TURN,               // turn back/flip
    ANI_RESPAWN,            //now spawn works for players
    ANI_FORWARDJUMP,
    ANI_RUNJUMP,
    ANI_JUMPLAND,
    ANI_JUMPDELAY,
    ANI_HITOBSTACLE,
    ANI_HITPLATFORM,
    ANI_HITWALL,
    ANI_GRABBACKWARD,
    ANI_GRABBACKWARD2,
    ANI_GRABWALK,
    ANI_GRABBEDWALK,
    ANI_GRABWALKUP,
    ANI_GRABBEDWALKUP,
    ANI_GRABWALKDOWN,
    ANI_GRABBEDWALKDOWN,
    ANI_GRABTURN,
    ANI_GRABBEDTURN,
    ANI_GRABBACKWALK,
    ANI_GRABBEDBACKWALK,
    ANI_SLIDE,              //Down + Jump animation.
    ANI_RUNSLIDE,           //Down + Jump while running.
    ANI_BLOCKPAIN,          //If entity has this, it will play in place of "pain" when it's blokcpain is 1 and incomming attack is blocked.
    ANI_DUCKATTACK,
    ANI_RISE2,
    ANI_RISE3,
    ANI_RISE4,
    ANI_RISE5,
    ANI_RISE6,
    ANI_RISE7,
    ANI_RISE8,
    ANI_RISE9,
    ANI_RISE10,
    ANI_RISEB,
    ANI_RISES,
    ANI_BLOCKPAIN2,
    ANI_BLOCKPAIN3,
    ANI_BLOCKPAIN4,
    ANI_BLOCKPAIN5,
    ANI_BLOCKPAIN6,
    ANI_BLOCKPAIN7,
    ANI_BLOCKPAIN8,
    ANI_BLOCKPAIN9,
    ANI_BLOCKPAIN10,
    ANI_BLOCKPAINB,
    ANI_BLOCKPAINS,
    ANI_CHIPDEATH,
    ANI_GUARDBREAK,
    ANI_RISEATTACK2,
    ANI_RISEATTACK3,
    ANI_RISEATTACK4,
    ANI_RISEATTACK5,
    ANI_RISEATTACK6,
    ANI_RISEATTACK7,
    ANI_RISEATTACK8,
    ANI_RISEATTACK9,
    ANI_RISEATTACK10,
    ANI_RISEATTACKB,
    ANI_RISEATTACKS,
    ANI_WALKOFF,
    ANI_BACKPAIN,
    ANI_BACKPAIN2,
    ANI_BACKPAIN3,
    ANI_BACKPAIN4,
    ANI_BACKPAIN5,
    ANI_BACKPAIN6,
    ANI_BACKPAIN7,
    ANI_BACKPAIN8,
    ANI_BACKPAIN9,
    ANI_BACKPAIN10,
    ANI_BACKFALL,
    ANI_BACKFALL2,
    ANI_BACKFALL3,
    ANI_BACKFALL4,
    ANI_BACKFALL5,
    ANI_BACKFALL6,
    ANI_BACKFALL7,
    ANI_BACKFALL8,
    ANI_BACKFALL9,
    ANI_BACKFALL10,
    ANI_BACKDIE,
    ANI_BACKDIE2,
    ANI_BACKDIE3,
    ANI_BACKDIE4,
    ANI_BACKDIE5,
    ANI_BACKDIE6,
    ANI_BACKDIE7,
    ANI_BACKDIE8,
    ANI_BACKDIE9,
    ANI_BACKDIE10,
    ANI_BACKRUN,
    ANI_BACKBURNPAIN,
    ANI_BACKSHOCKPAIN,
    ANI_BACKBURN,
    ANI_BACKSHOCK,
    ANI_BACKBURNDIE,
    ANI_BACKSHOCKDIE,
    ANI_BACKRISEB,
    ANI_BACKRISES,
    ANI_BACKRISE,
    ANI_BACKRISE2,
    ANI_BACKRISE3,
    ANI_BACKRISE4,
    ANI_BACKRISE5,
    ANI_BACKRISE6,
    ANI_BACKRISE7,
    ANI_BACKRISE8,
    ANI_BACKRISE9,
    ANI_BACKRISE10,
    ANI_BACKRISEATTACKB,
    ANI_BACKRISEATTACKS,
    ANI_BACKRISEATTACK,
    ANI_BACKRISEATTACK2,
    ANI_BACKRISEATTACK3,
    ANI_BACKRISEATTACK4,
    ANI_BACKRISEATTACK5,
    ANI_BACKRISEATTACK6,
    ANI_BACKRISEATTACK7,
    ANI_BACKRISEATTACK8,
    ANI_BACKRISEATTACK9,
    ANI_BACKRISEATTACK10,
    ANI_BACKBLOCKPAINB,
    ANI_BACKBLOCKPAINS,
    ANI_BACKBLOCKPAIN,
    ANI_BACKBLOCKPAIN2,
    ANI_BACKBLOCKPAIN3,
    ANI_BACKBLOCKPAIN4,
    ANI_BACKBLOCKPAIN5,
    ANI_BACKBLOCKPAIN6,
    ANI_BACKBLOCKPAIN7,
    ANI_BACKBLOCKPAIN8,
    ANI_BACKBLOCKPAIN9,
    ANI_BACKBLOCKPAIN10,
    ANI_EDGE,
    ANI_BACKEDGE,
    ANI_DUCKING,
    ANI_DUCKRISE,
    ANI_VICTORY,
    ANI_FALLLOSE,
    ANI_LOSE,
    MAX_ANIS                // Maximum # of animations. This must always be last.
} e_animations;

typedef enum
{
    BOSS_SLOW_OFF,
    BOSS_SLOW_ON
} e_boss_slow_flag;

typedef enum
{
    DAMAGE_FROM_ENEMY_OFF,
    DAMAGE_FROM_ENEMY_ON
} e_damage_from_enemy_flag;

typedef enum
{
    DAMAGE_FROM_PLAYER_OFF,
    DAMAGE_FROM_PLAYER_ON
} e_damage_from_player_flag;

typedef enum
{
    LEVEL_PROP_AUTO_SCROLL_DIRECTION,           // int bgdir;
    LEVEL_PROP_AUTO_SCROLL_X,                   // float bgspeed;
    LEVEL_PROP_AUTO_SCROLL_Y,                   // float vbgspeed;
    LEVEL_PROP_BASEMAP_COLLECTION,              // s_basemap *basemaps;
    LEVEL_PROP_BASEMAP_COUNT,                   // int numbasemaps;
    LEVEL_PROP_BOSS_COUNT,                      // int bossescount;
    LEVEL_PROP_BOSS_MUSIC_NAME,                 // char bossmusic[256];
    LEVEL_PROP_BOSS_MUSIC_OFFSET,               // unsigned bossmusic_offset;
    LEVEL_PROP_BOSS_SLOW,                       // int boss_slow;
    LEVEL_PROP_CAMERA_OFFSET_X,                 // int cameraxoffset;
    LEVEL_PROP_CAMERA_OFFSET_Z,                 // int camerazoffset;
    LEVEL_PROP_COMPLETE_FORCE,                  // int force_finishlevel;
    LEVEL_PROP_GAMEOVER,                        // int force_gameover;
    LEVEL_PROP_DAMAGE_FROM_ENEMY,               // int nohurt;
    LEVEL_PROP_DAMAGE_FROM_PLAYER,              // int nohit;
    LEVEL_PROP_FACING,                          // e_facing_adjust facing;
    LEVEL_PROP_GRAVITY,                         // float gravity;
    LEVEL_PROP_HOLE_COLLECTION,                 // s_terrain *holes;
    LEVEL_PROP_HOLE_COUNT,                      // int numholes;
    LEVEL_PROP_LAYER_BACKGROUND_DEFAULT_HANDLE, // s_layer *background;
    LEVEL_PROP_LAYER_BACKGROUND_COLLECTION,     // s_layer **bglayers;
    LEVEL_PROP_LAYER_BACKGROUND_COUNT,          // int numbglayers;
    LEVEL_PROP_LAYER_COLLECTION,                // s_layer *layers;
    LEVEL_PROP_LAYER_COUNT,                     // int numlayers;
    LEVEL_PROP_LAYER_FOREGROUND_COLLECTION,     // s_layer **fglayers;
    LEVEL_PROP_LAYER_FOREGROUND_COUNT,          // int numfglayers;
    LEVEL_PROP_LAYER_FRONTPANEL_COLLECTION,     // s_layer **frontpanels;
    LEVEL_PROP_LAYER_FRONTPANEL_COUNT,          // int numfrontpanels;
    LEVEL_PROP_LAYER_GENERIC_COLLECTION,        // s_layer **genericlayers;
    LEVEL_PROP_LAYER_GENERIC_COUNT,             // int numgenericlayers;
    LEVEL_PROP_LAYER_PANEL_COLLECTION,          // s_layer *(*panels)[3]; //normal neon screen
    LEVEL_PROP_LAYER_PANEL_COUNT,               // int numpanels;
    LEVEL_PROP_LAYER_REF_COLLECTION,            // s_layer *layersref;
    LEVEL_PROP_LAYER_REF_COUNT,                 // int numlayersref;
    LEVEL_PROP_LAYER_WATER_COLLECTION,          // s_layer **waters;
    LEVEL_PROP_LAYER_WATER_COUNT,               // int numwaters;
    LEVEL_PROP_MAX_FALL_VELOCITY,               // float maxfallspeed;
    LEVEL_PROP_MAX_TOSS_VELOCITY,               // float maxtossspeed;
    LEVEL_PROP_MIRROR,                          // int mirror;
    LEVEL_PROP_NAME,                            // char *name;
    LEVEL_PROP_NUM_BOSSES,                      // int numbosses;
    LEVEL_PROP_PALETTE_BLENDING_COLLECTION,     // unsigned char *(*blendings)[MAX_BLENDINGS];
    LEVEL_PROP_PALETTE_COLLECTION,              // unsigned char (*palettes)[1024];
    LEVEL_PROP_PALETTE_COUNT,                   // int numpalettes;
    LEVEL_PROP_POSITION_X,                      // int pos;
    LEVEL_PROP_QUAKE,                           // int quake;
    LEVEL_PROP_QUAKE_TIME,                      // u32 quaketime;
    LEVEL_PROP_ROCKING,                         // int rocking;
    LEVEL_PROP_SCRIPT_LEVEL_END,                // Script endlevel_script;
    LEVEL_PROP_SCRIPT_LEVEL_START,              // Script level_script;
    LEVEL_PROP_SCRIPT_KEY,                      // Script key_script;
    LEVEL_PROP_SCRIPT_UPDATE,                   // Script update_script;
    LEVEL_PROP_SCRIPT_UPDATED,                  // Script updated_script;
    LEVEL_PROP_SCROLL_DIRECTION,                // int scrolldir;
    LEVEL_PROP_SCROLL_VELOCITY,                 // float scrollspeed;
    LEVEL_PROP_SIZE_X,                          // int width;
    LEVEL_PROP_SPAWN_COLLECTION,                // s_spawn_entry *spawnpoints;
    LEVEL_PROP_SPAWN_COUNT,                     // int numspawns;
    LEVEL_PROP_SPAWN_PLAYER_COLLECTION,         // s_axis_principal_float spawn[MAX_PLAYERS];
    LEVEL_PROP_SPECIAL_DISABLE,                 // int nospecial;
    LEVEL_PROP_TEXT_OBJECT_COLLECTION,          // s_textobj *textobjs;
    LEVEL_PROP_TEXT_OBJECT_COUNT,               // int numtextobjs;
    LEVEL_PROP_TIME_ADVANCE,                    // u32 advancetime;
    LEVEL_PROP_TIME_DISPLAY,                    // int notime;
    LEVEL_PROP_TIME_RESET,                      // int noreset;
    LEVEL_PROP_TIME_SET,                        // int settime;
    LEVEL_PROP_TYPE,                            // int type;
    LEVEL_PROP_WAITING,                         // int waiting;
    LEVEL_PROP_WALL_COLLECTION,                 // s_terrain *walls;
    LEVEL_PROP_WALL_COUNT,                      // int numwalls;
    LEVEL_PROP_WEAPON                           // int setweap;
} e_level_properties;

typedef enum
{
    SET_PROP_COMPLETE_FLAG,         // int ifcomplete;
    SET_PROP_COMPLETE_SKIP,         // int noshowcomplete;
    SET_PROP_CONTINUE_SCORE_TYPE,   // int continuescore;
    SET_PROP_CREDITS,               // int credits;
    SET_PROP_GAME_OVER_SKIP,        // int noshowgameover;
    SET_PROP_HOF_DISABLE,           // int noshowhof;
    SET_PROP_LEVELSET_COLLECTION,   // s_level_entry *levelorder;
    SET_PROP_LEVELSET_COUNT,        // int numlevels;
    SET_PROP_LIVES,                 // int lives;
    SET_PROP_MP_RECOVER_TYPE,       // int typemp;
    SET_PROP_MUSIC_FADE_TIME,       // int custfade;
    SET_PROP_MUSIC_OVERLAP,         // int musicoverlap;
    SET_PROP_NAME,                  // char *name;
    SET_PROP_PLAYER_MAX,            // int maxplayers;
    SET_PROP_SAVE_TYPE,             // int saveflag;
    SET_PROP_SELECT_DISABLE,        // int noselect;
    SET_PROP_SELECT_NO_SAME         // int nosame;
} e_set_properties;

typedef enum
{
    /*
    Argument type enum.
    Damon V. Caskey
    2013-12-27
    */

    ARG_FLOAT,
    ARG_STRING,
    ARG_INT
} e_arg_types;


// Caskey, Damon V.
// 2013-12-27
//
// Attack types. If more types are added,
// don't forget to add them to script
// access and account for them in the
// model load logic.
typedef enum
{
    ATK_NONE            = -1,   // When we want no attack at all, such as damage_on_landing's default.
    ATK_NORMAL,
    ATK_NORMAL1			= ATK_NORMAL,
    ATK_NORMAL2,
    ATK_NORMAL3,
    ATK_NORMAL4,
    ATK_BLAST,
    ATK_BURN,
    ATK_FREEZE,
    ATK_SHOCK,
    ATK_STEAL,
    ATK_NORMAL5,
    ATK_NORMAL6,
    ATK_NORMAL7,
    ATK_NORMAL8,
    ATK_NORMAL9,
    ATK_NORMAL10,

    // For engine and script use. These are
    // applied automatically by various
    // conditions or intended for script logic.
    ATK_BOSS_DEATH,					// KO leftover enemies when boss is defeated.
    ATK_ITEM,						// Scripting item logic. Item "attacks" entity that collects it.
    ATK_LAND,						// Touching ground during a damage on landing fall.
    ATK_LIFESPAN,					// Entity's lifespan timer expires.
    ATK_LOSE,						// Players (with lose animation) when level time expires.
    ATK_PIT,						// Entity falls into a pit and reaches specified depth.
	ATK_SUB_ENTITY_PARENT_KILL,		// Used to KO a summon when parent is killed.
	ATK_SUB_ENTITY_UNSUMMON,		// Used to KO a summon on unsummon frame.
	ATK_TIMEOVER,					// Players (without lose animation) when level time expires.
    
	// Default max attack types (must
    // be below all attack types in enum
    // to get correct value)
    MAX_ATKS,
    STA_ATKS       = (MAX_ATKS-1)
} e_attack_types;

// Attack box properties.
// Caskey, Damon V.
// 2016-10-26
typedef enum
{
    ATTACK_PROP_BLOCK_COST,
    ATTACK_PROP_BLOCK_PENETRATE,
    ATTACK_PROP_COORDINATES,
    ATTACK_PROP_COUNTER,
    ATTACK_PROP_DAMAGE_FORCE,
    ATTACK_PROP_DAMAGE_LAND_FORCE,
    ATTACK_PROP_DAMAGE_LAND_MODE,
    ATTACK_PROP_DAMAGE_LETHAL_DISABLE,
    ATTACK_PROP_DAMAGE_RECURSIVE_FORCE,
    ATTACK_PROP_DAMAGE_RECURSIVE_INDEX,
    ATTACK_PROP_DAMAGE_RECURSIVE_MODE,
    ATTACK_PROP_DAMAGE_RECURSIVE_TIME_RATE,
    ATTACK_PROP_DAMAGE_RECURSIVE_TIME_EXPIRE,
    ATTACK_PROP_DAMAGE_STEAL,
    ATTACK_PROP_DAMAGE_TYPE,
    ATTACK_PROP_EFFECT_BLOCK_FLASH,
    ATTACK_PROP_EFFECT_BLOCK_SOUND,
    ATTACK_PROP_EFFECT_HIT_FLASH,
    ATTACK_PROP_EFFECT_HIT_FLASH_DISABLE,
    ATTACK_PROP_EFFECT_HIT_SOUND,
    ATTACK_PROP_INDEX,
    ATTACK_PROP_GROUND,
    ATTACK_PROP_MAP_INDEX,
    ATTACK_PROP_MAP_TIME,
    ATTACK_PROP_REACTION_FALL_FORCE,
    ATTACK_PROP_REACTION_FALL_VELOCITY,
    ATTACK_PROP_REACTION_FREEZE_MODE,
    ATTACK_PROP_REACTION_FREEZE_TIME,
    ATTACK_PROP_REACTION_INVINCIBLE_TIME,
    ATTACK_PROP_REACTION_REPOSITION_DIRECTION,
    ATTACK_PROP_REACTION_REPOSITION_DISTANCE,
    ATTACK_PROP_REACTION_REPOSITION_MODE,
    ATTACK_PROP_REACTION_PAIN_SKIP,
    ATTACK_PROP_REACTION_PAUSE_TIME,
    ATTACK_PROP_SEAL_COST,
    ATTACK_PROP_SEAL_TIME,
    ATTACK_PROP_STAYDOWN_RISE,
    ATTACK_PROP_STAYDOWN_RISEATTACK,
    ATTACK_PROP_TAG
} e_attack_properties;

// Body collision (bbox) properties.
// Caskey, Damon V.
// 2016-10-31
typedef enum
{
    BODY_COLLISION_PROP_COORDINATES,
    BODY_COLLISION_PROP_DEFENSE,
    BODY_COLLISION_PROP_TAG
} e_body_collision_properties;

// Caskey, Damon V.
// 2018-01-04
//
// Coordinate structure, mainly for accessing
// collision box position and dimensions.
typedef enum
{
    COLLISION_COORDINATES_PROP_DEPTH_BACKGROUND,
    COLLISION_COORDINATES_PROP_DEPTH_FOREGROUND,
    COLLISION_COORDINATES_PROP_HEIGHT,
    COLLISION_COORDINATES_PROP_WIDTH,
    COLLISION_COORDINATES_PROP_X,
    COLLISION_COORDINATES_PROP_Y
} e_collision_coordinates;

// Entity collision (ebox) properties.
typedef enum
{
    ENTITY_COLLISION_PROP_COORDINATES,
    ENTITY_COLLISION_PROP_TAG
} e_entity_collision_properties;

typedef enum
{
    /*
    Status bar direction enum.
    Damon V. Caskey
    2013-12-29
    */

    BARSTATUS_DIR_NORMAL,  //Left to Right or Up to Down.
    BARSTATUS_DIR_INVERT   //Right to Left or Down to Up.
} e_bar_dir;

typedef enum
{
    HORIZONTALBAR,
    VERTICALBAR
} e_barorient;

typedef enum
{
    VALUEBAR,
    PERCENTAGEBAR
} e_bartype;

typedef enum
{
    BGT_BGLAYER,
    BGT_FGLAYER,
    BGT_PANEL,
    BGT_FRONTPANEL,
    BGT_WATER,
    BGT_BACKGROUND,
    BGT_GENERIC
} e_bgloldtype;

typedef enum
{
    /*
    Blocktype enum. Type of resource drained (if any) when attack is blocked.
    Damon V. Caskey
    2013-12-28
    */

    BLOCK_TYPE_HP         = -1,   //HP only.
    BLOCK_TYPE_MP_FIRST   = 1,    //MP until MP is exhuasted, then HP.
    BLOCK_TYPE_BOTH,              //Both MP and HP.
    BLOCK_TYPE_MP_ONLY            //Only MP, even if MP is 0.
} e_blocktype;

typedef enum
{
    /*
    Energy check type enum.
    Damon V. Caskey
    2013-12-29
    */

    ENERGY_TYPE_HP,
    ENERGY_TYPE_MP
} e_cost_check;

typedef enum
{
    /*
    energy_cost type enum.
    Damon V. Caskey
    2013-12-29
    */

    COST_TYPE_MP_THEN_HP,
    COST_TYPE_MP_ONLY,
    COST_TYPE_HP_ONLY
} e_cost_type;

typedef enum
{
    /*
    energy_cost value enum.
    */

    ENERGY_COST_NOCOST = 0,
    ENERGY_COST_DEFAULT_COST = 6,
} e_cost_value;

typedef enum
{
    BIND_CONFIG_NONE = 0,

    /* 
    * These must be kept in the current order
    * to ensure legacy compatibility with
    * modules that used magic numbers before
    * constants were available.
	*/
    BIND_CONFIG_ANIMATION_TARGET			= (1 << 0),
    BIND_CONFIG_ANIMATION_FRAME_TARGET		= (1 << 1),
    BIND_CONFIG_ANIMATION_REMOVE			= (1 << 2),
    BIND_CONFIG_ANIMATION_FRAME_REMOVE		= (1 << 3),

	/* End legacy order. */

    BIND_CONFIG_ANIMATION_DEFINED			= (1 << 4),
    BIND_CONFIG_ANIMATION_FRAME_DEFINED	    = (1 << 5),
    BIND_CONFIG_AXIS_X_LEVEL                = (1 << 6),
    BIND_CONFIG_AXIS_X_TARGET               = (1 << 7),
    BIND_CONFIG_AXIS_Y_LEVEL                = (1 << 8),
    BIND_CONFIG_AXIS_Y_TARGET               = (1 << 9),
    BIND_CONFIG_AXIS_Z_LEVEL                = (1 << 10),
    BIND_CONFIG_AXIS_Z_TARGET               = (1 << 11),
    BIND_CONFIG_OVERRIDE_FALL_LAND          = (1 << 12),
    BIND_CONFIG_OVERRIDE_DROPFRAME          = (1 << 13),
    BIND_CONFIG_OVERRIDE_LANDFRAME          = (1 << 14),
    BIND_CONFIG_OVERRIDE_SPECIAL_AI         = (1 << 15),
    BIND_CONFIG_OVERRIDE_SPECIAL_PLAYER     = (1 << 16)

} e_bind_config;

typedef enum e_move_constraint
{
    MOVE_CONSTRAINT_NONE                = 0,
    MOVE_CONSTRAINT_NO_ADJUST_BASE      = (1 << 0),
    MOVE_CONSTRAINT_NO_HIT_HEAD         = (1 << 1), // True = Pass upward through platforms when entity has valid height set.
    MOVE_CONSTRAINT_SUBJECT_TO_BASEMAP  = (1 << 2),
    MOVE_CONSTRAINT_SUBJECT_TO_GRAVITY  = (1 << 3),
    MOVE_CONSTRAINT_SUBJECT_TO_HOLE     = (1 << 4),
    MOVE_CONSTRAINT_SUBJECT_TO_MAX_Z    = (1 << 5),
    MOVE_CONSTRAINT_SUBJECT_TO_MIN_Z    = (1 << 6),
    MOVE_CONSTRAINT_SUBJECT_TO_OBSTACLE = (1 << 7),
    MOVE_CONSTRAINT_SUBJECT_TO_PLATFORM = (1 << 8),
    MOVE_CONSTRAINT_SUBJECT_TO_SCREEN   = (1 << 9),
    MOVE_CONSTRAINT_SUBJECT_TO_WALL     = (1 << 10)
} e_move_constraint;

// Caskey, Damon V.
// 2013-12-16
//
// Direction (facing) enum.
typedef enum
{
	DIRECTION_NONE = -1,	// Only to indicate a temporary direction flag isn't set or in use.
	DIRECTION_LEFT,
	DIRECTION_RIGHT
} e_direction;

// Caskey, Damon V.
// 2013-12-28
//
// Direction adjustment enum. Used for binding and changing direction of defender when hit.
typedef enum
{
    

    DIRECTION_ADJUST_NONE,             //Leave as is.
    DIRECTION_ADJUST_SAME,             //Same as attacker/bind/etc.
    DIRECTION_ADJUST_OPPOSITE  = -1,   //Opposite attacker/bind/etc.
    DIRECTION_ADJUST_RIGHT     = 2,    //Always right.
    DIRECTION_ADJUST_LEFT      = -2    //Always left.
} e_direction_adjust;

typedef enum
{
    /*
    Run adjust_grabposition check on dograb or not.
    Damon V. Caskey
    2013-12-30
    */

    DOGRAB_ADJUSTCHECK_TRUE,
    DOGRAB_ADJUSTCHECK_FALSE
} e_dograb_adjustcheck;

// 2019-12-08
// Caskey, Damon V.
//
// Legacy values for backward compatability. These are used to 
// interpret the recursive damage command from author. Then we
// populate the recursive damage mode with a set of bit values 
// from e_damage_recursive_logic accordingly. 
typedef enum
{
	DAMAGE_RECURSIVE_CMD_READ_NONLETHAL_HP = 1, //  1 = Nonlethal HP(can reduce to 1 but not below).
	DAMAGE_RECURSIVE_CMD_READ_MP = 2, // = MP.
	DAMAGE_RECURSIVE_CMD_READ_MP_NONLETHAL_HP = 3, // 3 = MP and nonlethal HP.
	DAMAGE_RECURSIVE_CMD_READ_HP = 4, // = HP.
	DAMAGE_RECURSIVE_CMD_READ_HP_MP = 5 // = MP and HP.
}e_damage_recursive_cmd_read;

typedef enum
{
	DAMAGE_RECURSIVE_MODE_NONE			= 0,
	DAMAGE_RECURSIVE_MODE_HP			= (1 << 0),
	DAMAGE_RECURSIVE_MODE_MP			= (1 << 1),
	DAMAGE_RECURSIVE_MODE_NON_LETHAL	= (1 << 2)
} e_damage_recursive_logic;

typedef enum
{
    /*
    Edelay factor modes.
    2013-12-16
    Damon V. Caskey
    */
    EDELAY_MODE_ADD,       //Factor is added directly to edelay.
    EDELAY_MODE_MULTIPLY   //Orginal delay value is multiplied by factor.
} e_edelay_mode;

typedef enum
{
    /*
    Facing adjustment enum.
    Damon V. Caskey
    2013-12-29
    */

    FACING_ADJUST_NONE,    //No facing adjustment.
    FACING_ADJUST_RIGHT,   //Always face right.
    FACING_ADJUST_LEFT,    //Always face left.
    FACING_ADJUST_LEVEL    //Face according to level scroll direction.
} e_facing_adjust;

// Caskey, Damon V.
// 2019-11-24 (refactored from 2014-01-04 version)
//
// Legacy values for backward compatability. These are used to 
// interpret the follow command from author. Then we
// populate the follow condition with a set of bit values 
// from e_follow_condition_logic accordingly.
typedef enum
{
    FOLLOW_CONDITION_CMD_READ_DISABLED,                     //No followup (default).
    FOLLOW_CONDITION_CMD_READ_ALWAYS,                       //Always perform.
    FOLLOW_CONDITION_CMD_READ_HOSTILE,                      //Perform if target is hostile.
    FOLLOW_CONDITION_CMD_READ_HOSTILE_NOKILL_NOBLOCK,       //Perform if target is hostile, will not be killed and didn't block.
    FOLLOW_CONDITION_CMD_READ_HOSTILE_NOKILL_NOBLOCK_NOGRAB, //Perform if target is hostile, will not be killed, didn't block, and cannot be grabbed.
    FOLLOW_CONDITION_CMD_READ_HOSTILE_NOKILL_BLOCK,         //Perform if target is hostile, will not be killed and block.
} e_follow_condition_command_read;

// Caskey, Damon V.
// 2019-11-24
// 
// Logic values for follow up condiiton. Must meet all conditions
// to perform follow up.
typedef enum
{
	FOLLOW_CONDITION_NONE					= 0,		// No conditions.		
	FOLLOW_CONDITION_ANY					= (1 << 0),	// Always follow up.
	FOLLOW_CONDITION_BLOCK_FALSE			= (1 << 1),	// Not blocked.
	FOLLOW_CONDITION_BLOCK_TRUE				= (1 << 2),	// Blocked.
	FOLLOW_CONDITION_GRAB_FALSE				= (1 << 3),	// Target can not grabbed.
	FOLLOW_CONDITION_GRAB_TRUE				= (1 << 4),	// Target can be grabbed.
	FOLLOW_CONDITION_HOSTILE_ATTACKER_FALSE	= (1 << 5),	// Attacker neutral/friendly.
	FOLLOW_CONDITION_HOSTILE_ATTACKER_TRUE	= (1 << 6),	// Attacker hostile to target.
	FOLLOW_CONDITION_HOSTILE_TARGET_FALSE	= (1 << 7),	// Target neutral/friendly.
	FOLLOW_CONDITION_HOSTILE_TARGET_TRUE	= (1 << 8),	// Target hostile to attacker.
	FOLLOW_CONDITION_LETHAL_FALSE			= (1 << 9),	// Target not killed by damage.
	FOLLOW_CONDITION_LETHAL_TRUE			= (1 << 10)	// Target killed by damage.
} e_follow_condition_logic;

// Caskey, Damon V.
// 2019-12-04 (refactored from 2012-12-16 version)
//
// Legacy values for backward compatability. These are used to 
// interpret the counter command from author. Then we
// populate the counter condition with a set of bit values 
// from e_follow_condition_logic accordingly.
typedef enum
{
	COUNTER_ACTION_CONDITION_CMD_READ_NONE,						// No counter.
	COUNTER_ACTION_CONDITION_CMD_READ_ALWAYS,					// Always perform coutner action.
	COUNTER_ACTION_CONDITION_CMD_READ_HOSTILE,					// Only if attacker is hostile entity.
	COUNTER_ACTION_CONDITION_CMD_READ_HOSTILE_FRONT_NOFREEZE,	// Attacker is hostile, strikes from front, and uses non-freeze attack.
	COUNTER_ACTION_CONDITION_CMD_READ_ALWAYS_RAGE,				// Always perform coutner action and if health - attack_damage <= 0, set health to 1
} e_counter_action_condition_command_read;

typedef enum
{
	COUNTER_ACTION_CONDITION_NONE					= 0,			// No conditions.
	COUNTER_ACTION_CONDITION_ANY					= (1 << 0),		// Always counter.
	COUNTER_ACTION_CONDITION_BACK_FALSE				= (1 << 1),		// Not from back.
	COUNTER_ACTION_CONDITION_BACK_TRUE				= (1 << 2),		// ONLY from back.
	COUNTER_ACTION_CONDITION_BLOCK_FALSE			= (1 << 3),		// No unblockable attacks.
	COUNTER_ACTION_CONDITION_BLOCK_TRUE				= (1 << 4),		// Only blockable attacks.
	COUNTER_ACTION_CONDITION_DAMAGE_LETHAL_FALSE	= (1 << 5),		// Damage must be non-lethal.
	COUNTER_ACTION_CONDITION_DAMAGE_LETHAL_TRUE		= (1 << 6),		// Damage must be lethal.
	COUNTER_ACTION_CONDITION_FREEZE_FALSE			= (1 << 7),		// Not against freeze attack.
	COUNTER_ACTION_CONDITION_FREEZE_TRUE			= (1 << 8),		// Only against freeze attack.
	COUNTER_ACTION_CONDITION_HOSTILE_ATTACKER_FALSE	= (1 << 9),		// Attacker neutral/friendly.
	COUNTER_ACTION_CONDITION_HOSTILE_ATTACKER_TRUE	= (1 << 10),	// Attacker hostile to target.
	COUNTER_ACTION_CONDITION_HOSTILE_TARGET_FALSE	= (1 << 11),	// Target neutral/friendly.
	COUNTER_ACTION_CONDITION_HOSTILE_TARGET_TRUE	= (1 << 12)		// Target hostile to attacker.
} e_counter_action_condition_logic;

typedef enum
{
    MAP_TYPE_KO = -4,
    MAP_TYPE_SHOCK = -3,
    MAP_TYPE_BURN = -2,
    MAP_TYPE_FREEZE = -1,  
    MAP_TYPE_NONE = 0
} e_maptype;

// Caskey, Damon V.
// 2012-12-16
//	 
// Counteraction damage taking modes.
typedef enum
{
	COUNTER_ACTION_TAKE_DAMAGE_NONE,	// No damage.
	COUNTER_ACTION_TAKE_DAMAGE_NORMAL	// Normal damage.
} e_counter_action_take_damage;

// Caskey, Damon V.
// 2019-05-31
// Grab attack selection.
typedef enum
{
	// Note these action constants are used as element IDs for
	// an array of grab attack options.
	//
	// GRAB_ACTION_SELECT_FINISH is a special action not included 
	// in the array of grab attacks, and GRAB_ACTION_SELECT_MAX
	// is used as the array size. 
	
	// Also note that AI selects which grab attack to perform 
	// by randomly generating a number from 0 to GRAB_ACTION_SELECT_MAX. 
	// This means GRAB_ACTION_SELECT_MAX should reflect number 
	// of options with exception of GRAB_ACTION_SELECT_FINISH, 
	// and that the value GRAB_ACTION_SELECT_FINISH should always 
	// fall outside of the 0 to GRAB_ACTION_SELECT_MAX range. Order
	// of the options does not matter otherwise.
	// Kratus (10-2021) Added vault animations
	
	GRAB_ACTION_SELECT_ATTACK,	
	GRAB_ACTION_SELECT_BACKWARD,
	GRAB_ACTION_SELECT_FORWARD,
	GRAB_ACTION_SELECT_DOWN,
	GRAB_ACTION_SELECT_UP,
	GRAB_ACTION_SELECT_VAULT,
	GRAB_ACTION_SELECT_MAX,
	GRAB_ACTION_SELECT_FINISH
} e_grab_action_select;

typedef enum
{
    /*
    Komap application enum. When to apply KO map to entity.
    Damon V. Caskey
    2013-12-28
    */

    KOMAP_TYPE_INSTANT,    //Apply instantly.
    KOMAP_TYPE_FINISH       // Apply on last frame of fall.
} e_komap_type;

typedef enum
{
	COLOR_SET_ADJUST_NONE			= -1,	// Don't adjust color.
	COLOR_SET_ADJUST_PARENT_INDEX	= -2,	// Match parent/owner index.
	COLOR_SET_ADJUST_PARENT_TABLE	= -3	// Match parent/owner table.
} e_color_adjust;

typedef enum
{
    LE_TYPE_NORMAL,
    LE_TYPE_CUT_SCENE,
    LE_TYPE_SELECT_SCREEN,
    LE_TYPE_SKIP_SELECT
} e_le_type;

typedef enum
{
    LS_TYPE_NONE,        //No loading screen.
    LS_TYPE_BOTH,        //Background and status bar.
    LS_TYPE_BACKGROUND,  //Background only.
    LS_TYPE_BAR,         //Status bar only.
} e_loadingScreenType;

/*
* Caskey, Damon V.  
* 2013-12-28 
* 
* Model copy flags. Mark portions
* of original model we don't want 
* copied during a model switch.
*/
typedef enum e_model_copy
{    
    MODEL_COPY_FLAG_NONE        = 0,        
    MODEL_COPY_FLAG_NO_BASIC    = (1 << 0), // As of 2022-05-24, animations, icons, and movement speeds. 
    MODEL_COPY_FLAG_NO_WEAPON   = (1 << 1), 
    MODEL_COPY_FLAG_NO_SCRIPT   = (1 << 2) 

    /* 
    * Flags above this line must 
    * keep current order for legacy
    * compatability. If you add any 
    * more flags, place them below. 
    */

} e_model_copy;

typedef enum
{
    MF_NONE,
    MF_ANIMLIST,
    MF_COLOURMAP,
    MF_PALETTE              = 4,
    MF_WEAPONS              = 8,
    MF_BRANCH               = 16,
    MF_ANIMATION            = 32,
    MF_DEFENSE              = 64,
    MF_OFF_FACTORS          = 128,
    MF_SPECIAL              = 256,
    MF_SMARTBOMB            = 512,
    MF_SCRIPTS              = 1024,
    MF_ALL                  = 0x7ff
} e_ModelFreetype;

typedef enum
{
    /*
    Over thr ground enum. Controls ability to hit downed targets.
    Damon V. Caskey
    2013-12-28
    */

   OTG_NONE,       //Cannot hit grounded targets.
   OTG_BOTH,       //Can hit grounded targets.
   OTG_GROUND_ONLY //Can ONLY hit grounded targets.
} e_otg;

typedef enum
{
    /*
    Scroll enum.
    Damon V. Caskey
    2013-12-28
    */

    SCROLL_RIGHT        = 2,
    SCROLL_DOWN			= 4,
    SCROLL_LEFT			= 8,
    SCROLL_UP			= 16,
    SCROLL_BACK			= 1,
    SCROLL_BOTH			= (SCROLL_BACK|SCROLL_RIGHT),
    SCROLL_RIGHTLEFT    = SCROLL_BOTH,
    SCROLL_LEFTRIGHT    = (SCROLL_LEFT|SCROLL_BACK),
    SCROLL_INWARD       = 32,
    SCROLL_OUTWARD      = 64,
    SCROLL_OUTIN		= (SCROLL_OUTWARD|SCROLL_BACK),
    SCROLL_INOUT		= (SCROLL_INWARD|SCROLL_BACK),
    SCROLL_UPWARD       = 128,
    SCROLL_DOWNWARD     = 256
} e_scroll;

typedef enum
{
    /*
    Slow motion switch enum.
    Damon V. Caskey
    2014-01-21
    */

    SLOW_MOTION_OFF,
    SLOW_MOTION_ON
} e_slow_motion_enable;

//macros for drawing menu text, fits different font size
#define _strmidx(font, s, args...) ((videomodes.hRes-font_string_width((font), s, ##args))/2)
#define _colx(f,c) ((int)(videomodes.hRes/2+(c)*(fontmonowidth((f))+1)))
#define _liney(f,line) ((int)(videomodes.vRes/2+(line)*(fontheight((f))+1)))
#define _menutextm(font, line, shift, string, args...) font_printf(_strmidx(font,string, ##args)+(int)((shift)*(fontmonowidth((font))+1)), _liney(font,line), (font), 0, string, ##args)
#define _menutextmshift(f, l, shift, shiftx, shifty, s, args...) font_printf(_strmidx(f,s, ##args)+(int)((shift)*(fontmonowidth((f))+1))+shiftx, _liney(f,l)+shifty, (f), 0, s, ##args)
#define _menutext(f, c, l, s, args...) font_printf(_colx(f,c), _liney(f,l), (f), 0, s, ##args)
#define _menutextshift(f, c, l, shiftx, shifty, s, args...) font_printf(_colx(f,c)+shiftx, _liney(f,l)+shifty, (f), 0, s, ##args)

//string starts with constant, for animation# series
#define strclen(s) (sizeof(s)-1)
#define starts_with(a, b) (strnicmp(a, b, strclen(b))==0)
#define starts_with_num(a, b) (starts_with(a, b) && (!a[strclen(b)] || (a[strclen(b)] >= '1' && a[strclen(b)] <= '9')))
#define get_tail_number(n, a, b) \
n = atoi(a+strclen(b)); \
if(n<1) n = 1;

#define ABS(x) ((x)>0?(x):(-(x)))

#define set_attacking(e) e->attacking = ATTACKING_PREPARED;\
						 e->idling = IDLING_NONE;

#define set_jumping(e)   e->jumping = 1;\
						 e->idling = IDLING_NONE; \
						 e->ducking = DUCK_NONE;

#define set_charging(e)  e->charging = 1;\
						 e->idling = IDLING_NONE; \
						 e->ducking = DUCK_NONE;

#define set_getting(e)   e->getting = 1;\
						 e->idling = IDLING_NONE; \
						 e->ducking = DUCK_NONE;

#define set_blocking(e)  e->blocking = 1;\
						 e->idling = IDLING_NONE;

#define set_turning(e)  e->turning = 1;\
						e->idling = IDLING_NONE; \
						 e->ducking = DUCK_NONE;

#define expand_time(e)   if(e->stalltime>0) e->stalltime++;\
						 if(e->releasetime>0)e->releasetime++;\
						 if(e->nextanim>0)e->nextanim++;\
						 if(e->nextthink>0)e->nextthink++;\
						 if(e->nextmove>0)e->nextmove++;\
						 if(e->magictime>0)e->magictime++;\
						 if(e->guardtime>0)e->guardtime++;\
						 if(e->toss_time>0)e->toss_time++;\
						 if(e->freezetime>0 && (textbox || smartbomber))e->freezetime++;\
						 if(e->mpchargetime>0)e->mpchargetime++;\
						 if(e->invinctime>0) e->invinctime++;\
						 if(e->turntime>0) e->turntime++;\
						 if(e->sealtime>0) e->sealtime++;
/*                       if(e->dot_time>0) e->dot_time++;\
						 if(e->dot_cnt>0) e->dot_cnt++;
*/

#define freezeall        (smartbomber || textbox)

#define is_projectile(e) (e->modeldata.type & TYPE_SHOT || e->model->subtype & SUBTYPE_ARROW || e->owner)

#define screeny (level?((level->scrolldir == SCROLL_UP || level->scrolldir == SCROLL_DOWN )? 0:advancey ):0)
#define screenx (level?advancex:0)

#define tobounce(e) (e->animation->bounce_factor && diff(0, e->velocity.y) > 1.5 && \
					 !((autoland == 1 && e->damage_on_landing.attack_force == -1) || e->damage_on_landing.attack_force == -2))

#define getpal ((current_palette&&level)?(level->palettes[current_palette-1]):pal)

#define validanim(e, a) ((e)->modeldata.animation[a]&&(e)->modeldata.animation[a]->numframes)

//#define     MAX_MOVES             16
//#define     MAX_MOVE_STEPS        16

#pragma pack(4)

 /*
 * Caskey, Damon V.
 * 2022-05-04
 *
 * Cheat options available through menu.
 */
typedef enum e_cheat_options
{
    CHEAT_OPTIONS_NONE = 0,
    CHEAT_OPTIONS_CREDITS_ACTIVE = (1 << 0),
    CHEAT_OPTIONS_CREDITS_MENU = (1 << 1),
    CHEAT_OPTIONS_ENERGY_ACTIVE = (1 << 2),
    CHEAT_OPTIONS_ENERGY_MENU = (1 << 3),
    CHEAT_OPTIONS_HEALTH_ACTIVE = (1 << 4),
    CHEAT_OPTIONS_HEALTH_MENU = (1 << 5),
    CHEAT_OPTIONS_IMPLACABLE_ACTIVE = (1 << 6),
    CHEAT_OPTIONS_IMPLACABLE_MENU = (1 << 7),
    CHEAT_OPTIONS_MASTER_MENU = (1 << 8),
    CHEAT_OPTIONS_LIVES_ACTIVE = (1 << 9),
    CHEAT_OPTIONS_LIVES_MENU = (1 << 10),
    CHEAT_OPTIONS_MULTIHIT_ACTIVE = (1 << 11),
    CHEAT_OPTIONS_MULTIHIT_MENU = (1 << 12),
    CHEAT_OPTIONS_TOD_ACTIVE = (1 << 13),
    CHEAT_OPTIONS_TOD_MENU = (1 << 14),    

    CHEAT_OPTIONS_ALL_MENU = (CHEAT_OPTIONS_MASTER_MENU | CHEAT_OPTIONS_CREDITS_MENU | CHEAT_OPTIONS_ENERGY_MENU | CHEAT_OPTIONS_HEALTH_MENU | CHEAT_OPTIONS_LIVES_MENU | CHEAT_OPTIONS_MULTIHIT_MENU)

} e_cheat_options;

/*
* Caskey, Damon V.
* 2022-05-03
*
* Miscellaneous settings and game 
* options we don’t want to save 
* between engines startups.
*/
typedef struct s_global_config
{
    e_ajspecial_config ajspecial;   // Which buttons can trigger breakout Special or Smartbomb.
    e_cheat_options cheats;         // Cheat menu config and active cheats.

} s_global_config;

/*
* Caskey, Damon V.
* 2022-05-03
* 
* Native hard coded sample IDs.
*/
typedef struct s_global_sample
{    
    int beat;
    int beep;
    int beep_2;
    int bike;
    int block;
    int fall;
    int get;
    int get_2;
    int go;
    int indirect;
    int jump;
    int one_up;
    int pause;
    int punch;
    int time_over;

} s_global_sample;

// Caskey, Damon V.
// 2020-02-17
//
// Tags are data defined by author on various other structures
// that have no associated engine logic. For example, an author
// might place tags on a given attack that identifies the attack
// source as "right arm", "left leg", and so on. The engine will 
// not use this data in any way, but the author could write scripts 
// to cause unique reactions when attacks make contact.
typedef struct s_meta_data
{
    struct s_meta_data* next;
    char* string[512];
    float decimal;
    int integer;
} s_meta_data;

// Caskey, Damon V.
// 2014-01-20
//
// Axis - Horizontal and lateral only (float).
typedef struct
{
    float x;    // Horizontal axis.
    float z;    // Lateral axis.
} s_axis_plane_lateral_float;

// Caskey, Damon V.
// 2014-01-20
//
// Axis - Horizontal and lateral only (int).
typedef struct
{
    int x;    // Horizontal axis.
    int z;    // Lateral axis.
} s_axis_plane_lateral_int;

// Caskey, Damon V.
// 2014-01-20
//
// Axis - Horizontal and vertical only (int).
typedef struct
{
    int x;      // Horizontal axis.
    int y;      // Altitude/Vertical axis.
} s_axis_plane_vertical_int;

// Caskey, Damon V.
// 2018-04-18
//
// Axis - 3D float.
typedef struct
{
    float x;
    float y;
    float z;
} s_axis_principal_float;

// Caskey, Damon V.
// 2018-04-18
//
// Axis - 3D int.
typedef struct
{
    int x;
    int y;
    int z;
} s_axis_principal_int;

typedef struct
{
    s_axis_principal_int    axis;
    int                     base;
} s_move;

// distance x and z for edge animation
typedef struct
{
    float x;
    float z;
} s_edge_range;

typedef struct
{
    /*
    Min/max cap for integer measurements.
    2013-12-10
    Damon Caskey
    */

    int max;    //max value.
    int min;    //min value.
} s_metric_range;

typedef struct
{
    /*
    Min/current/max cap for integer measurements.
    2014-01-20
    Damon Caskey
    */

    int current;    //Current.
    int max;    //max value.
    int min;    //min value.
} s_metric_range_current;

typedef struct
{
    unsigned compatibleversion;
    char dName[MAX_NAME_LEN]; // Difficulty Name
    unsigned level; // Level Number
    unsigned stage; // Stage
    unsigned pLives[MAX_PLAYERS]; // Player Lives Left
    unsigned pCredits[MAX_PLAYERS]; // Player Credits Left
    unsigned pScores[MAX_PLAYERS]; // Player Scores
    unsigned credits; // Number Of Credits
    unsigned times_completed;
    unsigned which_set;
    //-------------------new strict save features-----------------------
    int flag; // 0 useless slot 1 only load level number 2 load player info and level
    char pName[MAX_PLAYERS][MAX_NAME_LEN];   // player names
    int pSpawnhealth[MAX_PLAYERS];              // hit points left
    int pSpawnmp[MAX_PLAYERS];                  // magic points left
    int pWeapnum[MAX_PLAYERS];                  // weapon
    int pColourmap[MAX_PLAYERS];                // colour map

    int selectFlag;                             // saved a select.txt infos
    char allowSelectArgs[MAX_ALLOWSELECT_LEN];      // allowselect arguments
    char selectMusic[MAX_ARG_LEN];          // select music arguments
    char selectBackground[MAX_ARG_LEN];     // select background arguments
    char selectLoad[MAX_SELECT_LOADS][MAX_ARG_LEN];           // select load arguments
    int selectLoadCount;
    char selectSkipSelect[MAX_ARG_LEN];     // skipselect arguments
} s_savelevel;

typedef struct
{
    unsigned compatibleversion;
    unsigned highsc[10];
    char hscoren[10][MAX_NAME_LEN];
} s_savescore;

typedef struct
{
    /*
    Slow motion struct
    Damon V. Caskey
    2014-01-21
    */

    int duration;
    int counter;
    int toggle;
} s_slow_motion;

// Caskey, Damon V.
// 2011-04-08
//
// Delay modifiers before rise or
// riseattack can take place.
typedef struct
{
    unsigned int rise;               // Time modifier before rise.
    unsigned int riseattack;         // Time modifier before riseattack.
    unsigned int riseattack_stall;   // Total stalltime before riseattack.
} s_staydown;

// Caskey, Damon V.
// 2016-10-31
//
// Recursive damage structure
// for attack boxes and damage 
// recipient.
typedef struct s_damage_recursive
{
    int							force;  // Damage force per tick.
    int							index;  // Index.
	e_damage_recursive_logic			mode;   // Mode.
    int							rate;   // Tick delay.
    unsigned int				tick;   // Time of next tick.
    unsigned int				time;   // Time to expire.
	int							type;	// Attack type.
	struct entity				*owner;	// Entity that caused the recursive damage.
	struct s_damage_recursive	*next;	// Next node of linked list.

    // Meta data.
    s_meta_data*                meta_data;              // User defiend data.
    int					        meta_tag;	            // User defined int.
} s_damage_recursive;

typedef struct
{
	int x;
	int y;
	int width;
	int height;
	int z_background;
	int z_foreground;
} s_hitbox;

/*
* Caskey, Damon V.
* 2021-08-29
* 
* Used by model read in functions to
* tell the defense application which
* parameter is incoming. This is really 
* crude, but we do it this way because 
* the "all" option for attack types needs 
* to know beforehand which parameter to 
* work with.
*/
typedef enum
{    
    DEFENSE_PARAMETER_BLOCK_POWER,
    DEFENSE_PARAMETER_BLOCK_RATIO,
    DEFENSE_PARAMETER_BLOCK_THRESHOLD,
    DEFENSE_PARAMETER_BLOCK_TYPE,
    DEFENSE_PARAMETER_FACTOR,
    DEFENSE_PARAMETER_KNOCKDOWN,   
    DEFENSE_PARAMETER_LEGACY,
    DEFENSE_PARAMETER_PAIN
} e_defense_parameters;

typedef struct
{
    int         blockpower;     // If > unblockable, this attack type is blocked.
    int         blockthreshold; // Strongest attack from this attack type that can be blocked.
    float       blockratio;     // % of damage still taken from this attack type when blocked.
    e_blocktype blocktype;      // Resource drained when attack is blocked.
    float       factor;         // Multiplier applied to incoming damage.
    float       knockdown;      // Multiplier applied to incoming knockdown.
    int         pain;           // Pain factor (like nopain) for defense type.

    // Meta data.
    s_meta_data* meta_data;     // User defiend data.
    int			 meta_tag;	    // User defined int.
} s_defense;

// Caskey, Damon V.
// 2018-04-10
//
// Causing damage when an entity lands from
// a fall.
typedef struct
{
    int attack_force;
    e_attack_types attack_type;
} s_damage_on_landing;

// Collision box for detecting
// entity boxes.
typedef struct
{
    s_hitbox    *coords;        // Collision box dimensions.
    int         index;          // To enable user tracking of this box's index when multiple instances are in use.
    s_meta_data* meta_data;  // User defiend data.
    int			meta_tag;	// User defined int.
} s_collision_entity;

// List of collision body boxes
// per animation frame.
typedef struct
{
    s_collision_entity **instance;
} s_collision_entity_list;

// Collision box for active
// attacks.
typedef struct
{
        int                 blast;              // Attack box active on hit opponent's fall animation.
        int                 steal;              // Add damage to owner's hp.
        int                 ignore_attack_id;   // Ignore attack ID to attack in every frame
        int                 no_flash;           // Flag to determine if an attack spawns a flash or not
        int                 no_kill;            // this attack won't kill target (leave 1 HP)
        int                 no_pain;            // No animation reaction on hit.
        int                 pause_add;          // Flag to determine if an attack adds a pause before updating the animation
        int                 freeze;             // Lock target in place and set freeze time.
    
        int                 grab;               // Not a grab as in grapple - behavior on hit for setting target's position
        e_otg               otg;                // Over The Ground. Gives ground projectiles the ability to hit lying ents.

    int                 attack_drop;        // now be a knock-down factor, how many this attack will knock victim down
    e_attack_types      attack_type;        // Reaction animation, death, etc.
    int                 counterattack;      // Treat other attack boxes as body box.
        
    int                 jugglecost;         // cost for juggling a falling ent
    int                 no_block;           // If this is greater than defense block power, make the hit
        
    int                 seal;               // Disable target's animations with energy_cost > seal.
    
    e_direction_adjust  force_direction;    // Adjust target's direction on hit.
    int                 attack_force;       // Hit point damage attack inflicts.
    int                 blockflash;         // Custom bflash for each animation, model id
    int                 blocksound;         // Custom sound for when an attack is blocked
    int                 forcemap;           // Set target's palette on hit.
    unsigned int        freezetime;         // Time for target to remain frozen.
    
    int                 guardcost;          // cost for blocking an attack
    int                 hitflash;           // Custom flash for each animation, model id
    int                 hitsound;           // Sound effect to be played when attack hits opponent
    int                 index;              // Possible future support of multiple boxes - it's doubt even if support is added this property will be needed.
    unsigned int        maptime;            // Time for forcemap to remain in effect.
    unsigned int        next_hit_time;      // pain invincible time
    unsigned int        sealtime;           // Time for seal to remain in effect.
    int                 grab_distance;      // Distance used by "grab".
    s_axis_principal_float            dropv;              // Velocity of target if knocked down.
    s_damage_on_landing damage_on_landing;  // Cause damage when target entity lands from fall.
    s_staydown          staydown;           // Modify victum's stayodwn properties.
    s_damage_recursive  *recursive;         // Set up recursive damage (dot) on hit.

    // Meta data.
    s_meta_data*        meta_data;              // User defiend data.
    int					meta_tag;	            // User defined int.
} s_attack;

/* ** Collision Refactor IP - 2020-02-10 **/

/* 
* Collision box for detecting
* physical space.
*/
typedef struct
{
    int         index;              // To enable user tracking of this box's index when multiple instances are in use.
    s_meta_data*      meta_data;    // User defined data.
    int         meta_tag;           // user defined int.
} s_collision_space;

/* 
* Caskey, Damon V.
* 2020-02-20
*
* Collision attack container for
* dishing out hits. 
*/
typedef struct s_collision_attack
{
    struct s_collision_attack* next;       // Next item in linked list.
    s_attack*           attack;     // Attacking properties.
    s_hitbox*           coords;     // Collision box dimensions.
    s_meta_data*        meta_data;  // User defined data.
    int                 meta_tag;   // User defined int.      
    int                 index;      // Listing index.
} s_collision_attack;

/*
* Caskey, Damon V.
* 2020-02-20
*
* Body properties for detecting hits.
*/
typedef struct
{    
    s_defense* defense;       // Defense properties for this collision box only.    
} s_body;

/*
* Caskey, Damon V.
* 2020-02-20
*
* Collision body container for
* detecting hits.
*/
typedef struct s_collision_body
{
    struct s_collision_body* next;    // Next item in linked list.
    s_body* body;                       // Body properties.
    s_hitbox* coords;                   // Collision box dimensions.
    s_meta_data* meta_data;             // User defined data.
    int                 meta_tag;       // User defined int.      
    int                 index;          // Listing index.
} s_collision_body;

// Caskey, Damon V.
// 2013-12-15
//
// Last hit structure. Populated each time a collision is detected.
typedef struct
{
    int						    confirm;                    // Will engine's default hit handling be used?
    s_axis_principal_float	    position;                   // X,Y,Z of last hit.
    s_collision_attack*         collision_attack;           // Collision container for attack.
    s_attack*                   attack;                     // Attack object (has attack properties).
    s_collision_body*           detect_collision_body;      // Collision container for body.
    s_body*                     detect_body;                // Body object (has body properties).
    s_collision_attack*         detect_collision_attack;    // When hit by counterattack, this is collision attack container taking hit.      
    struct entity*			    target;	                    // Entity taking the hit.
	struct entity*			    attacker;	                // Entity dishing out the hit.
    
} s_lasthit;

// Caskey, Damon V.
// 2011-04-01
//
// Counter action when taking hit.
typedef struct
{
	e_counter_action_condition_logic condition; // Counter conditions.
    e_counter_action_take_damage damaged;		// Receive damage from attack.
    s_metric_range frame;						// Frame range.
} s_counter_action;

typedef struct
{
    /*
    HP and/or MP cost to perform special/freespecials.
    Damon V. Caskey
    2011-04-01
    */

    int cost;           //Amount of energy cost.
    int disable;        //Disable flag. See check_energy function.
    e_cost_type mponly; //MPonly type. 0 = MP while available, then HP. 1 = MP only. 2 = HP only.
} s_energy_cost;

// Caskey, Damon V.
// 2011-04-01
//
// On frame movement (slide, jump, dive, etc.).
typedef struct
{
    unsigned int  frame;      // Frame to perform action.
    int                 ent;        // Index of entity to spawn.
    s_axis_principal_float            velocity;   // x,a,z velocity.
} s_onframe_move;

#define FRAME_SET_MODEL_INDEX_DEFAULT MODEL_INDEX_NONE

// Caskey, Damon V.
// 2018-04-20
//
// On frame action, where no movement is needed. (Landing, starting to fall...).
typedef struct
{
    unsigned int	frame;			// Frame to perform action.
    int				model_index;	// Index of model to spawn.
} s_onframe_set;

typedef struct
{
    /*
    Animation looping.
    Damon V. Caskey
    2011-04-01
    */

    s_metric_range frame;   // max = Frame animation reaches before looping, min = Frame animation loops back to.
    int mode;           // 0 = No loop, 1 = Loop. Redundant after frame additions, but needed for backward compatibility.
} s_loop;

typedef struct //2011_04_01, DC: Frame based screen shake functionality.
{
    int cnt;        //Repetition count.
    int framestart; //Frame to start quake.
    int repeat;     //Repetitons.
    int v;          //Vertical distance of screen movement (in pixels).
} s_quakeframe;

// Caskey, Damon V.
//
// Distance to target verification for AI running, jumping,
// following parent, and combo chains for all entity types.
typedef struct
{
    s_metric_range base;
    s_metric_range x;
    s_metric_range y;
    s_metric_range z;
} s_range;

typedef struct
{
    /*
    Model/entity level delay modifier.
    Damon V. Caskey
    (unknown date) revised 2013-12-16.
    */
    s_metric_range cap;
    float factor;
    e_edelay_mode mode;
    s_metric_range range;
} s_edelay;

typedef struct
{
    /*
    Follow up animation struct.
    Damon V. caskey
    2014-01-04
    */

    unsigned int animation;   // Follow animation to perform.
    e_follow_condition_logic condition;   // Condition in which follow up will be performed.
} s_follow;

// Caskey, Damon V.
// 2019-12-17
//
// Placements for projectile entities.  Controls
// how position is applied (relative to parent, 
// the screen, ...). 
typedef enum
{
	// Keep these in order for legacy compatability.
	PROJECTILE_PLACEMENT_SCREEN,
	PROJECTILE_PLACEMENT_PARENT,
	PROJECTILE_PLACEMENT_ABSOLUTE
} e_projectile_placement;

// Caskey, Damon V.
// 2014-01-18
//
// Projectile spawning.
#define PROJECTILE_LEGACY_COMPATABILITY_POSITION_X -2147483648.f
#define PROJECTILE_DEFAULT_STAR_POSITION_X 50.f
#define PROJECTILE_DEFAULT_POSITION_X 0.f
#define PROJECTILE_DEFAULT_POSITION_Y 70.f
#define PROJECTILE_DEFAULT_POSITION_Z 0.f
#define	PROJECTILE_DEFAULT_SPEED_X	1.f
#define	PROJECTILE_DEFAULT_SPEED_Y	0.f
#define	PROJECTILE_DEFAULT_SPEED_Z	0.f

typedef struct
{
	int                     bomb;				// ~ custbomb;
	e_color_adjust			color_set_adjust;	// ~ Palette selection.
	e_direction_adjust		direction_adjust;	// ~
	int                     flash;				// ~ custpshotno;
	int                     knife;				// ~ custknife;
	e_projectile_offense	offense;			// ~ Offense factor source.
	e_projectile_placement	placement;			// ~ How position applies.
	s_axis_principal_float	position;			// ~ Location at which projectiles are spawned.
	int						shootframe;         // ~ Frame to throw flash.
	int                     star;				// ~ custstar.
	float					star_velocity[3];	// Legacy star velocity.
	int						throwframe;         // ~ Frame to throw knife.
	int						tossframe;			// ~ Frame to toss bomb/grenade.
	s_axis_principal_float	velocity;			// ~ Throw velocity.
} s_projectile;

// Caskey, Damon V.
// 2019-12-15
//
// Placements for sub entities.  Controls
// how position is applied (relative to 
// parent, the screen, ...). 
typedef enum
{
	// Keep these in order for legacy compatability.
	SUB_ENTITY_PLACEMENT_PARENT,
	SUB_ENTITY_PLACEMENT_SCREEN,
	SUB_ENTITY_PLACEMENT_ABSOLUTE
} e_sub_entity_placement;

// Caskey, Damon V.
// 2019-12-11
//
//  Sub entity spawning.
typedef struct
{
	int frame;
	e_sub_entity_placement placement;
	s_axis_principal_float position;
} s_sub_entity;



#define ANIMATION_BOUNCE_FACTOR_DEFAULT	4
#define ANIMATION_CHARGE_TIME_DEFAULT	2

/* 
* Caskey, Damon V
* 2019-11-19
*
* Cancel feature originally coded by orochi_x ("OX" in code). 
* Functionally the cancel member appears to be a simple Boolean 
* flag and the code uses it as such. Therefore we normally wouldn't
* need or bother with named constants. However, OX used a value 
* of 3 for the enabled state and left a notation stressing the 
* importance of keeping it as is. I am unable to determine why, 
* but since 3 works let�s take his advice and leave it be for now.
*/
typedef enum
{
	ANIMATION_CANCEL_DISABLED	= 0,
	ANIMATION_CANCEL_ENABLED	= 3
} e_anim_cancel;

typedef struct
{
	// Sub structures.
	s_counter_action			counter_action;			// Auto counter attack. ~~
	s_energy_cost				energy_cost;			// Energy (MP/HP) required to perform special moves. ~~
	s_onframe_set				dropframe;				// if tossv < 0, this frame will be set. ~~
	s_follow					followup;               // Subsequent animation on hit. ~~
	s_onframe_move				jumpframe;				// Jumpframe action. 2011_04_01, DC: moved to struct. ~~
	s_onframe_set				landframe;				// Landing behavior. ~~
	s_loop						loop;                   // Animation looping. 2011_03_31, DC: Moved to struct. ~~
	s_quakeframe				quakeframe;             // Screen shake effect. 2011_04_01, DC; Moved to struct. ~~
	s_range						range;                  // Verify distance to target, jump landings, etc. ~~
	s_axis_principal_int		size;                   // Dimensions (height, width). ~~
	
	s_sub_entity*				sub_entity_spawn;		// Replace legacy "spawnframe" - spawn an entity unrelated to parent. ~~
	s_sub_entity*				sub_entity_summon;		// Replace legacy "summonframe" - spawn an entity as child we can unsommon later (limited to one). ~~
	s_projectile*				projectile;             // Sub entity spawn for knives, stars, bombs, hadouken, etc. ~~

    s_collision_attack**        collision_attack;       // Head node for collision detection (attack).
    s_collision_body**          collision_body;         // Head node for collision detection (body).
	s_collision_entity_list**	collision_entity;
	s_move**					move;					// base = seta, x = move, y = movea, z = movez
	s_axis_plane_vertical_int**	offset;				    // original sprite offsets
	s_drawmethod**				drawmethods;

	float						(*platform)[8];			// Now entities can have others land on them
	
	unsigned					*idle;					// Allow free move
	int							*delay;
	int							*shadow;
	int							(*shadow_coords)[2];	// x, z offset of shadow
	int							*soundtoplay;           // each frame can have a sound
	int							*sprite;                // sprite[set][framenumber]
	int							*vulnerable;
	int							*weaponframe;           // Specify with a frame when to switch to a weapon model
	
	float						bounce_factor;			// On fall landing, New Y = -(old Y) / bounce_factor. ~~

	// Enumerated integers
	e_anim_cancel				cancel;                 // Cancel anims with freespecial. ~~
    e_move_constraint           move_constraint;        // Subject to gravity, walls, etc.

	// Integers
	unsigned int				charge_time;            // charge time for an animation. ~~
	int							flipframe;              // Turns entities around on the desired frame. ~~
	int							hit_count;              // How many consecutive hits have been made? Used for canceling. ~~
	int							index;                  // unique id.~~
	int							numframes;              // Count of frames in the animation. ~~	
	int							model_index;			// model index animation loaded to. ~~
	int							sub_entity_model_index;	// Sub entity model index (for spawn/summon).
	int							sub_entity_unsummon;    // Un-summon the entity
	int							sync;                   // Synchronize frame to previous animation if they matches

    
	int						    attack_one;             // Attack hits only one target. ~~
	
    // Meta data.
    s_meta_data*                meta_data;              // User defiend data.
    int					        meta_tag;	            // User defined int.
} s_anim;

struct animlist
{
    s_anim *anim;
    struct animlist *next;
};
typedef struct animlist s_anim_list;
extern s_anim_list *anim_list;

// Caskey, Damon V.
// 2019-02-03
// 
// Absolute Cube. This is when
// we need the post calculation 
// coordinates at each side of 
// a cube as opposed to demensions.
typedef struct
{
    int background;	// Side of cube facing toward background.
    int foreground;	// Side of cube facing foreground/camera.
    int center_x;
    int center_y;
    int center_z;
    int left;
    int right;
    int bottom;
    int top;
} s_box;

// Caskey, Damon V.
// 2020-02-03
//
// Data structure to calculate collisions. We want to 
// break collision detection down into reusable functions.
// These functions usually run in loops and much of the
// processing can be factored outside of loops, but we
// also want to avoid a ton of messy and repetitive 
// parameters. This structre gives us a "one stop shop"
// we can use to pass data around between the functions
// with a single fast pointer, and allows future extension.
//
// Some members may appear redendant (i.e animation when
// we could just get it from entity pointer). This is
// because of the nested looping needed to check collisions.
// Some attributes must be aquired at different points
// in the checking process.
typedef struct {

    // return_overlap is the center position between both
    // collision boxes. This is vital for functionality like
    // spawning hit flash entities.

    s_box* return_overlap;

    // Seek is generally the initiating party. In the 
    // case of attack detection, it would be the attacker.
    // Target is the party we want to know if we are making
    // contact with. Both are just labels for human use. The 
    // code can use them interchangeably.

    s_anim* seeker_animation;    // Current animation. use this to determine which animation's collision boxes to check.    
    s_hitbox* seeker_coords;            // Current set of collision coordinates to compare.
    e_direction seeker_direction;       // Current facing. In the case of entities, we have to reverse the X coordinates when facing left. 
    struct entity* seeker_ent;          // Acting entity (if any).
    int seeker_frame;                   // Current animation frame.       
    s_axis_principal_int* seeker_pos;   // Current position as integer. Collision coordinates are relative positions and dimensions - We need the acting entity's location as an integer to calculate absolute collisions box before we can test overlap. 

    // Target is the testing target. In the case of an
    // attack, this is the party that might get hit. The
    // attribites are otherwise identical to seeker.

    s_anim* target_animation;
    s_hitbox* target_coords;
    e_direction target_direction;
    struct entity* target_ent;
    int target_frame;
    s_axis_principal_int* target_pos;

} s_collision_check_data;

typedef struct
{
    s_axis_plane_vertical_int offset;
    s_axis_plane_vertical_int size;
    e_bartype type;
    e_barorient orientation;
    int noborder;
    e_bar_dir direction;
    int barlayer;
    int backlayer;
    int borderlayer;
    int shadowlayer;
    int (*colourtable)[11]; //0 default backfill 1-10 foreground colours
} s_barstatus;

typedef struct
{
    e_loadingScreenType set;    //Loading bar mode.
    int tf;                     //Font number for "LOADING" text (last element in command, moved here because of alignment)
    s_axis_plane_vertical_int bar_position;   //Loading bar position.
    s_axis_plane_vertical_int text_position;  //Loading text position.
    int bsize;                  // length of bar in pixels
    int refreshMs;              // modder defined number of milliseconds in which the screen is updated while loading
} s_loadingbar;

typedef struct
{
    Script         *animation_script;               //system generated script
    Script         *update_script;                  //execute when update_ents
    Script         *think_script;                   //execute when entity thinks.
    Script         *takedamage_script;              //execute when taking damage.
    Script         *on_bind_update_other_to_self_script;   //execute when adjust_bind runs, for the bind target entity.
    Script         *on_bind_update_self_to_other_script;   //execute when adjust_bind runs, for the bound entity.
    Script         *ondeath_script;                 //execute when killed in game.
    Script         *onkill_script;                  //execute when removed from play.
    Script         *onpain_script;                  //Execute when put in pain animation.
    Script         *onfall_script;                  //execute when falling.
    Script         *inhole_script;                  //execute when yoy're in a hole
    Script         *onblocks_script;                //execute when blocked by screen.
    Script         *onblockw_script;                //execute when blocked by wall.
    Script         *onblockp_script;                //execute when blocked by platform.
    Script         *onblocko_script;                //execute when blocked by obstacle.
    Script         *onblockz_script;                //execute when blocked by Z.
    Script         *onblocka_script;                //execute when "hit head".
    Script         *onmovex_script;                 //execute when moving along X axis.
    Script         *onmovez_script;                 //execute when moving along Z axis.
    Script         *onmovea_script;                 //execute when moving along A axis.
    Script         *didhit_script;                  //execute when attack hits another.
    Script         *onspawn_script;                 //execute when spawned.
    Script         *key_script;                     //execute when entity's player presses a key
    Script         *didblock_script;                //execute when blocking attack.
    Script         *ondoattack_script;              //execute when attack passes do_attack checks.
    Script			*onmodelcopy_script;			//execute when set_model_ex is done
    Script			*ondraw_script;					//when update_ents is called
    Script			*onentitycollision_script;		//execute when entity collides with other entity
} s_scripts;

typedef struct
{
    /*
    In game icons added 2005_01_20.
    2011-04-05
    Damon V. Caskey
    */

    int def; //Default icon.
    int die; //Health depleted.
    int get; //Retrieving item.
    int mphigh; //MP bar icon; at 66% or more (default if other mp icons not used).
    int mplow; //MP bar icon; at or between 0% and 32%.
    int mpmed; //MP bar icon; at or between 33% and 65%.
    int pain; //Taking damage.
    int usemap;
    int weapon; //Weapon model.
    s_axis_plane_vertical_int position;
} s_icon;



typedef struct
{
    /*
    Pre defined color map selections and behavior.
    Damon V. Caskey
    2011_04_07
    */

    int burn;
    int shock;
    int frozen;             //Frozen.
    int hide_end;           //End range for maps hidden during character selection.
    int hide_start;         //Start range for maps hidden during character selection.
    int ko;                 //Health depleted.
    e_komap_type kotype;   //KO map application.
} s_maps;

typedef struct
{
    /*
    Perception distance (range from self AI can detect other entities).
    Damon V. Caskey
    2013-12-16
    */

    s_axis_principal_int max;   //Maximum.
    s_axis_principal_int min;   //Minimum.
} s_sight;

typedef struct
{
    signed char     detect;                         //Invisbility penetration. If self's detect >= target's hide, self can "see" target.
    signed char     hide;                           //Invisibility to AI.
} s_stealth;                                        //2011_04_05, DC: Invisibility to AI feature added by DC.


// WIP
typedef struct
{
    int input[MAX_SPECIAL_INPUTS];
    int	steps;
    int numkeys; // num keys pressed
    int anim;
    int	cancel;		//should be fine to have 0 if idle is not a valid choice
    s_metric_range frame;
    int hits;
    int valid;		// should not be global unless nosame is set, but anyway...
    //int (*function)(); //reserved
} s_com;

//UT: new bit flags for noquake property
#define NO_QUAKE 1  //do not make screen quake
#define NO_QUAKEN 2  //do not quake with screen

/*
* Caskey, Damon V.
* 2022-04-26
* 
* Player control options while jumping.
*/

#define AIR_CONTROL_STOP_FACTOR 0.95

typedef enum e_air_control
{
    AIR_CONTROL_NONE                = 0,
    AIR_CONTROL_JUMP_DISABLE        = (1 << 0),
    AIR_CONTROL_JUMP_TURN           = (1 << 1),
    AIR_CONTROL_JUMP_X_ADJUST       = (1 << 2),
    AIR_CONTROL_JUMP_X_MOVE         = (1 << 3),
    AIR_CONTROL_JUMP_X_STOP         = (1 << 4),
    AIR_CONTROL_JUMP_Y_STOP         = (1 << 5),
    AIR_CONTROL_JUMP_Z_ADJUST       = (1 << 6),
    AIR_CONTROL_JUMP_Z_INITIAL      = (1 << 7),
    AIR_CONTROL_JUMP_Z_MOVE         = (1 << 8),
    AIR_CONTROL_JUMP_Z_STOP         = (1 << 9),
    AIR_CONTROL_WALKOFF_TURN        = (1 << 10),
    AIR_CONTROL_WALKOFF_X_ADJUST    = (1 << 11),
    AIR_CONTROL_WALKOFF_X_MOVE      = (1 << 12),
    AIR_CONTROL_WALKOFF_X_STOP      = (1 << 13),
    AIR_CONTROL_WALKOFF_Z_ADJUST    = (1 << 14),
    AIR_CONTROL_WALKOFF_Z_MOVE      = (1 << 15),
    AIR_CONTROL_WALKOFF_Z_STOP      = (1 << 16)
} e_air_control;

/*
* Caskey, Damon V.
* 2022-04-26
*
* Used to interpret legacy air 
* control text. Do not adjust 
* these values or you will
* break legacy compatability
* for air control.
*/
typedef enum e_air_control_legacy_x
{
    // low byte: 0 default 1 flip in air, 2 move in air, 3 flip and move
    AIR_CONTROL_LEGACY_X_NONE = 0,
    AIR_CONTROL_LEGACY_X_FLIP = 1,
    AIR_CONTROL_LEGACY_X_ADJUST = 2,          // Change velocity during horizontal jump.
    AIR_CONTROL_LEGACY_X_ADJUST_AND_FLIP = 3, // Change velocity or flip during horizontal jump.
    AIR_CONTROL_LEGACY_X_MOVE = 4,             // Change velocity during vertical jump.
    AIR_CONTROL_LEGACY_X_MOVE_AND_FLIP = 5,
    AIR_CONTROL_LEGACY_X_MOVE_ALT = 6,
    AIR_CONTROL_LEGACY_X_MOVE_AND_FLIP_ALT = 7

} e_air_control_legacy_x;

typedef enum e_air_control_legacy_z
{
    // low byte: 0 default 1 flip in air, 2 move in air, 3 flip and move
    AIR_CONTROL_LEGACY_Z_NONE = 0,
    AIR_CONTROL_LEGACY_Z_MOMENTUM = 1,        // Keep walking momentum.
    AIR_CONTROL_LEGACY_Z_ADJUST = 2,
    AIR_CONTROL_LEGACY_Z_MOMENTUM_AND_ADJUST = 3,
    AIR_CONTROL_LEGACY_Z_MOMENTUM_AND_FLIP = 4
} e_air_control_legacy_z;

typedef struct
{
    /*
    Dust struct. "Dust" effect entity spawned during certain actions.
    Damon V. Caskey
    2013-12-28
    */

    int fall_land;  //Knockdown landing.
    int jump_land;  //Jump landing.
    int jump_start; //Jump lift off.
} s_dust;

/*
* Caskey, Damon V.
* 2022-05-02
* 
* Properties for icon displayed
* over player entity when spawned 
* into game.
*/
typedef struct
{
    int sprite;
    s_axis_plane_vertical_int position;
} s_player_arrow;

typedef enum
{
    /*
    Weapon loss type enum.
    Damon V. Caskey
    2013-12-29
    */

    WEAPLOSS_TYPE_ANY,         //Weapon lost taking any hit.
    WEAPLOSS_TYPE_KNOCKDOWN,   //Weapon lost on knockdown.
    WEAPLOSS_TYPE_DEATH,       //Weapon lost on death.
    WEAPLOSS_TYPE_CHANGE       //weapon is lost only when level ends or character is changed during continue. This depends on the level settings and whether players had weapons on start or not.
} e_weapon_loss_condition_legacy;

/*
* Weapon loss conditions.
*/
typedef enum
{
    WEAPON_LOSS_CONDITION_NONE          = 0,
    WEAPON_LOSS_CONDITION_DAMAGE        = (1 << 0),
    WEAPON_LOSS_CONDITION_DEATH         = (1 << 1),
    WEAPON_LOSS_CONDITION_FALL          = (1 << 2),
    WEAPON_LOSS_CONDITION_GRABBED       = (1 << 3),
    WEAPON_LOSS_CONDITION_GRABBING       = (1 << 4),
    WEAPON_LOSS_CONDITION_LAND_DAMAGE   = (1 << 5),
    WEAPON_LOSS_CONDITION_PAIN          = (1 << 6),
    WEAPON_LOSS_CONDITION_STAGE         = (1 << 7),
    WEAPON_LOSS_CONDITION_DEFAULT       = (WEAPON_LOSS_CONDITION_DAMAGE | WEAPON_LOSS_CONDITION_DEATH | WEAPON_LOSS_CONDITION_FALL | WEAPON_LOSS_CONDITION_GRABBED | WEAPON_LOSS_CONDITION_GRABBING | WEAPON_LOSS_CONDITION_LAND_DAMAGE | WEAPON_LOSS_CONDITION_PAIN)
} e_weapon_loss_condition;

typedef enum e_weapon_state
{
    WEAPON_STATE_NONE           = 0,    
    WEAPON_STATE_ANIMAL         = (1 << 1), // Legacy "Animal". Behaviors to emulate ridable animals from Golden Axe.
    WEAPON_STATE_DEDUCT_USE     = (1 << 2), // Limited item will deduct a use from count.
    WEAPON_STATE_HAS_LIST       = (1 << 3), // Has a weapon list.
    WEAPON_STATE_LIMITED_USE    = (1 << 4)  // Legacy "typeshot". Item is limited use with a remaining count shown in HUD.    
} e_weapon_state;

/*
* Caskey, Damon V.
* 2022-05-02
* 
* Properties for controlling 
* weapon and weapon pickup behavior.
*/
typedef struct
{
    e_weapon_state weapon_state; // Booloean weapon behavior flags.

    e_weapon_loss_condition loss_condition; // What events cause loss of weapon.
    int loss_count; // Losses remaining before weapon is destroyed.
    int loss_index; // If >0, switch to this weapon index when current weapon is lost.

    unsigned use_count; // Uses (i.e. ammo) remaining for limited quantity weapon.
    unsigned use_add; // Item adds this value to use_count if collector has limited use weapon.
    int weapon_index; // Weapon list entry in use (or collector will use if this is an item).   
    int* weapon_list; // Weapon model list.
    int weapon_count; // Number of entries in weapon list.
} s_weapon;

typedef struct
{
    int index;
    char *name;
    char *path; // Path, so scripts can dynamically get files, sprites, sounds, etc.
    unsigned score;
    int health;
    float scroll; // Autoscroll like panel entity.
    unsigned offscreenkill;                  // for biker, arrow, etc
    float offscreen_noatk_factor;
    int	priority;
    //unsigned offscreenkillz;
    //unsigned offscreeenkila;
    int mp; // mp's variable for mpbar by tails
    
    
    
        int nolife; // Feb 25, 2005 - Variable flag to show life 0 = no, else yes
        int makeinv; // Option to spawn player invincible >0 blink <0 noblink
    int riseinv; // how many seconds will the character become invincible after rise >0 blink, <0 noblink
        int dofreeze; // Flag to freeze all enemies/players while special is executed
        int noquake; // Flag to make the screen shake when entity lands 1 = no, else yes
        int ground; // Flag to determine if enemy projectiles only hit the enemy when hitting the ground
    int multiple; // So you can control how many points are given for hitting opponents
    int bounce; // Flag to determine if bounce/quake is to be used.
    e_entity_type type;
    e_entity_type_sub subtype;
    s_icon icon; //In game icons added 2005_01_20. 2011_04_05, DC: Moved to struct.

    s_player_arrow player_arrow[MAX_PLAYERS]; // Image to be displayed when player spawns invincible
    
    int setlayer; // Used for forcing enities to be displayed behind
    
    s_maps maps; //2011_04_07, DC: Pre defined color map selections and behavior.
    int alpha; // New alpha variable to determine if the entity uses alpha transparency
    int toflip; // Flag to determine if flashes flip or not
    
    /* Shadows */
    int shadow;
    int gfxshadow; // use current frame to create a shadow
    int shadowbase;
    int aironly; // Used to determine if shadows will be shown when jumping only
    
    int nomove; // Flag for static enemies
    int noflip; // Flag to determine if static enemies flip or stay facing the same direction
    int nodrop; // Flag to determine if enemies can be knocked down
    int nodieblink; // Flag to determine if blinking while playing die animation
    
    /* Blocking */
    int thold; // The entities threshold for block
    int holdblock; // Continue the block animation as long as the player holds the button down
    int nopassiveblock; // Don't auto block randomly
    int blockback; // Able to block attacks from behind
    int blockodds; // Odds that an enemy will block an attack (1 : blockodds)

    s_edelay edelay; // Entity level delay adjustment.
    float runspeed; // The speed the character runs at
    float runjumpheight; // The height the character jumps when running
    float runjumpdist; // The distance the character jumps when running
    int noatflash; // Flag to determine if attacking characters attack spawns a flash
    int runupdown; // Flag to determine if a player will continue to run while pressing up or down
    int runhold; // Flag to determine if a player will continue to run if holding down forward when landing
    int remove; // Flag to remove a projectile on contact or not
    
    s_com *special; // Stores freespecials
    int specials_loaded; // Stores how many specials have been loaded
    int diesound;
    
    s_weapon weapon_properties;
    
    /* Availability. */
    int secret;
    int clearcount;
    

    /* Projectile model IDs */
    int project;
    int rider; // 7-1-2005 now every "biker" can have a new driver!
    int knife; // 7-1-2005 now every enemy can have their own "knife" projectile
    int pshotno; // 7-1-2005 now every enemy can have their own "knife" projectile
    int star; // 7-1-2005 now every enemy can have their own "ninja star" projectiles
    int bomb; // New projectile type for exploding bombs/grenades/dynamite
    int flash; // Now each entity can have their own flash
    int bflash; // Flash that plays when an attack is blocked

    s_dust dust; //Spawn entity during certain actions.

    s_axis_plane_vertical_int size; // Used to set height of player in pixels
    s_axis_principal_float speed;
    
    float pathfindstep; // UT: how long each step if the entity is trying to find a way
        
    float jumpspeed; // normal jump foward speed, default to max(1, speed)
    float jumpheight; // 28-12-2004	Jump height variable added per character

    e_air_control air_control; /* Mid air control options (turning, moving, etc.). */
    
    /* Grab flags. */
        int grabback; // Flag to determine if entities grab images display behind opponenets    
        int grabfinish; // Cannot take further action until grab animation is complete.
        int grabflip; // Flip target or not, bit0: grabber, bit1: opponent
        int grabturn; // Turn with grabbed target using Left/Right (if valid ANI_GRABTURN).

    /* Grab variables. */
    int paingrab; // Added to grab resistance when not in pain.
    float grabdistance; // 30-12-2004	grabdistance varirable adder per character    
    int grab_force; /* Attacker's grab force must exceed target's grab_resistance to initiate grab. */
    int grab_resistance; /* Attacker's grab force must exceed target's grab_resistance to initiate grab. */    
    float grabwalkspeed;
    int throwdamage; // 1-14-05  adjust throw damage
    int throwframewait; // The frame victim is thrown during ANIM_THROW, added by kbandressen 10/20/06
    float throwdist; // The distance an opponent can now be adjusted
    float throwheight; // The height at which an opponent can now be adjusted    

    e_facing_adjust facing;
    
    unsigned char  *palette; // original palette for 32/16bit mode
    unsigned char	**colourmap;
    int maps_loaded; // Used for player colourmap selecting
    int unload; // Unload model after level completed?
    int falldie; // Play die animation?
    int globalmap; // use global palette for its colour map in 24bit mode
    int nopain;
    int summonkill; // kill it's summoned entity when died;  0. dont kill 1. kill summoned only 2. kill all spawned entity
    int combostyle;
    int blockpain;
    int atchain[MAX_ATCHAIN];
    int chainlength;
    s_anim **animation;
    int credit;
    int escapehits; // Escape spammers!
    int chargerate; // For the charge animation
    int guardrate; // Rate for guardpoints recover.
    int mprate; // For time-based mp recovery.
    int mpdroprate; // Time based MP loss.
    int mpstable; // MP stable type.
    int mpstableval; // MP Stable target.
    int aggression; // For enemy A.I.
    s_staydown risetime;
    unsigned sleepwait;
    int riseattacktype;
    s_metric_range_current jugglepoints; // Juggle points feature by OX. 2011_04_05, DC: Moved to struct.
    s_metric_range_current guardpoints; // Guard points feature by OX. 2011_04_05, DC: Moved to struct.
    int mpswitch; // switch between reduce or gain mp for mpstabletype 4
    int turndelay; // turn delay
    int lifespan; // lifespan count down
    float knockdowncount; // the knock down count for this entity
    float attackthrottle; // how often the enemy refuse to attack
    float attackthrottletime; // how long does the throttle status last
    s_stealth stealth; // Invisibility to AI feature added by DC. 2011_04_05, DC: Moved to struct.
    s_edge_range edgerange; // Edge range
    int entitypushing; // entity pushing active in entity collision
    float pushingfactor; // pushing factor in entity collision

    //---------------new A.I. switches-----------
    e_entity_type hostile; // specify hostile types
    e_entity_type candamage; // specify types that can be damaged by this entity
    e_entity_type projectilehit; // specify types that can be hit by this entity if it is thrown
    s_sight sight; // Sight range. 2011_04_05, DC: Moved to struct.
    unsigned int aimove; // move style
    unsigned int aiattack; // attack/defend style

    //----------------physical system-------------------
    float antigravity;                    //antigravity : gravity * (1- antigravity)

    //--------------new property for endlevel item--------
    char *branch; //level branch name
    e_model_copy model_flag; // Control portions copied from orginal model when entity switches model.

    s_defense *defense; //defense related, make a struct to aid copying
    float *offense_factors; //basic offense factors: damage = damage*offense
    s_attack *smartbomb;

    // e.g., boss
    s_barstatus hpbarstatus;
    int hpx;
    int hpy;
    int namex;
    int namey;

    /* Movement restriction flags. Subject to screen, wall, hole, hit head, etc. */
    e_move_constraint move_constraint;
        
    int instantitemdeath; // no delay before item suicides
    int	hasPlatforms;
    int isSubclassed;
    int backpain;
    
    int hitwalltype; // wall type to toggle hitwall animations

    //Kratus (12-2021) Moved the new added properties to the end of the list for easy searching
    int jumpspecial; // 0 default, 1 don't kill the "xyz" movement
    int noshadow; // 0 default, 1 temporarily disable shadow without losing entity's shadow configuration

    e_ModelFreetype freetypes;
    s_scripts *scripts;

    // Meta data.
    s_meta_data*    meta_data;      // User defined data.
    int             meta_tag;       // user defined int.

} s_model;

typedef struct
{
    char *name;
    char *path;
    s_model *model;
    int loadflag;
    int selectable;
} s_modelcache;
extern s_modelcache *model_cache;

// Caskey, Damon V.
// 2013-12-08
//
// Jumping action setup.
typedef struct
{
    e_animations    animation_id;   // Jumping Animation.
    s_axis_principal_float        velocity;       // x,a,z velocity setting.
} s_jump;

/* 
* Caskey, Damon V.
* 2013-12-17
*
* Binding struct. Control linking
* of entity to a target entity.
*/
typedef struct
{
    e_bind_config           config;			    // Animation matching, axis matching, overrides, etc. ~~
    int                     sortid;             // Relative binding sortid. Default = -1
    int                     frame;              // Frame to match (only if requested in matching).
    e_animations            animation;          // Animation to match (only if requested in matching).
    s_axis_principal_int    offset;             // x,y,z offset.
    e_direction_adjust      direction_adjust;   // Direction force.
    struct entity*          target;             // Entity subject will bind itself to.

    // Meta data.
    s_meta_data*            meta_data;          // User defined data.
    int                     meta_tag;           // user defined int.

} s_bind;

typedef struct
{
    /*
    Rush combo struct.
    Damon V. Caskey
    2013-12-17
    */

    s_metric_range_current count;   //Hits counter.
    u32 time;           //Time to perform combo.
} s_rush;

typedef struct
{
    int health_current;
    int health_old;
    int mp_current;
    int mp_old;
} s_energy_state;

// Caskey, Damon V.
// 2018-04-25
//
// Entity item values. Encapsulates properties
// entity uses for item pickups.
typedef struct
{
    int alpha;                      // int itemmap alpha effect of item
    int colorset;                   // int itemmap; // Now items spawned can have their properties changed
    int health;                     // int itemhealth; // Now items spawned can have their properties changed
    int index;                      // int itemindex; // item model index
    int player_count;               // int itemplayer_count;
    char alias[MAX_NAME_LEN];   // char itemalias[MAX_NAME_LEN]; // Now items spawned can have their properties changed
} s_item_properties;

typedef struct entity
{
	// Sub structures.
	s_damage_on_landing		damage_on_landing;					// ~~
	s_bind					binding;							// Binding self to another entity. ~~
	s_axis_principal_float	position;							// x,y,z location. ~~
	s_axis_principal_float	velocity;							// x,y,z movement speed. ~~ 
	s_energy_state			energy_state;						// Health and MP. ~~	
	s_model					modeldata;							// model data copied here ~~
	s_jump					jump;								// Jumping velocity and animationnid. ~~	
	s_rush					rush;								// Rush combo display. ~~

	// Structured pointers.
	s_anim					*animation;							// Pointer to animation collection. ~~
	s_drawmethod			*drawmethod;						// Graphic settings. ~~
	s_item_properties		*item_properties;					// Properties copied to an item entity when it is dropped. ~~	
	s_model					*defaultmodel;						// this is the default model ~~
	s_defense				*defense;							// Resistance or vulnerability to certain attack types. ~~
	s_model					*model;								// current model ~~
	s_damage_recursive		*recursive_damage;					// Recursive damage linked list head. ~~
    s_axis_plane_lateral_float *waypoints;						// Pathfinding waypoint array. ~~
	s_scripts				*scripts;							// Loaded scripts. ~~

	struct entity			*collided_entity;					// Opposing entity when entities occupy same space. ~~
	struct entity			*custom_target;						// Target forced by modder via script ~~
	struct entity			*grabbing;							// Added for "platform level" layering. ~~
	struct entity			*hithead;							// Platform entity when jumping and hitting head on the bottom. ~~
	struct entity			*landed_on_platform;				// Platform entity this entity landed on. ~~
	struct entity			*lasthit;							// Last entity this one hit. ~~
	struct entity			*link;								// Used to link 2 entities together. ~~
	struct entity			*opponent;							// Last entity interacted with. ~~	
	struct entity			*owner;								// Projectile knows its owner. ~~
	struct entity			*parent;							// Its spawner (when a sub entity). ~~
	struct entity			*subentity;							// Summoned sub entity. ~~
	struct entity			*weapent;							// Item entity that was picked up as a weapon. ~~

	// Pointers
	float					*offense_factors;					// Augment or reduce damage output for some attack types. ~~

	unsigned char			*colourmap;							// Colortable in use. ~~

	Varlist					*varlist;							// Entity var collection. ~~

	// Floating decimals.
	float					altbase;							// Altitude affected by movea. ~~
	float					base;								// Default altitude. ~~
	float					destx;								// temporary values for ai functions ~~
	float					destz;								// ~~
	float					knockdowncount;						// Attack knockdown force reduces this. Only fall when at 0. ~~
	float					movex;								// Reposition this many pixels per frame. Used by animation movex command. ~~
	float					movez;								// Reposition this many pixels per frame. Used by animation movez command. ~~
	float					speedmul;							// Final multiplier for movement/velocity. ~~

    // Size defined ints (for time).
	u32						combotime;							// If not expired, continue to next attack in series combo. ~~
	u32						guardtime;							// Next time to auto adjust guardpoints. ~~
	u32						freezetime;							// Used to store at what point the a frozen entity becomes unfrozen. ~~
	u32						invinctime;							// Used to set time for invincibility to expire. ~~
	u32						knockdowntime;						// When knockdown count is expired. ~~
	u32						magictime;							// Next time to auto adjust MP. ~~
	u32						maptime;							// When forcemap expires. ~~
	u32						movetime;							// For special moves. Grace time between player inputs. ~~
	u32						mpchargetime;						// Next recharge tick when in the CHARGE animation. ~~
	u32						next_hit_time;						// When temporary invincibility after getting hit expires. ~~
	u32						nextanim;							// Time for next frame (or to mark animation finished). ~~
	u32						nextattack;							// Time for next chance to attack. ~~
	u32						nextmove;							// Same as tosstime, but for X, Z movement. ~~
	u32						nextthink;							// Time for next main AI update. ~~
	u32						pausetime;							// 2012/4/30 UT: Remove lastanimpos and add this. Otherwise hit pause is always bound to frame and attack box. ~~
	u32						releasetime;						// Delay letting go of grab when holding away command. ~~
	u32						sealtime;							// When seal expires. ~~    
	u32						sleeptime;							// When to start the SLEEP animation. ~~
	u32						stalltime;							// AI waits to perform actions. ~~
	s_staydown				staydown;							// Delay modifiers before rise or riseattack can take place. 2011_04_08, DC: moved to struct. ~~
	u32						timestamp;							// Elasped time assigned when spawned. ~~
    u32						toss_time;							// Used by gravity code (If > elapsed time, gravity has no effect). ~~
    u32						turntime;							// Time when entity can switch direction. ~~
    // -------------------------end of times ------------------------------
	
	// Unsigned integers
	unsigned int			animpos;							// Current animation frame. ~~
	unsigned int			attack_id_incoming[MAX_ATTACK_IDS];	// ~~ (	//Kratus (20-04-21) used to memorize the last 4 hitboxes and avoid the multihit bug. 2021-09-04, DC: Combine members into array. Should probably use pointer.
    unsigned int			attack_id_outgoing;	                // ~~
    unsigned int			animnum;							// Current animation id. ~~
	unsigned int			animnum_previous;					// Previous animation id. ~~
	unsigned int			combostep[MAX_SPECIAL_INPUTS];		// merge into an array to clear up some code. ~~
	unsigned int			dying;								// Corresponds with which remap is to be used for the dying flash ~~
	unsigned int			dying2;								// Corresponds with which remap is to be used for the dying flash for per2 ~~
	unsigned int			escapecount;						// hit count for escapehits. ~~
	unsigned int			idlemode;							// Force a specfic alternate idle. ~~
	unsigned int			pathblocked;						// Time accumulated while obstructed. Used to start pathfining routine. ~~
	unsigned int			per1;								// Used to store at what health value the entity begins to flash ~~
	unsigned int			per2;								// Used to store at what health value the entity flashes more rapidly ~~
	unsigned int			numwaypoints;						// Count of waypoints in use. ~~
	unsigned int			walkmode;							// Force a specfic alternate walk. ~~

	// Signed integers
	int						last_damage_type;					// Used for set death, pain, rise, etc. animation. ~~
	int						lifespancountdown;					// Life span count down. ~~
	int						map;								// Stores the colourmap for restoring purposes. ~~
	int						nograb;								// Some enemies cannot be grabbed (bikes) - now used with cantgrab as well ~~
	int						nograb_default;						// equal to nograb  but this is remain the default value setetd in entity txt file (by White Dragon) ~~
	int						playerindex;						// Player controlling the entity. ~~
	int						seal;								// If 0+, entity can't perform special with >= energy cost. ~~
	int						sortid;								// Drawing order (sprite queue sort id). ~~

	// Enumerated integers.
	e_spawn_type			spawntype;							// Type of spawn (level spawn, script spawn, ...) ~~
	e_projectile_prime		projectile_prime;					// If this entity is a projectile, several priming values go here to set up its behavior. ~~
	e_animating				animating;							// Animation status (none, forward, reverse). ~~
	e_idling_state			idling;								// ~~ Kratus (10-2021) Moved from "bool" to the "Enumerated integers" section
	e_attacking_state		attacking;							// ~~
	e_autokill_state		autokill;							// Kill entity on condition. ~~
	e_direction				direction;							//  ~~
	e_duck_state			ducking;							// In or transitioning to/from duck. ~~
	e_edge_state			edge;								// At an edge (unbalanced).
	e_invincible_state		invincible;							// Attack invulnerability. ~~
	e_direction				normaldamageflipdir;				// Used to reset backpain direction. ~~
	e_blasted_state			projectile;							// Blasted or tossed (bowl over other entities in fall). ~~
	e_rising_state			rising;								// Rise/Rise attacking. ~~
	e_explode_state			toexplode;							// Bomb projectiles prepared or time to detonate. ~~
	e_update_mark			update_mark;						// Which updates are completed. ~~
    e_move_constraint       move_constraint;                    // Subject to basemap, wall, obstacle, hitting head on platforms, etc.

	// Boolean flags.
    int					    arrowon;							// Display arrow icon (parrow<player>) ~~
	int					    blink;								// Toggle flash effect. ~~
	int					    boss;								// I'm the BOSS playa, I'm the reason that you lost! ~~
	int					    blocking;							// In blocking state. ~~
	int					    charging;							// Charging MP. Gain according to chargerate. ~~
	int					    dead;								// He's dead Jim. ~~
	e_weapon_state		    weapon_state;						// Check for ammo count? ~~
	int					    die_on_landing;						// Flag for death by damageonlanding (active if self->health <= 0). ~~
	int					    drop;								// Knocked down. Remains true until rising. ~~
	int					    exists;								// flag to determine if it is a valid entity. ~~
	int					    falling;							// Knocked down and haven't landed. ~~
	int					    frozen;								// Frozen in place. ~~
	int					    getting;							// Picking up item. ~~
	int					    grabwalking;						// Walking while grappling. ~~
	int					    hitwall;							// Blcoked by wall/platform/obstacle. ~~
	int					    inbackpain;							// Playing back pain/fall/rise/riseattack/die animation. ~~
	int					    inpain;								// Hit and block stun. ~~
	int					    jumping;							// ~~
	int					    noaicontrol;						// No AI or automated control. ~~
	int					    running;							// ~~
	int					    tocost;								// Cost life on hit with special. ~~
	int					    turning;							// Turning around. ~~
	int					    walking;							// ~~
	
	// Signed char.
	char					name[MAX_NAME_LEN];					// Display name (alias). ~~	
       
    // Function pointers.
	void					(*takeaction)();					// Take an action (lie, attack, etc.). ~~
	void					(*think)();							// Entity thinks. ~~
    
	int						(*takedamage)(struct entity* attacking_entity, s_attack* attack_object, int fall_flag, s_defense* defense_object);	// Entity applies damage to itself when hit, thrown, and so on. ~~
    int						(*trymove)(float, float);			// Attempts to move. Container for most movement logic. ~~

    // Meta data.
    s_meta_data*            meta_data;              // User defiend data.
    int					    meta_tag;	            // User defined int.
} entity;


typedef struct
{
    char name[MAX_NAME_LEN];
    int colourmap;
    unsigned score;
    unsigned lives;
    unsigned credits;
    entity *ent;
    u64 keys;
    u64 newkeys;
    u64 playkeys;
    u64 releasekeys;
    u32 combokey[MAX_SPECIAL_INPUTS];
    u32 inputtime[MAX_SPECIAL_INPUTS];
    u64 disablekeys;
    u64 prevkeys; // used for play/rec mode
    int combostep;
    int spawnhealth;
    int spawnmp;
    int joining;
    int hasplayed;
    int weapnum;
    int status;

    // Meta data.
    s_meta_data*    meta_data;              // User defiend data.
    int			    meta_tag;	            // User defined int.

} s_player;

typedef struct
{
    int at;
    int wait;
    int nojoin; // dont allow new hero to join
    int spawnplayer_count; // spawn this entity according to the amount of players
    int palette; //change system palette to ...
    int groupmin;
    int groupmax;
    int scrollminz; // new scroll limit
    int scrollmaxz;
    int scrollminx; // new scroll limit
    int scrollmaxx;
    int blockade; //limit how far you can go back
    s_axis_plane_vertical_int light; // light direction, for gfx shadow
    int shadowcolor; // -1 no shadow
    int shadowalpha;
    int shadowopacity;
    char music[MAX_BUFFER_LEN];
    float musicfade;
    u32 musicoffset;
    char *name; // must be a name in the model list, so just reference
    int index; // model index
    int weaponindex; // the spawned entity with an weapon item, this is the index of the item model
    int alpha; // Used for alpha effects
    int boss;
    int flip;
    int colourmap;
    int dying; // Used for the dying flash animation
    int dying2; // Used for the dying flash animation health 25% (optional)
    unsigned per1; // Used to store at what health value the entity begins to flash
    unsigned per2; // Used to store at what health value the entity flashes more rapidly
    int nolife; // So nolife can be overriden for all characters
    s_item_properties item_properties; // Alias, health, index, etc. for items.
    char *item; // must be a name in the model list, so just reference
    s_model *itemmodel;
    s_model *model;
    char alias[MAX_NAME_LEN];
    int health[MAX_PLAYERS];
    int mp; // mp's variable for mpbar by tails
    unsigned score; // So score can be overridden for enemies/obstacles
    int multiple; // So score can be overridden for enemies/obstacles
    s_axis_principal_float position;  //x, y, z location.
    unsigned credit;
    int aggression; // For enemy A.I.
    int spawntype; // Pass 1 when a level spawn.
    int entitytype; // if it's a enemy, player etc..
    entity *parent;
    char *weapon; // spawn with a weapon, since it should be in the model list, so the model must be loaded, just reference its name
    s_model *weaponmodel;
    Script spawnscript;
} s_spawn_entry;

typedef struct
{
    char *branchname; // Use a name so we can find this level in branches
    char *filename;
    e_le_type type; // see e_le_type
    int z_coords[3]; // Used for setting custom "z"
    int gonext; // 0. dont complete this level and display score,
    char *skipselect[MAX_PLAYERS]; // skipselect level based //[MAX_NAME_LEN]
    int	noselect;
    // 1. complete level and display score,
    // 2. complete game, show hall of fame
} s_level_entry;

typedef struct
{
    char *name;
    int maxplayers;
    int numlevels;
    s_level_entry *levelorder;
    int ifcomplete;
    int noshowhof;
    int noshowgameover;
    int lives;
    int credits;
    int custfade;
    int musicoverlap; //** shouldn't it be level based?
    int typemp; //** shouldn't it be model based?
    int continuescore;
    //char *skipselect[MAX_PLAYERS]; //** better if level based // depreciated
    int	noselect;
    int saveflag;
    int nosame;
    int noshowcomplete;
} s_set_entry;

typedef struct
{
    e_bgloldtype    oldtype;
    int             order;	        // for panel order
    gfx_entry       gfx;
    s_axis_plane_vertical_int   size;
    s_axis_plane_lateral_float  ratio;          // Only x and z.
    s_axis_plane_lateral_int    offset;         // Only x and z.
    s_axis_plane_lateral_int    spacing;        // Only x and z.
    s_drawmethod    drawmethod;
    float           bgspeedratio;
    int             enabled;
    int             z;
    int             quake;
    int             neon;
    
    // Meta data.
    s_meta_data*    meta_data;              // User defiend data.
    int				meta_tag;	            // User defined int.
} s_layer;

typedef struct
{
    /*
    Text object (display text on screen) struct
    2013-12-07
    Damon Caskey (Feature originally added by kbanderson)
    */

    int font;           //Font index.
    s_axis_principal_int position;  //x,y,z location on screen.
    u32 time;           //Time to expire.
    char *text;         //Text to display.
    
    // Meta data.
    s_meta_data*        meta_data;              // User defiend data.
    int					meta_tag;	            // User defined int.
} s_textobj;

typedef struct
{
    int pos;
    char *buf;
    size_t size;
} s_filestream;

typedef struct
{
    s_axis_plane_lateral_int position;
    s_axis_plane_lateral_int size;
    float *map;

    // Meta data.
    s_meta_data*    meta_data;              // User defiend data.
    int		        meta_tag;	            // User defined int.
} s_basemap;

 typedef struct
 {
    /*
    Hole/Wall structure.
    2013-12-07
    Damon Caskey
    */
    float depth;
    float height;
    float lowerleft;
    float lowerright;
    float upperleft;
    float upperright;
    float x;
    float z;
    int type;

    // Meta data.
    s_meta_data*    meta_data;              // User defiend data.
    int             meta_tag;	            // User defined int.
} s_terrain;

typedef struct
{
    char *name;
    int numspawns;
    s_spawn_entry *spawnpoints;
    int numlayers;
    s_layer *layers;
    int numlayersref;
    s_layer *layersref;
    ////////////////these below are layer reference
    ////////////////use them to ease layer finding for script users
    s_layer *background; // the bglayer that contains the default background
    int numpanels;
    s_layer *(*panels)[3]; //normal neon screen
    int numfrontpanels;
    s_layer **frontpanels;
    int numbglayers;
    s_layer **bglayers;
    int numfglayers;
    s_layer **fglayers;
    int numgenericlayers;
    s_layer **genericlayers;
    int numwaters;
    s_layer **waters;
    ////////////////layer reference ends here
    ///////////////////////////////////////////////////////////////
    int numtextobjs;
    s_textobj *textobjs;
    int cameraxoffset;
    int camerazoffset;
    int numholes;
    int numwalls;
    int numbasemaps;
    s_terrain *holes;
    s_terrain *walls;
    s_basemap *basemaps;
    int scrolldir;
    int width;
    int rocking;
    float bgspeed; // Used to make autoscrolling backgrounds
    float vbgspeed;
    float scrollspeed; // UT: restore this command  2011/7/8
    int bgdir; // Used to set which direction the backgrounds scroll for autoscrolling backgrounds
    int mirror;
    int bossescount;
    int numbosses;
    char bossmusic[MAX_BUFFER_LEN];
    unsigned bossmusic_offset;
    int numpalettes;
    unsigned char (*palettes)[1024];//dynamic palettes
    int settime; // Set time limit per level
    int notime; // Used to specify if the time is displayed 1 = no, else yes
    int noreset; // If set, clock will not reset when players spawn/die
    int type; // Used to specify which level type (1 = bonus, else regular)
    int nospecial; // Used to specify if you can use your special during bonus levels
    int nohurt; // Used to specify if you can hurt the other player during bonus levels
    int boss_slow; // Flag so the level doesn't slow down after a boss is defeated
    int nohit; // Not able to grab / hit other player on a per level basis
    int force_finishlevel; // flag to force to finish a level
    int force_gameover; // flag to force game over
    s_axis_principal_float *spawn; // Used to determine the spawn position of players
    int setweap; // Levels can now specified which weapon will be used by default
    e_facing_adjust facing; // Force the players to face to ...
//--------------------gravity system-------------------------
    float maxfallspeed;
    float maxtossspeed;
    float gravity;
//---------------------scripts-------------------------------
    Script update_script;
    Script updated_script;
    Script key_script;
    Script level_script;
    Script endlevel_script;
    int pos;
    u32 advancetime;
    u32 quaketime;
    int quake;
    int waiting;

    // Meta data.
    s_meta_data*    meta_data;              // User defiend data.
    int			    meta_tag;	            // User defined int.
} s_level;

typedef struct ArgList
{
    size_t count;
    size_t arglen[MAX_ARG_COUNT];
    char *args[MAX_ARG_COUNT];
} ArgList;

#pragma pack()


#define GET_ARG(z) (arglist.count > z ? arglist.args[z] : "")
#define GET_ARG_LEN(z) (arglist.count > z ? arglist.arglen[z] : 0)
#define GET_ARGP(z) (arglist->count > z ? arglist->args[z] : "")
#define GET_ARGP_LEN(z) (arglist->count > z ? arglist->arglen[z] : 0)
#define GET_INT_ARG(z) getValidInt(GET_ARG(z), filename, command)
#define GET_FLOAT_ARG(z) getValidFloat(GET_ARG(z), filename, command)
#define GET_INT_ARGP(z) getValidInt(GET_ARGP(z), filename, command)
#define GET_FLOAT_ARGP(z) getValidFloat(GET_ARGP(z), filename, command)

#define GET_FRAME_ARG(z) (stricmp(GET_ARG(z), "this")==0?newanim->numframes:GET_INT_ARG(z))

e_air_control air_control_interpret_from_legacy_jumpmove_x(e_air_control air_control_value, e_air_control_legacy_x legacy_value);
e_air_control air_control_interpret_from_legacy_jumpmove_z(e_air_control air_control_value, e_air_control_legacy_z legacy_value);
e_air_control air_control_interpret_from_legacy_walkoffmove_x(e_air_control air_control_value, e_air_control_legacy_x legacy_value);
e_air_control air_control_interpret_from_legacy_walkoffmove_z(e_air_control air_control_value, e_air_control_legacy_z legacy_value);
e_air_control_legacy_x air_control_interpret_to_legacy_jumpmove_x(e_air_control air_control_value);
e_air_control_legacy_z air_control_interpret_to_legacy_jumpmove_z(e_air_control air_control_value);
e_air_control_legacy_x air_control_interpret_to_legacy_walkoffmove_x(e_air_control air_control_value);
e_air_control_legacy_z air_control_interpret_to_legacy_walkoffmove_z(e_air_control air_control_value);



int is_attack_type_special(e_attack_types attack_type);
int is_frozen(entity *e);
void unfrozen(entity *e);
void    adjust_bind(entity *e);
int     check_bind_override(entity *ent, e_bind_config bind_config);

/* Defense. */
int calculate_force_damage(entity* target, entity* attacker, s_attack* attack_object, s_defense* defense_object);
s_defense* defense_allocate_object();
void defense_apply_setup_to_property(char* filename, char* command, s_defense* defense, ArgList* arglist, e_defense_parameters target_parameter);
void defense_free_object(s_defense* target);
s_defense* defense_find_current_object(entity* ent, s_body* body_object, e_attack_types attack_type);
int defense_result_damage(s_attack* attack_object, s_defense* defense_object, int attack_force);
int defense_result_pain(s_attack* attack_object, s_defense* defense_object);
void defense_setup_from_arg(char* filename, char* command, s_defense* defense, ArgList* arglist, e_defense_parameters target_parameter);

/* Recursive damage. */
s_damage_recursive*         recursive_damage_allocate_object();
void                        recursive_damage_check_apply(entity* ent, entity* other, s_attack* attack);
void                        recursive_damage_dump_object(s_damage_recursive* recursive);
void	                    recursive_damage_free_list(s_damage_recursive* head);
void                        recursive_damage_free_node(s_damage_recursive** list, s_damage_recursive* node);
void                        recursive_damage_free_object(s_damage_recursive* target);
e_damage_recursive_logic    recursive_damage_get_mode_flag_from_argument(char* value);
e_damage_recursive_logic    recursive_damage_get_mode_setup_from_arg_list(ArgList* arglist);
e_damage_recursive_logic    recursive_damage_get_mode_setup_from_legacy_argument(e_damage_recursive_cmd_read value);

/* Blocking logic. */
int     check_blocking_decision(entity *ent);
int     check_blocking_eligible(entity *ent, entity *other, s_attack *attack, s_body* body);
int     check_blocking_master(entity *ent, entity *other, s_attack *attack, s_body* body);
int     check_blocking_rules(entity *ent);
int     check_blocking_pain(entity *ent, s_attack *attack);
void	do_active_block(entity *ent);
void	do_passive_block(entity *ent, entity *other, s_attack *attack);
void    set_blocking_action(entity *ent, entity *other, s_attack *attack);
void    set_blocking_animation(entity *ent, s_attack *attack);

/* Counter action (aka. couner attack). */
int check_counter_condition(entity* target, entity* attacker, s_attack* attack_object, s_body* body_object);
int try_counter_action(entity* target, entity* attacker, s_attack* attack_object, s_body* body_object);

// Select player models.
int		find_selectable_model_count				();
int		is_model_cache_index_selectable			(int cache_index);
int		is_model_selectable						(s_model *model);
s_model *nextplayermodel						(s_model *current);
s_model *nextplayermodeln						(s_model *current, int player_index);
s_model *prevplayermodel						(s_model *current);
s_model *prevplayermodeln						(s_model *current, int player_index);

// Select player maps (colors).
int		is_map_hidden							(s_model *model, int map_index);
int		nextcolourmap							(s_model *model, int map_index);
int		nextcolourmapn							(s_model *model, int map_index, int player_index);
int		prevcolourmap							(s_model *model, int map_index);
int		prevcolourmapn							(s_model *model, int map_index, int player_index);	

int     buffer_pakfile							(char *filename, char **pbuffer, size_t *psize);
size_t  ParseArgs								(ArgList *list, char *input, char *output);
int     getsyspropertybyindex					(ScriptVariant *var, int index);
int     changesyspropertybyindex				(int index, ScriptVariant *value);
e_direction_adjust direction_get_adjustment_from_argument(char* filename, char* command, char* value);
e_direction	direction_get_adjustment_result				(e_direction direction_default, e_direction direction_target, e_direction_adjust adjustment);
int     load_script								(Script *script, char *path);
void    init_scripts();
void    load_scripts();
void    execute_animation_script                (entity *ent);
void    execute_takedamage_script               (entity *ent, entity *other, s_attack *attack);
void    execute_on_bind_update_other_to_self    (entity *ent, entity *other, s_bind *bind);
void    execute_on_bind_update_self_to_other    (entity *ent, entity *other, s_bind *bind);
void    execute_ondeath_script                  (entity *ent, entity *other, s_attack *attack);
void    execute_onkill_script                   (entity *ent);
void    execute_onpain_script                   (entity *ent, int iType, int iReset);
void    execute_onfall_script                   (entity *ent, entity *other, s_attack *attack);
void    execute_inhole_script                   (entity *ent, s_terrain *hole, int index);
void    execute_onblocks_script                 (entity *ent);
void    execute_onblockw_script                 (entity *ent, s_terrain *wall, int index, e_plane plane);
void    execute_onblockp_script                 (entity *ent, int plane, entity *platform);
void    execute_onblocko_script                 (entity *ent, int plane, entity *other);
void    execute_onblockz_script                 (entity *ent);
void    execute_onblocka_script                 (entity *ent, entity *other);
void    execute_onmovex_script                  (entity *ent);
void    execute_onmovez_script                  (entity *ent);
void    execute_onmovea_script                  (entity *ent);
void    execute_didblock_script                 (entity *ent, entity *other, s_attack *attack);
void    execute_ondoattack_script               (entity *ent, entity *other, s_attack *attack, e_exchange which, int attack_id);
void    execute_updateentity_script             (entity *ent);
void    execute_think_script                    (entity *ent);
void    execute_didhit_script                   (entity *ent, entity *other, s_attack *attack, int blocked);
void    execute_onspawn_script                  (entity *ent);
void    clearbuttonss(int player);
void    clearsettings(void);
void    savesettings(void);
void    saveasdefault(void);
void    loadsettings(void);
void    loadfromdefault(void);
void    clearSavedGame(void);
void    clearHighScore(void);
int    saveGameFile(void);
int     loadGameFile(void);
int		saveScriptFile(void);
int		loadScriptFile(void);
int    saveHighScoreFile(void);
int    loadHighScoreFile(void);
int translate_SDID(char *value);
int music(char *filename, int loop, long offset);
int readByte(char* buf);
char *findarg(char *command, int which);
float diff(float a, float b);
int inair(entity *e);
int inair_range(entity *e);
float randf(float max);
int _makecolour(int r, int g, int b);
int load_colourmap(s_model *model, char *image1, char *image2);
int load_palette(unsigned char *pal, char *filename);
void standard_palette();
void change_system_palette(int palindex);
void unload_background();
void lifebar_colors();
void load_background(char *filename);
void unload_texture();
void load_texture(char *filename);
void freepanels();
s_sprite *loadpanel2(char *filename);
int loadpanel(char *filename_normal, char *filename_neon, char *filename_screen);
int loadfrontpanel(char *filename);
void resourceCleanUp(void);
void freesprites();
s_sprite *loadsprite2(char *filename, int *width, int *height);
int loadsprite(char *filename, int ofsx, int ofsy, int bmpformat);
void load_special_sprites();
int load_special_sounds();
s_model *find_model(char *name);
s_model *nextplayermodel(s_model *current);
s_model *prevplayermodel(s_model *current);
void free_anim(s_anim *anim);
void free_models();
int free_model();
void cache_attack_hit_sounds(s_collision_attack* head, int load);
void cache_model_sprites();

s_drawmethod			*allocate_drawmethod();
s_projectile			*allocate_projectile();
s_onframe_set			*allocate_frame_set();
s_sub_entity			*allocate_sub_entity();
s_anim                  *alloc_anim();

/*
* Caskey, Damon V.
* 2020-03-04
*
* Used to package up the previously massive and 
* unwieldy parameter list of addframe() and related 
* functions.
*/
typedef struct 
{
    s_anim*                     animation;      // Animation we will add frame to.
    int                         spriteindex;    // Image displayed during frame.
    int                         framecount;     // Number of frames.
    int                         delay;          // Frame duration (centiseonds).
    unsigned                    idle;           // TRUE = Set idle status during frame.
    s_collision_entity*         ebox;           // "Entity" box added by WD. To be removed.
    s_hitbox*                   entity_coords;  // Coordinates for "Entity" box. To be removed.
    s_damage_recursive*         recursive;      // Recursive damage properties for attack.
    s_move*                     move;           // Move <n> horizontal pixels on frame.
    float*                      platform;       // Platform coordinates.
    int                         frameshadow;    // TRUE = Display shadow during frame.
    int*                        shadow_coords;  // Shadow position.
    int                         soundtoplay;    // Sound index played on frame.
    s_drawmethod*               drawmethod;     // Drawmethod to apply on frame.
    s_axis_plane_vertical_int*  offset;         // X & Y offset coordinates.    
    s_collision_attack*         collision;      // Head node of collision list (attack) for frame.
    s_collision_body*           collision_body; // Head node of collision list (body) for frame. 
    s_model*                    model;          // New model in progress.
} s_addframe_data;

int addframe(s_addframe_data* data);

int check_in_screen();

/* Collision and attcking control. */

/* -- Attack properties. */
s_attack*   attack_allocate_object();
s_attack*   attack_clone_object(s_attack* source);
void        attack_dump_object(s_attack* attack);
void        attack_free_object(s_attack* target);

s_collision_attack* collision_attack_allocate_object();
s_collision_attack* collision_attack_append_node(struct s_collision_attack* head);
int                 collision_attack_check_has_coords(s_collision_attack* target);
s_collision_attack* collision_attack_clone_list(s_collision_attack* source_head);
void                collision_attack_dump_list(s_collision_attack* head);
s_collision_attack* collision_attack_find_no_block_on_frame(s_anim* animation, int frame, int block);
s_collision_attack* collision_attack_find_node_index(s_collision_attack* head, int index);
void                collision_attack_free_list(s_collision_attack* head);
void                collision_attack_free_node(s_collision_attack* target);
void                collision_attack_initialize_frame_property(s_addframe_data* data, ptrdiff_t frame);
void                collision_attack_prepare_coordinates_for_frame(s_collision_attack* collision_head, s_model* model, s_addframe_data* add_frame_data);
void                collision_attack_remove_undefined_coordinates(s_collision_attack** head);
s_hitbox*           collision_attack_upsert_coordinates_property(s_collision_attack** head, int index);
s_collision_attack* collision_attack_upsert_index(s_collision_attack* head, int index);
s_attack*           collision_attack_upsert_property(s_collision_attack** head, int index);
s_damage_recursive* collision_attack_upsert_recursive_property(s_collision_attack** head, int index);

/* -- Body properties */
s_body* body_allocate_object();
s_body* body_clone_object(s_body* source);
void    body_dump_object(s_body* body);
void    body_free_object(s_body* target);

s_collision_body*   collision_body_allocate_object();
s_collision_body*   collision_body_append_node(struct s_collision_body* head);
int                 collision_body_check_has_coords(s_collision_body* target);
s_collision_body*   collision_body_clone_list(s_collision_body* source_head);
void                collision_body_dump_list(s_collision_body* head);
s_collision_body*   collision_body_find_node_index(s_collision_body* head, int index);
void                collision_body_free_list(s_collision_body* head);
void                collision_body_free_node(s_collision_body* target);
void                collision_body_initialize_frame_property(s_addframe_data* data, ptrdiff_t frame);
void                collision_body_prepare_coordinates_for_frame(s_collision_body* collision_head, s_model* model, s_addframe_data* add_frame_data);
void                collision_body_remove_undefined_coordinates(s_collision_body** head);
s_hitbox*           collision_body_upsert_coordinates_property(s_collision_body** head, int index);
s_collision_body*   collision_body_upsert_index(s_collision_body* head, int index);
s_body*             collision_body_upsert_property(s_collision_body** head, int index);


// -- Recursive damage
s_damage_recursive*     recursive_damage_allocate_object();
void                    recursive_damage_dump_object(s_damage_recursive* recursive);

/* -- Collision container and list. */
s_hitbox*               collision_allocate_coords(s_hitbox* coords);

void populate_lasthit(s_collision_check_data* collision_data, s_collision_attack* collision_attack, s_collision_body* detect_collision_body, s_collision_attack* detect_collision_attack);

/* --Legacy */
s_collision_entity*     collision_alloc_entity_instance(s_collision_entity *properties);
s_collision_entity**    collision_alloc_entity_list();

// Meta data control.
void meta_data_free_list(s_meta_data* head);

int play_hit_impact_sound(s_attack* attack_object, entity* attacking_entity, int attack_blocked);

void cache_model(char *name, char *path, int flag);
void free_modelcache();
int get_cached_model_index(char *name);
char *get_cached_model_path(char *name);
s_model *load_cached_model(char *name, char *owner, char unload);
int is_set(s_model *model, int m);
int load_script_setting();
int load_models();
void unload_levelorder();
void load_levelorder();
void unload_level();
void load_level(char *filename);
void drawlifebar(int x, int y, int h, int maxh);
void drawmpbar(int x, int y, int m, int maxm);
void update_loading(s_loadingbar *s,  int value, int max);
void spawnplayer(int);
unsigned getFPS(void);
unsigned char *model_get_colourmap(s_model *model, unsigned which);
void ent_set_colourmap(entity *ent, unsigned int which);
void predrawstatus();
void drawstatus();
void addscore(int playerindex, int add);
void free_ent(entity *e);
void free_ents();
int alloc_ents();
int is_walking(int iAni);
entity *smartspawn(s_spawn_entry *p);
void initialize_item_carry(entity *ent, s_spawn_entry *spawn_entry);
int adjust_grabposition(entity *ent, entity *other, float dist, int grabin);
int player_trymove(float xdir, float zdir);
void toss(entity *ent, float lift);
void player_think(void);
void subtract_shot(void);
void set_model_ex(entity *ent, char *modelname, int index, s_model *newmodel, int flag);

e_weapon_loss_condition weapon_loss_condition_interpret_from_legacy_weaploss(e_weapon_loss_condition weapon_loss_condition_value, e_weapon_loss_condition_legacy legacy_value);
e_weapon_loss_condition_legacy weapon_loss_condition_interpret_to_legacy(e_weapon_loss_condition weapon_loss_condition_value);
void dropweapon(int flag);

void biker_drive(void);
void trap_think(void);
void steamer_think(void);
void text_think(void);
void anything_walk(void);
void adjust_walk_animation(entity *other);
int player_takedamage(entity *other, s_attack *attack, int fall_flag, s_defense* defense_object);
int biker_takedamage(entity *other, s_attack *attack, int fall_flag, s_defense* defense_object);
int obstacle_takedamage(entity *other, s_attack *attack, int fall_flag, s_defense* defense_object);
void suicide(void);
void player_blink(void);
void common_prejump();
void common_preduck();
void common_idle();
void recursive_damage_update(entity *target);
void tryjump(float, float, float, e_animations);
void dojump(float, float, float, e_animations);
void tryduck(entity*);
void tryduckrise(entity*);
void tryvictorypose(entity*);
void doduck(entity*);
void biker_drive(void);
void ent_default_init(entity *e);
void ent_spawn_ent(entity *ent);
void ent_summon_ent(entity *ent);
void ent_set_anim(entity *ent, int aninum, int resetable);
void ent_set_colourmap(entity *ent, unsigned int which);
void ent_set_model(entity *ent, char *modelname, int syncAnim);
entity *spawn_attack_flash(entity *ent, s_attack *attack, int attack_flash, int model_flash);
entity *spawn(float x, float z, float a, e_direction direction, char *name, int index, s_model *model);
void ent_unlink(entity *e);
void ents_link(entity *e1, entity *e2);
void kill_entity(entity *victim);
void kill_all();


int projectile_wall_deflect(entity *ent);

void sort_invert_by_parent(entity *ent, entity* parent);

int check_canbegrabbed(entity* acting_entity, entity* target_entity);
int check_cangrab(entity* acting_entity, entity* target_entity);
int checkgrab(entity *other, s_attack *attack);
void checkdamageeffects(s_attack *attack);
void checkdamagedrop(entity* target_entity, s_attack* attack_object, s_defense* defense_object);
void checkdamageflip(entity* target_entity, entity* other, s_attack* attack_object, s_defense* defense_object);
void checkmpadd();
void checkhitscore(entity *other, s_attack *attack);
void checkdamage(entity* target_entity, entity* attacking_entity, s_attack* attack_object, s_defense* defense_object);
void checkdamageonlanding();
int checkhit(entity *attacker, entity *target);
int checkhole(float x, float z);
int checkhole_index(float x, float z);
int checkhole_in(float x, float z, float a);
int checkholeindex_in(float x, float z, float a);
int checkhole_between(float x, float z, float a1, float a2);
int testplatform(entity *, float, float, entity *);
int testhole(int, float, float);
int testwall(int, float, float);
int checkwalls(float x, float z, float a1, float a2);
int checkholes(float, float);
int checkwall_below(float x, float z, float a);
int checkwall_index(float x, float z);
float check_basemap(int x, int z);
int check_basemap_index(int x, int z);
float checkbase(float x, float z, float y, entity *ent);
entity *check_block_obstacle(entity *entity);
int check_block_wall(entity *entity);
int colorset_timed_expire(entity *ent);
int check_lost();
int check_range_target_all(entity *ent, entity *target, e_animations animation_id);
int check_range_target_base(entity *ent, entity *target, s_anim *animation);
int check_range_target_x(entity *ent, entity *target, s_anim *animation);
int check_range_target_y(entity *ent, entity *target, s_anim *animation);
int check_range_target_z(entity *ent, entity *target, s_anim *animation);
void check_entity_collision_for(entity* ent);
int check_entity_collision(entity *ent, entity *target);


void generate_basemap(int map_index, float rx, float rz, float x_size, float z_size, float min_a, float max_a, int x_cont);
int testmove(entity *, float, float, float, float);
entity *check_platform_below(float x, float z, float a, entity *exclude);
entity *check_platform_above(float x, float z, float a, entity *exclude);
entity *check_platform_between(float x, float z, float amin, float amax, entity *exclude);
entity *check_platform(float x, float z, entity *exclude);
float get_platform_base(entity *);
int is_on_platform(entity *);
entity *get_platform_on(entity *);
void do_item_script(entity *ent, entity *item);

int attack_id_check_match(entity* acting_entity, s_attack* attack_object, int attack_id, int multihit);
void attack_id_update(entity* acting_entity, int attack_id);
void do_attack(entity *e);

int do_energy_charge(entity *ent);
void adjust_base(entity *e, entity **pla);
void check_gravity(entity *e);
bool check_jumpframe(entity *ent, unsigned int frame);
bool check_frame_set_drop(entity *ent);
bool check_landframe(entity* ent);
int check_edge(entity *ent);
void update_ents();
entity *find_ent_here(entity *exclude, float x, float z, int types, int (*test)(entity *, entity *));
void display_ents();
void toss(entity *ent, float lift);
entity *findent(int types);
int count_ents(int types);
int set_idle(entity *ent);
int set_death(entity *iDie, int type, int reset);
int set_fall(entity *ent, entity *other, s_attack *attack, int reset);
int set_rise(entity *iRise, int type, int reset);
int set_riseattack(entity *iRiseattack, int type, int reset);
int set_blockpain(entity *iBlkpain, int type, int reset);
int set_pain(entity *iPain, int type, int reset);
int reset_backpain(entity *ent);
int check_backpain(entity* attacker, entity* defender);
void set_weapon(entity *ent, int wpnum, int anim_flag);
entity *melee_find_target();
entity *long_find_target();
entity *normal_find_target(int anim, int iDetect);
entity *normal_find_item();
int long_attack();
int melee_attack();
void dothrow();
void doprethrow();
void dograbattack(int which);
e_animations do_grab_attack_finish(entity *ent, int which);
int check_special();
void normal_prepare();
void common_jump();
void common_spawn(void);
void common_drop(void);
void common_walkoff(void);
void common_jumpattack();
void common_turn();
void common_fall();
void common_lie();
void common_rise();
void common_pain();
void common_get();
void common_land();
void common_grab(void);
void common_grabattack();
void common_grabbed();
void common_block(void);
int arrow_takedamage(entity *other, s_attack *attack, int fall_flag, s_defense* defense_object);
int common_takedamage(entity *other, s_attack *attack, int fall_flag, s_defense* defense_object);
int normal_attack();
void common_throw(void);
void common_throw_wait(void);
void common_prethrow(void);
void npc_warp();
int checkpathblocked();
int common_trymove(float xdir, float zdir);
void normal_runoff();
void common_animation_normal();
void common_attack_proc();
void normal_attack_finish();
entity *common_find_target();
int common_attack(void);
int common_try_jump(void);
int common_try_pick(entity *other);
int common_try_chase(entity *target, int dox, int doz);
int common_try_follow(entity *target, int dox, int doz);
int common_try_avoid(entity *target, int dox, int doz);
int common_try_wandercompletely(int dox, int doz);
int common_try_wander(entity *target, int dox, int doz);
void common_pickupitem(entity *other);
int common_backwalk_anim(entity *ent);
void draw_properties_entity(entity *entity, int offset_z, int color, s_drawmethod *drawmethod);
void draw_box_on_entity(entity *entity, int pos_x, int pos_y, int pos_z, int size_w, int size_h, int offset_z, int color, s_drawmethod *drawmethod);
void draw_visual_debug();
e_entity_type find_entity_type_from_string(char* value);
int bomb_move(entity *ent);
int arrow_move(void);
int common_move(void);
void common_think(void);
void suicide(void);
void prethrow(void);
void player_die();
int player_trymove(float xdir, float zdir);
int check_energy(e_cost_check which, int ani);
int player_preinput();
int player_check_special();
void runanimal(void);
void player_blink(void);
int check_combo();
int check_costmove(int s, int fs, int jumphack);
void didfind_item(entity *other);
void player_think(void);
void subtract_shot();
void dropweapon(int flag);
void drop_all_enemies();
void kill_all_enemies();
void smart_bomb(entity *e, s_attack *attack);
void anything_walk(void);
entity* knife_spawn(entity *parent, s_projectile* projectile);
entity *bomb_spawn(entity *parent, s_projectile *projectile);
void bomb_explode(void);
int star_spawn(entity *parent, s_projectile *projectile);
void steam_think(void);
void trap_think(void);
void steam_spawn(float x, float z, float a);
void steamer_think(void);
void text_think(void);
entity *homing_find_target(int type);
void biker_drive(void);
void bike_crash(void);
void obstacle_fall(void);
void obstacle_fly(void);
entity *smartspawn(s_spawn_entry *props);
int is_incam(float x, float z, float a, float threshold);
void spawnplayer(int index);
void time_over();
void update_scroller();
void draw_scrolled_bg();
void update(int ingame, int usevwait);
void fade_out(int type, int speed);
void apply_controls();
void plan();
int is_in_backrun(entity*);
int ai_check_ducking();
int ai_check_warp();
int ai_check_lie();
int ai_check_grabbed();
int ai_check_grab();
int ai_check_escape();
int ai_check_busy();
void display_credits(void);
void borShutdown(int status, char *msg, ...);
#ifdef DC
void guistartup(void);
#endif
void startup(void);
int playgif(char *filename, int x, int y, int noskip);
void playscene(char *filename);
void gameover();
void hallfame(int addtoscore);
void showcomplete(int num);
int playlevel(char *filename);
int selectplayer(int *players, char *filename, int useSavedGame);
void playgame(int *players,  unsigned which_set, int useSavedGame);
int load_saved_game();
void term_videomodes();
void init_videomodes(int log);
void safe_set(int *arr, int index, int newkey, int oldkey);

void keyboard_setup_menu(int player);
void keyboard_setup(int player);
void inputrefresh();

int menu_difficulty();
void menu_options();
void menu_options_config();
void menu_options_debug();
void menu_options_input();
void menu_options_sound();
void menu_options_soundcard();
void menu_options_system();
void menu_options_video();

void openborMain(int argc, char **argv);
int getValidInt(char *text, char *file, char *cmd);
float getValidFloat(char *text, char *file, char *cmd);
int dograb(entity *attacker, entity *target, e_dograb_adjustcheck adjustcheck);
int stopRecordInputs(void);
int recordInputs(void);
int playRecordedInputs(void);
int freeRecordedInputs(void);
a_playrecstatus* init_input_recorder(void);
void free_input_recorder(void);
void goto_mainmenu(int);

extern s_savelevel   *savelevel;
extern s_savescore    savescore;

#endif
