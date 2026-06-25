#pragma once
/* ===================================================================
   KOAddresses.h — Knight Online Pointer & Offset Table
   Version: 2614
   Source:  Ghidra static analysis of UNPACKED KnightOnLine.exe v2614
            (re-anchor pass, 2026-06-25). Rehber: RENotes/REBASELINE_GUIDE.md
   ===================================================================

   ⭐ v2613 → v2614 DELTA (DOĞRULANMIŞ):
     .text  : +~0xA000 büyüdü (.text sonu 0xf81abd → 0xf8bfdd).
              AMA erken fonksiyonlar (0x4cdxxx crypto) DEĞİŞMEDİ.
     .data  : base 0x10d1000 → 0x10dc000. Singleton cluster KABACA +0xB000
              kaydı AMA slot'lar PERMUTE oldu (uniform DEĞİL!): player 2613'te
              0x10fa834 slot'undaydı, 2614'te 0x01105840'a taşındı (FORUM +
              FUN_007e9660 ile doğrulandı). +0xB000 ile körlemesine hesaplama
              YANLIŞ sonuç verir → her pointer'ı decompile/forum ile DOĞRULA.
              Crypto-flag bloğu (0x10fb6xx) +0xAFE4, lock +0xB010 (yine farklı).
     struct : CHR_* offset'leri DEĞİŞMEDİ (object-relative, 2609-LAYOUT).
              Patch struct alanı eklemediyse 2613 ile aynı → runtime verify.
     crypto : wrapper FUN_004cd460 / CRC32 4cd4a0 / XOR 4cd3e0 SABİT.

   ⛔ NOT: 2610'un +0x1D0/+0x60 struct shift'leri YANLIŞTI. v2613+'te
      CHR_* = 2609-LAYOUT (MyInfo writer ile doğrulandı).

   GÜVEN ETİKETLERİ:
     ✅  = Ghidra decompile ile doğrulandı (yüksek güven)
     ⚠️  = aday / runtime test gerekli
     ❓  = BULUNAMADI — tahmin etmek yerine boş bırakıldı (0x0)

   !! "AES" ASLINDA AES DEĞİL — custom XOR stream cipher + CRC32 !!
     Cipher:  byte[i] ^= key[i%8] ^ PRNG(state>>8) ^ (len*0x9D)
     PRNG:    state = state * 0x87B, initial = 0x86D
     CRC32:   standard, FUN_004cd4a0
     Wrapper: FUN_004cd460 → FUN_004cd4a0(CRC32) + FUN_004cd3e0(XOR)  ✅
   =================================================================== */

/* ===================================================================
   STATIC POINTER ADDRESSES — v2614 (cluster +0xB000, decompile doğrulanmış)
   =================================================================== */

// ⚠️⚠️ CLUSTER PERMUTE UYARISI: 2613→2614'te bu cluster slot'ları SADECE +0xB000 kaymadı,
//   PERMUTE oldu (player 2613'te 0x834 slot'undaydı, 2614'te 0x840'a taşındı). Forum cross-check
//   ile yakalandı. Aşağıda ✅ = decompile/forum DOĞRULANMIŞ; ⚠️ = +0xB000 hesaplandı, GÜVENİLMEZ → verify.
#define KO_PTR_CHR              0x01105840   // ✅ CPlayerMySelf (FORUM + FUN_007e9660: +0xc90=zone,+0x660=target,+0x134=state)
#define KO_ENTITY_LIST          0x00000000   // ❓ CPlayerOtherMgr — eski 0x840 aslında CHR'di! Re-derive gerek (cluster permuted)
#define KO_PTR_PKT              0x01105914   // ✅ aktif game socket — FORUM + send fn DAT_01105914
#define KO_PTR_RECV1            0x00000000   // ❓ s_pProcActive — re-derive (cluster permuted, +0xB000 güvenilmez)

