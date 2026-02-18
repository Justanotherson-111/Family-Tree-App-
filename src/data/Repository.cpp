#include "Repository.h"
#include "JsonMapper.h"
#include "CSVMapper.h"

#include <QFile>
#include <QJsonDocument>

namespace data
{

    core::FamilyTree *
    Repository::loadJson(const QString &filePath)
    {
        QFile file(filePath);

        if (!file.open(QIODevice::ReadOnly))
            return nullptr;

        const auto doc =
            QJsonDocument::fromJson(file.readAll());

        if (!doc.isObject())
            return nullptr;

        auto *tree =
            JsonMapper::fromJson(doc.object());

        if (tree)
            tree->rebuildIdRegistry(); // Important

        return tree;
    }

    bool Repository::saveJson(const core::FamilyTree *tree,
                              const QString &filePath)
    {
        if (!tree)
            return false;

        QFile file(filePath);

        if (!file.open(QIODevice::WriteOnly))
            return false;

        QJsonDocument doc(
            JsonMapper::toJson(tree));

        file.write(doc.toJson(
            QJsonDocument::Indented));

        return true;
    }

    bool Repository::saveCSV(const core::FamilyTree *tree,
                             const QString &filePath)
    {
        if (!tree)
            return false;

        QFile file(filePath);

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return false;

        QTextStream textStream(&file);
        // Header
        textStream << "id,name,gender,birth,death,job,father,mother,spouses\n";

        CSVMapper::toCSV(textStream, tree->ancestor());

        return true;
    }

    core::FamilyTree *
    Repository::loadCSV(const QString &filePath)
    {
        QFile file(filePath);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return nullptr;

        QTextStream ts(&file);

        auto *tree = CSVMapper::fromCSV(ts);

        if (tree)
            tree->rebuildIdRegistry(); // Important

        return tree;
    }

}
