#pragma once
/*
 * KOPacketDefine.h — Knight Online Packet Opcode Definitions
 * Tum paket opcode'lari ve isimleri
 */

#ifndef KOPACKETDEFINE_H
#define KOPACKETDEFINE_H

 //////////////////////////////////////////////////////////////////////////////////////
 // LOGIN SERVER
 //////////////////////////////////////////////////////////////////////////////////////
#define LS_VERSION_REQ          0x01
#define LS_DOWNLOADINFO_REQ     0x02
#define LS_CRYPTION             0xF2
#define LS_LOGIN_REQ            0xF3
#define LS_MGAME_LOGIN          0xF4
#define LS_SERVERLIST           0xF5
#define LS_NEWS                 0xF6
#define LS_CLOSESOCKET          0xF7
#define LS_OTP                  0xFA
#define LS_OTP_SYNC             0xFD

//////////////////////////////////////////////////////////////////////////////////////
// GAME SERVER — Core
//////////////////////////////////////////////////////////////////////////////////////
#define WIZ_LOGIN               0x01
#define WIZ_NEW_CHAR            0x02
#define WIZ_DEL_CHAR            0x03
#define WIZ_SEL_CHAR            0x04
#define WIZ_SEL_NATION          0x05
#define WIZ_MOVE                0x06
#define WIZ_USER_INOUT          0x07
#define WIZ_ATTACK              0x08
#define WIZ_ROTATE              0x09
#define WIZ_NPC_INOUT           0x0A
#define WIZ_NPC_MOVE            0x0B
#define WIZ_ALLCHAR_INFO_REQ    0x0C
#define WIZ_GAMESTART           0x0D
#define WIZ_MYINFO              0x0E
#define WIZ_LOGOUT              0x0F

//////////////////////////////////////////////////////////////////////////////////////
// GAME SERVER — Chat & Info
//////////////////////////////////////////////////////////////////////////////////////
#define WIZ_CHAT                0x10
#define WIZ_DEAD                0x11
#define WIZ_REGENE              0x12
#define WIZ_TIME                0x13
#define WIZ_WEATHER             0x14
#define WIZ_REGIONCHANGE        0x15
#define WIZ_REQ_USERIN          0x16
#define WIZ_HP_CHANGE           0x17
#define WIZ_MP_CHANGE           0x18
#define WIZ_ITEM_LOG            0x19
#define WIZ_EXP_CHANGE          0x1A
#define WIZ_LEVEL_CHANGE        0x1B
#define WIZ_NPC_REGION          0x1C
#define WIZ_REQ_NPCIN           0x1D
#define WIZ_WARP                0x1E
#define WIZ_ITEM_MOVE           0x1F

//////////////////////////////////////////////////////////////////////////////////////
// GAME SERVER — Items & Trade
//////////////////////////////////////////////////////////////////////////////////////
#define WIZ_NPC_EVENT           0x20
#define WIZ_ITEM_TRADE          0x21
#define WIZ_TARGET_HP           0x22
#define WIZ_ITEM_DROP           0x23
#define WIZ_BUNDLE_OPEN_REQ     0x24
#define WIZ_TRADE_NPC           0x25
#define WIZ_ITEM_GET            0x26
#define WIZ_ZONE_CHANGE         0x27
#define WIZ_POINT_CHANGE        0x28
#define WIZ_STATE_CHANGE        0x29
#define WIZ_LOYALTY_CHANGE      0x2A
#define WIZ_VERSION_CHECK       0x2B
#define WIZ_CRYPTION            0x2C
#define WIZ_USERLOOK_CHANGE     0x2D
#define WIZ_NOTICE              0x2E
#define WIZ_PARTY               0x2F

//////////////////////////////////////////////////////////////////////////////////////
// GAME SERVER — Exchange & Magic
//////////////////////////////////////////////////////////////////////////////////////
#define WIZ_EXCHANGE            0x30
#define WIZ_MAGIC_PROCESS       0x31
#define WIZ_SKILLPT_CHANGE      0x32
#define WIZ_OBJECT_EVENT        0x33
#define WIZ_CLASS_CHANGE        0x34
#define WIZ_CHAT_TARGET         0x35
#define WIZ_CONCURRENTUSER      0x36
#define WIZ_DATASAVE            0x37
#define WIZ_DURATION            0x38
#define WIZ_TIMENOTIFY          0x39
#define WIZ_REPAIR_NPC          0x3A
#define WIZ_ITEM_REPAIR         0x3B
#define WIZ_KNIGHTS_PROCESS     0x3C
#define WIZ_ITEM_COUNT_CHANGE   0x3D
#define WIZ_KNIGHTS_LIST        0x3E
#define WIZ_ITEM_REMOVE         0x3F

