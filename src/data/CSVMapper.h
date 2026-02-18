#pragma once

#include <QTextStream>
#include <QSet>
#include <QMap>

#include "FamilyTree.h"
#include "entities/PersonNode.h"

namespace data
{
    class CSVMapper
    {
    public:
        static bool toCSV(QTextStream &stream, const core::entities::PersonNode *p);

        static core::FamilyTree *fromCSV(QTextStream &stream);
    };
}