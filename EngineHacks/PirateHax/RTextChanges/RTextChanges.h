struct HelpBoxProc
{
    /* 00 */ PROC_HEADER;

    /* 2C */ const struct HelpBoxInfo* info;

    /* 30 */ short xBox;
    /* 32 */ short yBox;
    /* 34 */ short wBox;
    /* 36 */ short hBox;
    /* 38 */ short xBoxInit;
    /* 3A */ short yBoxInit;
    /* 3C */ short xBoxFinal;
    /* 3E */ short yBoxFinal;
    /* 40 */ short wBoxInit;
    /* 42 */ short hBoxInit;
    /* 44 */ short wBoxFinal;
    /* 46 */ short hBoxFinal;
    /* 48 */ short timer;
    /* 4A */ short timerMax;

    /* 4C */ u16 mid;
    /* 4E */ Item item;

    /* 50 */ u16 moveKey; // move ctrl proc only

    /* 52 */ u8 unk52;

    // NOTE: there's likely more, need to decompile more files
};

struct HelpBox8A01650Proc
{
    /* 00 */ PROC_HEADER;

    /* 29 */ u8 _pad[0x58-0x29];

    /* 58 */ Item unk_58;
    /* 5C */ int unk_5c;
    /* 60 */ int unk_60;
    /* 64 */ s16 unk_64; //height needed for display stats?
};

struct HelpBoxInfo
{
    /* 00 */ const struct HelpBoxInfo* adjUp;
    /* 04 */ const struct HelpBoxInfo* adjDown;
    /* 08 */ const struct HelpBoxInfo* adjLeft;
    /* 0C */ const struct HelpBoxInfo* adjRight;
    /* 10 */ u8 xDisplay;
    /* 11 */ u8 yDisplay;
    /* 12 */ Item mid;
    /* 14 */ void(*redirect)(struct HelpBoxProc* proc);
    /* 18 */ void(*populate)(struct HelpBoxProc* proc);
};

int GetHelpBoxItemInfoKind(Item item);
void ApplyHelpBoxContentSize(struct HelpBoxProc* proc, int width, int height);

int DrawHelpBoxWeaponLabels(Item item);
int DrawHelpBoxStaffLabels(Item item);
void DrawHelpBoxSaveMenuLabels(void);
void DrawHelpBoxLabels(struct HelpBox8A01650Proc* proc);

struct HelpBoxSt {
    /* 00 */ struct FontData font;
    /* 16 */ struct TextHandle text[3];
    /* 30 */ u16 oam2_base;
};

extern struct HelpBoxSt gHelpBoxSt;

enum
{
    HB_EXTINFO_NONE, //0
    HB_EXTINFO_WEAPON, //1
    HB_EXTINFO_STAFF, //2
    HB_EXTINFO_SAVEINFO, //3
};

enum text_colors {
    TEXT_COLOR_0123 = 0,
    TEXT_COLOR_0456 = 1,
    TEXT_COLOR_0789 = 2,
    TEXT_COLOR_0ABC = 3,
    TEXT_COLOR_0DEF = 4,
    TEXT_COLOR_0030 = 5,
    TEXT_COLOR_4DEF = 6,
    TEXT_COLOR_456F = 7,
    TEXT_COLOR_47CF = 8,
    TEXT_COLOR_MASK = 9,

    TEXT_COLOR_COUNT,

    TEXT_COLOR_SYSTEM_WHITE = TEXT_COLOR_0123,
    TEXT_COLOR_SYSTEM_GRAY  = TEXT_COLOR_0456,
    TEXT_COLOR_SYSTEM_BLUE  = TEXT_COLOR_0789,
    TEXT_COLOR_SYSTEM_GOLD  = TEXT_COLOR_0ABC,
    TEXT_COLOR_SYSTEM_GREEN = TEXT_COLOR_0DEF,
    TEXT_COLOR_SYSTEM_BLACK = TEXT_COLOR_0030,

    // TEXT_COLOR_TALK_...
};

enum text_special_char
{
    TEXT_SPECIAL_BIGNUM_0   = 0x00,
    TEXT_SPECIAL_BIGNUM_1   = 0x01,
    TEXT_SPECIAL_BIGNUM_2   = 0x02,
    TEXT_SPECIAL_BIGNUM_3   = 0x03,
    TEXT_SPECIAL_BIGNUM_4   = 0x04,
    TEXT_SPECIAL_BIGNUM_5   = 0x05,
    TEXT_SPECIAL_BIGNUM_6   = 0x06,
    TEXT_SPECIAL_BIGNUM_7   = 0x07,
    TEXT_SPECIAL_BIGNUM_8   = 0x08,
    TEXT_SPECIAL_BIGNUM_9   = 0x09,
    TEXT_SPECIAL_SMALLNUM_0 = 0x0A,
    TEXT_SPECIAL_SMALLNUM_1 = 0x0B,
    TEXT_SPECIAL_SMALLNUM_2 = 0x0C,
    TEXT_SPECIAL_SMALLNUM_3 = 0x0D,
    TEXT_SPECIAL_SMALLNUM_4 = 0x0E,
    TEXT_SPECIAL_SMALLNUM_5 = 0x0F,
    TEXT_SPECIAL_SMALLNUM_6 = 0x10,
    TEXT_SPECIAL_SMALLNUM_7 = 0x11,
    TEXT_SPECIAL_SMALLNUM_8 = 0x12,
    TEXT_SPECIAL_SMALLNUM_9 = 0x13,
    TEXT_SPECIAL_DASH       = 0x14,
    TEXT_SPECIAL_PLUS       = 0x15,
    TEXT_SPECIAL_SLASH      = 0x16,
    TEXT_SPECIAL_TILDE      = 0x17,
    TEXT_SPECIAL_S          = 0x18,
    TEXT_SPECIAL_A          = 0x19,
    TEXT_SPECIAL_B          = 0x1A,
    TEXT_SPECIAL_C          = 0x1B,
    TEXT_SPECIAL_D          = 0x1C,
    TEXT_SPECIAL_E          = 0x1D,
    TEXT_SPECIAL_G          = 0x1E,
    TEXT_SPECIAL_K          = 0x1F, // NOTE: this is an E? used as statscreen exp label and equip marker
    TEXT_SPECIAL_COLON      = 0x20,
    TEXT_SPECIAL_DOT        = 0x21,
    TEXT_SPECIAL_HP_A       = 0x22,
    TEXT_SPECIAL_HP_B       = 0x23,
    TEXT_SPECIAL_LV_A       = 0x24,
    TEXT_SPECIAL_LV_B       = 0x25,
    TEXT_SPECIAL_ARROW      = 0x26,
    TEXT_SPECIAL_HEART      = 0x27,
    TEXT_SPECIAL_100_A      = 0x28,
    TEXT_SPECIAL_100_B      = 0x29,
    TEXT_SPECIAL_PERCENT    = 0x2A,


    TEXT_SPECIAL_35         = 0x35,

    // TODO: rest

    TEXT_SPECIAL_NOTHING    = 0xFF,
};

void DrawUiSmallNumber(u16 *tm, int color, int number);
extern u16 gpStatScreenPageBg0Map[0x280];
extern u16 gpStatScreenPageBg2Map[0x240];