// Game state / proc machine
#define KO_PTR_DLG              0x011058FC   // ✅ CGameProcMain (inventory/skill/state chain) (was 0x10fa8fc)
#define KO_GAME_STATE_MGR       0x011058FC   // = CGameProcMain
#define KO_PTR_SKILL_MGR        0x011058FC   // = CGameProcMain
#define KO_PTR_NOTICE_DLG       0x011058F4   // ⚠️ notice/symbol mgr (cluster +0xB000) (was 0x10fa8f4)
#define KO_PTR_GameProcMain     0x011058FC   // ✅
#define KO_PTR_GameProcIntro    0x01105904   // ⚠️ login proc (cluster +0xB000) (was 0x10fa904)
#define KO_PTR_ChrSelect        0x01105900   // ⚠️ char select (cluster +0xB000) (was 0x10fa900)
#define KO_PTR_GameProcLogo     0x01105908   // ⚠️ (cluster +0xB000) (was 0x10fa908)

// Tablolar (cluster +0xB000)
#define KO_ITEM_TABLE_MGR       0x01105804   // ⚠️ KO_ITOB (+0xB000 hesap, cluster permuted → verify)
#define KO_SKILL_TABLE_MGR      0x0110581C   // ⚠️ KO_SMMB (+0xB000 hesap, cluster permuted → verify)
#define KO_MOB_TABLE_MGR        0x011056B0   // ⚠️ __TABLE_MOB_LIST (+0xB000 hesap, cluster permuted → verify)

// UI / güvenlik
#define KO_PTR_UIMGR            0x011058EC   // ⚠️ CUIManager (cluster +0xB000) (was 0x10fa8ec)
#define KO_PTR_HACKCHECK        0x0110588C   // ⚠️ CHackCheck (cluster +0xB000); HackCheck↔Modules runtime verify
#define KO_PTR_MODULES          0x011058A8   // ⚠️ CModulesCheck (cluster +0xB000); runtime verify

#define KO_PTR_SOCKET           0x011058D8   // ⚠️ CAPISocket login/API kanalı (cluster +0xB000)
#define KO_PTR_LOGIN_UI         0x00000000   // ❓ NEED_TEST
#define KO_PTR_LOGO             0x00000000   // ❓ NEED_TEST
#define KO_PTR_BATTLEROYAL      0x00000000   // ❓ NEED_TEST
#define KO_PTR_CRYPTO           0x00000000   // ❓ CNetCrypto obj re-anchor gerek (2613'te 0xf786c0; .text/.rdata bölgesi kaydı). Pratik cipher state ↓
#define KO_CN3_WORLD_MGR        0x01105830   // ⚠️ CN3WorldManager (+0xB000 hesap, cluster permuted → verify)

/* ----- Engine singleton'ları (cluster +0xB000) ----- */
#define KO_PTR_GAME_ENG         0x0110584C   // ⚠️ CGameEng / CN3Eng
#define KO_PTR_N3SCENE          0x00000000   // ❓ CN3Scene (2613 0x11702c8 farklı bölge — re-anchor gerek)
#define KO_PTR_N3SNDMGR         0x01105050   // ⚠️ CN3SndMgr
#define KO_PTR_N3FXMGR          0x011058E4   // ⚠️ CN3FXMgr
#define KO_PTR_GAMECURSOR       0x01105848   // ⚠️ CGameCursor
#define KO_PTR_SYMBOLMGR        0x011058F4   // ⚠️ CSymbolManager
#define KO_PTR_SEEDJOBMGR       0x01105634   // ⚠️ CSeedJobManager

/* ----- Game-state proc band (cluster +0xB000) ----- */
#define KO_PTR_GameProcMainCont 0x011058FC   // ✅ = KO_PTR_DLG
#define KO_PTR_GameProcNotice   0x0110589C   // ⚠️
#define KO_PTR_GameProcMovie    0x011058A0   // ⚠️
#define KO_PTR_GameProcLangSel  0x011058A4   // ⚠️
#define KO_PTR_GameProcNationSel 0x011058AC  // ⚠️
#define KO_PTR_GameProcOption   0x011058B4   // ⚠️
#define KO_PTR_GameProcDuelLobby 0x011058B8  // ⚠️

