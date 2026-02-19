#include "FamilyRules.h"

namespace core::rules
{

    using core::entities::Gender;
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

        // FIRST PASS:
        // eldest son who can continue lineage
        for (const auto &marriage : deceased->marriages())
        {
            for (auto *child : marriage.children())
            {
                if (child->gender() == Gender::Male &&
                    canContinueLineage(child))
                {
                    return child;
                }
            }
        }

        // FALLBACK:
        // just eldest son
        for (const auto &marriage : deceased->marriages())
        {
            for (auto *child : marriage.children())
            {
                if (child->gender() == Gender::Male)
                    return child;
            }
        }

        return nullptr;
    }

}
