#pragma once
/* ===================================================================
   KOAddresses.h — Knight Online Pointer & Offset Table
   Version: 2609
   Source:  Static analysis + runtime verification of 2609 unpacked exe
   Migration from: 2605 → 2609
   ===================================================================

   DELTA PATTERNS (2605 → 2609):
     .rdata  : DEĞİŞMEDİ
     .data   : DEĞİŞMEDİ (tüm pointer'lar 2605 ile aynı)
     .text   : DEĞİŞMEDİ (tüm fonksiyonlar 2605 ile aynı)
     struct  : DEĞİŞMEDİ (tek istisna: CHR_POS_Y 0x3D0 → 0x3D4)

   IMPORTANT: 2605 ve 2609 binary neredeyse identical.
     AES KEY: AYNI
     Stolen bytes: AYNI format, SEH handler adresi değişti
       2605: 68 F6 37 ED 00  (handler 0x00ED37F6)
       2609: 68 A6 33 ED 00  (handler 0x00ED33A6)

   CUMULATIVE SHIFTS (2602 baseline):
     .rdata  : +0x1000
     .data   : MIXED (+0x1000 most, +0x1008 for SOCK_PTR/GAME_STATE_MGR cluster)
     .text   : mostly unchanged, KO_MYINFO_FUNC +0x20

   VERIFICATION:
     ✅ CONFIRMED     — runtime peek or static analysis match
     ✅ XREF_VERIFIED — XREF count ile doğrulandı
     ⚠️  NEED_TEST    — runtime doğrulama gerekli
   =================================================================== */

   /* ===================================================================
      STATIC POINTER ADDRESSES
      =================================================================== */

      // ✅ CONFIRMED — 4435 xref
#define KO_PTR_CHR          0x011761A8   // -> CPlayerMySelf base ptr

// ✅ XREF_VERIFIED
#define KO_WORLD_MGR        0x011761A0   // 328 xref
#define KO_ENTITY_LIST      0x011761A4   // 478 xref
#define KO_PTR_DLG          0x011761AC   // 124 xref — Dialog/UI manager
#define KO_PTR_PKT          0x011761B0   // 87 xref

// ✅ CONFIRMED — runtime non-zero (+0x1008 cluster)
#define KO_SOCK_PTR         0x01177628   // -> CAPISocket*
#define KO_SOCK_PTR2        0x0117762C   // ⚠️ NEED_TEST

/* ===================================================================
   AES ENCRYPTION
   KEY BYTES (2602'den beri DEĞİŞMEDİ):
     32 4E AA 58  BC B3 AE E3  6B C7 4C 56  36 47 34 F2
   =================================================================== */

   // ✅ XREF_VERIFIED
#define KO_AES_FLAG         0x011873BA   // BYTE: 0=off, 1=on (7 xref)
#define KO_AES_IV           0x011873BC   // AES CBC IV (8 bytes, dynamic) (5 xref)
#define KO_AES_IV2          0x011873DC

// ✅ CONFIRMED — byte pattern match
#define KO_AES_KEY          0x00F9137C   // AES key (16 bytes, static .rdata)

// ✅ CONFIRMED — runtime value 238, valid range (+0x1008 cluster)
#define KO_PKT_COUNTER      0x01177601   // Packet counter (BYTE, 1-250)
#define KO_PKT_BYPASS_FLAG  0x01177602

// ✅ XREF_VERIFIED
#define KO_AES_COMPRESS_FLAG 0x011873B0
#define KO_AES_COMPRESS_CTR  0x011873B4

/* ===================================================================
   SEND / RECV
   =================================================================== */

   // ✅ CONFIRMED — .text unchanged
#define KO_SEND_FUNC        0x0061E5D0
#define KO_RECV_HANDLER     0x0061E5D0
#define KO_RECV_DISPATCH    0x00706C60   // "Current Zone" XREF confirmed
#define KO_RECV_SUB_DISP    0x0072EAA0
#define KO_RECV_FIX_ADDR    0x00706C50

