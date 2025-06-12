#include "Unit.h"
#include "Drawable.h"
#include "UnitMetadata.h"

static Animation GetExpectedAnimation(Unit* unit, int action, int direction) {
    return unit->Metadata[action * unit->UnitAnimationMetadata.Actions + direction];
}

void Unit_Init(Unit* unit, Unit_Type type) {
	unit->Action = 0;
	unit->Direction = 0;

	unit->Position = &unit->Animation.Drawable.Position;
    unit->Scale = &unit->Animation.Drawable.Scale;

    unit->UnitAnimationMetadata = UnitMetadata_GetUnitAnimationMetadataByUnitType(type);    
    unit->Metadata = UnitMetadata_GetMetadataByUnitMetadataType(type);

    Animation_Change(&unit->Animation, GetExpectedAnimation(unit, 0, 0));
}

void Unit_Update(Unit* unit) { Animation_Update(&unit->Animation); }

void Unit_Draw(Unit* unit) { Animation_Draw(&unit->Animation); }

void Unit_ChangeDirection(Unit* unit, int direction) {
    unit->Direction = direction;

    // Passing the animation as parameter to enforce copying the struct
    Animation animation = GetExpectedAnimation(unit, unit->Action, direction);
    Animation_Change(&unit->Animation, animation);
}

void Unit_ChangeAction(Unit* unit, int action) {
    unit->Action = action;

    // Passing the animation as parameter to enforce copying the struct
    Animation animation = GetExpectedAnimation(unit, action, unit->Direction);
    Animation_Change(&unit->Animation, animation);
}