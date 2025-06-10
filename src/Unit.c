#include "Unit.h"
#include "Drawable.h"
#include "SpecificLists.h"
#include "UnitMetadata.h"

// Public

void Unit_New() {}
void Unit_Load() {}
void Unit_Unload() {}

void Unit_Init(Unit* unit) {
	unit->Action = 0;
	unit->Direction = 0;
	unit->Position = &unit->Animation.Drawable.Position;
    Animation newAnimation = UnitMetadata_GetMetadataIndex(unit->Action, unit->Direction);
    Animation_Change(&unit->Animation, newAnimation);
}

void Unit_Update(Unit* unit) {
    Animation_Update(&unit->Animation);

    if (IsKeyPressed(KEY_W)) {
        Unit_ChangeDirection(unit, 3);
    }
    else if (IsKeyPressed(KEY_A)) {
        Unit_ChangeDirection(unit, 1);
    }
    else if (IsKeyPressed(KEY_S)) {
        Unit_ChangeDirection(unit, 0);
    }
    else if (IsKeyPressed(KEY_D)) {
        Unit_ChangeDirection(unit, 2);
    }
}

void Unit_Draw(Unit* unit) {
    Animation_Draw(&unit->Animation);
}

void Unit_ChangeDirection(Unit* unit, int direction) {
    unit->Direction = direction;
    Animation newAnimation = UnitMetadata_GetMetadataIndex(unit->Action, direction);
    Animation_Change(&unit->Animation, newAnimation);
}

void Unit_ChangeAction(Unit* unit, int action) {
    unit->Action = action;
	Animation newAnimation = UnitMetadata_GetMetadataIndex(action, unit->Direction);

    Animation_Change(&unit->Animation, newAnimation);
}