/* ----- Statik veri tabloları (cluster +0xB000) ----- */
#define KO_TBL_ITEM_BASIC       0x01105804   // ✅ = KO_ITEM_TABLE_MGR
#define KO_TBL_UPC_SKILL        0x0110581C   // ✅ = KO_SKILL_TABLE_MGR
#define KO_TBL_MOB_LIST         0x011056B0   // ⚠️ = KO_MOB_TABLE_MGR (verify)
#define KO_TBL_NPC_LIST         0x011056AC   // ⚠️
#define KO_TBL_ZONE             0x01105630   // ⚠️ record size 0x1c4
#define KO_TBL_WARP_INFO        0x01105740   // ⚠️
#define KO_TBL_PLAYER_EXP       0x011056C8   // ⚠️
#define KO_TBL_TEXT             0x01105744   // ⚠️
#define KO_TBL_ITEM_EXT         0x00000000   // ❓ flat global değil

/* ----- Manager'lar (flat global YOK — GameProcMain container 0x11058fc + offset) ----- */
#define MGR_CHAIN_BASE          0x011058FC   // CGameProcMain container
#define OFF_MAGICSKILLMNG       0x468        // [container+0x468] = CMagicSkillMng
#define OFF_INSTANCEMANAGER     0x384        // [container+0x384] = CInstanceManager
#define OFF_MAPSYSTEMMGR        0x4A0        // [container+0x4a0] = CMapSystemMgr
// CPetMgr: container'ın kendisi; CItemUpgrade: per-instance (singleton değil)
// CQuestManager: stack/member (flat global yok); CKnightChrMgr/CItemRepairMgr/CMainStoryMgr: UNKNOWN (vtable unlinked)

/* ===================================================================
   PACKET ENCRYPTION — CUSTOM XOR CIPHER (AES DEĞİL!)
   Decrypt Python:
     def decrypt(data, key8):
         state = 0x86D
         kc = (len(data) * 0x9D) & 0xFF
         out = bytearray(len(data))
         for i in range(len(data)):
             out[i] = data[i] ^ key8[i%8] ^ ((state>>8)&0xFF) ^ kc
             state = (state * 0x87B) & 0xFFFFFFFF
         return out
   =================================================================== */

// Crypto state adresleri (v2614 — crypt fn FUN_008d1580 ile doğrulandı)
#define KO_PKT_COUNTER      0x01101FCC   // ✅ BYTE, 1-250 rolling counter (was 0x10f6fcc)
#define KO_PKT_BYPASS_FLAG  0x01101FCD   // ✅ BYTE, counter skip flag (was 0x10f6fcd)
#define KO_CIPHER_COUNTER   0x011066D0   // ✅ DWORD, block/seq counter (was 0x10fb6ec)
#define KO_CIPHER_ENABLE    0x011066F8   // ✅ DWORD, XOR cipher enable (0=off) (was 0x10fb6f0)
#define KO_CIPHER_LOCK      0x011E83D8   // ✅ CRITICAL_SECTION (crypt fn EnterCS) (was 0x11dd3c8)
#define KO_CIPHER_BUF_PTR   0x0121D578   // ✅ PTR, encrypt/decrypt working buffer (was 0x1212568)
#define KO_SEND_BUF_PTR     0x0120F92C   // ✅ PTR, final send buffer (AA55/55AA sarmalı) (was 0x120491c)
#define KO_CIPHER_CONTEXT   0x011E83F0   // ⚠️ CNetCrypto context (lock+0x18; computed) verify
#define KO_CIPHER_KEY       0x011E8400   // ⚠️ 8 BYTE XOR key (context+0x10; computed) — runtime verify
#define KO_CRC32_TABLE      0x010EC120   // ⚠️ CRC32 table (cluster +0xB000) NEED_VERIFY
#define KO_AES_FLAG         0x00000000   // ❓ NEED_TEST

#define KO_AES_KEY          0x00000000   // ❓ .rdata key — re-locate gerek