// ✅ CONFIRMED — .text unchanged
#define KO_AES_CBC_FUNC     0x0061AEB0

// ⚠️ NEED_TEST — AES bölgesi 2604'te restructured, 2605-2609 aynı
#define KO_AES_CRYPT_FUNC   0x00834F23
#define KO_AES_DECRYPT_FUNC 0x00834E63

// ⚠️ NEED_TEST
#define KO_SEND_BUF_PTR     0x01187418
#define KO_SEND_BUF_SIZE    0x01187414

/* ===================================================================
   DISCONNECT
   =================================================================== */

   // ✅ CONFIRMED — runtime 0 when connected
#define KO_DISCONNECT_FLAG   0x011775F4
#define KO_DISCONNECT_REASON 0x011775F5
#define KO_DISCONNECT_ERR    0x011775F6

/* ===================================================================
   X3 / XIGNCODE
   =================================================================== */

   // ✅ CONFIRMED — .text unchanged
#define KO_X3_VALIDATOR     0x00710D60
#define KO_X3_LOADER        0x00712060

// ✅ CONFIRMED — prologue 81 EC 08 06 00 00
#define KO_MAKERESP_CB      0x00711090
#define KO_MAKERESP_CB2     0x00711180
#define KO_HB_HANDLER       0x0070712D

// ✅ CONFIRMED — runtime: xst MakeResponse ptr
#define KO_X3_CALLBACK      0x011776B0
#define KO_X3_CB_MAKERESPONSE 0x011776B0

// ✅ XREF_VERIFIED
#define KO_X3_HMODULE       0x010F8380   // 12 XREFs
#define KO_X3_ORD1          0x010F8384   // 8 XREFs
#define KO_X3_CB_SETOPTION  0x010F8388   // 3 XREFs
#define KO_X3_CB_STOP       0x01175E78   // 3 XREFs

// ✅ CONFIRMED — runtime: x3_base + 0x13F0
#define KO_X3_CB_INIT       0x011776A8

// ⚠️ NEED_TEST
#define KO_X3_CB_UNINIT     0x011A78B8
#define KO_X3_ISVALID       0x00710740
#define KO_X3_ERR_CB1       0x00710A80
#define KO_X3_ERR_CB2       0x00710A90
#define KO_X3_ERR_CB3       0x00710B10
#define KO_X3_ERR_CB4       0x00710B30

// ⚠️ NEED_TEST — legacy slots
#define KO_X3_CB_SLOT       0x011766B0
#define KO_X3_CB_SLOT_B     0x01173E78
#define KO_X3_INIT_CB       0x011756A8
#define KO_X3_GUARD_FLAG    0x011755ED
#define KO_X3_MODULE_SLOT   0x010F6380
#define KO_X3_ORDINAL1_OLD  0x010F6384
#define KO_X3_ORDINAL1  0x010F6384
#define KO_X3_HANDLER_1A    0x010F6388
#define KO_X3_HMODULE_MM    0x010F7380
#define KO_X3_ORDINAL1_MM   0x010F7384
#define KO_X3_HANDLER1A_MM  0x010F7388

/* ===================================================================
   XST.XEM — ASLR shift = runtime_sbox - XST_IDA_SBOX
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
      X3.XEM — Static addresses (binary unchanged)
      =================================================================== */

#define X3_BF_PARRAY_1      0x72AE4A18u  // ⚠️ WRONG VA
#define X3_BF_PARRAY_2      0x72AE9348u  // ⚠️ WRONG VA
#define X3_BF_VTABLE        0x72B06C34u
#define X3_SETKEY_B         0x7293726Cu
#define X3_CIPHER_SETUP     0x72914E83u
#define X3_SCAN_L           0x72800000u
#define X3_SCAN_H           0x72E00000u

      /* ===================================================================
         GAME DATA MANAGERS
         =================================================================== */

         // ✅ XREF_VERIFIED
