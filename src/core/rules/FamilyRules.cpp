#include "FamilyRules.h"

namespace core::rules
{

    using core::entities::PersonNode;

    bool FamilyRules::canContinueLineage(
        const PersonNode *person)
    {
        if (!person)
            return false;

        return person->canContinueLineage();
    }

    const PersonNode *
    FamilyRules::chooseHeir(
        const PersonNode *deceased)
    {
        if (!deceased)
            return nullptr;

        // First pass:
        // eldest son who can continue lineage
        for (const auto &marriage : deceased->marriages())
        {
            for (auto *son : marriage.sons())
            {
                if (canContinueLineage(son))
                    return son;
            }
        }

        // Fallback:
        // just eldest son
        for (const auto &marriage : deceased->marriages())
        {
            if (!marriage.sons().isEmpty())
                return marriage.sons().first();
        }

        return nullptr;
    }

}