// Crypto fonksiyonları (v2614)
#define KO_CRYPT_HANDLER    0x008D1580   // ✅ encrypt/decrypt dispatcher (param5=1 encrypt) (was 0x8ce9e0)
#define KO_CRYPT_WRAP       0x004CD460   // ✅ CRC32 + XOR wrapper (DEĞİŞMEDİ)
#define KO_CRC32_FUNC       0x004CD4A0   // ✅ CRC32 (DEĞİŞMEDİ)
#define KO_XOR_CIPHER       0x004CD3E0   // ✅ XOR stream cipher (DEĞİŞMEDİ)
#define KO_CRYPT_DECRYPT    0x00000000   // ⚠️ decrypt path FUN_008d12c0/1360/1400 içinde NEED_TEST
#define KO_CRYPT_EXTRA      0x00000000   // ⚠️ NEED_TEST
#define KO_CRYPT_VALIDATE   0x00000000   // ⚠️ NEED_TEST

/* ===================================================================
   SEND / RECV / FUNCTIONS — v2614 Ghidra doğrulanmış
   NOT: gerçek send = FUN_006fd6c0; FUN_006fd940 = sadece invalid-packet logger.
   =================================================================== */

#define KO_SEND_FUNC        0x006FD6C0   // ✅ gerçek send: ws2_32_send + AA55/55AA + crypt (thiscall: socket,buf,len)
#define KO_FNC_SND          0x006FD6C0   // alias
#define KO_RECV_DISPATCH    0x007AF000   // ✅ "Current Zone" xref (was 0x7aec60)
#define KO_HB_HANDLER       0x00000000   // ⚠️ 0xA0 case KO_RECV_DISPATCH içinde NEED_TEST
#define KO_MYINFO_FUNC      0x007F53D0   // ✅ MsgRecv_MyInfo_All handler (was 0x7f3e80)
#define KO_MYINFO_WRITER    0x0083C550   // ✅ player struct writer (was 0x83a8b0)
#define KO_X3_LOADER        0x007A6980   // ✅ "x3.xem" string xref (was 0x7a6630)

// ❓ String anchor yok — kod tamamen recompile, tahmin edilmedi
#define KO_FNC_SEL          0x00000000   // ❓ SelectTarget (was 0x80a0b0)
#define KO_FNC_NPC_IS_ENEMY 0x00000000   // ❓ (was 0x7915a0)
#define KO_FNC_Map_Next_Item 0x00000000  // ❓ (was 0x4e13f0)
#define KO_FNC_SHOWMSG_WRAP 0x00000000   // ❓ ShowMessageBox (was 0xbf66d0; 0xbf6xxx bölgesi CUIManager)
#define KO_MOVE_FUNC        0x00000000   // ❓ 0x06 move packet (was 0x841080; other-update dispatcher ~FUN_00898c60)
#define KO_CAMERA_HOOK      0x00000000   // ⚠️ NEED_TEST (was 0x7a2eea)
#define MOB_EFFECT          0x00000000   // ⚠️ NEED_TEST (was 0x916dad)
#define KO_LSCA             0x00000000   // ⚠️ NEED_TEST (was 0x87dbb0)
#define KO_SBEC             0x00000000   // ⚠️ NEED_TEST (was 0x5039f0)

/* ===================================================================
   DISCONNECT
   =================================================================== */
#define KO_DISCONNECT_FLAG  0x0110575C   // ✅ send-error flag (send fn DAT_0110575c) (was 0x10fa85f)
#define KO_DISCONNECT_ERR   0x011058D8   // ✅ son hata kodu (send fn DAT_011058d8; status DAT_011058d4) (was 0x10fa8d0)

/* ===================================================================
   X3 / XIGNCODE  (v2614 — re-anchor gerek; cipher RE yolu, bot-kritik değil)
   2613'te: resolver FUN_00553540, export tablo 0x011fec18, init 0x011fec1c,
   probe-cb 0x011fec10. v2614'te KO_X3_LOADER 0x7a6980'dan decompile ile
   resolver+tablo yeniden bulunmalı (REBASELINE_GUIDE.md §X3).
   =================================================================== */
