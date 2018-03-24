#pragma once

#include "Plugin.hpp"
#include "Services/Events/Events.hpp"
#include "API/Types.hpp"
#include "API/CGameEffect.hpp"
#include "Services/Hooks/Hooks.hpp"

using ArgumentStack = NWNXLib::Services::Events::ArgumentStack;

namespace Structs {

class Structs : public NWNXLib::Plugin
{
public:
    Structs(const Plugin::CreateParams& params);
    virtual ~Structs();

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
