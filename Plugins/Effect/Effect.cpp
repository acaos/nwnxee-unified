#include "Effect.hpp"

#include "API/CAppManager.hpp"
#include "API/CGameEffect.hpp"
#include "API/CGameObject.hpp"
#include "API/CNWSObject.hpp"
#include "API/CNWSScriptVar.hpp"
#include "API/CNWSScriptVarTable.hpp"
#include "API/CServerExoApp.hpp"
#include "API/CVirtualMachine.hpp"
#include "API/CWorldTimer.hpp"

#include "API/Constants.hpp"
#include "API/Globals.hpp"
#include "API/Functions.hpp"
#include "ViewPtr.hpp"

using namespace NWNXLib;
using namespace NWNXLib::API;


static ViewPtr<NWNX_STRUCTS_PLUGIN_NAME::NWNX_STRUCTS_PLUGIN_NAME> g_plugin;
static CGameEffect *g_lastPushedStruct;


NWNX_PLUGIN_ENTRY Plugin::Info* PluginInfo()
{
    return new Plugin::Info
    {
        NWNX_STRUCTS_STRINGIFY(NWNX_STRUCTS_PLUGIN_NAME),
        "Functions exposing additional properties of engine structures",
        "Acaos",
        "dswarin@gmail.com",
        1,
        true
    };
}

NWNX_PLUGIN_ENTRY Plugin* PluginLoad(Plugin::CreateParams params)
{
    g_plugin = new NWNX_STRUCTS_PLUGIN_NAME::NWNX_STRUCTS_PLUGIN_NAME(params);
    return g_plugin;
}


