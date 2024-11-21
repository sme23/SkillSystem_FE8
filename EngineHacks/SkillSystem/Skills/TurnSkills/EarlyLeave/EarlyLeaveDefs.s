
@Common
.macro blh to, reg=r3
  ldr \reg, =\to
  mov lr, \reg
  .short 0xf800
.endm

.equ UnitsPerPage, 6
.equ gChapterData, 0x0202BCF0
.equ GetUnitByCharId, 0x0801829C
.equ GetUnit, 0x08019430
.equ gMapUnit, 0x0202E4D8
.equ StartMenuChild, 0x0804EBC8
.equ String_GetFromIndex, 0x0800A240

@DrawSemiTransparentMenuBg/ResetGraphicsForMenuRedraw
.equ ClearBG0BG1, 0x0804E884
.equ gLCDIOBuffer, 0x03003080
.equ SetColorEffectsParameters, 0x08001EA0
.equ SetColorEffectsFirstTarget, 0x08001ED0
.equ SetColorEffectBackdropFirstTarget, 0x08001F48
.equ SetColorEffectsSecondTarget, 0x08001F0C
.equ SetColorEffectBackdropSecondTarget, 0x08001F64
.equ Text_SetFont, 0x08003D38
.equ Font_LoadForUI, 0x080043A8
.equ LoadNewUIGraphics, 0x0804EB68
.equ gBg2MapBuffer, 0x02023CA8
.equ FillBgMap, 0x08001220
.equ Text_ResetTileAllocation, 0x08003D20

@CallEarlyLeaveEvent
.equ CallMapEventEngine, 0x0800D07C

@EarlyLeaveUnitLeaves
.equ ConvoySizePointer, 0x080315BC
.equ ConvoyPointer, 0x080315B4
.equ ClearUnit, 0x080177F4
.equ gEventCounter, 0x03000568
.equ SMS_UpdateFromGameData, 0x080271A0

@StartEarlyLeaveMenu
.equ PlayerPhase_ReloadGameGfx, 0x0801D6FC
.equ ProcStart, 0x08002C7C

@SetupEarlyLeaveTotalReplacement
.equ TotalPlayerUnits, 62
.equ gUnitArrayBlue, 0x0202BE4C

@UpdateEarlyLeaveMenuCommandDefinition
.equ MenuCommandAlwaysUsable, 0x0804F448|1

@StartEarlyLeaveWindow/UpdateEarlyLeaveWindow
.equ Text_InitDB, 0x08003D84
.equ ProcFind, 0x08002E9C
.equ GetBgMapBuffer, 0x08001C4C
.equ TextClear, 0x08003DC8
.equ MakeUIWindowTileMap_BG0BG1, 0x0804E368
.equ Text_InsertString, 0x08004480
.equ gBg0MapBuffer, 0x02022CA8
.equ Text_Display, 0x08003E70
.equ EnableBgSyncByMask, 0x08001FAC

@EarlyLeaveUpdateFaceDisplay
.equ EndFaceById, 0x08005758
.equ gProc_Menu, 0x085B64D0 
.equ GetUnitPortraitId, 0x080192B8
.equ StartFace, 0x0800563C
.equ SetFaceBlinkControlById, 0x08006458

@EarlyLeaveMenuDirectionInputs/EarlyLeaveMenuSelectInputs
.equ gpKeyState, 0x0858791C
.equ Menu_DrawHoverThing, 0x0804F0E0
.equ m4aSongNumStart, 0x080D01FC

@EarlyLeaveEffect_UnitSelect
.equ DrawSecondMenuBg, 0x080234AC
.equ Word_FFFFFF00, 0xFFFFFF00
.equ Word_FFFF00FF, 0xFFFF00FF
.equ Word_FF00FFFF, 0xFF00FFFF
.equ Word_00FFFFFF, 0x00FFFFFF
.equ StartMenuAt, 0x0804EC98

@EarlyLeaveEffect_UnitConfirm
.equ GetRescueStaffeePosition, 0x0802ECD0

@EarlyLeaveViewStatScreen
.equ SetStatScreenNextUnitLogic, 0x08086DE4
.equ ProcStartBlocking, 0x08002CE0
.equ StartStatScreen, 0x0808894C
.equ gProc_StatScreen, 0x08A009D8

@EarlyLeaveStatScreenToMenu
.equ StatScreenStruct, 0x2003BFC
.equ EndProc, 0x08002D6C
