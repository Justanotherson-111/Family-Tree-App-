#pragma once

#include <QString>
#include "FamilyTree.h"

namespace data
{

    class Repository
    {
    public:
        static core::FamilyTree *
        loadJson(const QString &filePath);

        static bool
        saveJson(const core::FamilyTree *tree,
                 const QString &filePath);

        static core::FamilyTree *
        loadCSV(const QString &filePath);

        static bool
        saveCSV(const core::FamilyTree *tree,
                const QString &filePath);
    };

}