namespace NWNX_STRUCTS_PLUGIN_NAME {

NWNX_STRUCTS_PLUGIN_NAME::NWNX_STRUCTS_PLUGIN_NAME(const Plugin::CreateParams& params)
    : Plugin(params)
{
#define REGISTER(func) \
    GetServices()->m_events->RegisterEvent(#func, std::bind(&NWNX_STRUCTS_PLUGIN_NAME::func, this, std::placeholders::_1))

    REGISTER(GetCasterLevel);
    REGISTER(GetDuration);
    REGISTER(GetDurationRemaining);
    REGISTER(GetHasMatchingEffect);
    REGISTER(GetInteger);
    REGISTER(GetNumIntegers);
    REGISTER(GetSpellId);
    REGISTER(GetTrueType);
    REGISTER(SetCasterLevel);
    REGISTER(SetCreator);
    REGISTER(SetInteger);
    REGISTER(SetSpellId);
    REGISTER(SetTrueType);

#undef REGISTER

    g_lastPushedStruct = NULL;

    GetServices()->m_hooks->RequestSharedHook
        <Functions::CVirtualMachine__StackPushEngineStructure,
            int32_t, CVirtualMachine*, int32_t, void*>(&HandleStackPushEngineStructure);

}

NWNX_STRUCTS_PLUGIN_NAME::~NWNX_STRUCTS_PLUGIN_NAME()
{
}

ArgumentStack NWNX_STRUCTS_PLUGIN_NAME::GetCasterLevel(ArgumentStack&&)
{
    int32_t ret = 0;
    ArgumentStack stack;

    if (g_lastPushedStruct != NULL)
    {
        ret = g_lastPushedStruct->m_nCasterLevel;
    }
    else
    {
        LOG_ERROR("Unable to get last pushed struct");
    }

    Services::Events::InsertArgument(stack, ret);

    return stack;
}

ArgumentStack NWNX_STRUCTS_PLUGIN_NAME::GetDuration(ArgumentStack&&)
{
    float ret = -1.0;
    ArgumentStack stack;

    if (g_lastPushedStruct != NULL)
    {
        ret = g_lastPushedStruct->m_fDuration;
    }
    else
    {
        LOG_ERROR("Unable to get last pushed struct");
    }

    Services::Events::InsertArgument(stack, ret);

    return stack;
}

ArgumentStack NWNX_STRUCTS_PLUGIN_NAME::GetDurationRemaining(ArgumentStack&&)
{
    float ret = -1.0;
    ArgumentStack stack;

    if (g_lastPushedStruct != NULL)
    {
        CServerExoApp* server = Globals::AppManager()->m_pServerExoApp;
        CWorldTimer* world_timer = server->GetWorldTimer();
        uint32_t world_time_days, world_time_secs;
        int64_t current, expires;

        world_timer->GetWorldTime(&world_time_days, &world_time_secs);

        current = world_time_days;
        current = (current * 2880000LL) + world_time_secs;

        expires = g_lastPushedStruct->m_nExpiryCalendarDay;
        expires = (expires * 2880000LL) + g_lastPushedStruct->m_nExpiryTimeOfDay;

        ret = static_cast<float>(expires - current) / 1000.0;
    }
    else
    {
        LOG_ERROR("Unable to get last pushed struct");
    }

    Services::Events::InsertArgument(stack, ret);

    return stack;
}

ArgumentStack NWNX_STRUCTS_PLUGIN_NAME::GetHasEffect(ArgumentStack&&)
{
    int32_t ret = 0;
    ArgumentStack stack;

    /* TODO */

    if (g_lastPushedStruct != NULL)
    {
        ret = g_lastPushedStruct->m_nNumIntegers;
    }
    else
    {
        LOG_ERROR("Unable to get last pushed struct");
    }

    Services::Events::InsertArgument(stack, ret);

    return stack;
}

ArgumentStack NWNX_STRUCTS_PLUGIN_NAME::GetInteger(ArgumentStack&& args)
{
    int32_t ret = 0;
    ArgumentStack stack;

    if (g_lastPushedStruct != NULL)
    {
        const auto idx = Services::Events::ExtractArgument<int32_t>(args);

        if (idx >= 0 && idx < g_lastPushedStruct->m_nNumIntegers)
        {
            ret = g_lastPushedStruct->m_nParamInteger[idx];
        }
    }
    else
    {
        LOG_ERROR("Unable to get last pushed struct");
    }

    Services::Events::InsertArgument(stack, ret);

    return stack;
}

ArgumentStack NWNX_STRUCTS_PLUGIN_NAME::GetNumIntegers(ArgumentStack&&)
{
    int32_t ret = 0;
    ArgumentStack stack;

    if (g_lastPushedStruct != NULL)
    {
        ret = g_lastPushedStruct->m_nNumIntegers;
    }
    else
    {
        LOG_ERROR("Unable to get last pushed struct");
    }

    Services::Events::InsertArgument(stack, ret);

    return stack;
}

ArgumentStack NWNX_STRUCTS_PLUGIN_NAME::GetSpellId(ArgumentStack&&)
{
    int32_t ret = 0;
    ArgumentStack stack;

    if (g_lastPushedStruct != NULL)
    {
        ret = g_lastPushedStruct->m_nSpellId;
    }
    else
    {
        LOG_ERROR("Unable to get last pushed struct");
    }

    Services::Events::InsertArgument(stack, ret);

    return stack;
}

ArgumentStack NWNX_STRUCTS_PLUGIN_NAME::GetTrueType(ArgumentStack&&)
{
    int32_t ret = 0;
    ArgumentStack stack;

    if (g_lastPushedStruct != NULL)
    {
        ret = g_lastPushedStruct->m_nType;
    }
    else
    {
        LOG_ERROR("Unable to get last pushed struct");
    }

    Services::Events::InsertArgument(stack, ret);

    return stack;
}

ArgumentStack NWNX_STRUCTS_PLUGIN_NAME::SetCasterLevel(ArgumentStack&& args)
{
    ArgumentStack stack;

    if (g_lastPushedStruct != NULL)
    {
        const auto level = Services::Events::ExtractArgument<int32_t>(args);

        g_lastPushedStruct->m_nCasterLevel = level;
    }
    else
    {
        LOG_ERROR("Unable to get last pushed struct");
    }

    return stack;
}

ArgumentStack NWNX_STRUCTS_PLUGIN_NAME::SetCreator(ArgumentStack&& args)
{
    ArgumentStack stack;

    if (g_lastPushedStruct != NULL)
    {
        const auto creatorId = Services::Events::ExtractArgument<Types::ObjectID>(args);
        g_lastPushedStruct->m_oidCreator = creatorId;
    }
    else
    {
        LOG_ERROR("Unable to get last pushed struct");
    }

    return stack;
}

ArgumentStack NWNX_STRUCTS_PLUGIN_NAME::SetInteger(ArgumentStack&&)
{
    ArgumentStack stack;

    /* TODO */

    if (g_lastPushedStruct != NULL)
    {
/*
        const auto val = Services::Events::ExtractArgument<int32_t>(args);
        const auto idx = Services::Events::ExtractArgument<int32_t>(args);
*/
    }
    else
    {
        LOG_ERROR("Unable to get last pushed struct");
    }

    return stack;
}

ArgumentStack NWNX_STRUCTS_PLUGIN_NAME::SetSpellId(ArgumentStack&& args)
{
    ArgumentStack stack;

    if (g_lastPushedStruct != NULL)
    {
        const auto spellid = Services::Events::ExtractArgument<int32_t>(args);
        g_lastPushedStruct->m_nSpellId = spellid;
    }
    else
    {
        LOG_ERROR("Unable to get last pushed struct");
    }

    return stack;
}

ArgumentStack NWNX_STRUCTS_PLUGIN_NAME::SetTrueType(ArgumentStack&& args)
{
    ArgumentStack stack;

    if (g_lastPushedStruct != NULL)
    {
        const auto truetype = Services::Events::ExtractArgument<int32_t>(args);
        g_lastPushedStruct->m_nType = truetype;
    }
    else
    {
        LOG_ERROR("Unable to get last pushed struct");
    }

    return stack;
}


void NWNX_STRUCTS_PLUGIN_NAME::HandleStackPushEngineStructure(Services::Hooks::CallType type, CVirtualMachine *, int32_t structure_type, void *engine_structure)
{
    // Before or after doesn't matter, just pick one so it happens only once
    // Structure types 0 and 4 are effect and item property, respectively
    if (type == Services::Hooks::CallType::BEFORE_ORIGINAL &&
        structure_type == NWNX_STRUCTS_EXPECTED_TYPE)
    {
        g_lastPushedStruct = static_cast<CGameEffect*>(engine_structure);
    }
}

}