//////////////////////////////////////////////////////////////////////////////////////
// GAME SERVER — System
//////////////////////////////////////////////////////////////////////////////////////
#define WIZ_OPERATOR            0x40
#define WIZ_SPEEDHACK_CHECK     0x41
#define WIZ_COMPRESS_PACKET     0x42
#define WIZ_SERVER_CHECK        0x43
#define WIZ_CONTINOUS_PACKET    0x44
#define WIZ_WAREHOUSE           0x45
#define WIZ_SERVER_CHANGE       0x46
#define WIZ_REPORT_BUG          0x47
#define WIZ_HOME                0x48
#define WIZ_FRIEND_PROCESS      0x49
#define WIZ_GOLD_CHANGE         0x4A
#define WIZ_WARP_LIST           0x4B
#define WIZ_VIRTUAL_SERVER      0x4C
#define WIZ_ZONE_CONCURRENT     0x4D
#define WIZ_CORPSE              0x4E
#define WIZ_PARTY_BBS           0x4F

//////////////////////////////////////////////////////////////////////////////////////
// GAME SERVER — Extended
//////////////////////////////////////////////////////////////////////////////////////
#define WIZ_MARKET_BBS          0x50
#define WIZ_KICKOUT             0x51
#define WIZ_CLIENT_EVENT        0x52
#define WIZ_WAR_SYSTEM          0x53
#define WIZ_WEIGHT_CHANGE       0x54
#define WIZ_SELECT_MSG          0x55
#define WIZ_NPC_SAY             0x56
#define WIZ_BATTLE_EVENT        0x57
#define WIZ_AUTHORITY_CHANGE    0x58
#define WIZ_EDIT_BOX            0x59
#define WIZ_SANTA               0x5A
#define WIZ_ITEM_UPGRADE        0x5B
#define WIZ_CLAN_PREMIUM        0x5C
#define WIZ_ZONEABILITY         0x5E
#define WIZ_EVENT               0x5F
#define WIZ_STEALTH             0x60
#define WIZ_ROOM_PACKETPROCESS  0x61
#define WIZ_ROOM                0x62
#define WIZ_CLAN_BATTLE         0x63
#define WIZ_QUEST               0x64
#define WIZ_PP_CARD             0x65
#define WIZ_KISS                0x66
#define WIZ_RECOMMEND_USER      0x67
#define WIZ_MERCHANT            0x68
#define WIZ_MERCHANT_INOUT      0x69
#define WIZ_SHOPPING_MALL       0x6A
#define WIZ_SERVER_INDEX        0x6B
#define WIZ_EFFECT              0x6C
#define WIZ_SIEGE               0x6D
#define WIZ_NAME_CHANGE         0x6E
#define WIZ_WEBPAGE             0x6F
#define WIZ_CAPE                0x70
#define WIZ_PREMIUM             0x71
#define WIZ_HACKTOOL            0x72
#define WIZ_RENTAL              0x73
#define WIZ_COMBAT              0x75
#define WIZ_PET                 0x76
#define WIZ_CHINA               0x77
#define WIZ_KING                0x78
#define WIZ_SKILLDATA           0x79
#define WIZ_PROGRAMCHECK        0x7A
#define WIZ_BIFROST             0x7B
#define WIZ_REPORT              0x7C
#define WIZ_LOGOS_SHOUT         0x7D
#define WIZ_SERVER_KILL         0x7F
#define WIZ_RANK                0x80
#define WIZ_STORY               0x81
#define WIZ_CAPTURE             0x85
#define WIZ_MINE                0x86
#define WIZ_HELMET              0x87
#define WIZ_PVP                 0x88
#define WIZ_CHANGE_HAIR         0x89
#define WIZ_VIPWAREHOUSE        0x8B
#define WIZ_GENDERCHANGE        0x8D
#define WIZ_DEATH_LIST          0x90
#define WIZ_CLANPOINTS_BATTLE   0x91
#define WIZ_GENIE               0x97
#define WIZ_USER_INFORMATIN     0x98
#define WIZ_ACHIEVE             0x99
#define WIZ_I_LOVE_KNIGHT_ONLINE 0x9C
#define WIZ_USERLIST            0x9F

