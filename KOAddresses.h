#pragma once
/* ===================================================================
   KOAddresses.h — Knight Online Pointer & Offset Table
   Version: 2605
   Source:  Static analysis + runtime verification of KnightOnLine_unpacked.exe (2605)
   Migration from: 2604 → 2605 (patch May 2026)
   ===================================================================

   DELTA PATTERNS (2604 → 2605):
     .rdata  : +0x1000 (uniform)
     .data   : KARIŞIK! 8 byte insert var:
               0x010Fxxxx..0x01175xxx bölgesi = +0x1000
               0x01176xxx bölgesi = +0x1000 (bazı) veya +0x1008 (bazı)
               Her adres ayrı doğrulandı, aşağıda belirtildi.
     .text   : DEĞİŞMEDİ (tek istisna: KO_MYINFO_FUNC +0x20)
               KO_AES_CRYPT_FUNC bölgesi yeniden yapılandırıldı

   IMPORTANT: Stolen bytes 2604 ile AYNI. SEH prologue'lar değişmedi.
     KO_RECV_DISPATCH: 55 8B EC 6A FF  (5 byte, E9 JMP için yeterli)

   VERIFICATION:
     ✅ CONFIRMED     — runtime peek ile doğrulandı
     ✅ XREF_VERIFIED — XREF count ile doğrulandı (güçlü)
     ⚠️  NEED_TEST    — runtime doğrulama gerekli
   =================================================================== */

   /* ===================================================================
      STATIC POINTER ADDRESSES  (.data +0x1000)
      =================================================================== */

      // ✅ CONFIRMED — runtime: 0x30A7CC00 (non-zero, info çalışıyor)
#define KO_PTR_CHR          0x011761A8   // -> CPlayerMySelf base ptr (+0x1000)

// ✅ XREF_VERIFIED — komşu global'lar (+0x1000)
#define KO_WORLD_MGR        0x011761A0   // 328 xref
#define KO_ENTITY_LIST      0x011761A4   // 478 xref
#define KO_PTR_DLG          0x011761AC   // 124 xref
#define KO_PTR_PKT          0x011761B0   // 87 xref

// ✅ CONFIRMED — runtime: non-zero (+0x1008!)
#define KO_SOCK_PTR         0x01177628   // -> CAPISocket* (+0x1008, NOT +0x1000!)
#define KO_SOCK_PTR2        0x0117762C   // ⚠️ NEED_TEST (+0x1008 assumed, adjacent)

/* ===================================================================
   AES ENCRYPTION
   =================================================================== */

   // ✅ XREF_VERIFIED — 7 xref (+0x1000)
#define KO_AES_FLAG         0x011873BA   // AES active (BYTE: 0=off, 1=on)

// ✅ XREF_VERIFIED — 5 xref (+0x1000)
#define KO_AES_IV           0x011873BC   // AES CBC IV (8 bytes, dynamic)
#define KO_AES_IV2          0x011873DC   // AES CBC IV part 2

// ✅ CONFIRMED — byte pattern match (.rdata +0x1000)
// AES KEY BYTES (2602'DEN DEĞİŞMEDİ):
//   32 4E AA 58  BC B3 AE E3  6B C7 4C 56  36 47 34 F2
#define KO_AES_KEY          0x00F9137C   // AES key (16 bytes, static .rdata)

// ✅ CONFIRMED — runtime: 238 (0xEE), valid range 1-250 (+0x1008!)
#define KO_PKT_COUNTER      0x01177601   // Packet counter (+0x1008, NOT +0x1000!)
#define KO_PKT_BYPASS_FLAG  0x01177602   // Skip counter+padding (+0x1008)

// ✅ XREF_VERIFIED (+0x1000)
#define KO_AES_COMPRESS_FLAG 0x011873B0  // Compression flag
#define KO_AES_COMPRESS_CTR  0x011873B4  // Compression counter

/* ===================================================================
   SEND / RECV  (.text UNCHANGED)
   =================================================================== */

   // ✅ CONFIRMED — .text SAME
#define KO_SEND_FUNC        0x0061E5D0   // Send function
#define KO_RECV_HANDLER     0x0061E5D0   // Recv packet handler

// ✅ CONFIRMED — .text SAME
// Stolen bytes: 55 8B EC 6A FF → E9 rel32
#define KO_RECV_DISPATCH    0x00706C60   // recv opcode router

// ✅ CONFIRMED — .text SAME
#define KO_RECV_SUB_DISP    0x0072EAA0   // CGameProcMain::ProcessRecvPacket

