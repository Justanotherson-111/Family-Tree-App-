#include "PersonInfoWidget.h"
#include "entities/PersonNode.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QSignalBlocker>

using namespace core::entities;

namespace ui
{

    // ------------------------------------------------------------
    // Helper
    // ------------------------------------------------------------
    static QString buildAncestralLine(PersonNode *person)
    {
        if (!person)
            return QString();

        QStringList chain;
        PersonNode *current = person;

        while (current)
        {
            chain.prepend(current->name());
            current = current->father();
        }

        return chain.join("  →  ");
    }

    // ------------------------------------------------------------
    // Constructor
    // ------------------------------------------------------------
    PersonInfoWidget::PersonInfoWidget(QWidget *p)
        : QDialog(p)
    {
        setWindowTitle("Person Information");
        resize(400, 450);

        QVBoxLayout *layout = new QVBoxLayout(this);

        // Fields
        m_nameEdit = new QLineEdit;
        m_genderCombo = new QComboBox;
        m_genderCombo->addItems({"Male", "Female"});

        m_jobEdit = new QLineEdit;

        m_birthEdit = new QDateEdit;
        m_birthEdit->setCalendarPopup(true);
        m_birthEdit->setDisplayFormat("yyyy-MM-dd");

        m_deathEdit = new QDateEdit;
        m_deathEdit->setCalendarPopup(true);
        m_deathEdit->setDisplayFormat("yyyy-MM-dd");
        m_deathEdit->setSpecialValueText("Alive");
        m_deathEdit->setDate(QDate());

        m_noteEdit = new QTextEdit;

        m_ancestralLineLabel = new QLabel;
        m_ancestralLineLabel->setWordWrap(true);
        m_ancestralLineLabel->setStyleSheet("color: gray;");

        // Layout
        layout->addWidget(new QLabel("Name:"));
        layout->addWidget(m_nameEdit);

        layout->addWidget(new QLabel("Gender:"));
        layout->addWidget(m_genderCombo);

        layout->addWidget(new QLabel("Job:"));
        layout->addWidget(m_jobEdit);

        layout->addWidget(new QLabel("Birth Date:"));
        layout->addWidget(m_birthEdit);

        layout->addWidget(new QLabel("Death Date:"));
        layout->addWidget(m_deathEdit);

        layout->addWidget(new QLabel("Note:"));
        layout->addWidget(m_noteEdit);

        layout->addWidget(new QLabel("Ancestral Line:"));
        layout->addWidget(m_ancestralLineLabel);

        // Buttons
        m_editButton = new QPushButton("Edit");
        m_saveButton = new QPushButton("Save");
        m_cancelButton = new QPushButton("Cancel");

        layout->addWidget(m_editButton);
        layout->addWidget(m_saveButton);
        layout->addWidget(m_cancelButton);

        m_saveButton->hide();
        m_cancelButton->hide();

        // Button logic
        connect(m_editButton, &QPushButton::clicked, this, [this]()
                { setEditMode(true); });

        connect(m_saveButton, &QPushButton::clicked, this, [this]()
                {
        if (!m_person)
            return;

        // Apply UI → Model
        m_person->rename(m_nameEdit->text());
        m_person->setJob(m_jobEdit->text());
        m_person->setNote(m_noteEdit->toPlainText());
        m_person->setBirthDate(m_birthEdit->date());

        Gender g = (m_genderCombo->currentIndex() == 0)
                       ? Gender::Male
                       : Gender::Female;

        m_person->setGender(g);

        QDate d = m_deathEdit->date();
        if (!d.isValid())
            m_person->clearDeathDate();
        else
            m_person->setDeathDate(d);

        updateUiFromPerson();   // refresh
        setEditMode(false); });

        connect(m_cancelButton, &QPushButton::clicked, this, [this]()
                {
        updateUiFromPerson();   // revert UI
        setEditMode(false); });

        setEditMode(false); // start readonly

        accept();
    }

    // ------------------------------------------------------------
    // Public
    // ------------------------------------------------------------
    void PersonInfoWidget::setPerson(PersonNode *p)
    {
        m_person = p;
        updateUiFromPerson();
    }

    // ------------------------------------------------------------
    // UI Sync
    // ------------------------------------------------------------
    void PersonInfoWidget::updateUiFromPerson()
    {
        if (!m_person)
            return;

        QSignalBlocker b1(m_nameEdit);
        QSignalBlocker b2(m_genderCombo);
        QSignalBlocker b3(m_jobEdit);
        QSignalBlocker b4(m_birthEdit);
        QSignalBlocker b5(m_deathEdit);
        QSignalBlocker b6(m_noteEdit);

        m_nameEdit->setText(m_person->name());
        m_jobEdit->setText(m_person->job());
        m_noteEdit->setText(m_person->note());

        m_genderCombo->setCurrentIndex(
            m_person->gender() == Gender::Male ? 0 : 1);

        m_birthEdit->setDate(m_person->birthDate());

        if (m_person->deathDate().isValid())
            m_deathEdit->setDate(m_person->deathDate());
        else
            m_deathEdit->setDate(QDate());

        m_ancestralLineLabel->setText(buildAncestralLine(m_person));
    }

    // ------------------------------------------------------------
    // Edit Mode
    // ------------------------------------------------------------
    void PersonInfoWidget::setEditMode(bool enabled)
    {
        m_editMode = enabled;

        m_nameEdit->setReadOnly(!enabled);
        m_jobEdit->setReadOnly(!enabled);
        m_noteEdit->setReadOnly(!enabled);

        m_genderCombo->setEnabled(enabled);
        m_birthEdit->setEnabled(enabled);
        m_deathEdit->setEnabled(enabled);

        m_editButton->setVisible(!enabled);
        m_saveButton->setVisible(enabled);
        m_cancelButton->setVisible(enabled);
    }

} // namespace ui