//////////////////////////////////////////////////////////////////////////////////////
// *** XIGNCODE3 & ANTI-CHEAT ***
//////////////////////////////////////////////////////////////////////////////////////
#define WIZ_XIGNCODE3           0xA0  // X3 heartbeat — KRITIK!
#define WIZ_DC                  0xB5
#define WIZ_UI_INFO             0xBD
#define WIZ_CAPTCHA             0xC0
#define WIZ_CR                  0xC2
#define WIZ_CLAN_BANK           0xC3
#define WIZ_WATCHMAN            0xCC
#define WIZ_MORADON_MONUMENT    0xD9
#define WIZ_RENTAL_ITEM         0x73  // same as WIZ_RENTAL
#define WIZ_DEBUG_STRING_PACKET 0xFE
#define WIZ_TEST_PACKET         0xFF

//////////////////////////////////////////////////////////////////////////////////////
// Chat sub-types
//////////////////////////////////////////////////////////////////////////////////////
#define GENERAL_CHAT            0x01
#define PRIVATE_CHAT            0x02
#define PARTY_CHAT              0x03
#define FORCE_CHAT              0x04
#define SHOUT_CHAT              0x05
#define KNIGHTS_CHAT            0x06
#define PUBLIC_CHAT             0x07
#define WAR_SYSTEM_CHAT         0x08
#define PERMANENT_CHAT          0x09
#define COMMAND_CHAT            0x0D
#define MERCHANT_CHAT           0x0E
#define ALLIANCE_CHAT           0x0F
#define CLAN_NOTICE             0x18

//////////////////////////////////////////////////////////////////////////////////////
// Party sub-types
//////////////////////////////////////////////////////////////////////////////////////
#define PARTY_CREATE            0x01
#define PARTY_PERMIT            0x02
#define PARTY_INSERT            0x03
#define PARTY_REMOVE            0x04
#define PARTY_DELETE            0x05
#define PARTY_HPCHANGE          0x06
#define PARTY_LEVELCHANGE       0x07

//////////////////////////////////////////////////////////////////////////////////////
// Magic sub-types
//////////////////////////////////////////////////////////////////////////////////////
#define MAGIC_CASTING           0x01
#define MAGIC_FLYING            0x02
#define MAGIC_EFFECTING         0x03
#define MAGIC_FAIL              0x04
#define MAGIC_TYPE4_END         0x05
#define MAGIC_CANCEL            0x06

//////////////////////////////////////////////////////////////////////////////////////
// Knights sub-types
//////////////////////////////////////////////////////////////////////////////////////
#define KNIGHTS_CREATE          0x01
#define KNIGHTS_JOIN            0x02
#define KNIGHTS_WITHDRAW        0x03
#define KNIGHTS_REMOVE          0x04
#define KNIGHTS_DESTROY         0x05

//////////////////////////////////////////////////////////////////////////////////////
// Warehouse sub-types
//////////////////////////////////////////////////////////////////////////////////////
#define WAREHOUSE_OPEN          0x01
#define WAREHOUSE_INPUT         0x02
#define WAREHOUSE_OUTPUT        0x03
#define WAREHOUSE_MOVE          0x04

//////////////////////////////////////////////////////////////////////////////////////
// Opcode Name Lookup (C compatible)
//////////////////////////////////////////////////////////////////////////////////////

typedef struct {
    unsigned char opcode;
    const char* name;
} OpcodeEntry;

