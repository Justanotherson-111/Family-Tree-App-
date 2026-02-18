#pragma once

#include "entities/PersonNode.h"

namespace core::rules
{

    class FamilyRules
    {
    public:
        // Whether a person can continue the lineage
        static bool canContinueLineage(
            const entities::PersonNode *person);

        // Choose heir (eldest valid son)
        static const entities::PersonNode *
        chooseHeir(const entities::PersonNode *deceased);
    };

}
