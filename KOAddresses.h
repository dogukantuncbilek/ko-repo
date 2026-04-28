#pragma once
/* ===================================================================
   KOAddresses.h — Knight Online Pointer & Offset Table
   Version: 2604
   Source:  Static analysis of KnightOnLine_unpacked.exe (2604, 18.9 MB)
   Migration from: 2602 → 2604 (patch April 2026)
   ===================================================================

   DELTA PATTERNS (2602 → 2604):
     .rdata  : +0x1000 (uniform)
     .data   : +0x1000 (uniform, XREF-verified)
     .text   : per-function
               0x00401000..0x00720000 = +0x10  (SEH prologue eklendi)
               0x00720000+            = +0x260 (yeni kod insert)
               KO_ITEMBASIC_LOOKUP    = -0x10  (istisnai)
               KO_AES_CRYPT_FUNC bölgesi tamamen yeniden yapılandı

   IMPORTANT: SEH prologue tüm major fonksiyonlara eklendi.
     Stolen bytes 2602'de geçersiz. KO_RECV_DISPATCH:
       Eski (2602): 53 55 56 8B 74 24 14  (7 byte)
       Yeni (2604): 55 8B EC 6A FF         (5 byte, E9 JMP için yeterli)
     Trampoline bu 5 byte'ı + SEH setup'ı çalıştırmalı.

   VERIFICATION:
     ✅ CONFIRMED     — static analysis match
     ✅ XREF_VERIFIED — XREF count ile doğrulandı
     ⚠️  NEED_TEST    — runtime doğrulama gerekli
     ⚠️  MAYBE        — candidate, netleştirilmedi
   =================================================================== */

/* ===================================================================
   STATIC POINTER ADDRESSES  (.data +0x1000)
   =================================================================== */

// ✅ XREF_VERIFIED — 4432 xref
#define KO_PTR_CHR          0x011751A8   // -> CPlayerMySelf base ptr

// ✅ XREF_VERIFIED — komşu global'lar
#define KO_WORLD_MGR        0x011751A0   // -> World/Camera manager (328 xref)
#define KO_ENTITY_LIST      0x011751A4   // -> Entity list (478 xref)
#define KO_PTR_DLG          0x011751AC   // -> Dialog/UI manager (124 xref)
#define KO_PTR_PKT          0x011751B0   // -> Packet manager (87 xref)

// ✅ CONFIRMED — AES fn body ref
#define KO_SOCK_PTR         0x01176620   // -> Main socket object ptr (CAPISocket*)
#define KO_SOCK_PTR2        0x01176624   // -> Secondary socket ptr

/* ===================================================================
   AES ENCRYPTION  (.data +0x1000, .rdata +0x1000)
   =================================================================== */

// ✅ XREF_VERIFIED — 7 xref
#define KO_AES_FLAG         0x011863BA   // AES active (BYTE: 0=off, 1=on)

// ✅ XREF_VERIFIED — 5 xref
#define KO_AES_IV           0x011863BC   // AES CBC IV (8 bytes, dynamic)
#define KO_AES_IV2          0x011863DC   // AES CBC IV part 2

// ✅ CONFIRMED — byte pattern match (.rdata +0x1000)
// AES KEY BYTES 2604 (2602'DEN DEĞİŞMEDİ):
//   32 4E AA 58  BC B3 AE E3  6B C7 4C 56  36 47 34 F2
#define KO_AES_KEY          0x00F9037C   // AES key (16 bytes, static .rdata)

// ✅ XREF_VERIFIED — 4 xref
#define KO_PKT_COUNTER      0x011765F9   // Packet counter (BYTE, 1-250, wraps)
#define KO_PKT_BYPASS_FLAG  0x011765FA   // Skip counter+padding when set

// ✅ CONFIRMED — AES fn body ref
#define KO_AES_COMPRESS_FLAG 0x011863B0  // Compression flag (0=none)
#define KO_AES_COMPRESS_CTR  0x011863B4  // Compression counter

/* ===================================================================
   SEND / RECV
   =================================================================== */