#define KO_X3_RESOLVER      0x00000000   // ⚠️ re-anchor (2613: 0x553540)
#define KO_X3_EXPORT_TABLE  0x00000000   // ⚠️ re-anchor (2613: 0x11fec18)
#define KO_X3_INIT_EXPORT   0x00000000   // ⚠️ re-anchor (2613: 0x11fec1c)
#define KO_X3_PROBE_CB      0x00000000   // ⚠️ re-anchor (2613: 0x11fec10)
#define KO_X3_HMODULE       0x00000000   // ❓ NEED_TEST
#define KO_X3_ORD1          0x00000000   // ❓ NEED_TEST
#define KO_X3_CB_INIT       0x00000000   // ❓ NEED_TEST
#define KO_X3_CALLBACK      0x00000000   // ❓ MakeResponse CB ptr — runtime arama
#define KO_MAKERESP_CB      0x00000000   // ❓ runtime arama gerekli

/* ===================================================================
   XST.XEM — ⛔ v2613 STALE (xst.xem ASLR runtime — session başında re-locate)
   =================================================================== */
#define XST_IDA_SBOX            0x149D43E0u
#define XST_IDA_SBOX_VTCHASE   0x14BF43E0u
#define XST_IDA_ENCRYPT_FUNC   0x148BF246u
#define XST_IDA_DISPATCH       0x1486CE38u
#define XST_IDA_SBOX_DW        0x14BB43E0u
#define XST_IDA_ENCRYPT_DW     0x14A9F246u
#define XST_IDA_DISPATCH_DW    0x14A4CE38u
#define XST_SBOX_TO_ENCRYPT    0x232ACEu
#define XST_SBOX_TO_CABC4      0x19D67E4u
#define XST_RANGE_NARROW_L     0x14800000u
#define XST_RANGE_NARROW_H     0x15200000u
#define XST_RANGE_WIDE_L       0x0E000000u
#define XST_RANGE_WIDE_H       0x18000000u
#define XST_RANGE_MAX_L        0x08000000u
#define XST_RANGE_MAX_H        0x1F000000u
#define XST_SCAN_L             0x14000000u
#define XST_SCAN_H             0x17000000u
#define XST_DW_SCAN_H          0x16000000u
#define XST_DW_RANGE_LOW_L     0x0E000000u
#define XST_DW_RANGE_LOW_H     0x10000000u
#define XST_DW_RANGE_MID_L     0x14000000u
#define XST_DW_RANGE_MID_H     0x18000000u
#define XST_DW_RANGE_EXT_L     0x1A000000u
#define XST_DW_RANGE_EXT_H     0x1C000000u

/* ===================================================================
   CHARACTER OFFSETS (from KO_PTR_CHR base) — v2613 = 2609 LAYOUT
   MyInfo writer FUN_0083a8b0 + consumer fonksiyonlar ile doğrulandı.
   Struct, player-self ve TÜM karakter nesneleri için ORTAK (object-relative).
   =================================================================== */

// --- Identity ---
#define CHR_PLAYER_ID       0x6A0        // ✅ dword (FUN_008fda70 target+0x660==*(p+0x6a0))
#define CHR_NAME            0x6A4        // ✅ std::string SSO (capacity/len @ +0x6B8)
#define CHR_NAME_LEN        0x6B8        // ✅ string len/capacity (inline vs heap seçimi)
#define CHR_RACE            0x6C0        // ✅ int race/sex (avatar builder param)
#define CHR_NATION          0x6C4        // ✅ int (taraf — FUN_0080a340 [0x1b1])
#define CHR_SAMETEAM_FLAG   0x6C8        // ✅ byte same-team
#define CHR_JOB             0x6CC        // ✅ int class (avatar builder param)
#define CHR_LEVEL           0x6D0        // ✅ int (cmp 0x32 cap; mirror @ +0xBE8)
#define CHR_CUR_HP          0x6D4        // ✅ (forum ✅; ⚠️ Agent A okumada max/cur ters olabilir → runtime doğrula)
#define CHR_MAX_HP          0x6D8        // ✅ (cur/max pairing — bkz CHR_CUR_HP notu)
#define CHR_TRANSFORM_STATE 0x6DC        // ✅ transform/death/GM state (==0xfa ⇒ unattackable)
#define CHR_GROUP_ID        0x6F8        // ✅ ikincil grup/alliance id
#define CHR_CLAN_ID         0x6FC        // ✅ ana clan/war-side id (attackability dominant)
#define CHR_RIVAL_ALLIANCE  0x700        // ✅ rakip war-target alliance
#define CHR_MAP_ID2         0x6E4        // ✅ int map/zone id (0x753a/0x7602)

