#include "FamilyController.h"

#include <QInputDialog>
#include <QMessageBox>

namespace ui
{

    using core::entities::Gender;
    using core::entities::Marriage;
    using core::entities::PersonNode;
    using core::services::BranchAnalyzer;

    ////////////////////////////////////////////////////////

    FamilyController::FamilyController(
        FamilyTreeView *view,
        PersonInspector *inspector,
        QObject *parent)
        : QObject(parent),
          m_view(view),
          m_inspector(inspector)
    {
        Q_ASSERT(m_view);

        connect(m_view, &FamilyTreeView::personClicked,
                this, &FamilyController::onPersonClicked);

        connect(m_view, &FamilyTreeView::personAddSonRequested,
                this, &FamilyController::onAddSon);

        connect(m_view, &FamilyTreeView::personAddDaughterRequested,
                this, &FamilyController::onAddDaughter);

        connect(m_view, &FamilyTreeView::personAddWifeRequested,
                this, &FamilyController::onAddWife);

        connect(m_view, &FamilyTreeView::personRemoveRequested,
                this, &FamilyController::onRemove);

        connect(m_view, &FamilyTreeView::personEditRequested,
                this, &FamilyController::onEdit);

        if (m_inspector)
        {
            connect(m_inspector,
                    &PersonInspector::personEdited,
                    this,
                    [this](auto *p, bool relayout)
                    {
                        if (relayout)
                            rebuildAll();
                        else
                            m_view->updatePerson(p);

                        updateVisualState();
                    });
        }
    }

    ////////////////////////////////////////////////////////

    void FamilyController::setFamilyTree(core::FamilyTree *tree)
    {
        m_tree = tree;
        m_firstLoad = true;
        rebuildAll();
    }

    ////////////////////////////////////////////////////////

    void FamilyController::rebuildAll()
    {
        if (!m_view)
            return;

        m_view->setFamilyTree(m_tree);

        if (m_firstLoad)
        {
            m_view->zoomToFit();
            m_firstLoad = false;
        }

        rebuildMainLine();
        updateVisualState();
    }

    ////////////////////////////////////////////////////////

    void FamilyController::rebuildMainLine()
    {
        m_mainLine.clear();

        if (!m_tree || !m_tree->ancestor())
            return;

        auto line =
            BranchAnalyzer::mainLine(
                m_tree->ancestor());

        for (auto *p : line)
            m_mainLine.insert(p);

        m_view->setMainLine(line);
    }

    ////////////////////////////////////////////////////////

    void FamilyController::updateVisualState()
    {
        if (!m_view)
            return;

        const auto &items = m_view->items();

        for (auto it = items.begin(); it != items.end(); ++it)
        {
            const PersonNode *person = it.key();
            PersonItem *item = it.value();

            item->setSelected(person == m_selected);
            item->setMainLine(m_mainLine.contains(person));

            bool extinct =
                BranchAnalyzer::isExtinctBranch(person);

            item->setExtinct(extinct &&
                             !m_mainLine.contains(person));
        }
    }

    ////////////////////////////////////////////////////////

    QString FamilyController::askName(const QString &title)
    {
        bool ok = false;

        QString name =
            QInputDialog::getText(
                m_view,
                title,
                "Name:",
                QLineEdit::Normal,
                "",
                &ok);

        return (ok && !name.isEmpty())
                   ? name
                   : QString();
    }

    PersonNode *FamilyController::createPerson(
        const QString &name,
        Gender g)
    {
        if (!m_tree)
            return nullptr;

        return new PersonNode(
            m_tree->generateId(),
            name,
            g);
    }

    ////////////////////////////////////////////////////////
    // Selection
    ////////////////////////////////////////////////////////

    void FamilyController::onPersonClicked(
        const PersonNode *person)
    {
        m_selected = person;

        if (m_inspector)
            m_inspector->setPerson(
                const_cast<PersonNode *>(person));

        updateVisualState();
    }

    ////////////////////////////////////////////////////////
    // Add Son
    ////////////////////////////////////////////////////////

    void FamilyController::onAddSon(
        const PersonNode *father,
        const PersonNode *wife)
    {
        if (!m_tree || !father || !wife)
            return;

        QString name = askName("Add Son");
        if (name.isEmpty())
            return;

        auto *son = createPerson(name, Gender::Male);

        int order = 0;

        for (const Marriage &m : father->marriages())
        {
            if (m.wife() == wife)
            {
                order = m.children().size();
                break;
            }
        }

        m_tree->addSon(
            const_cast<PersonNode *>(father),
            const_cast<PersonNode *>(wife),
            son,
            order);

        rebuildAll();
    }

    ////////////////////////////////////////////////////////
    // Add Daughter
    ////////////////////////////////////////////////////////

    void FamilyController::onAddDaughter(
        const PersonNode *father,
        const PersonNode *wife)
    {
        if (!m_tree || !father || !wife)
            return;

        QString name = askName("Add Daughter");
        if (name.isEmpty())
            return;

        auto *daughter =
            createPerson(name, Gender::Female);

        int order = 0;

        for (const Marriage &m : father->marriages())
        {
            if (m.wife() == wife)
            {
                order = m.children().size();
                break;
            }
        }

        m_tree->addDaughter(
            const_cast<PersonNode *>(father),
            const_cast<PersonNode *>(wife),
            daughter,
            order);

        rebuildAll();
    }

    ////////////////////////////////////////////////////////
    // Add Wife
    ////////////////////////////////////////////////////////

    void FamilyController::onAddWife(
        const PersonNode *husband)
    {
        if (!m_tree || !husband)
            return;

        if (husband->gender() != Gender::Male)
            return;

        QString name = askName("Add Wife");
        if (name.isEmpty())
            return;

        auto *wife =
            createPerson(name, Gender::Female);

        m_tree->addMarriage(
            const_cast<PersonNode *>(husband),
            wife);

        rebuildAll();
    }

    ////////////////////////////////////////////////////////
    // Edit
    ////////////////////////////////////////////////////////

    void FamilyController::onEdit(const PersonNode *person)
    {
        if (!person || !m_inspector)
            return;

        m_selected = person;

        m_inspector->setPerson(
            const_cast<PersonNode *>(person));

        emit inspectorRequested();
    }

    ////////////////////////////////////////////////////////
    // Remove
    ////////////////////////////////////////////////////////

    void FamilyController::onRemove(
        const PersonNode *person)
    {
        if (!m_tree || !person)
            return;

        if (!m_tree->canRemove(person))
        {
            QMessageBox::warning(
                m_view,
                "Cannot remove",
                "This person cannot be removed.");
            return;
        }

        auto reply =
            QMessageBox::question(
                m_view,
                "Confirm remove",
                QString("Remove \"%1\"?")
                    .arg(person->name()),
                QMessageBox::Yes | QMessageBox::No);

        if (reply != QMessageBox::Yes)
            return;

        if (!m_tree->removePerson(person))
            return;

        m_selected = nullptr;
        rebuildAll();
    }

} // namespace ui