// ⚠️ NEED_TEST — +0x1000 had 12 xref, +0x1008 had 3
#define KO_SEND_BUF_PTR     0x01187418   // Send buffer pointer (+0x1000)
#define KO_SEND_BUF_SIZE    0x01187414   // Send buffer capacity (+0x1000)

// ⚠️ MAYBE — AES bölgesi yeniden yapılandırıldı
//   AES KEY XREF ile bulunan fn'ler: 0x00834E63, 0x00834F23, 0x00834FF0
#define KO_AES_CRYPT_FUNC   0x00834F23   // ⚠️ RESTRUCTURED
#define KO_AES_DECRYPT_FUNC 0x00834E63   // ⚠️ RESTRUCTURED

// ✅ CONFIRMED — .text SAME
#define KO_AES_CBC_FUNC     0x0061AEB0   // AES-CBC core

/* ===================================================================
   DISCONNECT  (.data +0x1000)
   =================================================================== */

   // ✅ CONFIRMED — runtime: 0 (bağlı = disconnect yok) (+0x1000)
#define KO_DISCONNECT_FLAG   0x011775F4   // Disconnect state byte 1
#define KO_DISCONNECT_REASON 0x011775F5   // Disconnect reason
#define KO_DISCONNECT_ERR    0x011775F6   // Disconnect error code

/* ===================================================================
   X3 / XIGNCODE
   =================================================================== */

   // ✅ CONFIRMED — .text SAME
#define KO_X3_VALIDATOR     0x00710D60

// ✅ CONFIRMED — runtime: 0x0DFF5ED0 (xst MakeResponse ptr) (+0x1000)
#define KO_X3_CALLBACK      0x011776B0   // X3 challenge callback pointer

// ✅ CONFIRMED — .text SAME, prologue 81 EC 08 06 00 00
#define KO_MAKERESP_CB      0x00711090   // MakeResponse callback

// ✅ CONFIRMED — .text SAME
#define KO_MAKERESP_CB2     0x00711180   // ko_cb (2nd callback)
#define KO_HB_HANDLER       0x0070712D   // 0xA0 heartbeat packet handler

// ⚠️ NEED_TEST — (+0x1000)
#define KO_X3_CB_SLOT       0x011766B0   // DAT: xst.xem MakeResponse ptr (cmd=6 slot)
#define KO_X3_CB_SLOT_B     0x01173E78   // DAT: ikincil x3 callback slot
#define KO_X3_INIT_CB       0x011756A8   // DAT: x3 init callback
#define KO_X3_GUARD_FLAG    0x011755ED   // BYTE: x3 init-complete guard flag

// ⚠️ NEED_TEST — .text SAME
#define KO_RECV_FIX_ADDR    0x00706C50
#define KO_X3_ISVALID       0x00710740
#define KO_X3_ERR_CB1       0x00710A80
#define KO_X3_ERR_CB2       0x00710A90
#define KO_X3_ERR_CB3       0x00710B10   // ⚠️ may be GONE
#define KO_X3_ERR_CB4       0x00710B30

// ⚠️ NEED_TEST — x3.xem HMODULE slots (.data +0x1000)
#define KO_X3_MODULE_SLOT   0x010F6380
#define KO_X3_ORDINAL1   0x010F6380
#define KO_X3_ORDINAL1_OLD  0x010F6384
#define KO_X3_HANDLER_1A    0x010F6388

// ⚠️ NEED_TEST — KoMemMap era (+0x1000)
#define KO_X3_HMODULE_MM    0x010F7380
#define KO_X3_ORDINAL1_MM   0x010F7384
#define KO_X3_HANDLER1A_MM  0x010F7388

// ✅ XREF_VERIFIED — Ghidra confirmed (+0x1000)
#define KO_X3_HMODULE       0x010F8380   // 12 XREFs ✅
#define KO_X3_ORD1          0x010F8384   // 8 XREFs ✅
#define KO_X3_CB_SETOPTION  0x010F8388   // 3 XREFs ✅
#define KO_X3_CB_STOP       0x01175E78   // 3 XREFs ✅ (+0x1000)

// ✅ CONFIRMED — runtime: 0x596913F0 (x3_base + 0x13F0) (+0x1000)
#define KO_X3_CB_INIT       0x011776A8   // Init callback (cmd 0x01)

// ✅ CONFIRMED — runtime: 0x0DFF5ED0 (xst MakeResponse) (+0x1000)
#define KO_X3_CB_MAKERESPONSE 0x011776B0 // MakeResponse callback (cmd 0x06)

// ⚠️ NEED_TEST — (+0x1000)
#define KO_X3_CB_UNINIT     0x011A78B8   // Uninit callback (cmd 0x02)

