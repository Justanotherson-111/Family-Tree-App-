#pragma once

#include <QList>
#include "entities/PersonNode.h"

namespace core::services
{

    class BranchAnalyzer
    {
    public:
        // Returns the main lineage line from ancestor downward
        static QList<const entities::PersonNode *>
        mainLine(const entities::PersonNode *ancestor);

        // Whether a branch has no valid male heir
        static bool
        isExtinctBranch(const entities::PersonNode *person);

    private:
        // Find eldest son that can continue lineage
        static const entities::PersonNode *
        findEldestLineageSon(const entities::PersonNode *person);
    };

}
