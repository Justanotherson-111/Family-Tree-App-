#include "PersonInfoWidget.h"
#include "entities/PersonNode.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>

using namespace core::entities;

namespace ui
{

    PersonInfoWidget::PersonInfoWidget(QWidget *p)
        : QDialog(p)
    {
        setWindowTitle("Person Information");
        resize(400, 300);

        QVBoxLayout *layout = new QVBoxLayout(this);

        m_nameLabel = new QLabel;
        m_birthLabel = new QLabel;
        m_deathLabel = new QLabel;
        m_jobLabel = new QLabel;
        m_noteEdit = new QTextEdit;

        m_noteEdit->setReadOnly(true);

        layout->addWidget(m_nameLabel);
        layout->addWidget(m_birthLabel);
        layout->addWidget(m_deathLabel);
        layout->addWidget(m_jobLabel);
        layout->addWidget(new QLabel("Note:"));
        layout->addWidget(m_noteEdit);

        QPushButton *closeBtn = new QPushButton("Close");
        layout->addWidget(closeBtn);

        connect(closeBtn, &QPushButton::clicked,
                this, &QDialog::accept);

        setLayout(layout);
    }

    void PersonInfoWidget::setPerson(const PersonNode *person)
    {
        if (!person)
            return;

        m_nameLabel->setText("Name: " + person->name());

        m_birthLabel->setText("Birth: " +
                              (person->birthDate().isValid()
                                   ? person->birthDate().toString("dd-MM-yyyy")
                                   : "?"));

        m_deathLabel->setText("Death: " +
                              (person->isDeceased()
                                   ? person->deathDate().toString("dd-MM-yyyy")
                                   : "Alive"));

        m_jobLabel->setText("Job: " + person->job());

        m_noteEdit->setText(person->note());
    }

}