#define KO_ITEM_TABLE_MGR   0x01175FB0   // 273 XREFs
#define KO_ZONE_DATA_MGR    0x01175FA0   // 31 XREFs
#define KO_ITEM_EXT_ARRAY   0x01175FB8   // 196 XREFs

// ✅ CONFIRMED — runtime non-zero, 4927 XREFs (+0x1008 cluster)
#define KO_GAME_STATE_MGR   0x01177654
#define KO_PTR_SKILL_MGR    0x01177654

// ✅ CONFIRMED — runtime non-zero (+0x1008 cluster)
#define KO_UI_STATE         0x0117767C   // 177 XREFs

/* ===================================================================
   FUNCTIONS
   =================================================================== */

   // ✅ CONFIRMED — .text unchanged
#define KO_MYINFO_FUNC      0x00733730   // 154 xref to KO_PTR_CHR
#define KO_ITEMBASIC_LOOKUP 0x0062E6E0

/* ===================================================================
   CHARACTER OFFSETS (from KO_PTR_CHR base)
   2605 ile AYNI — tek değişiklik: CHR_POS_Y 0x3D0 → 0x3D4
   =================================================================== */

   // --- Identity ---
#define CHR_PLAYER_ID       0x6A0
#define CHR_NAME            0x6A4
#define CHR_TARGETID        0x660

// --- Class / Race ---
#define CHR_NATION          0x6C4
#define CHR_RACE            0x6C0
#define CHR_JOB             0x6CC

// --- Level / HP ---
#define CHR_LEVEL           0x6D0
#define CHR_CUR_HP          0x6D4
#define CHR_MAX_HP          0x6D8

// --- MP / Stat Points ---
#define CHR_STAT_PT         0xBE4
#define CHR_MAX_MP          0xBEC
#define CHR_CUR_MP          0xBF0

// --- Gold / XP ---
#define CHR_GOLD            0xBFC
#define CHR_MAX_XP          0xC00
#define CHR_CUR_XP          0xC08

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
#define CHR_POS_Y           0x3D4        // ⚠️ 2609'da DEĞİŞTİ (2605: 0x3D0)
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
   SKILL POINTS (chain: KO_GAME_STATE_MGR → +0x210 → SkillDlg)
   =================================================================== */
#define CGP_SKILL_DLG       0x210
#define SKL_AVAIL           0x160
#define SKL_TREE1           0x174
#define SKL_TREE2           0x178
#define SKL_TREE3           0x17C
#define SKL_MASTER          0x180

   /* ===================================================================
      INVENTORY (chain: KO_GAME_STATE_MGR → +0x1D8 → InventoryMgr)
      =================================================================== */
#define CGP_INV_MGR         0x1D8
#define INV_EQUIP_START     0x260
#define INV_BAG_START       0x298
#define ITEM_BASE_PTR       0x60
#define ITEM_EXT_PTR        0x64
#define ITEM_COUNT          0x68
#define ITEM_DURABILITY     0x6C

      /* ===================================================================
         BANK / WAREHOUSE
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
            HOOK — STOLEN BYTES

            KO_RECV_DISPATCH @ 0x00706C60:
              2609: 55 8B EC 6A FF 68 A6 33 ED 00  (SEH handler: 0x00ED33A6)
              Trampoline: 5 byte çal (55 8B EC 6A FF) + JMP back

            KO_MAKERESP_CB @ 0x00711090:
              81 EC 08 06 00 00  (sub esp,0x608 — SEH yok, değişmedi)
            =================================================================== */

            /* ===================================================================
               PACKET STRUCTURE (UNCHANGED)
               [AA 55] [LL LL] [CC] [data..] [55 AA]
               AES KEY: 32 4E AA 58 BC B3 AE E3 6B C7 4C 56 36 47 34 F2
               =================================================================== */