// --- MP / Level mirror ---
#define CHR_LEVEL_MIRROR    0xBE8        // ✅ level kopyası
#define CHR_MAX_MP          0xBEC        // ✅
#define CHR_CUR_MP          0xBF0        // ✅

// --- Combat (⚠️ attack/AC ayrımı belirsiz) ---
#define CHR_ATTACK          0xBC8        // ⚠️ attack/AC alanı NEED_TEST
#define CHR_DEFENCE         0xBCC        // ⚠️ defence/flags alanı NEED_TEST

// --- Attributes (base + item-extra interleaved) ---
#define CHR_STR             0xC24        // ✅ STR base
#define CHR_STR_EXTRA       0xC28        // ✅ STR item-added
#define CHR_HP_STAT         0xC2C        // ✅ STA(HP) base
#define CHR_HP_EXTRA        0xC30        // ✅
#define CHR_DEX             0xC34        // ✅ DEX base
#define CHR_DEX_EXTRA       0xC38        // ✅
#define CHR_INT             0xC3C        // ✅ INT base
#define CHR_INT_EXTRA       0xC40        // ✅
#define CHR_MP_STAT         0xC44        // ✅ MP(CHA) base
#define CHR_MP_EXTRA        0xC48        // ✅

// --- Gold / StatPt / XP (⚠️ 0xc00-0xc20 dword bloğu — disambiguate edilemedi) ---
#define CHR_STAT_PT         0x00000000   // ❓ aday 0xBE4 veya 0x724 — NEED_TEST
#define CHR_GOLD            0x00000000   // ❓ aday 0xBFC veya 0xc00-0xc20 bloğu — NEED_TEST
#define CHR_MAX_XP          0x00000000   // ❓ aday 0xC00-0xC14 bloğu — NEED_TEST
#define CHR_CUR_XP          0x00000000   // ❓ aday 0xC00-0xC14 bloğu — NEED_TEST

// --- Zone ---
#define CHR_ZONE            0xC90        // ✅ int zone id (FUN_007e8270 *10==0x1c2)
#define CHR_ZONE_SUB        0xC94        // ⚠️ sub-zone (0xc90 ile birlikte save/restore) NEED_TEST

// --- Target / State ---
#define CHR_TARGETID        0x660        // ✅ int (-1 = hedef yok)
#define CHR_NPC_STATE       0x134        // ✅ 4=dead,5=dying,7,0xd
#define CHR_MOVE_STATE      0x140        // ⚠️ (was 0x140) NEED_TEST

// --- Position (float, CN3Transform) ---
#define CHR_POS_X           0x3CC        // ✅ float map-X
#define CHR_POS_Y           0x3D0        // ✅ float height
#define CHR_POS_Z           0x3D4        // ✅ float map-Z (eski dosya bunu POS_Y sanmıştı)
#define CHR_ORIENT_MTX      0x3B0        // ✅ float[4] orientation/rotation satırı (yaw burada gömülü)
#define CHR_POS_X_SVR       0x00000000   // ⚠️ NEED_TEST (was 0x408)
#define CHR_POS_Y_SVR       0x00000000   // ⚠️ NEED_TEST (was 0x40c)
#define CHR_POS_X_INT       0x00000000   // ⚠️ NEED_TEST
#define CHR_POS_Y_INT       0x00000000   // ⚠️ NEED_TEST

// --- Rotation / Misc ---
#define CHR_YAW             0x17C        // ⚠️ (was 0x17c; orientation 0x3b0'da da var) NEED_TEST
#define CHR_FLAG            0x28         // ✅ char flag
#define CHR_SPEED           0x00000000   // ❓ (0x7ec runtime hareket float'u; MyInfo alanı değil)
#define CHR_TITLE           0x00000000   // ⚠️ NEED_TEST (was 0x764)
#define CHR_COS_COUNT       0x00000000   // ⚠️ NEED_TEST (was 0x774)
#define CHR_SKILL_BASE      0x250        // ⚠️ NEED_TEST

