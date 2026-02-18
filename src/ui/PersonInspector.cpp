#include "PersonInspector.h"
#include "entities/PersonNode.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QSignalBlocker>
#include <QCloseEvent>

using namespace core::entities;

namespace ui
{

    PersonInspector::PersonInspector(QWidget *parent)
        : QWidget(parent)
    {
        setAttribute(Qt::WA_DeleteOnClose, false);

        auto *layout = new QVBoxLayout(this);

        // ID
        layout->addWidget(new QLabel("ID:"));
        m_idLabel = new QLabel(this);
        layout->addWidget(m_idLabel);

        // Name
        layout->addWidget(new QLabel("Name:"));
        m_nameEdit = new QLineEdit(this);
        layout->addWidget(m_nameEdit);

        // Gender
        layout->addWidget(new QLabel("Gender:"));
        m_genderCombo = new QComboBox(this);
        m_genderCombo->addItems({"Male", "Female"});
        layout->addWidget(m_genderCombo);

        // Job
        layout->addWidget(new QLabel("Job:"));
        m_jobEdit = new QLineEdit(this);
        layout->addWidget(m_jobEdit);

        // Birth date
        layout->addWidget(new QLabel("Birth Date:"));
        m_birthDateEdit = new QDateEdit(this);
        m_birthDateEdit->setCalendarPopup(true);
        m_birthDateEdit->setDisplayFormat("yyyy-MM-dd");
        layout->addWidget(m_birthDateEdit);

        // Death date
        layout->addWidget(new QLabel("Death Date:"));
        m_deathDateEdit = new QDateEdit(this);
        m_deathDateEdit->setCalendarPopup(true);
        m_deathDateEdit->setDisplayFormat("yyyy-MM-dd");
        m_deathDateEdit->setSpecialValueText("Alive");
        m_deathDateEdit->setDate(QDate()); // invalid by default
        layout->addWidget(m_deathDateEdit);

        layout->addStretch();

        // Connections
        connect(m_nameEdit, &QLineEdit::editingFinished,
                this, &PersonInspector::onNameEdited);

        connect(m_genderCombo, &QComboBox::currentIndexChanged,
                this, &PersonInspector::onGenderChanged);

        connect(m_jobEdit, &QLineEdit::editingFinished,
                this, &PersonInspector::onJobEdited);

        connect(m_birthDateEdit, &QDateEdit::dateChanged,
                this, &PersonInspector::onBirthDateChanged);

        connect(m_deathDateEdit, &QDateEdit::dateChanged,
                this, &PersonInspector::onDeathDateChanged);

        setEditorsEnabled(false);
    }

    ////////////////////////////////////////////////////////////
    // Public
    ////////////////////////////////////////////////////////////

    void PersonInspector::setPerson(PersonNode *person)
    {
        m_person = person;
        updateUiFromPerson();
    }

    ////////////////////////////////////////////////////////////
    // UI Sync
    ////////////////////////////////////////////////////////////

    void PersonInspector::updateUiFromPerson()
    {
        QSignalBlocker b1(m_nameEdit);
        QSignalBlocker b2(m_genderCombo);
        QSignalBlocker b3(m_jobEdit);
        QSignalBlocker b4(m_birthDateEdit);
        QSignalBlocker b5(m_deathDateEdit);

        if (!m_person)
        {
            m_idLabel->clear();
            m_nameEdit->clear();
            m_jobEdit->clear();
            setEditorsEnabled(false);
            return;
        }

        setEditorsEnabled(true);

        m_idLabel->setText(m_person->id());
        m_nameEdit->setText(m_person->name());
        m_jobEdit->setText(m_person->job());

        m_genderCombo->setCurrentIndex(
            m_person->gender() == Gender::Male ? 0 : 1);

        m_birthDateEdit->setDate(m_person->birthDate());

        if (m_person->deathDate().isValid())
            m_deathDateEdit->setDate(m_person->deathDate());
        else
            m_deathDateEdit->setDate(QDate());
    }

    void PersonInspector::setEditorsEnabled(bool enabled)
    {
        m_nameEdit->setEnabled(enabled);
        m_genderCombo->setEnabled(enabled);
        m_jobEdit->setEnabled(enabled);
        m_birthDateEdit->setEnabled(enabled);
        m_deathDateEdit->setEnabled(enabled);
    }

    ////////////////////////////////////////////////////////////
    // Slots
    ////////////////////////////////////////////////////////////

    void PersonInspector::onNameEdited()
    {
        if (!m_person)
            return;

        const QString v = m_nameEdit->text();
        if (v == m_person->name())
            return;

        m_person->rename(v);
        emit personEdited(m_person, false);
    }

    void PersonInspector::onGenderChanged()
    {
        if (!m_person)
            return;

        Gender g = (m_genderCombo->currentIndex() == 0)
                       ? Gender::Male
                       : Gender::Female;

        if (g == m_person->gender())
            return;

        m_person->setGender(g);
        emit personEdited(m_person, true);
    }

    void PersonInspector::onJobEdited()
    {
        if (!m_person)
            return;

        const QString v = m_jobEdit->text();
        if (v == m_person->job())
            return;

        m_person->setJob(v);
        emit personEdited(m_person, false);
    }

    void PersonInspector::onBirthDateChanged()
    {
        if (!m_person)
            return;

        m_person->setBirthDate(m_birthDateEdit->date());
        emit personEdited(m_person, false);
    }

    void PersonInspector::onDeathDateChanged()
    {
        if (!m_person)
            return;

        QDate d = m_deathDateEdit->date();

        if (!d.isValid())
            m_person->clearDeathDate();
        else
            m_person->setDeathDate(d);

        emit personEdited(m_person, false);
    }
}