/* ===================================================================
   X3.XEM — Static addresses (x3.xem binary UNCHANGED)
   =================================================================== */

#define X3_BF_PARRAY_1      0x72AE4A18u  // ⚠️ WRONG VA — needs re-scan
#define X3_BF_PARRAY_2      0x72AE9348u  // ⚠️ WRONG VA — needs re-scan
#define X3_BF_VTABLE        0x72B06C34u
#define X3_SETKEY_B         0x7293726Cu
#define X3_CIPHER_SETUP     0x72914E83u
#define X3_SCAN_L           0x72800000u
#define X3_SCAN_H           0x72E00000u

   /* ===================================================================
      XST.XEM — IDA static reference addresses — UNCHANGED
      =================================================================== */

#define XST_IDA_SBOX            0x149D43E0u
#define XST_IDA_SBOX_VTCHASE    0x14BF43E0u
#define XST_IDA_ENCRYPT_FUNC    0x148BF246u
#define XST_IDA_DISPATCH        0x1486CE38u

#define XST_IDA_SBOX_DW         0x14BB43E0u
#define XST_IDA_ENCRYPT_DW      0x14A9F246u
#define XST_IDA_DISPATCH_DW     0x14A4CE38u

#define XST_SBOX_TO_ENCRYPT     0x232ACEu
#define XST_SBOX_TO_CABC4       0x19D67E4u

#define XST_RANGE_NARROW_L      0x14800000u
#define XST_RANGE_NARROW_H      0x15200000u
#define XST_RANGE_WIDE_L        0x0E000000u
#define XST_RANGE_WIDE_H        0x18000000u
#define XST_RANGE_MAX_L         0x08000000u
#define XST_RANGE_MAX_H         0x1F000000u
#define XST_SCAN_L              0x14000000u
#define XST_SCAN_H              0x17000000u
#define XST_DW_SCAN_H           0x16000000u
#define XST_DW_RANGE_LOW_L      0x0E000000u
#define XST_DW_RANGE_LOW_H      0x10000000u
#define XST_DW_RANGE_MID_L      0x14000000u
#define XST_DW_RANGE_MID_H      0x18000000u
#define XST_DW_RANGE_EXT_L      0x1A000000u
#define XST_DW_RANGE_EXT_H      0x1C000000u

      /* ===================================================================
         GAME DATA MANAGERS
         =================================================================== */

         // ✅ XREF_VERIFIED (+0x1000)
#define KO_ITEM_TABLE_MGR   0x01175FB0   // 273 XREFs
#define KO_ZONE_DATA_MGR    0x01175FA0   // 31 XREFs
#define KO_ITEM_EXT_ARRAY   0x01175FB8   // 196 XREFs

// ✅ CONFIRMED — runtime: non-zero (+0x1008!)
#define KO_GAME_STATE_MGR   0x01177654   // 4927 XREFs ✅ (+0x1008, NOT +0x1000!)
#define KO_PTR_SKILL_MGR    0x01177654   // same DAT

// ✅ CONFIRMED — runtime: non-zero (+0x1008!)
#define KO_UI_STATE         0x0117767C   // 177 XREFs ✅ (+0x1008!)

/* ===================================================================
   FUNCTIONS
   =================================================================== */

   // ✅ XREF_VERIFIED — 154 xref, MOVED +0x20 from 2604
#define KO_MYINFO_FUNC      0x00733730   // MsgRecv_MyInfo_All

// ✅ CONFIRMED — .text SAME
#define KO_ITEMBASIC_LOOKUP 0x0062E6E0
#define KO_X3_LOADER        0x00712060

/* ===================================================================
   CHARACTER OFFSETS (from KO_PTR_CHR base)
   UNCHANGED — struct layout değişmedi, XREF count doğrulandı.
   =================================================================== */

   // --- Identity ---
#define CHR_PLAYER_ID       0x6A0
#define CHR_NAME            0x6A4
#define CHR_TARGETID        0x660

// --- Class / Race ---
#define CHR_NATION          0x6C4
#define CHR_RACE            0x6C0
#define CHR_JOB             0x6CC

// --- Level / Stats ---
#define CHR_LEVEL           0x6D0
#define CHR_CUR_HP          0x6D4
#define CHR_MAX_HP          0x6D8

// --- MP / Stat Points ---
#define CHR_STAT_PT         0xBE4
#define CHR_MAX_MP          0xBEC
#define CHR_CUR_MP          0xBF0

// --- Gold / XP ---
#define CHR_GOLD            0xBFC
#define CHR_MAX_XP          0xC00   // QWORD
#define CHR_CUR_XP          0xC08   // QWORD

