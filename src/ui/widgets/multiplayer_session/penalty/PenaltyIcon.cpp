#include "multiplayer_session/penalty/PenaltyIcon.h"
#include <QWidget>
#include "StyleSheetFactory.h"
#include "multiplayer_session/penalty/PenaltyFlag.h"
#include "multiplayer_session/penalty/PenaltyTextBackground.h"



UserInterface::Widget::PenaltyIcon::PenaltyIcon(QWidget* parent) : 
    QWidget(parent),
    m_flagIcon(new UserInterface::Widget::PenaltyFlag(this)),
    m_textBackground(new UserInterface::Widget::PenaltyTextBackground(this)),
    m_text(new QLabel(this)),
    m_active(false),
    m_timePen(0),
    m_driveThroughs(0),
    m_stopGos(0) {

    if (m_flagIcon) {

        m_flagIcon->hide();

    }

    if (m_textBackground) {

        m_textBackground->hide();

    }
    UserInterface::StyleSheetFactory* instance = UserInterface::StyleSheetFactory::instance();
    Q_ASSERT(instance);
    if (m_text) {

        if (instance) {

            m_text->setStyleSheet(instance->requestByColorAndThickness(UserInterface::StyleSheetFactory::FontThickness::Bold));

        }
        m_text->hide();
        m_text->setAlignment(Qt::AlignCenter);

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

            m_text->hide();
            m_textBackground->hide();
            m_flagIcon->hide();

        }
        // If activated now, or if just values updated, set text, resize the background, and display
        else if (m_active) {

            m_flagIcon->show();

            const uint16_t baseX = m_flagIcon->x() + (m_flagIcon->width() / 2);
            const uint16_t baseY = m_flagIcon->y() + (m_flagIcon->height() / 2);

            m_text->setText(generateText());
            m_text->show();
            m_text->move(baseX, baseY);

            m_textBackground->show();
            m_textBackground->resize(m_text->width() + (HORIZONTAL_OFFSET * 2),
                m_text->height() + (VERTICAL_OFFSET * 2));
            m_textBackground->move(baseX, baseY);


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