// --- Party (⚠️ v2613'te re-derive edilmedi) ---
#define CHR_PARTY_MGR       0x20C
#define CHR_PARTY_MEMBERCNT 0x36C
#define CHR_PARTY_ARRAY     0x374
#define PARTY_MEMBER_NEXT   0x00
#define PARTY_MEMBER_ID     0x20
#define PARTY_MEMBER_CLASS  0x28
#define PARTY_MEMBER_HP     0x34
#define PARTY_MEMBER_MAXHP  0x38
#define PARTY_MEMBER_NAME   0x4C

/* ===================================================================
   SKILL POINTS (chain: KO_PTR_DLG → +0x210 → SkillDlg)
   ⚠️ v2613'te re-derive edilmedi (2609 layout varsayımı ile)
   =================================================================== */
#define CGP_SKILL_DLG       0x210
#define SKL_AVAIL           0x160
#define SKL_TREE1           0x174
#define SKL_TREE2           0x178
#define SKL_TREE3           0x17C
#define SKL_MASTER          0x180

/* ===================================================================
   INVENTORY (chain: KO_PTR_DLG(=GameProcMain 0x10fa8fc) → +offset)
   ✅ GameProcMain item container @ +0x1D8 (Agent B doğruladı)
   =================================================================== */
#define CGP_INV_MGR             0x1D8    // ✅ item container (was 2610: 0x218 — şimdi 2609 değeri 0x1d8)
#define INV_EQUIP_START         0x260    // ⚠️ NEED_TEST
#define INV_BAG_START           0x298    // ⚠️ NEED_TEST
#define ITEM_BASE_PTR           0x60
#define ITEM_EXT_PTR            0x64
#define ITEM_COUNT              0x68
#define ITEM_DURABILITY         0x6C
#define ITEMBASIC_ID            0x00
#define ITEMBASIC_NAME          0x08
#define ITEM_UPGRADE_LEVEL      0x00

/* ===================================================================
   BANK / WAREHOUSE  ⚠️ v2613 re-derive edilmedi
   =================================================================== */
#define DLG_WAREHOUSE           0x22C    // ⚠️ 2609 değeri (was 2610: 0x26c)
#define WAREHOUSE_FIRST_ITEM    0x114
#define WAREHOUSE_SLOTS         192
#define DLG_VIPBANK             0x230    // ⚠️ 2609 değeri (was 2610: 0x270)
#define VIPBANK_FIRST_ITEM      0x114
#define VIPBANK_SLOTS           48

/* ===================================================================
   LOGIN UI (from KO_PTR_GameProcIntro → +0x2C → UILoginIntro)
   ⚠️ v2613 re-derive edilmedi
   =================================================================== */
#define UI_LOGIN_INTRO          0x2C
#define UI_EDIT_ID              0x118
#define UI_EDIT_PASS            0x11C
#define UI_EDIT_VALUE           0x134
#define UI_CONNECT_BUTTON       0x120
#define UI_VISIBLE              0xEA
#define UI_FIRST_SERVER         0x254
#define UI_SERVER_OFFSET        0x1C
#define UI_CH_LIST              0x480

/* ===================================================================
   PACKET STRUCTURE (SEND, cipher on)
     [AA 55]   magic header (htons 0xaa55)
     [LL LL]   payload length
     [counter] (KO_PKT_COUNTER, bypass flag yoksa)
     [block#]  (KO_CIPHER_COUNTER, cipher enable ise)
     [data...] XOR stream cipher (key@KO_CIPHER_KEY, PRNG 0x87B/0x86D)
     [CRC32]
     [55 AA]   magic footer (htons 0x55aa)
   =================================================================== */

/* ===================================================================
   ⚙ LEGACY COMPAT — build yeşil kalsın (AddrTest/Blowfish/AutoLogin/
   Heartbeat/KOAesCheck/ClientCommand/KoSkill/ASLRState referansları).
   ⛔ Çoğu v2613 için STALE/0x0 — gerekirse runtime re-derive.
   =================================================================== */
