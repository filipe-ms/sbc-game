#include "Unit.h"
#include "Drawable.h"
#include "AnimationMetadata.h"

static void OnAnimationStart(Unit* unit);
static void OnAnimationEnd(Unit* unit);
static Animation GetExpectedAnimation(Unit* unit, int action, int direction);

// Public
void Unit_Init(Unit* unit, Unit_Type type) {
    unit->Action = 0;
    unit->Direction = 0;

    unit->Position = &unit->Animation.Drawable.Position;
    unit->Scale = &unit->Animation.Drawable.Scale;

    unit->UnitAnimationMetadata = AnimationMetadata_GetUnitAnimationMetadataByUnitType(type);
    unit->Metadata = AnimationMetadata_GetMetadataByAnimationMetadataType(type);
  
    Animation_Change(&unit->Animation, GetExpectedAnimation(unit, 0, 0));
    Animation_AddTransitionEvents(&unit->Animation, unit, OnAnimationStart, OnAnimationEnd);

    unit->Animation.Drawable.Color = WHITE;
}

void Unit_Update(Unit* unit) {
    Animation_Update(&unit->Animation);
}

void Unit_Draw(Unit* unit) {
    Animation_Draw(&unit->Animation);
}

void Unit_ChangeDirection(Unit* unit, int direction) {
    unit->Direction = direction;

    // Passing the animation as parameter to enforce copying the struct
    Animation animation = GetExpectedAnimation(unit, unit->Action, direction);
    Animation_Change(&unit->Animation, animation);
}

void Unit_ChangeAnimationOrder(Unit* unit, Animation_Order order)
{
    unit->Animation.Order = order;
    unit->Animation.CurrentFrame = unit->Animation.StartingFrame;
    unit->Animation.ElapsedTime = 0;
}

void Unit_ChangeAction(Unit* unit, int action) {
    unit->Action = action;

    // Passing the animation as parameter to enforce copying the struct
    Animation animation = GetExpectedAnimation(unit, action, unit->Direction);
    Animation_Change(&unit->Animation, animation);
}

void Unit_AddTransitionEvents(Unit* unit, void* owner, Function onAnimationStart, Function onAnimationFinish)
{
    unit->OnAnimationStart = onAnimationStart;
    unit->OnAnimationEnd = onAnimationFinish;
}

// Private
static void OnAnimationStart(Unit* unit) {
    Function_Invoke_Arg1(unit->OnAnimationStart, unit->Owner);
}

static void OnAnimationEnd(Unit* unit) {
    Function_Invoke_Arg1(unit->OnAnimationEnd, unit->Owner);
}

static Animation GetExpectedAnimation(Unit* unit, int action, int direction) {
    return unit->Metadata[action * unit->UnitAnimationMetadata.Actions + direction];
}