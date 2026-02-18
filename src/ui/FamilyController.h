#pragma once

#include <QObject>
#include <QSet>

#include "FamilyTree.h"
#include "services/BranchAnalyzer.h"
#include "FamilyTreeView.h"
#include "PersonInspector.h"

namespace ui
{

    class FamilyController : public QObject
    {
        Q_OBJECT

    public:
        explicit FamilyController(
            FamilyTreeView *view,
            PersonInspector *inspector,
            QObject *parent = nullptr);

        void setFamilyTree(core::FamilyTree *tree);

    private slots:
        void onPersonClicked(const core::entities::PersonNode *);
        void onAddSon(const core::entities::PersonNode *, const core::entities::PersonNode *);
        void onAddDaughter(const core::entities::PersonNode *, const core::entities::PersonNode *);
        void onAddWife(const core::entities::PersonNode *);
        void onRemove(const core::entities::PersonNode *);
        void onEdit(const core::entities::PersonNode *);

    private:
        // ===== Core =====
        FamilyTreeView *m_view = nullptr;
        PersonInspector *m_inspector = nullptr;
        core::FamilyTree *m_tree = nullptr;

        const core::entities::PersonNode *m_selected = nullptr;
        QSet<const core::entities::PersonNode *> m_mainLine;

        // ===== Helpers =====
        void rebuildMainLine();
        void updateVisualState();
        void rebuildAll();

        QString askName(const QString &title);
        core::entities::PersonNode *createPerson(
            const QString &name,
            core::entities::Gender g);
    signals:
        void inspectorRequested();
    };

}