static const OpcodeEntry g_opcodeTable[] = {
    /* Login Server */
    { 0xF2, "LS_CRYPTION" },
    { 0xF3, "LS_LOGIN_REQ" },
    { 0xF5, "LS_SERVERLIST" },
    { 0xF6, "LS_NEWS" },
    { 0xFA, "LS_OTP" },

    /* Core */
    { 0x01, "WIZ_LOGIN" },
    { 0x02, "WIZ_NEW_CHAR" },
    { 0x03, "WIZ_DEL_CHAR" },
    { 0x04, "WIZ_SEL_CHAR" },
    { 0x05, "WIZ_SEL_NATION" },
    { 0x06, "WIZ_MOVE" },
    { 0x07, "WIZ_USER_INOUT" },
    { 0x08, "WIZ_ATTACK" },
    { 0x09, "WIZ_ROTATE" },
    { 0x0A, "WIZ_NPC_INOUT" },
    { 0x0B, "WIZ_NPC_MOVE" },
    { 0x0C, "WIZ_ALLCHAR_INFO" },
    { 0x0D, "WIZ_GAMESTART" },
    { 0x0E, "WIZ_MYINFO" },
    { 0x0F, "WIZ_LOGOUT" },
    { 0x10, "WIZ_CHAT" },
    { 0x11, "WIZ_DEAD" },
    { 0x12, "WIZ_REGENE" },
    { 0x13, "WIZ_TIME" },
    { 0x14, "WIZ_WEATHER" },
    { 0x17, "WIZ_HP_CHANGE" },
    { 0x18, "WIZ_MP_CHANGE" },
    { 0x1A, "WIZ_EXP_CHANGE" },
    { 0x1B, "WIZ_LEVEL_CHANGE" },
    { 0x1E, "WIZ_WARP" },
    { 0x1F, "WIZ_ITEM_MOVE" },
    { 0x20, "WIZ_NPC_EVENT" },
    { 0x21, "WIZ_ITEM_TRADE" },
    { 0x22, "WIZ_TARGET_HP" },
    { 0x23, "WIZ_ITEM_DROP" },
    { 0x25, "WIZ_TRADE_NPC" },
    { 0x26, "WIZ_ITEM_GET" },
    { 0x27, "WIZ_ZONE_CHANGE" },
    { 0x28, "WIZ_POINT_CHANGE" },
    { 0x29, "WIZ_STATE_CHANGE" },
    { 0x2B, "WIZ_VERSION_CHECK" },
    { 0x2C, "WIZ_CRYPTION" },
    { 0x2F, "WIZ_PARTY" },
    { 0x30, "WIZ_EXCHANGE" },
    { 0x31, "WIZ_MAGIC" },
    { 0x34, "WIZ_CLASS_CHANGE" },
    { 0x38, "WIZ_DURATION" },
    { 0x3C, "WIZ_KNIGHTS" },
    { 0x41, "WIZ_SPEEDHACK" },
    { 0x44, "WIZ_CONTINOUS" },
    { 0x45, "WIZ_WAREHOUSE" },
    { 0x48, "WIZ_HOME" },
    { 0x49, "WIZ_FRIEND" },
    { 0x4A, "WIZ_GOLD_CHANGE" },
    { 0x51, "WIZ_KICKOUT" },
    { 0x5B, "WIZ_ITEM_UPGRADE" },
    { 0x5F, "WIZ_EVENT" },
    { 0x64, "WIZ_QUEST" },
    { 0x68, "WIZ_MERCHANT" },
    { 0x6A, "WIZ_SHOPPING_MALL" },
    { 0x6D, "WIZ_SIEGE" },
    { 0x72, "WIZ_HACKTOOL" },
    { 0x76, "WIZ_PET" },
    { 0x79, "WIZ_SKILLDATA" },
    { 0x7A, "WIZ_PROGRAMCHECK" },
    { 0x7B, "WIZ_BIFROST" },
    { 0x80, "WIZ_RANK" },
    { 0x86, "WIZ_MINE" },

    /* XIGNCODE3 — DC sebebi */
    { 0xA0, "WIZ_XIGNCODE3" },
    { 0xB5, "WIZ_DC" },
    { 0xC0, "WIZ_CAPTCHA" },
    { 0xCC, "WIZ_WATCHMAN" },
    { 0xFE, "WIZ_DEBUG" },
    { 0xFF, "WIZ_TEST" },

    { 0, NULL }  /* sentinel */
};

/* Opcode -> isim çevirici */
static const char* GetOpcodeName(unsigned char opcode) {
    for (int i = 0; g_opcodeTable[i].name != NULL; i++) {
        if (g_opcodeTable[i].opcode == opcode)
            return g_opcodeTable[i].name;
    }
    return NULL;
}

#endif /* KOPACKETDEFINE_H */