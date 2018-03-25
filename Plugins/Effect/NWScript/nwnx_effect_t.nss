#include "nwnx_effect"


void WriteAndFloat(string sMessage) {
    WriteTimestampedLogEntry(sMessage);
    FloatingTextStringOnCreature(sMessage, OBJECT_SELF, FALSE);
}


void Test_CasterLevel_2(object oTest) {
    int bSuccess = FALSE;
    effect eEff;

    for (eEff = GetFirstEffect(oTest); GetIsEffectValid(eEff); eEff = GetNextEffect(oTest)) {
        if (GetEffectType(eEff) != EFFECT_TYPE_ATTACK_INCREASE)
            continue;

        if (GetEffectCasterLevel(eEff) == 42) {
            bSuccess = TRUE;
            break;
        }
    }

    if (bSuccess) {
        WriteAndFloat("Test_CasterLevel PASS");
    } else {
        WriteAndFloat("Test_CasterLevel FAIL");
    }

    if (!GetIsPC(oTest)) {
        SetPlotFlag(oTest, FALSE);
        DestroyObject(oTest);
    }
}

void Test_CasterLevel()
{
    WriteAndFloat("Test_CasterLevel START");

    effect eEff = EffectAttackIncrease(1);
    NWNX_Effect_SetEffectCasterLevel(eEff, 42);
    ApplyEffectToObject(DURATION_TYPE_TEMPORARY, eEff, OBJECT_SELF, 12.0);

    DelayCommand(0.1, Test_CasterLevel_2(oTest));
}


void Test_Creator_2(object oTest1, object oTest2) {
    int nSuccess = 0;
    effect eEff;

    for (eEff = GetFirstEffect(oTest1); GetIsEffectValid(eEff); eEff = GetNextEffect(oTest1)) {
        if (GetEffectCreator(eEff) == OBJECT_SELF) {
            nSuccess |= 1;
        } else if (GetEffectCreator(eEff) == oTest2) {
            nSuccess |= ~1;
            break;
        }
    }

    for (eEff = GetFirstEffect(oTest2); GetIsEffectValid(eEff); eEff = GetNextEffect(oTest2)) {
        if (GetEffectCreator(eEff) == oTest1) {
            nSuccess |= 2;
        } else if (GetEffectCreator(eEff) == OBJECT_SELF) {
            nSuccess |= ~2;
            break;
        }
    }

    if (nSuccess == 3) {
        WriteAndFloat("Test_Creator PASS");
    } else {
        WriteAndFloat("Test_Creator FAIL (" + IntToString(nSuccess) + " != 3)");
    }

    SetPlotFlag(oTest1, FALSE);
    DestroyObject(oTest1);

    SetPlotFlag(oTest2, FALSE);
    DestroyObject(oTest2);
}

void Test_Creator()
{
    WriteAndFloat("Test_Creator START");

    object oTest1 = CreateObject(OBJECT_TYPE_CREATURE, "NW_BTLFIRE", GetLocation(OBJECT_SELF));
    object oTest2 = CreateObject(OBJECT_TYPE_CREATURE, "NW_BTLFIRE", GetLocation(OBJECT_SELF));

    effect eEff1 = EffectCutsceneParalyze();
    effect eEff2 = EffectLinkEffects(EffectCutsceneParalyze(), EffectVisualEffect(VFX_DUR_ENTANGLE));

    NWNX_Effect_SetEffectCreator(eEff2, oTest1);

    ApplyEffectToObject(DURATION_TYPE_PERMANENT, eEff1, oTest1);
    ApplyEffectToObject(DURATION_TYPE_PERMANENT, eEff2, oTest2);

    DelayCommand(0.1, Test_Creator_2(oTest1, oTest2));
}


void Test_Duration()
{
    WriteAndFloat("Test_Duration START");

}


void Test_Integer_2(object oTest)
{
    int nSuccess = 0;

    if (GetCurrentHitPoints(oTest) == GetMaxHitPoints(oTest) + 100)
        nSuccess |= 1;

    for (eEff = GetFirstEffect(oTest); GetIsEffectValid(eEff); eEff = GetNextEffect(oTest)) {
        if (GetEffectType(eEff) != EFFECT_TYPE_TEMPORARY_HITPOINTS)
            continue;

        if (GetEffectInteger(eEff, 0) == 100)
            nSuccess |= 2;
    }

    if (nSuccess == 3) {
        WriteAndFloat("Test_Integer PASS");
    } else {
        WriteAndFloat("Test_Integer FAIL (" + IntToString(nSuccess) + " != 3)");
    }

    SetPlotFlag(oTest, FALSE);
    DestroyObject(oTest);
}