// --- Attributes ---
#define CHR_STR             0xC24
#define CHR_STR_EXTRA       0xC28
#define CHR_HP_STAT         0xC2C
#define CHR_HP_EXTRA        0xC30
#define CHR_DEX             0xC34
#define CHR_DEX_EXTRA       0xC38
#define CHR_INT             0xC3C
#define CHR_INT_EXTRA       0xC40
#define CHR_MP_STAT         0xC44
#define CHR_MP_EXTRA        0xC48
#define CHR_ATTACK          0xC4C
#define CHR_DEFENCE         0xC54

// --- Zone / Position ---
#define CHR_ZONE            0xC90
#define CHR_ZONE_SUB        0xC94
#define CHR_POS_X_INT       0xC18
#define CHR_POS_Y_INT       0xC20
#define CHR_POS_X           0x3CC
#define CHR_POS_Y           0x3D0
#define CHR_POS_X_SVR       0x408
#define CHR_POS_Y_SVR       0x40C

// --- Misc ---
#define CHR_TITLE           0x764
#define CHR_COS_COUNT       0x774

// --- Party / Social ---
#define CHR_PARTY_MGR       0x20C
#define CHR_PARTY_ACTIVE    0x105F
#define CHR_SPEED_MODE      0x1064
#define CHR_SPEED_MULT      0x1068

// --- Skill Data ---
#define KO_OFF_SKILL_DATA   0x214
#define KO_OFF_SKILL_ARRAY  0x8C
#define KO_OFF_SKILL_COUNT  0x90

/* ===================================================================
   PACKET STRUCTURE (UNCHANGED)
   AES KEY: 32 4E AA 58  BC B3 AE E3  6B C7 4C 56  36 47 34 F2
   =================================================================== */

   /* ===================================================================
      SKILL POINTS — UNCHANGED
      =================================================================== */
#define CGP_SKILL_DLG       0x210
#define SKL_AVAIL           0x160
#define SKL_TREE1           0x174
#define SKL_TREE2           0x178
#define SKL_TREE3           0x17C
#define SKL_MASTER          0x180

      /* ===================================================================
         INVENTORY — UNCHANGED
         =================================================================== */
#define CGP_INV_MGR         0x1D8
#define INV_EQUIP_START     0x260
#define INV_BAG_START       0x298
#define ITEM_BASE_PTR       0x60
#define ITEM_EXT_PTR        0x64
#define ITEM_COUNT          0x68
#define ITEM_DURABILITY     0x6C

         /* ===================================================================
            BANK / WAREHOUSE — UNCHANGED
            =================================================================== */
#define DLG_WAREHOUSE           0x22C
#define WAREHOUSE_FIRST_ITEM    0x114
#define WAREHOUSE_SLOTS         192
#define DLG_VIPBANK             0x230
#define VIPBANK_FIRST_ITEM      0x114
#define VIPBANK_SLOTS           48
#define ITEM_UPGRADE_LEVEL      0x00
#define ITEMBASIC_NAME          0x08

            /* ===================================================================
               HOOK — STOLEN BYTES (2604 ile AYNI)
               KO_RECV_DISPATCH @ 0x00706C60: 55 8B EC 6A FF 68 F6 37 ED 00
               KO_MAKERESP_CB: sub esp prologue (SEH yok)
               =================================================================== */

               /* ===================================================================
                  2605 SHIFT SUMMARY

                  +0x1000 (standard):
                    KO_PTR_CHR, ENTITY_LIST, PTR_DLG, PTR_PKT, WORLD_MGR
                    KO_X3_HMODULE, X3_ORD1, X3_CB_STOP, X3_CB_INIT, X3_CALLBACK
                    KO_AES_FLAG, AES_IV, AES_KEY, AES_COMPRESS_*
                    KO_ITEM_TABLE_MGR, ZONE_DATA_MGR, ITEM_EXT_ARRAY
                    KO_DISCONNECT_FLAG/REASON/ERR
                    KO_SEND_BUF_PTR/SIZE, X3_CB_UNINIT

                  +0x1008 (8-byte insert):
                    KO_SOCK_PTR           0x01176620 → 0x01177628
                    KO_GAME_STATE_MGR     0x0117664C → 0x01177654
                    KO_PTR_SKILL_MGR      (= GAME_STATE_MGR)
                    KO_UI_STATE            0x01176674 → 0x0117767C
                    KO_PKT_COUNTER        0x011765F9 → 0x01177601
                    KO_PKT_BYPASS_FLAG    0x011765FA → 0x01177602
                  =================================================================== */