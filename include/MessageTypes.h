#pragma once

//Messaging Bus Identifiers
#define AUDIOENG_ID 1000000
#define SCENEMAN_ID 1000001

//Game Object Messages
#define POS_REQUEST "POS"
#define LPOS_REQUEST "LPOS"
#define POS_FD_REQUEST "MVF"
#define POS_BK_REQUEST "MVB"
#define LK_LFT_REQUEST "MVL"
#define LK_RGHT_REQUEST "MVR"
#define LK_UP_REQUEST "LU"
#define LK_DWN_REQUEST "LD"
#define STP_FB_REQUEST "SFB"
#define STP_LR_REQUEST "SLR"
#define STP_UD_REQUEST "SUD"

#define POS_RESPONSE "PR"
#define LPOS_RESPONSE "LPR"

//Camera messages
#define GET_FRONT "GF"
#define GET_FRONT_RESPONSE "GFR"
#define SWITCH_VIEW_MODE "SVM"

//Player Messages
#define FIRE_WEAPON "FIRE"

//Menu object specific messagees
#define DISPLAY "DISP"
#define HIDE "HIDE"
#define TOGGLE "TG"

//Scene Manager Messages
#define CHNG_SCENE_REQUEST "CS"

//Audio Engine Messages
#define PLY_SND_SRC_REQUEST "PSS"
#define PLY_SND_REQUEST "PS"

//Render Module Messages
#define WIREFRAME "WF"
#define KILL "KILL"

//Game Object handler messages
#define ADD_TMP_OBJ "ATO"