#define KO_AES_IV            0x00000000          // ⛔ XOR cipher'da IV yok
#define KO_SOCK_PTR          KO_PTR_PKT          // aktif socket
#define KO_SOCK_PTR2         0x00000000          // ⛔ NEED_TEST
#define KO_WORLD_MGR         0x010FA830          // ✅ CN3WorldManager (düzeltildi — CHR değil, 0x830)
#define KO_MAKERESP_CB2      0x00000000          // ❓ runtime arama
#define KO_AES_COMPRESS_FLAG 0x00000000          // ⛔ NEED_TEST
#define KO_RECV_SUB_DISP     0x00000000          // ⛔ NEED_TEST
#define KO_RECV_FIX_ADDR     0x00000000          // ⛔ NEED_TEST
#define KO_X3_VALIDATOR      0x00000000          // ⛔ NEED_TEST
#define KO_AES_CBC_FUNC      KO_CRYPT_HANDLER    // → 0x8CE9E0
#define KO_AES_CRYPT_FUNC    KO_CRYPT_WRAP       // → 0x4CD460
#define KO_AES_DECRYPT_FUNC  KO_CRYPT_DECRYPT    // → 0x0 (NEED_TEST)
#define KO_ITEMBASIC_LOOKUP  0x00000000          // ⛔ NEED_TEST
#define KO_OFF_SKILL_DATA    0x214               // ⛔ NEED_TEST
#define KO_OFF_SKILL_ARRAY   0x8C                // ⛔ NEED_TEST
#define KO_OFF_SKILL_COUNT   0x90                // ⛔ NEED_TEST
// x3.xem RUNTIME addrs/scan (ASLR — runtime discovered, stale snapshot)
#define X3_BF_PARRAY_1       0x72AE4A18u         // ⛔ stale runtime VA
#define X3_BF_PARRAY_2       0x72AE9348u         // ⛔ stale runtime VA
#define X3_BF_VTABLE         0x72B06C34u         // ⛔ stale runtime VA
#define X3_SETKEY_B          0x7293726Cu         // ⛔ stale runtime VA
#define X3_CIPHER_SETUP      0x72914E83u         // ⛔ stale runtime VA
#define X3_SCAN_L            0x72800000u         // x3.xem scan range low
#define X3_SCAN_H            0x72E00000u         // x3.xem scan range high

/* === EK LEGACY DUMMY (build-fix) — eski X3/diagnostic semboller === */
#define KO_X3_ISVALID         0x00000000
#define KO_X3_ERR_CB1         0x00000000
#define KO_X3_ERR_CB2         0x00000000
#define KO_X3_ERR_CB3         0x00000000
#define KO_X3_ERR_CB4         0x00000000
#define KO_X3_CB_SLOT         0x00000000
#define KO_X3_CB_SLOT_B       0x00000000
#define KO_X3_INIT_CB         0x00000000
#define KO_X3_GUARD_FLAG      0x00000000
#define KO_X3_MODULE_SLOT     0x00000000
#define KO_X3_ORDINAL1        0x00000000
#define KO_X3_ORDINAL1_OLD    0x00000000
#define KO_X3_HANDLER_1A      0x00000000
#define KO_X3_HMODULE_MM      0x00000000
#define KO_X3_ORDINAL1_MM     0x00000000
#define KO_X3_HANDLER1A_MM    0x00000000
#define KO_X3_CB_SETOPTION    0x00000000
#define KO_X3_CB_STOP         0x00000000
#define KO_X3_CB_UNINIT       0x00000000
#define KO_X3_CB_MAKERESPONSE KO_X3_CALLBACK
#define KO_AES_IV2            0x00000000
#define KO_AES_COMPRESS_CTR   0x00000000
#define KO_RECV_HANDLER       KO_SEND_FUNC
#define KO_SEND_BUF_SIZE      0x00000000
#define KO_DISCONNECT_REASON  0x00000000
#define KO_ZONE_DATA_MGR      0x00000000
#define KO_ITEM_EXT_ARRAY     0x00000000
#define KO_UI_STATE           0x00000000
#define KO_MYINFO_FUNC_OLD    0x00000000