// ✅ CONFIRMED — "[Invalid packet]" XREF fn start
// ⚠️ NOT: 0x0061E5C0 (2602 adresi) artık JMP thunk → başka fonksiyon.
//          Gerçek handler 0x0061E5D0.
// Prologue 2604: 55 8B EC 6A FF 68 82 67 EB 00  (SEH handler: 0x00EB6782)
#define KO_SEND_FUNC        0x0061E5D0   // Send function
#define KO_RECV_HANDLER     0x0061E5D0   // Recv packet handler (this=CAPISocket*)

// ✅ CONFIRMED — "Current Zone" XREF + 0xA0 case
// Prologue 2604: 55 8B EC 6A FF 68 06 26 ED 00  (SEH handler: 0x00ED2606)
// ⚠️ STOLEN BYTES DEĞİŞTİ: eski "53 55 56 8B 74 24 14" (7B) GEÇERSİZ.
//    Yeni 5-byte patch: 55 8B EC 6A FF → E9 rel32 + 1 NOP
#define KO_RECV_DISPATCH    0x00706C60   // recv opcode router

// ✅ XREF_VERIFIED — 43 xref (.text bölge B, delta +0x260)
#define KO_RECV_SUB_DISP    0x0072EAA0   // CGameProcMain::ProcessRecvPacket

// ✅ CONFIRMED — fn body ref
#define KO_SEND_BUF_PTR     0x01186418   // Send buffer pointer
#define KO_SEND_BUF_SIZE    0x01186414   // Send buffer capacity

// ⚠️ MAYBE — AES bölgesi ikiye bölünmüş olabilir (2602'de unified idi).
//   0x00834CF0 = daha karmaşık (compression counter kullanıyor) → muhtemelen ENCRYPT
//   0x00834C30 = daha basit (sadece sendbuf ref) → muhtemelen DECRYPT
//   Runtime doğrulama: town komutu gönder, hangisi tetikleniyor bak.
#define KO_AES_CRYPT_FUNC   0x00834CF0   // MAYBE encrypt path (sub esp,0x100 + flag check)
#define KO_AES_DECRYPT_FUNC 0x00834C30   // MAYBE decrypt path

// ✅ CONFIRMED — prologue 83 EC 5C A1 C0 86 ... (+0x10)
#define KO_AES_CBC_FUNC     0x0061AEB0   // AES-CBC core

/* ===================================================================
   DISCONNECT  (.data +0x1000)
   =================================================================== */

// ✅ XREF_VERIFIED — 4 xref
#define KO_DISCONNECT_FLAG   0x011765F4   // Disconnect state byte 1
#define KO_DISCONNECT_REASON 0x011765F5   // Disconnect reason (0=normal,2=error,3=X3)
#define KO_DISCONNECT_ERR    0x011765F6   // Disconnect error code

/* ===================================================================
   X3 / XIGNCODE
   =================================================================== */

// ✅ CONFIRMED — "x3.xem" string XREF fn start
// Prologue 2604: 55 8B EC 6A FF 68 62 35 ED 00  (SEH handler: 0x00ED3562)
#define KO_X3_VALIDATOR     0x00710D60   // Checks x3.xem loaded + xhunter1 registry

// ✅ XREF_VERIFIED — 6 xref
#define KO_X3_CALLBACK      0x011766B0   // X3 challenge callback pointer

// ✅ CONFIRMED — prologue 81 EC 08 06 00 00 (sub esp,0x608) — SEH YOK
#define KO_MAKERESP_CB      0x00711090   // MakeResponse callback (spinhook/vtkhook hedef)

// ✅ CONFIRMED — prologue 81 EC 28 01 00 00 (sub esp,0x128) — SEH YOK
#define KO_MAKERESP_CB2     0x00711180   // ko_cb (2nd callback in chain)

// ✅ CONFIRMED — dispatch+0x4CD offset (case 0xA0 branch), +0x10
#define KO_HB_HANDLER       0x0070712D   // 0xA0 heartbeat packet handler

// ⚠️ NEED_TEST — vtkhook session 50'de runtime-verified, XREF doğrulaması yapılmadı
#define KO_X3_CB_SLOT       0x011756B0   // DAT: xst.xem MakeResponse ptr (cmd=6 slot)
#define KO_X3_CB_SLOT_B     0x01172E78   // DAT: ikincil x3 callback slot
#define KO_X3_INIT_CB       0x011746A8   // DAT: x3 init callback
#define KO_X3_GUARD_FLAG    0x011745ED   // BYTE: x3 init-complete guard flag

