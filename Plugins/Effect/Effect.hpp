#pragma once

#include "Plugin.hpp"
#include "Services/Events/Events.hpp"
#include "API/Types.hpp"
#include "API/CGameEffect.hpp"
#include "Services/Hooks/Hooks.hpp"


/* The code for the `Effect` and `ItemProperty` plugins are identical,
 * except for the following defines. If you make changes to this plugin,
 * copy the `.hpp` and `.cpp` files to the other plugin and adjust the
 * below defines appropriately.
 */
#define NWNX_STRUCTS_PLUGIN_NAME        Effect
#define NWNX_STRUCTS_EXPECTED_TYPE      0
#define NWNX_STRUCTS_STRINGIFY(X)       #X


using ArgumentStack = NWNXLib::Services::Events::ArgumentStack;

namespace NWNX_STRUCTS_PLUGIN_NAME {

class NWNX_STRUCTS_PLUGIN_NAME : public NWNXLib::Plugin
{
public:
    NWNX_STRUCTS_PLUGIN_NAME(const Plugin::CreateParams& params);
    virtual ~NWNX_STRUCTS_PLUGIN_NAME();

private:
    static void HandleStackPushEngineStructure(NWNXLib::Services::Hooks::CallType type,
                                               NWNXLib::API::CVirtualMachine *vm,
                                               int32_t structure_type,
                                               void *engine_structure);

    ArgumentStack GetDuration                   (ArgumentStack&& args);
    ArgumentStack GetDurationRemaining          (ArgumentStack&& args);
    ArgumentStack GetHasEffect                  (ArgumentStack&& args);
    ArgumentStack GetInteger                    (ArgumentStack&& args);
    ArgumentStack GetNumIntegers                (ArgumentStack&& args);
    ArgumentStack GetSpellId                    (ArgumentStack&& args);
    ArgumentStack GetTrueType                   (ArgumentStack&& args);
    ArgumentStack SetCasterLevel                (ArgumentStack&& args);
    ArgumentStack SetCreator                    (ArgumentStack&& args);
    ArgumentStack SetInteger                    (ArgumentStack&& args);
    ArgumentStack SetSpellId                    (ArgumentStack&& args);
    ArgumentStack SetTrueType                   (ArgumentStack&& args);

};

}
