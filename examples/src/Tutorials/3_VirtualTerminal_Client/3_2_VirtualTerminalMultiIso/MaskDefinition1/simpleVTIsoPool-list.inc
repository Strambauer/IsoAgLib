IsoAgLib::iVtObject_c* all_iVtObjects [] = {
  &iVtObjectimiIsoMaskupload,
  &iVtObjectUnnamed1,
  &iVtObjectUnnamed2,
  &iVtObjectFontAttributesNormal6x8,
  &iVtObjectFontAttributesNormal8x12,
  &iVtObjectFontAttributesNormal6x8R,
  &iVtObjectFontAttributesNormal6x8B,
  &iVtObjectFontAttributesNormal8x8,
  &iVtObjectFontAttributesNormal12x16,
  &iVtObjectFontAttributesNormal16x16,
  &iVtObjectFontAttributesNormal16x24,
  &iVtObjectFontAttributesNormal24x32,
  &iVtObjectLineAttributesNormal,
  &iVtObjectLineAttributesDotted,
  &iVtObjectFontAttributesSKM6x8,
  &iVtObjectFontAttributesSKM8x8,
  &iVtObjectFontAttributesSKM12x16,
  &iVtObjectLineAttributesSKM,
  &iVtObjectFontAttributesNormal6x8_Button60x30,
  &iVtObjectValSpeed,
  &iVtObjectValAccel,
  &iVtObjectValMiles,
  &iVtObjectStrYellow,
  &iVtObjectStrCyan,
  &iVtObjectStrMagenta,
  &iVtObjectStrBlack,
  &iVtObjectStrWhite,
  &iVtObjectLikeIt,
  &iVtObjectLikeItNot,
  &iVtObjectcontainerInAllMasks,
  &iVtObjectUnnamed3,
  &iVtObjectBigLogo,
  &iVtObjectleine,
  &iVtObjectKeyReset,
  &iVtObjectInputMiles,
  &iVtObjectMainMask,
  &iVtObjectmask1contentscontainer,
  &iVtObjectUnnamed4,
  &iVtObjectspeedLabel,
  &iVtObjectUnnamed5,
  &iVtObjectUnnamed6,
  &iVtObjectUnnamed7,
  &iVtObjectUnnamed8,
  &iVtObjectUnnamed9,
  &iVtObjectColLabel,
  &iVtObjectColOS,
  &iVtObjectAccelArchedBarGraph,
  &iVtObjectOpsFakeMileage,
  &iVtObjectChangeAwayPointer,
  &iVtObjectInputListTypFakeMiles,
  &iVtObjectUnnamed12,
  &iVtObjectUnnamed13,
  &iVtObjectUnnamed14,
  &iVtObjectUnnamed15,
  &iVtObjectUnnamed10,
  &iVtObjectUnnamed11,
  &iVtObjectInputLikeage,
  &iVtObjectLikeageOP,
  &iVtObjectKeyMoreAccel,
  &iVtObjectUnnamed16,
  &iVtObjectKeyLessAccel,
  &iVtObjectUnnamed17,
  &iVtObjectvtLang,
  &iVtObjectOSlanguage,
  &iVtObjectdriver,
  &iVtObjectresonible,
  &iVtObjectISdriver,
  &iVtObjectOSresonible,
  &iVtObjectsoftkeys1,
  &iVtObjectKeyMove,
  &iVtObjectUnnamed18,
  &iVtObjectKeyLogo,
  &iVtObjectUnnamed19,
  &iVtObjectKeyChangeLang,
  &iVtObjectUnnamed20,
  &iVtObjectKeyChangeCol,
  &iVtObjectUnnamed21,
  &iVtObjectUnnamed22,
  &iVtObjectKeyForbidden,
  &iVtObjectUnnamed23,
  &iVtObjectKeyChangeFill,
  &iVtObjectUnnamed24,
  &iVtObjectLineAttributes_Normal,
  &iVtObjectFillAttributes,
  &iVtObjectdEllipse,
  &iVtObjectdPolygon,
  &iVtObjectdMeter,
  &iVtObjectMacro_1,
  &iVtObjectMacro_2,
  &iVtObjectAnotherMask,
  &iVtObjectUnnamed25,
  &iVtObjectUnnamed26,
  &iVtObjectUnnamed27,
  &iVtObjectUnnamed28,
  &iVtObjectUnnamed29,
  &iVtObjectUnnamed30,
  &iVtObjectUnnamed31,
  &iVtObjectForbiddenAlarmMask,
  &iVtObjectalarm1contentscontainer,
  &iVtObjectUnnamed32,
  &iVtObjectUnnamed33,
  &iVtObjectUnnamed34,
  &iVtObjectsoftkeysAlarm
};

IsoAgLib::iVtObject_c** all_iVtObjectLists [] = {
  all_iVtObjects,
  all_iVtObjects0,
  all_iVtObjects1,
  all_iVtObjects2,
  NULL // indicate end of list
};

iObjectPool_simpleVTIsoPool_c::iObjectPool_simpleVTIsoPool_c () : iIsoTerminalObjectPool_c (all_iVtObjectLists, 103, 6, 200, 60, 32) {};