void Test_Integer()
{
    WriteAndFloat("Test_Integer START");

    object oTest = CreateObject(OBJECT_TYPE_CREATURE, "NW_BTLFIRE", GetLocation(OBJECT_SELF));
    effect eEff = EffectTemporaryHitPoints(10);
    NWNX_Effect_SetEffectInteger(eEff, 0, 100);
    eEff = EffectLinkEffects(eEff, EffectCutsceneParalyze());
    ApplyEffectToObject(DURATION_TYPE_PERMANENT, eEff, oTest);

    DelayCommand(0.1, Test_Integer_2(oTest));
}


void Test_Matching()
{
    WriteAndFloat("Test_Matching SKIP");
}


void Test_SpellId_2(object oTest)
{
    int bSuccess = FALSE;
    effect eEff;

    for (eEff = GetFirstEffect(oTest); GetIsEffectValid(eEff); eEff = GetNextEffect(oTest)) {
        if (GetEffectType(eEff) != EFFECT_TYPE_REGENERATE)
            continue;

        if (GetEffectSpellId(eEff) == SPELL_BLESS) {
            bSuccess = TRUE;
            break;
        }
    }

    if (bSuccess) {
        WriteAndFloat("Test_SpellId PASS");
    } else {
        WriteAndFloat("Test_SpellId FAIL");
    }

    if (!GetIsPC(oTest)) {
        SetPlotFlag(oTest, FALSE);
        DestroyObject(oTest);
    }
}

void Test_SpellId()
{
    WriteAndFloat("Test_SpellId START");

    effect eEff = EffectRegenerate(1, 3.0);
    SetEffectSpellId(eEff, SPELL_BLESS);
    ApplyEffectToObject(DURATION_TYPE_TEMPORARY, eEff, OBJECT_SELF, 12.0);

    DelayCommand(0.1, Test_SpellId_2(OBJECT_SELF));
}


void Test_TrueType_2(object oTest)
{
    int bSuccess = FALSE;
    effect eEff;

    for (eEff = GetFirstEffect(oTest); GetIsEffectValid(eEff); eEff = GetNextEffect(oTest)) {
        if (GetEffectType(eEff) != EFFECT_TYPE_INVALIDEFFECT)
            continue;

        if (GetEffectTrueType(eEff) == NWNX_EFFECT_EFFECT_TRUETYPE_KNOCKDOWN) {
            bSuccess = TRUE;
            break;
        }
    }

    if (bSuccess) {
        WriteAndFloat("Test_TrueType PASS");
    } else {
        WriteAndFloat("Test_TrueType FAIL");
    }

    if (!GetIsPC(oTest)) {
        SetPlotFlag(oTest, FALSE);
        DestroyObject(oTest);
    }
}

void Test_TrueType()
{
    WriteAndFloat("Test_TrueType START (expect to be knocked down)");

    effect eEff = EffectKnockdown();
    ApplyEffectToObject(DURATION_TYPE_TEMPORARY, eEff, OBJECT_SELF, 12.0);

    DelayCommand(0.1, Test_TrueType_2(OBJECT_SELF));
}


void main()
{
    if (!GetIsPC(OBJECT_SELF)) {
        WriteTimestampedLogEntry("The `nwnx_effect` test suite must be executed by a PC. This ensures there is a valid creator creator and also that temporary creatures created during the test have a place to stand.");
        return;
    }

    WriteAndFloat("Initiating testing of `nwnx_effect` (7 tests)");

    DelayCommand(1.0, Test_CasterLevel());
    DelayCommand(2.0, Test_Creator());
    DelayCommand(3.0, Test_Integer());
    DelayCommand(4.0, Test_Matching());
    DelayCommand(5.0, Test_SpellId());
    DelayCommand(6.0, Test_TrueType());

    /* do `Test_Duration()` last since it takes longer */
    DelayCommand(7.0, Test_Duration());
}
