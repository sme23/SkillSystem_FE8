
#include "gbafe.h"
#include "RTextChanges.h"


void ApplyHelpBoxContentSize(struct HelpBoxProc* proc, int width, int height){
    width = 0xF0 & (width + 15); // align to 16 pixel multiple

    switch (GetHelpBoxItemInfoKind(proc->item))
    {

    case 1: // weapon
        if (width < 0x90)
            width = 0x90;

        if (Text_GetStringTextWidth(GetStringFromIndex(proc->mid)) > 8)
            height += 0x20;
        else
            height += 0x10;

        break;
    
    case 2: // staff
        if (width < 0x90)
            width = 0x90;

        height += 0x10;

        break;

    case 3: // save stuff
        width = 0x80;
        height += 0x10;

        break;
    /*
    case 4: //equip
    case 5: //offensive equip
    case 6: //defensive equip
    if (width < 0x60)
        width = 0x60;

    height += 0x10;

    break;
    */
    } // switch (GetHelpBoxItemInfoKind(proc->item))

    proc->wBoxFinal = width;
    proc->hBoxFinal = height;
}

void DrawHelpBoxLabels(struct HelpBox8A01650Proc* proc) {
    Item item = proc->unk_58;

    Text_SetFont(&gUnknown_0203E794.font);
    Text_SetFontStandardGlyphSet(0);

    switch (GetHelpBoxItemInfoKind(item)) {
        case 0:
            proc->unk_64 = 0;
            break;

        case 1:
            DrawHelpBoxWeaponLabels(item);
            proc->unk_64 = 2;
            break;

        case 2:
            DrawHelpBoxStaffLabels(item);
            proc->unk_64 = 1;
            break;

        case 3:
            DrawHelpBoxSaveMenuLabels();
            proc->unk_64 = 1;
            break;
    }

    Text_SetFont(0);
    BreakProcLoop((Proc*) proc);

    return;
}

int DrawHelpBoxStaffLabels(Item item) {
    Text_InsertString(&gUnknown_0203E794.text[0], 0, 8, GetStringFromIndex(0x509)); // TODO: msg id "Staff[.]"
    Text_InsertString(&gUnknown_0203E794.text[0], 30, 7, GetItemDisplayRankString(item));
    Text_InsertString(&gUnknown_0203E794.text[0], 48, 8, GetStringFromIndex(0x500)); // TODO: msg id "Rng[.]"
    Text_InsertString(&gUnknown_0203E794.text[0], 70, 7, GetItemDisplayRangeString(item));
    Text_InsertString(&gUnknown_0203E794.text[0], 107, 8, GetStringFromIndex(0x502)); // TODO: msg id "Wt"
    Text_InsertNumberOr2Dashes(&gUnknown_0203E794.text[0], 135, 7, GetItemWeight(item));
    
    return 1;
}
