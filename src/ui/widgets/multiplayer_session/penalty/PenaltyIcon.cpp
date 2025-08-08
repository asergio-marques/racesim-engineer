#include "multiplayer_session/penalty/PenaltyIcon.h"

#include <QGridLayout>
#include "base/TextInterface.h"
#include "multiplayer_session/penalty/PenaltyFlag.h"
#include "multiplayer_session/penalty/PenaltyTextBackground.h"



UserInterface::Widget::PenaltyIcon::PenaltyIcon(QWidget* parent) : 
    QWidget(parent),
    m_flagIcon(new UserInterface::Widget::PenaltyFlag(parent)),
    m_textBackground(new UserInterface::Widget::PenaltyTextBackground(parent)),
    m_text(new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::PenaltyIcon, parent)),
    m_active(false),
    m_timePen(0),
    m_driveThroughs(0),
    m_stopGos(0) {

	QGridLayout* layout = new QGridLayout(this);
	// The layout is a bit complicated but it shall be constructed as follows, where TXBG is the background of the text and TXPN is the text, the rest being just the flag icon
    //          | col0 | col1 | col2 | col3 | col4 |
    // row 0 =  | ---- | ---- | ---- | ---- | ---- |
    // row 1 =  | ---- | TXBG | TXBG | TXBG | ---- |
    // row 2 =  | ---- | TXBG | TXPN | TXBG | ---- |
    // row 3 =  | ---- | TXBG | TXBG | TXBG | ---- |
    // row 4 =  | ---- | ---- | ---- | ---- | ---- |
    // rows 0, 1, 3 and 4, and cols 1 and 3, are a fixed size spacing equivalent to TEXT_BACKGROUND_OFFSET

    if (m_flagIcon) {

		m_flagIcon->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    }

    if (m_textBackground) {

        m_textBackground->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    }

    if (m_text) {

        m_text->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_text->setFontThickness(UserInterface::Widget::FontThickness::Bold);
        m_text->setAlignment(Qt::AlignCenter);

    }

    if (layout) {

        // cols 1 and 3 should never stretch and should always have 3 pixels of width
        layout->setColumnMinimumWidth(1, SPACING_OFFSET);
        layout->setColumnStretch(1, 0);
        layout->setColumnMinimumWidth(3, SPACING_OFFSET);
        layout->setColumnStretch(3, 0);

        // rows 0, 1, 3 and 4 should never stretch and should always have 3 pixels of height
        layout->setRowMinimumHeight(0, SPACING_OFFSET);
        layout->setRowStretch(0, 0);
        layout->setRowMinimumHeight(1, SPACING_OFFSET);
        layout->setRowStretch(1, 0);
        layout->setRowMinimumHeight(3, SPACING_OFFSET);
        layout->setRowStretch(1, 0);
        layout->setRowMinimumHeight(4, SPACING_OFFSET);
        layout->setRowStretch(4, 0);

        // the cell at col 2/row 2 is what has the penalty text, so it should use as much space as possible
		layout->setColumnStretch(2, 5);
		layout->setRowStretch(2, 5);

		layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);
		layout->addWidget(m_flagIcon, 0, 0, 5, 5, Qt::AlignCenter);
        layout->addWidget(m_textBackground, 1, 1, 3, 3, Qt::AlignCenter);
		layout->addWidget(m_text, 2, 2, 1, 1, Qt::AlignCenter);

    }

}



void UserInterface::Widget::PenaltyIcon::addTimePenalty(const int32_t change) {

    m_timePen += change;
    checkDisplayStatus();

}



void UserInterface::Widget::PenaltyIcon::addDriveThrough(const int32_t change) {

    m_driveThroughs += change;
    checkDisplayStatus();

}



void UserInterface::Widget::PenaltyIcon::addStopGo(const int32_t change) {

    m_stopGos += change;
    checkDisplayStatus();

}



void UserInterface::Widget::PenaltyIcon::checkDisplayStatus() {

    const bool previousActiveStatus = m_active;
    m_active = m_timePen > 0 || m_driveThroughs > 0 || m_stopGos > 0;

    if (m_flagIcon && m_textBackground && m_text) {

        // If deactivated now, reset status to default
        if (!m_active && previousActiveStatus) {

            hide();

        }
        // If activated now, or if just values updated, set text, adjust sizes and show
        else if (m_active) {

            m_text->setText(generateText());
            adjustSize();
            show();

        }

    }

}



const QString UserInterface::Widget::PenaltyIcon::generateText() {

    QString text = "";
    uint16_t totalTimePen = 5000 * m_stopGos + m_timePen;

    if (m_driveThroughs != 0) {

        if (!text.isEmpty()) text += "+";
        // if only 1 drive-through, don't show number
        text +=
            (m_driveThroughs == 1) ? "DT" : QString::number(m_driveThroughs) + "DT";

    }
    if (totalTimePen != 0) {

        if (!text.isEmpty()) text += "+";
        const int32_t fractionPart = totalTimePen % 1000;
        if (fractionPart > 0) text += QString::number(totalTimePen / 1000) + "." + QString::number(fractionPart);
        else text += QString::number(totalTimePen / 1000);

    }

    return text;

}