// ⚠️ NEED_TEST — fixrecv hedef (KO_RECV_DISPATCH öncesi entry)
#define KO_RECV_FIX_ADDR    0x00706C50

// ⚠️ NEED_TEST — X3 internal check/validator functions (2604, unverified)
#define KO_X3_ISVALID       0x00710740   // x3 validator (patched → MOV EAX,1; RET)
#define KO_X3_ERR_CB1       0x00710A80   // x3 error code check 1
#define KO_X3_ERR_CB2       0x00710A90   // x3 error code check 2
#define KO_X3_ERR_CB3       0x00710B10   // x3 error code check 3
#define KO_X3_ERR_CB4       0x00710B30   // x3 error code check 4

// ⚠️ NEED_TEST — x3.xem HMODULE slots (KO.exe .data, 2604 active)
#define KO_X3_MODULE_SLOT   0x010F5380   // x3.xem HMODULE
#define KO_X3_ORDINAL1      0x010F5384   // x3.xem ordinal 1
#define KO_X3_HANDLER_1A    0x010F5388   // x3.xem handler 1A

// ⚠️ NEED_TEST — x3.xem HMODULE slots (KoMemMap, possibly 2602 era)
#define KO_X3_HMODULE_MM    0x010f6380   // x3.xem HMODULE (KoMemMap snapshot)
#define KO_X3_ORDINAL1_MM   0x010f6384
#define KO_X3_HANDLER1A_MM  0x010f6388

/* ===================================================================
   X3.XEM — Static addresses (x3.xem loads at FIXED base 0x72900000)
   Source: bigdump_0x72900000 analizi (session 45 + 2604 analizi)
   x3.xem binary UNCHANGED (SizeOfImage 0x0053D000)
   =================================================================== */

// x3.xem default BF P-array (statik init sabiti, keyed context değil)
// ⚠️ WRONG — runtime dump'ta bu adresler .text (kod) gösteriyor.
//    bigdump raw file offset ≠ VA (FIX=-219 x3.xem kendi sectionlarına uygulanmamış).
//    vtkhook ile runtime key capture hedeflendiği için kritik değil.
//    Düzeltme: x3.xem .rdata section RVA'ya bakıp doğru offset hesaplanmalı.
#define X3_BF_PARRAY_1      0x72AE4A18u  // ⚠️ WRONG VA — needs re-scan
#define X3_BF_PARRAY_2      0x72AE9348u  // ⚠️ WRONG VA — needs re-scan

// x3.xem BF context vtable (x3.xem@0x72900000 iken sabit)
#define X3_BF_VTABLE        0x72B06C34u  // vtable ptr değeri (BF ctx objelerinde)

// x3.xem setkey_B (key schedule — 6 caller, heartbeat processing içinde)
// [ebp+8] = key parametresi
#define X3_SETKEY_B         0x7293726Cu
#define X3_CIPHER_SETUP     0x72914E83u  // setkey_B chain'ini çağıran tek fn

// x3.xem tarama aralıkları
#define X3_SCAN_L           0x72800000u
#define X3_SCAN_H           0x72E00000u

/* ===================================================================
   XST.XEM — IDA static reference addresses
   UNCHANGED from 2602 (x3.xem binary aynı)
   ASLR shift = runtime_sbox - XST_IDA_SBOX
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
   GAME DATA MANAGERS  (.data +0x1000)
   =================================================================== */

#define KO_ITEM_TABLE_MGR   0x01174FB0   // ItemBasic std::map tree root
#define KO_ZONE_DATA_MGR    0x01174FA0   // Zone data manager
#define KO_ITEM_EXT_ARRAY   0x01174FB8   // Item extension table array

// ✅ XREF_VERIFIED — 4915 xref
#define KO_GAME_STATE_MGR   0x0117664C   // Game state manager
#define KO_PTR_SKILL_MGR    0x0117664C   // → game_ptr (same DAT as GAME_STATE_MGR)
#define KO_UI_STATE         0x01176674   // UI state / Premium flag

/* ===================================================================
   FUNCTIONS
   =================================================================== */

// ✅ XREF_VERIFIED — 154 xref to KO_PTR_CHR (delta +0x260, NOT +0x10)
// Prologue 2604: 55 8B EC 6A FF 68 2E 50 ED 00  (SEH handler: 0x00ED502E)
#define KO_MYINFO_FUNC      0x00733710   // MsgRecv_MyInfo_All

