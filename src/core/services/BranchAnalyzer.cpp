#include "BranchAnalyzer.h"
#include "rules/FamilyRules.h"

namespace core::services
{

    using entities::PersonNode;
    using rules::FamilyRules;

    QList<const PersonNode *>
    BranchAnalyzer::mainLine(const PersonNode *ancestor)
    {
        QList<const PersonNode *> result;

        const PersonNode *current = ancestor;

        while (current)
        {
            result.append(current);
            current = findEldestLineageSon(current);
        }

        return result;
    }

    bool BranchAnalyzer::isExtinctBranch(
        const PersonNode *person)
    {
        if (!person)
            return true;

        return findEldestLineageSon(person) == nullptr;
    }

    const PersonNode *
    BranchAnalyzer::findEldestLineageSon(
        const PersonNode *person)
    {
        if (!person)
            return nullptr;

        for (const auto &marriage : person->marriages())
        {
            for (auto *son : marriage.children())
            {
                if (FamilyRules::canContinueLineage(son))
                    return son;
            }
        }

        return nullptr;
    }

}
