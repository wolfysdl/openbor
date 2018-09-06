/*
 * OpenBOR - http://www.chronocrash.com
 * -----------------------------------------------------------------------
 * All rights reserved. See LICENSE in OpenBOR root for license details.
 *
 * Copyright (c) 2004 - 2017 OpenBOR Team
 */

// Script constants
// 2017-04-27
// Caskey, Damon V.
//
// Mapping constants for use in script.

#include "scriptcommon.h"

// ===== openborconstant =====
#define IICMPCONST(x) \
if(stricmp(#x, constname)==0) {\
	v.lVal = (LONG)x;\
}


#define ICMPCONST(x) \
else if(stricmp(#x, constname)==0) {\
	v.lVal = (LONG)x;\
}

#define ICMPSCONSTA(x, y) \
else if(strnicmp(constname, #x, sizeof(#x)-1)==0 && constname[sizeof(#x)-1] >= '1' && constname[sizeof(#x)-1]<='9') \
{ \
	v.lVal = (LONG)(y[atoi(constname+(sizeof(#x)-1))-1]);\
}

#define ICMPSCONSTB(x, y) \
else if(strnicmp(constname, #x, sizeof(#x)-1)==0 && constname[sizeof(#x)-1] >= '1' && constname[sizeof(#x)-1]<='9') \
{ \
	v.lVal = (LONG)(y[atoi(constname+(sizeof(#x)-1))+STA_ATKS-1]);\
}

#define ICMPSCONSTC(x) \
else if(strnicmp(constname, #x, sizeof(#x)-1)==0 && constname[sizeof(#x)-1] >= '1' && constname[sizeof(#x)-1]<='9') \
{ \
	v.lVal = (LONG)(atoi(constname+(sizeof(#x)-1))+STA_ATKS-1);\
}

int mapstrings_transconst(ScriptVariant **varlist, int paramCount)
{
    char *constname = NULL;
    int found = TRUE;
    ScriptVariant v;

    if(paramCount < 1)
    {
        return 1;
    }

    if(varlist[0]->vt == VT_STR)
    {
        ScriptVariant_Init(&v);
        ScriptVariant_ChangeType(&v, VT_INTEGER);
        constname = (char *)StrCache_Get(varlist[0]->strVal);

        //printf("\nm Mapping Openborconstant: %s", constname);

        IICMPCONST(COMPATIBLEVERSION)

        // Binding animation flag
        ICMPCONST(BINDING_MATCHING_NONE)
        ICMPCONST(BINDING_MATCHING_ANIMATION_TARGET)
        ICMPCONST(BINDING_MATCHING_FRAME_TARGET)
        ICMPCONST(BINDING_MATCHING_ANIMATION_REMOVE)
        ICMPCONST(BINDING_MATCHING_FRAME_REMOVE)
        ICMPCONST(BINDING_MATCHING_ANIMATION_DEFINED)
        ICMPCONST(BINDING_MATCHING_FRAME_DEFINED)

        ICMPCONST(DIRECTION_LEFT)
        ICMPCONST(DIRECTION_RIGHT)
        ICMPCONST(DIRECTION_ADJUST_LEFT)
        ICMPCONST(DIRECTION_ADJUST_NONE)
        ICMPCONST(DIRECTION_ADJUST_OPPOSITE)
        ICMPCONST(DIRECTION_ADJUST_RIGHT)
        ICMPCONST(DIRECTION_ADJUST_SAME)
        ICMPCONST(MIN_INT)
        ICMPCONST(MAX_INT)
        ICMPCONST(PIXEL_8)
        ICMPCONST(PIXEL_x8)
        ICMPCONST(PIXEL_16)
        ICMPCONST(PIXEL_32)
        ICMPCONST(CV_SAVED_GAME)
        ICMPCONST(CV_HIGH_SCORE)
        ICMPCONST(THINK_SPEED)
        ICMPCONST(COUNTER_SPEED)
        ICMPCONST(MAX_ENTS)
        ICMPCONST(MAX_NAME_LEN)
        ICMPCONST(MAX_SPECIALS)
        ICMPCONST(MAX_ATCHAIN)
        ICMPCONST(MAX_ATTACKS)
        ICMPCONST(MAX_FOLLOWS)
        ICMPCONST(MAX_PLAYERS)
        ICMPCONST(MAX_ARG_LEN)
        ICMPCONST(FLAG_ESC)
        ICMPCONST(FLAG_START)
        ICMPCONST(FLAG_MOVELEFT)
        ICMPCONST(FLAG_MOVERIGHT)
        ICMPCONST(FLAG_MOVEUP)
        ICMPCONST(FLAG_MOVEDOWN)
        ICMPCONST(FLAG_ATTACK)
        ICMPCONST(FLAG_ATTACK2)
        ICMPCONST(FLAG_ATTACK3)
        ICMPCONST(FLAG_ATTACK4)
        ICMPCONST(FLAG_JUMP)
        ICMPCONST(FLAG_SPECIAL)
        ICMPCONST(FLAG_SCREENSHOT)
        ICMPCONST(FLAG_ANYBUTTON)
        ICMPCONST(FLAG_FORWARD)
        ICMPCONST(FLAG_BACKWARD)

        // Boss no slow flags.
        ICMPCONST(BOSS_SLOW_OFF)
        ICMPCONST(BOSS_SLOW_ON)

        // Damage control flags.
        ICMPCONST(DAMAGE_FROM_ENEMY_OFF)
        ICMPCONST(DAMAGE_FROM_ENEMY_ON)
        ICMPCONST(DAMAGE_FROM_PLAYER_OFF)
        ICMPCONST(DAMAGE_FROM_PLAYER_ON)

        // Exchange Flags. Indicate taking or delivering and attack.
        ICMPCONST(EXCHANGE_CONFERRER)
        ICMPCONST(EXCHANGE_RECIPIANT)

        // Level properties
        ICMPCONST(LEVEL_PROP_AUTO_SCROLL_DIRECTION)
        ICMPCONST(LEVEL_PROP_AUTO_SCROLL_X)
        ICMPCONST(LEVEL_PROP_AUTO_SCROLL_Y)
        ICMPCONST(LEVEL_PROP_BASEMAP_COLLECTION)
        ICMPCONST(LEVEL_PROP_BASEMAP_COUNT)
        ICMPCONST(LEVEL_PROP_BOSS_COUNT)
        ICMPCONST(LEVEL_PROP_BOSS_MUSIC_NAME)
        ICMPCONST(LEVEL_PROP_BOSS_MUSIC_OFFSET)
        ICMPCONST(LEVEL_PROP_BOSS_SLOW)
        ICMPCONST(LEVEL_PROP_CAMERA_OFFSET_X)
        ICMPCONST(LEVEL_PROP_CAMERA_OFFSET_Z)
        ICMPCONST(LEVEL_PROP_COMPLETE_FORCE)
        ICMPCONST(LEVEL_PROP_DAMAGE_FROM_ENEMY)
        ICMPCONST(LEVEL_PROP_DAMAGE_FROM_PLAYER)
        ICMPCONST(LEVEL_PROP_FACING)
        ICMPCONST(LEVEL_PROP_GRAVITY)
        ICMPCONST(LEVEL_PROP_HOLE_COLLECTION)
        ICMPCONST(LEVEL_PROP_HOLE_COUNT)
        ICMPCONST(LEVEL_PROP_LAYER_BACKGROUND_DEFAULT_HANDLE)
        ICMPCONST(LEVEL_PROP_LAYER_BACKGROUND_COLLECTION)
        ICMPCONST(LEVEL_PROP_LAYER_BACKGROUND_COUNT)
        ICMPCONST(LEVEL_PROP_LAYER_COLLECTION)
        ICMPCONST(LEVEL_PROP_LAYER_COUNT)
        ICMPCONST(LEVEL_PROP_LAYER_FOREGROUND_COLLECTION)
        ICMPCONST(LEVEL_PROP_LAYER_FOREGROUND_COUNT)
        ICMPCONST(LEVEL_PROP_LAYER_FRONTPANEL_COLLECTION)
        ICMPCONST(LEVEL_PROP_LAYER_FRONTPANEL_COUNT)
        ICMPCONST(LEVEL_PROP_LAYER_GENERIC_COLLECTION)
        ICMPCONST(LEVEL_PROP_LAYER_GENERIC_COUNT)
        ICMPCONST(LEVEL_PROP_LAYER_PANEL_COLLECTION)
        ICMPCONST(LEVEL_PROP_LAYER_PANEL_COUNT)
        ICMPCONST(LEVEL_PROP_LAYER_REF_COLLECTION)
        ICMPCONST(LEVEL_PROP_LAYER_REF_COUNT)
        ICMPCONST(LEVEL_PROP_LAYER_WATER_COLLECTION)
        ICMPCONST(LEVEL_PROP_LAYER_WATER_COUNT)
        ICMPCONST(LEVEL_PROP_MAX_FALL_VELOCITY)
        ICMPCONST(LEVEL_PROP_MAX_TOSS_VELOCITY)
        ICMPCONST(LEVEL_PROP_MIRROR)
        ICMPCONST(LEVEL_PROP_NAME)
        ICMPCONST(LEVEL_PROP_PALETTE_BLENDING_COLLECTION)
        ICMPCONST(LEVEL_PROP_PALETTE_COLLECTION)
        ICMPCONST(LEVEL_PROP_PALETTE_COUNT)
        ICMPCONST(LEVEL_PROP_POSITION_X)
        ICMPCONST(LEVEL_PROP_QUAKE)
        ICMPCONST(LEVEL_PROP_QUAKE_TIME)
        ICMPCONST(LEVEL_PROP_ROCKING)
        ICMPCONST(LEVEL_PROP_SCRIPT_LEVEL_END)
        ICMPCONST(LEVEL_PROP_SCRIPT_LEVEL_START)
        ICMPCONST(LEVEL_PROP_SCRIPT_KEY)
        ICMPCONST(LEVEL_PROP_SCRIPT_UPDATE)
        ICMPCONST(LEVEL_PROP_SCRIPT_UPDATED)
        ICMPCONST(LEVEL_PROP_SCROLL_DIRECTION)
        ICMPCONST(LEVEL_PROP_SCROLL_VELOCITY)
        ICMPCONST(LEVEL_PROP_SIZE_X)
        ICMPCONST(LEVEL_PROP_SPAWN_COLLECTION)
        ICMPCONST(LEVEL_PROP_SPAWN_COUNT)
        ICMPCONST(LEVEL_PROP_SPAWN_PLAYER_COLLECTION)
        ICMPCONST(LEVEL_PROP_SPECIAL_DISABLE)
        ICMPCONST(LEVEL_PROP_TEXT_OBJECT_COLLECTION)
        ICMPCONST(LEVEL_PROP_TEXT_OBJECT_COUNT)
        ICMPCONST(LEVEL_PROP_TIME_ADVANCE)
        ICMPCONST(LEVEL_PROP_TIME_DISPLAY)
        ICMPCONST(LEVEL_PROP_TIME_RESET)
        ICMPCONST(LEVEL_PROP_TIME_SET)
        ICMPCONST(LEVEL_PROP_TYPE)
        ICMPCONST(LEVEL_PROP_WAITING)
        ICMPCONST(LEVEL_PROP_WALL_COLLECTION)
        ICMPCONST(LEVEL_PROP_WALL_COUNT)
        ICMPCONST(LEVEL_PROP_WEAPON)

        // Plane access flags.
        ICMPCONST(PLANE_X)
        ICMPCONST(PLANE_Y)
        ICMPCONST(PLANE_Z)

        // Projectile spawn settings.
        ICMPCONST(PROJECTILE_PRIME_BASE_FLOOR)
        ICMPCONST(PROJECTILE_PRIME_BASE_Y)
        ICMPCONST(PROJECTILE_PRIME_LAUNCH_MOVING)
        ICMPCONST(PROJECTILE_PRIME_LAUNCH_STATIONARY)
        ICMPCONST(PROJECTILE_PRIME_REQUEST_UNDEFINED)
        ICMPCONST(PROJECTILE_PRIME_REQUEST_FLASH)
        ICMPCONST(PROJECTILE_PRIME_REQUEST_KNIFE)
        ICMPCONST(PROJECTILE_PRIME_REQUEST_PROJECTILE)
        ICMPCONST(PROJECTILE_PRIME_REQUEST_PSHOTNO)
        ICMPCONST(PROJECTILE_PRIME_REQUEST_SHOT)
        ICMPCONST(PROJECTILE_PRIME_SOURCE_ANIMATION)
        ICMPCONST(PROJECTILE_PRIME_SOURCE_GLOBAL)
        ICMPCONST(PROJECTILE_PRIME_SOURCE_INDEX)
        ICMPCONST(PROJECTILE_PRIME_SOURCE_HEADER)
        ICMPCONST(PROJECTILE_PRIME_SOURCE_NAME)
        ICMPCONST(PROJECTILE_PRIME_SOURCE_WEAPON)

        // Scrolling type flags.
        ICMPCONST(SCROLL_RIGHT)
        ICMPCONST(SCROLL_DOWN)
        ICMPCONST(SCROLL_LEFT)
        ICMPCONST(SCROLL_UP)
        ICMPCONST(SCROLL_BACK)
        ICMPCONST(SCROLL_BOTH)
        ICMPCONST(SCROLL_RIGHTLEFT)
        ICMPCONST(SCROLL_LEFTRIGHT)
        ICMPCONST(SCROLL_INWARD)
        ICMPCONST(SCROLL_OUTWARD)
        ICMPCONST(SCROLL_OUTIN)
        ICMPCONST(SCROLL_INOUT)
        ICMPCONST(SCROLL_UPWARD)
        ICMPCONST(SCROLL_DOWNWARD)

        // Key control flags.
        ICMPCONST(SDID_MOVEUP)
        ICMPCONST(SDID_MOVEDOWN)
        ICMPCONST(SDID_MOVELEFT)
        ICMPCONST(SDID_MOVERIGHT)
        ICMPCONST(SDID_SPECIAL)
        ICMPCONST(SDID_ATTACK)
        ICMPCONST(SDID_ATTACK2)
        ICMPCONST(SDID_ATTACK3)
        ICMPCONST(SDID_ATTACK4)
        ICMPCONST(SDID_JUMP)
        ICMPCONST(SDID_START)
        ICMPCONST(SDID_SCREENSHOT)

        // Spawn type.
        ICMPCONST(SPAWN_TYPE_UNDEFINED)
        ICMPCONST(SPAWN_TYPE_BIKER)
        ICMPCONST(SPAWN_TYPE_CMD_SPAWN)
        ICMPCONST(SPAWN_TYPE_CMD_SUMMON)
        ICMPCONST(SPAWN_TYPE_DUST_FALL)
        ICMPCONST(SPAWN_TYPE_DUST_JUMP)
        ICMPCONST(SPAWN_TYPE_DUST_LAND)
        ICMPCONST(SPAWN_TYPE_FLASH)
        ICMPCONST(SPAWN_TYPE_ITEM)
        ICMPCONST(SPAWN_TYPE_LEVEL)
        ICMPCONST(SPAWN_TYPE_PLAYER_MAIN)
        ICMPCONST(SPAWN_TYPE_PLAYER_SELECT)
        ICMPCONST(SPAWN_TYPE_PROJECTILE_BOMB)
        ICMPCONST(SPAWN_TYPE_PROJECTILE_NORMAL)
        ICMPCONST(SPAWN_TYPE_PROJECTILE_STAR)
        ICMPCONST(SPAWN_TYPE_STEAM)
        ICMPCONST(SPAWN_TYPE_WEAPON)

        // Model/Entity types.
        ICMPCONST(TYPE_NONE)
        ICMPCONST(TYPE_PLAYER)
        ICMPCONST(TYPE_ENEMY)
        ICMPCONST(TYPE_ITEM)
        ICMPCONST(TYPE_OBSTACLE)
        ICMPCONST(TYPE_STEAMER)
        ICMPCONST(TYPE_SHOT)
        ICMPCONST(TYPE_TRAP)
        ICMPCONST(TYPE_TEXTBOX)
        ICMPCONST(TYPE_ENDLEVEL)
        ICMPCONST(TYPE_NPC)
        ICMPCONST(TYPE_PANEL)
        ICMPCONST(TYPE_MAX)
        ICMPCONST(TYPE_RESERVED)
        ICMPCONST(SUBTYPE_NONE)
        ICMPCONST(SUBTYPE_BIKER)
        ICMPCONST(SUBTYPE_NOTGRAB)
        ICMPCONST(SUBTYPE_ARROW)
        ICMPCONST(SUBTYPE_TOUCH)
        ICMPCONST(SUBTYPE_WEAPON)
        ICMPCONST(SUBTYPE_NOSKIP)
        ICMPCONST(SUBTYPE_FLYDIE)
        ICMPCONST(SUBTYPE_BOTH)
        ICMPCONST(SUBTYPE_PROJECTILE)
        ICMPCONST(SUBTYPE_FOLLOW)
        ICMPCONST(SUBTYPE_CHASE)

        // Ai modes.
        ICMPCONST(AIMOVE1_NORMAL)
        ICMPCONST(AIMOVE1_CHASE)
        ICMPCONST(AIMOVE1_CHASEZ)
        ICMPCONST(AIMOVE1_CHASEX)
        ICMPCONST(AIMOVE1_AVOID)
        ICMPCONST(AIMOVE1_AVOIDZ)
        ICMPCONST(AIMOVE1_AVOIDX)
        ICMPCONST(AIMOVE1_WANDER)
        ICMPCONST(AIMOVE1_NOMOVE)
        ICMPCONST(AIMOVE1_BIKER)
        ICMPCONST(AIMOVE1_STAR)
        ICMPCONST(AIMOVE1_ARROW)
        ICMPCONST(AIMOVE1_BOMB)
        ICMPCONST(AIMOVE2_NORMAL)
        ICMPCONST(AIMOVE2_IGNOREHOLES)
        ICMPCONST(AIMOVE2_NOTARGETIDLE)
        ICMPCONST(AIATTACK1_NORMAL)
        ICMPCONST(AIATTACK1_LONG)
        ICMPCONST(AIATTACK1_MELEE)
        ICMPCONST(AIATTACK1_NOATTACK)
        ICMPCONST(AIATTACK1_ALWAYS)
        ICMPCONST(AIATTACK2_NORMAL)
        ICMPCONST(AIATTACK2_DODGE)
        ICMPCONST(AIATTACK2_DODGEMOVE)

        ICMPCONST(FRONTPANEL_Z)
        ICMPCONST(HOLE_Z)
        ICMPCONST(NEONPANEL_Z)
        ICMPCONST(SHADOW_Z)
        ICMPCONST(SCREENPANEL_Z)
        ICMPCONST(PANEL_Z)
        ICMPCONST(MIRROR_Z)
        ICMPCONST(PIT_DEPTH)
        ICMPCONST(P2_STATS_DIST)
        ICMPCONST(CONTACT_DIST_H)
        ICMPCONST(CONTACT_DIST_V)
        ICMPCONST(GRAB_DIST)
        ICMPCONST(GRAB_STALL)
        ICMPCONST(ATK_NORMAL)
        ICMPCONST(ATK_NORMAL2)
        ICMPCONST(ATK_NORMAL3)
        ICMPCONST(ATK_NORMAL4)
        ICMPCONST(ATK_BLAST)
        ICMPCONST(ATK_BURN)
        ICMPCONST(ATK_FREEZE)
        ICMPCONST(ATK_SHOCK)
        ICMPCONST(ATK_STEAL)
        ICMPCONST(ATK_NORMAL5)
        ICMPCONST(ATK_NORMAL6)
        ICMPCONST(ATK_NORMAL7)
        ICMPCONST(ATK_NORMAL8)
        ICMPCONST(ATK_NORMAL9)
        ICMPCONST(ATK_NORMAL10)
        ICMPCONST(ATK_BIND)
        ICMPCONST(ATK_ITEM)
        ICMPCONST(ATK_LAND)
        ICMPCONST(ATK_PIT)
        ICMPCONST(ATK_LIFESPAN)
        ICMPCONST(ATK_TIMEOVER)
        ICMPCONST(SCROLL_RIGHT)
        ICMPCONST(SCROLL_DOWN)
        ICMPCONST(SCROLL_LEFT)
        ICMPCONST(SCROLL_UP)
        ICMPCONST(SCROLL_BOTH)
        ICMPCONST(SCROLL_LEFTRIGHT)
        ICMPCONST(SCROLL_RIGHTLEFT)
        ICMPCONST(SCROLL_INWARD)
        ICMPCONST(SCROLL_OUTWARD)
        ICMPCONST(SCROLL_INOUT)
        ICMPCONST(SCROLL_OUTIN)
        ICMPCONST(SCROLL_UPWARD)
        ICMPCONST(SCROLL_DOWNWARD)
        ICMPCONST(ANI_IDLE)
        ICMPCONST(ANI_WALK)
        ICMPCONST(ANI_JUMP)
        ICMPCONST(ANI_LAND)
        ICMPCONST(ANI_PAIN)
        ICMPCONST(ANI_FALL)
        ICMPCONST(ANI_RISE)
        ICMPCONST(ANI_UPPER)
        ICMPCONST(ANI_BLOCK)
        ICMPCONST(ANI_JUMPATTACK)
        ICMPCONST(ANI_JUMPATTACK2)
        ICMPCONST(ANI_GET)
        ICMPCONST(ANI_GRAB)
        ICMPCONST(ANI_GRABATTACK)
        ICMPCONST(ANI_GRABATTACK2)
        ICMPCONST(ANI_THROW)
        ICMPCONST(ANI_SPECIAL)
        ICMPCONST(ANI_SPAWN)
        ICMPCONST(ANI_DIE)
        ICMPCONST(ANI_PICK)
        ICMPCONST(ANI_JUMPATTACK3)
        ICMPCONST(ANI_UP)
        ICMPCONST(ANI_DOWN)
        ICMPCONST(ANI_SHOCK)
        ICMPCONST(ANI_BURN)
        ICMPCONST(ANI_SHOCKPAIN)
        ICMPCONST(ANI_BURNPAIN)
        ICMPCONST(ANI_GRABBED)
        ICMPCONST(ANI_SPECIAL2)
        ICMPCONST(ANI_RUN)
        ICMPCONST(ANI_RUNATTACK)
        ICMPCONST(ANI_RUNJUMPATTACK)
        ICMPCONST(ANI_ATTACKUP)
        ICMPCONST(ANI_ATTACKDOWN)
        ICMPCONST(ANI_ATTACKFORWARD)
        ICMPCONST(ANI_ATTACKBACKWARD)
        ICMPCONST(ANI_RISEATTACK)
        ICMPCONST(ANI_DODGE)
        ICMPCONST(ANI_ATTACKBOTH)
        ICMPCONST(ANI_GRABFORWARD)
        ICMPCONST(ANI_GRABFORWARD2)
        ICMPCONST(ANI_JUMPFORWARD)
        ICMPCONST(ANI_GRABDOWN)
        ICMPCONST(ANI_GRABDOWN2)
        ICMPCONST(ANI_GRABUP)
        ICMPCONST(ANI_GRABUP2)
        ICMPCONST(ANI_SELECT)
        ICMPCONST(ANI_DUCK)
        ICMPCONST(ANI_FAINT)
        ICMPCONST(ANI_CANT)
        ICMPCONST(ANI_THROWATTACK)
        ICMPCONST(ANI_CHARGEATTACK)
        ICMPCONST(ANI_JUMPCANT)
        ICMPCONST(ANI_JUMPSPECIAL)
        ICMPCONST(ANI_BURNDIE)
        ICMPCONST(ANI_SHOCKDIE)
        ICMPCONST(ANI_PAIN2)
        ICMPCONST(ANI_PAIN3)
        ICMPCONST(ANI_PAIN4)
        ICMPCONST(ANI_FALL2)
        ICMPCONST(ANI_FALL3)
        ICMPCONST(ANI_FALL4)
        ICMPCONST(ANI_DIE2)
        ICMPCONST(ANI_DIE3)
        ICMPCONST(ANI_DIE4)
        ICMPCONST(ANI_CHARGE)
        ICMPCONST(ANI_BACKWALK)
        ICMPCONST(ANI_SLEEP)
        ICMPCONST(ANI_PAIN5)
        ICMPCONST(ANI_PAIN6)
        ICMPCONST(ANI_PAIN7)
        ICMPCONST(ANI_PAIN8)
        ICMPCONST(ANI_PAIN9)
        ICMPCONST(ANI_PAIN10)
        ICMPCONST(ANI_FALL5)
        ICMPCONST(ANI_FALL6)
        ICMPCONST(ANI_FALL7)
        ICMPCONST(ANI_FALL8)
        ICMPCONST(ANI_FALL9)
        ICMPCONST(ANI_FALL10)
        ICMPCONST(ANI_DIE5)
        ICMPCONST(ANI_DIE6)
        ICMPCONST(ANI_DIE7)
        ICMPCONST(ANI_DIE8)
        ICMPCONST(ANI_DIE9)
        ICMPCONST(ANI_DIE10)
        ICMPCONST(ANI_TURN)
        ICMPCONST(ANI_RESPAWN)
        ICMPCONST(ANI_FORWARDJUMP)
        ICMPCONST(ANI_RUNJUMP)
        ICMPCONST(ANI_JUMPLAND)
        ICMPCONST(ANI_JUMPDELAY)
        ICMPCONST(ANI_HITWALL)
        ICMPCONST(ANI_GRABBACKWARD)
        ICMPCONST(ANI_GRABBACKWARD2)
        ICMPCONST(ANI_GRABWALK)
        ICMPCONST(ANI_GRABBEDWALK)
        ICMPCONST(ANI_GRABWALKUP)
        ICMPCONST(ANI_GRABBEDWALKUP)
        ICMPCONST(ANI_GRABWALKDOWN)
        ICMPCONST(ANI_GRABBEDWALKDOWN)
        ICMPCONST(ANI_GRABTURN)
        ICMPCONST(ANI_GRABBEDTURN)
        ICMPCONST(ANI_GRABBACKWALK)
        ICMPCONST(ANI_GRABBEDBACKWALK)
        ICMPCONST(ANI_SLIDE)
        ICMPCONST(ANI_RUNSLIDE)
        ICMPCONST(ANI_BLOCKPAIN)
        ICMPCONST(ANI_DUCKATTACK)
        ICMPCONST(ATK_LOSE)
        ICMPCONST(MAX_ANIS)

        // Attacking state.
        ICMPCONST(ATTACKING_ACTIVE)
        ICMPCONST(ATTACKING_INACTIVE)
        ICMPCONST(ATTACKING_PREPARED)

        // Idling state.
        ICMPCONST(IDLING_INACTIVE)
        ICMPCONST(IDLING_PREPARED)
        ICMPCONST(IDLING_ACTIVE)

        // Edge type.
        ICMPCONST(EDGE_NO)
        ICMPCONST(EDGE_LEFT)
        ICMPCONST(EDGE_RIGHT)

        // Duck state.
        ICMPCONST(DUCK_INACTIVE)
        ICMPCONST(DUCK_PREPARED)
        ICMPCONST(DUCK_ACTIVE)
        ICMPCONST(DUCK_RISE)

        // Platform props.
        ICMPCONST(PLATFORM_X)
        ICMPCONST(PLATFORM_Z)
        ICMPCONST(PLATFORM_UPPERLEFT)
        ICMPCONST(PLATFORM_LOWERLEFT)
        ICMPCONST(PLATFORM_UPPERRIGHT)
        ICMPCONST(PLATFORM_LOWERRIGHT)
        ICMPCONST(PLATFORM_DEPTH)
        ICMPCONST(PLATFORM_HEIGHT)

        ICMPCONST(PLAYER_MIN_Z)
        ICMPCONST(PLAYER_MAX_Z)
        ICMPCONST(BGHEIGHT)
        ICMPCONST(MAX_WALL_HEIGHT)

        // Default sound effects.
        ICMPCONST(SAMPLE_GO)
        ICMPCONST(SAMPLE_BEAT)
        ICMPCONST(SAMPLE_BLOCK)
        ICMPCONST(SAMPLE_INDIRECT)
        ICMPCONST(SAMPLE_GET)
        ICMPCONST(SAMPLE_GET2)
        ICMPCONST(SAMPLE_FALL)
        ICMPCONST(SAMPLE_JUMP)
        ICMPCONST(SAMPLE_PUNCH)
        ICMPCONST(SAMPLE_1UP)
        ICMPCONST(SAMPLE_TIMEOVER)
        ICMPCONST(SAMPLE_BEEP)
        ICMPCONST(SAMPLE_BEEP2)
        ICMPCONST(SAMPLE_BIKE)

        // Level sets (practice, easy, hard, etc.)
        ICMPCONST(SET_PROP_COMPLETE_FLAG)
        ICMPCONST(SET_PROP_COMPLETE_SKIP)
        ICMPCONST(SET_PROP_CONTINUE_SCORE_TYPE)
        ICMPCONST(SET_PROP_CREDITS)
        ICMPCONST(SET_PROP_GAME_OVER_SKIP)
        ICMPCONST(SET_PROP_HOF_DISABLE)
        ICMPCONST(SET_PROP_LEVELSET_COLLECTION)
        ICMPCONST(SET_PROP_LEVELSET_COUNT)
        ICMPCONST(SET_PROP_LIVES)
        ICMPCONST(SET_PROP_MP_RECOVER_TYPE)
        ICMPCONST(SET_PROP_MUSIC_FADE_TIME)
        ICMPCONST(SET_PROP_MUSIC_OVERLAP)
        ICMPCONST(SET_PROP_NAME)
        ICMPCONST(SET_PROP_PLAYER_MAX)
        ICMPCONST(SET_PROP_SAVE_TYPE)
        ICMPCONST(SET_PROP_SELECT_DISABLE)
        ICMPCONST(SET_PROP_SELECT_NO_SAME)

        // Spawning types.
        ICMPCONST(SPAWN_TYPE_UNDEFINED)
        ICMPCONST(SPAWN_TYPE_LEVEL)

        ICMPCONST(ANI_RISE2)
        ICMPCONST(ANI_RISE3)
        ICMPCONST(ANI_RISE4)
        ICMPCONST(ANI_RISE5)
        ICMPCONST(ANI_RISE6)
        ICMPCONST(ANI_RISE7)
        ICMPCONST(ANI_RISE8)
        ICMPCONST(ANI_RISE9)
        ICMPCONST(ANI_RISE10)
        ICMPCONST(ANI_RISEB)
        ICMPCONST(ANI_RISES)
        ICMPCONST(ANI_BLOCKPAIN2)
        ICMPCONST(ANI_BLOCKPAIN3)
        ICMPCONST(ANI_BLOCKPAIN4)
        ICMPCONST(ANI_BLOCKPAIN5)
        ICMPCONST(ANI_BLOCKPAIN6)
        ICMPCONST(ANI_BLOCKPAIN7)
        ICMPCONST(ANI_BLOCKPAIN8)
        ICMPCONST(ANI_BLOCKPAIN9)
        ICMPCONST(ANI_BLOCKPAIN10)
        ICMPCONST(ANI_BLOCKPAINB)
        ICMPCONST(ANI_BLOCKPAINS)
        ICMPCONST(ANI_CHIPDEATH)
        ICMPCONST(ANI_GUARDBREAK)
        ICMPCONST(ANI_RISEATTACK2)
        ICMPCONST(ANI_RISEATTACK3)
        ICMPCONST(ANI_RISEATTACK4)
        ICMPCONST(ANI_RISEATTACK5)
        ICMPCONST(ANI_RISEATTACK6)
        ICMPCONST(ANI_RISEATTACK7)
        ICMPCONST(ANI_RISEATTACK8)
        ICMPCONST(ANI_RISEATTACK9)
        ICMPCONST(ANI_RISEATTACK10)
        ICMPCONST(ANI_RISEATTACKB)
        ICMPCONST(ANI_RISEATTACKS)
        ICMPCONST(ANI_WALKOFF)
        ICMPCONST(ANI_FREESPECIAL)
        ICMPCONST(ANI_ATTACK)
        ICMPCONST(ANI_BACKPAIN)
        ICMPCONST(ANI_BACKPAIN2)
        ICMPCONST(ANI_BACKPAIN3)
        ICMPCONST(ANI_BACKPAIN4)
        ICMPCONST(ANI_BACKPAIN5)
        ICMPCONST(ANI_BACKPAIN6)
        ICMPCONST(ANI_BACKPAIN7)
        ICMPCONST(ANI_BACKPAIN8)
        ICMPCONST(ANI_BACKPAIN9)
        ICMPCONST(ANI_BACKPAIN10)
        ICMPCONST(ANI_BACKFALL)
        ICMPCONST(ANI_BACKFALL2)
        ICMPCONST(ANI_BACKFALL3)
        ICMPCONST(ANI_BACKFALL4)
        ICMPCONST(ANI_BACKFALL5)
        ICMPCONST(ANI_BACKFALL6)
        ICMPCONST(ANI_BACKFALL7)
        ICMPCONST(ANI_BACKFALL8)
        ICMPCONST(ANI_BACKFALL9)
        ICMPCONST(ANI_BACKFALL10)
        ICMPCONST(ANI_BACKDIE)
        ICMPCONST(ANI_BACKDIE2)
        ICMPCONST(ANI_BACKDIE3)
        ICMPCONST(ANI_BACKDIE4)
        ICMPCONST(ANI_BACKDIE5)
        ICMPCONST(ANI_BACKDIE6)
        ICMPCONST(ANI_BACKDIE7)
        ICMPCONST(ANI_BACKDIE8)
        ICMPCONST(ANI_BACKDIE9)
        ICMPCONST(ANI_BACKDIE10)
        ICMPCONST(ANI_BACKBURNPAIN)
        ICMPCONST(ANI_BACKSHOCKPAIN)
        ICMPCONST(ANI_BACKBURN)
        ICMPCONST(ANI_BACKSHOCK)
        ICMPCONST(ANI_BACKBURNDIE)
        ICMPCONST(ANI_BACKSHOCKDIE)
        ICMPCONST(ANI_BACKRISEB)
        ICMPCONST(ANI_BACKRISES)
        ICMPCONST(ANI_BACKRISE)
        ICMPCONST(ANI_BACKRISE2)
        ICMPCONST(ANI_BACKRISE3)
        ICMPCONST(ANI_BACKRISE4)
        ICMPCONST(ANI_BACKRISE5)
        ICMPCONST(ANI_BACKRISE6)
        ICMPCONST(ANI_BACKRISE7)
        ICMPCONST(ANI_BACKRISE8)
        ICMPCONST(ANI_BACKRISE9)
        ICMPCONST(ANI_BACKRISE10)
        ICMPCONST(ANI_BACKRISEATTACKB)
        ICMPCONST(ANI_BACKRISEATTACKS)
        ICMPCONST(ANI_BACKRISEATTACK)
        ICMPCONST(ANI_BACKRISEATTACK2)
        ICMPCONST(ANI_BACKRISEATTACK3)
        ICMPCONST(ANI_BACKRISEATTACK4)
        ICMPCONST(ANI_BACKRISEATTACK5)
        ICMPCONST(ANI_BACKRISEATTACK6)
        ICMPCONST(ANI_BACKRISEATTACK7)
        ICMPCONST(ANI_BACKRISEATTACK8)
        ICMPCONST(ANI_BACKRISEATTACK9)
        ICMPCONST(ANI_BACKRISEATTACK10)
        ICMPCONST(ANI_BACKBLOCKPAINB)
        ICMPCONST(ANI_BACKBLOCKPAINS)
        ICMPCONST(ANI_BACKBLOCKPAIN)
        ICMPCONST(ANI_BACKBLOCKPAIN2)
        ICMPCONST(ANI_BACKBLOCKPAIN3)
        ICMPCONST(ANI_BACKBLOCKPAIN4)
        ICMPCONST(ANI_BACKBLOCKPAIN5)
        ICMPCONST(ANI_BACKBLOCKPAIN6)
        ICMPCONST(ANI_BACKBLOCKPAIN7)
        ICMPCONST(ANI_BACKBLOCKPAIN8)
        ICMPCONST(ANI_BACKBLOCKPAIN9)
        ICMPCONST(ANI_BACKBLOCKPAIN10)
        ICMPCONST(ANI_BACKRUN)
        ICMPCONST(ANI_HITOBSTACLE)
        ICMPCONST(ANI_HITPLATFORM)
        ICMPCONST(ANI_HITWALL)
        ICMPCONST(ANI_EDGE)
        ICMPCONST(ANI_BACKEDGE)
        ICMPCONST(ANI_DUCKING)
        ICMPCONST(ANI_DUCKRISE)
        ICMPCONST(ANI_VICTORY)
        ICMPCONST(ANI_FALLLOSE)
        ICMPCONST(ANI_LOSE)

        // for the extra animation ids
        ICMPSCONSTC(ATK_NORMAL)
        ICMPSCONSTA(ANI_DOWN, animdowns)
        ICMPSCONSTA(ANI_UP, animups)
        ICMPSCONSTA(ANI_BACKWALK, animbackwalks)
        ICMPSCONSTA(ANI_WALK, animwalks)
        ICMPSCONSTA(ANI_IDLE, animidles)
        ICMPSCONSTB(ANI_FALL, animfalls)
        ICMPSCONSTB(ANI_RISE, animrises)
        ICMPSCONSTB(ANI_RISEATTACK, animriseattacks)
        ICMPSCONSTB(ANI_PAIN, animpains)
        ICMPSCONSTB(ANI_DIE, animdies)
        ICMPSCONSTA(ANI_ATTACK, animattacks)
        ICMPSCONSTA(ANI_FOLLOW, animfollows)
        ICMPSCONSTA(ANI_FREESPECIAL, animspecials)
        ICMPSCONSTA(ANI_BACKPAIN, animbackpains)
        ICMPSCONSTA(ANI_BACKFALL, animbackfalls)
        ICMPSCONSTA(ANI_BACKDIE, animbackdies)
        ICMPSCONSTA(ANI_BACKRISE, animbackrises)
        ICMPSCONSTA(ANI_BACKRISEATTACK, animbackriseattacks)
        ICMPSCONSTA(ANI_BLOCKPAIN, blkpains)
        ICMPSCONSTA(ANI_BACKBLOCKPAIN, backblkpains)

        // Animation properties.
        ICMPCONST(ANI_PROP_ANIMHITS)
        ICMPCONST(ANI_PROP_ANTIGRAV)
        ICMPCONST(ANI_PROP_ATTACK)
        ICMPCONST(ANI_PROP_COLLISIONONE)
        ICMPCONST(ANI_PROP_BODY_COLLISION)
        ICMPCONST(ANI_PROP_ENTITY_COLLISION)
        ICMPCONST(ANI_PROP_BOUNCE)
        ICMPCONST(ANI_PROP_CANCEL)
        ICMPCONST(ANI_PROP_CHARGETIME)
        ICMPCONST(ANI_PROP_COUNTERRANGE)
        ICMPCONST(ANI_PROP_DELAY)
        ICMPCONST(ANI_PROP_DRAWMETHODS)
        ICMPCONST(ANI_PROP_DROPFRAME)
        ICMPCONST(ANI_PROP_DROPV)
        ICMPCONST(ANI_PROP_ENERGYCOST)
        ICMPCONST(ANI_PROP_FLIPFRAME)
        ICMPCONST(ANI_PROP_FOLLOWUP)
        ICMPCONST(ANI_PROP_IDLE)
        ICMPCONST(ANI_PROP_INDEX)
        ICMPCONST(ANI_PROP_JUMPFRAME)
        ICMPCONST(ANI_PROP_LANDFRAME)
        ICMPCONST(ANI_PROP_LOOP)
        ICMPCONST(ANI_PROP_MODEL_INDEX)
        ICMPCONST(ANI_PROP_MOVE)
        ICMPCONST(ANI_PROP_NUMFRAMES)
        ICMPCONST(ANI_PROP_OFFSET)
        ICMPCONST(ANI_PROP_PLATFORM)
        ICMPCONST(ANI_PROP_PROJECTILE)
        ICMPCONST(ANI_PROP_QUAKEFRAME)
        ICMPCONST(ANI_PROP_RANGE)
        ICMPCONST(ANI_PROP_SHADOW)
        ICMPCONST(ANI_PROP_SIZE)
        ICMPCONST(ANI_PROP_SOUNDTOPLAY)
        ICMPCONST(ANI_PROP_SPAWNFRAME)
        ICMPCONST(ANI_PROP_SPRITE)
        ICMPCONST(ANI_PROP_SPRITEA)
        ICMPCONST(ANI_PROP_SUBENTITY)
        ICMPCONST(ANI_PROP_SUMMONFRAME)
        ICMPCONST(ANI_PROP_SYNC)
        ICMPCONST(ANI_PROP_UNSUMMONFRAME)
        ICMPCONST(ANI_PROP_VULNERABLE)
        ICMPCONST(ANI_PROP_WEAPONFRAME)

        // Attack properties
        ICMPCONST(ATTACK_PROP_BLOCK_COST)
        ICMPCONST(ATTACK_PROP_BLOCK_PENETRATE)
        ICMPCONST(ATTACK_PROP_COUNTER)
        ICMPCONST(ATTACK_PROP_DAMAGE_FORCE)
        ICMPCONST(ATTACK_PROP_DAMAGE_LAND_FORCE)
        ICMPCONST(ATTACK_PROP_DAMAGE_LAND_MODE)
        ICMPCONST(ATTACK_PROP_DAMAGE_LETHAL_DISABLE)
        ICMPCONST(ATTACK_PROP_DAMAGE_RECURSIVE_FORCE)
        ICMPCONST(ATTACK_PROP_DAMAGE_RECURSIVE_INDEX)
        ICMPCONST(ATTACK_PROP_DAMAGE_RECURSIVE_MODE)
        ICMPCONST(ATTACK_PROP_DAMAGE_RECURSIVE_TIME_RATE)
        ICMPCONST(ATTACK_PROP_DAMAGE_RECURSIVE_TIME_EXPIRE)
        ICMPCONST(ATTACK_PROP_DAMAGE_STEAL)
        ICMPCONST(ATTACK_PROP_DAMAGE_TYPE)
        ICMPCONST(ATTACK_PROP_EFFECT_BLOCK_FLASH)
        ICMPCONST(ATTACK_PROP_EFFECT_BLOCK_SOUND)
        ICMPCONST(ATTACK_PROP_EFFECT_HIT_FLASH)
        ICMPCONST(ATTACK_PROP_EFFECT_HIT_FLASH_DISABLE)
        ICMPCONST(ATTACK_PROP_EFFECT_HIT_SOUND)
        ICMPCONST(ATTACK_PROP_GROUND)
        ICMPCONST(ATTACK_PROP_MAP_INDEX)
        ICMPCONST(ATTACK_PROP_MAP_TIME)
        ICMPCONST(ATTACK_PROP_REACTION_FALL_FORCE)
        ICMPCONST(ATTACK_PROP_REACTION_FALL_VELOCITY)
        ICMPCONST(ATTACK_PROP_REACTION_FREEZE_MODE)
        ICMPCONST(ATTACK_PROP_REACTION_FREEZE_TIME)
        ICMPCONST(ATTACK_PROP_REACTION_INVINCIBLE_TIME)
        ICMPCONST(ATTACK_PROP_REACTION_REPOSITION_DIRECTION)
        ICMPCONST(ATTACK_PROP_REACTION_REPOSITION_DISTANCE)
        ICMPCONST(ATTACK_PROP_REACTION_REPOSITION_MODE)
        ICMPCONST(ATTACK_PROP_REACTION_PAIN_SKIP)
        ICMPCONST(ATTACK_PROP_REACTION_PAUSE_TIME)
        ICMPCONST(ATTACK_PROP_SEAL_COST)
        ICMPCONST(ATTACK_PROP_SEAL_TIME)
        ICMPCONST(ATTACK_PROP_STAYDOWN_RISE)
        ICMPCONST(ATTACK_PROP_STAYDOWN_RISEATTACK)
        ICMPCONST(ATTACK_PROP_TAG)

        // Body Collision (bbox) properties.
        ICMPCONST(BODY_COLLISION_PROP_COORDINATES)
        ICMPCONST(BODY_COLLISION_PROP_DEFENSE)
        ICMPCONST(BODY_COLLISION_PROP_TAG)

        // Entity Collision (ebox) properties.
        ICMPCONST(ENTITY_COLLISION_PROP_COORDINATES)
        ICMPCONST(ENTITY_COLLISION_PROP_TAG)

        // Collision coordinate properties.
        ICMPCONST(COLLISION_COORDINATES_PROP_DEPTH_BACKGROUND)
        ICMPCONST(COLLISION_COORDINATES_PROP_DEPTH_FOREGROUND)
        ICMPCONST(COLLISION_COORDINATES_PROP_HEIGHT)
        ICMPCONST(COLLISION_COORDINATES_PROP_WIDTH)
        ICMPCONST(COLLISION_COORDINATES_PROP_X)
        ICMPCONST(COLLISION_COORDINATES_PROP_Y)

        // Porting
        ICMPCONST(PORTING_ANDROID)
        ICMPCONST(PORTING_DARWIN)
        ICMPCONST(PORTING_DREAMCAST)
        ICMPCONST(PORTING_GPX2)
        ICMPCONST(PORTING_LINUX)
        ICMPCONST(PORTING_OPENDINGUX)
        ICMPCONST(PORTING_PSP)
        ICMPCONST(PORTING_UNKNOWN)
        ICMPCONST(PORTING_WII)
        ICMPCONST(PORTING_WINDOWS)
        ICMPCONST(PORTING_WIZ)
        ICMPCONST(PORTING_XBOX)

        // Variable types.
        ICMPCONST(VT_DECIMAL)
        ICMPCONST(VT_EMPTY)
        ICMPCONST(VT_INTEGER)
        ICMPCONST(VT_PTR)
        ICMPCONST(VT_STR)

        else
        {
            found = FALSE;
        }

        if(found)
        {
            ScriptVariant_Copy(varlist[0], &v);
        }
        else
        {
            ScriptVariant_Clear(&v);
            printf("Can't find openbor constant '%s' \n", constname);
        }

        return found;
    }

    return 1;
}

//openborconstant(constname);
//translate a constant by string, used to retrieve a constant or macro of openbor
HRESULT openbor_transconst(ScriptVariant **varlist , ScriptVariant **pretvar, int paramCount)
{
    static char buf[128];
    if(paramCount < 1)
    {
        goto transconst_error;
    }

    //if(varlist[0]->vt == VT_INTEGER) printf("debug: mapstring for openborconstant works!\n");

    mapstrings_transconst(varlist, paramCount);

    if(varlist[0]->vt == VT_INTEGER) // return value already determined by mapstrings
    {
        ScriptVariant_Copy((*pretvar), varlist[0]);
        return S_OK;
    }

transconst_error:
    ScriptVariant_ToString(varlist[0], buf);
    printf("Can't translate constant %s\n", buf);
    *pretvar = NULL;
    return E_FAIL;
}