// ✅ CONFIRMED — thiscall prologue 56 8B F1 E8 ... at 0x0062E6E0 (-0x10)
#define KO_ITEMBASIC_LOOKUP 0x0062E6E0   // ItemBasic lookup by ID

/* ===================================================================
   CHARACTER OFFSETS (from KO_PTR_CHR base)
   2604'te AYNEN GEÇERLİ — struct layout değişmedi.
   Runtime doğrulama: peek [KO_PTR_CHR+0x6D0] (level)
                      peek [KO_PTR_CHR+0x6A4] (name, 4B ascii)
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
#define CHR_POS_X           0x3CC   // ⚠️ NEED_TEST smooth X (float)
#define CHR_POS_Y           0x3D0   // ⚠️ NEED_TEST smooth Y (float)
#define CHR_POS_X_SVR       0x408   // ⚠️ NEED_TEST server X
#define CHR_POS_Y_SVR       0x40C   // ⚠️ NEED_TEST server Y

// --- Misc ---
#define CHR_TITLE           0x764
#define CHR_COS_COUNT       0x774

// --- Party / Social ---
#define CHR_PARTY_MGR       0x20C
#define CHR_PARTY_ACTIVE    0x105F
#define CHR_SPEED_MODE      0x1064
#define CHR_SPEED_MULT      0x1068  // float

// --- Skill Data ---
#define KO_OFF_SKILL_DATA   0x214   // game_ptr + offset → skill data obj
#define KO_OFF_SKILL_ARRAY  0x8C    // skill_data + offset → int* array
#define KO_OFF_SKILL_COUNT  0x90    // skill_data + offset → byte count

/* ===================================================================
   PACKET STRUCTURE (2604'te AYNEN GEÇERLİ)

   SEND (AES on):
     [AA 55]  magic header       (2 bytes, big-endian)
     [LL LL]  payload length     (2 bytes, big-endian)
     [CC]     packet counter     = KO_PKT_COUNTER (1 byte)
     [data..] payload            (N bytes)
     [55 AA]  magic footer       (2 bytes, big-endian)

   AES KEY (2602'den DEĞİŞMEDİ):
     32 4E AA 58  BC B3 AE E3  6B C7 4C 56  36 47 34 F2
   =================================================================== */

/* ===================================================================
   SKILL POINTS (chain: KO_GAME_STATE_MGR → +0x210 → SkillDlg)
   UNCHANGED
   =================================================================== */
#define CGP_SKILL_DLG       0x210
#define SKL_AVAIL           0x160
#define SKL_TREE1           0x174
#define SKL_TREE2           0x178
#define SKL_TREE3           0x17C
#define SKL_MASTER          0x180

/* ===================================================================
   INVENTORY (chain: KO_GAME_STATE_MGR → +0x1D8 → InventoryMgr)
   UNCHANGED
   =================================================================== */
#define CGP_INV_MGR         0x1D8
#define INV_EQUIP_START     0x260
#define INV_BAG_START       0x298
#define ITEM_BASE_PTR       0x60
#define ITEM_EXT_PTR        0x64
#define ITEM_COUNT          0x68
#define ITEM_DURABILITY     0x6C

/* ===================================================================
   HOOK — STOLEN BYTES NOTU (2604)

   KO_RECV_DISPATCH @ 0x00706C60:
     Eski patch (2602, GEÇERSİZ): 53 55 56 8B 74 24 14  (7 byte)
     Yeni patch (2604):
       5-byte E9 JMP için: 55 8B EC 6A FF  (ilk 5 byte çal)
       Trampoline: stolen bytes çalıştır + SEH setup'a dön
       SEH handler adresi: 0x00ED2606

   SEH prologue'lu tüm major fonksiyonlar:
     KO_SEND_FUNC       @ 0x0061E5D0  handler 0x00EB6782
     KO_RECV_DISPATCH   @ 0x00706C60  handler 0x00ED2606
     KO_X3_VALIDATOR    @ 0x00710D60  handler 0x00ED3562
     KO_MYINFO_FUNC     @ 0x00733710  handler 0x00ED502E

   KO_MAKERESP_CB ve KO_MAKERESP_CB2: sub esp prologue (SEH yok, eski gibi)
   =================================================================== */
