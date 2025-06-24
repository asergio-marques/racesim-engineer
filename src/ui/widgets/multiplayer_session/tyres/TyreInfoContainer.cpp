#include "multiplayer_session/tyres/TyreInfoContainer.h"

#include <cstdint>
#include <QString>
#include <QGridLayout>
#include <QWidget>
#include "base/Container.h"
#include "base/TextInterface.h"
#include "multiplayer_session/tyres/TyreIcon.h"



UserInterface::Widget::TyreInfoContainer::TyreInfoContainer(QWidget* parent) :
    QWidget(parent),
    m_visualCompoundIcon(nullptr),
    m_actualCompoundText(nullptr),
    m_lapsText(nullptr),
    m_numLaps(0) {

    m_visualCompoundIcon = new UserInterface::Widget::TyreIcon(UserInterface::Widget::ID::TyreInfo, parent);
    Q_ASSERT(m_visualCompoundIcon);
    if (m_visualCompoundIcon) {

        m_visualCompoundIcon->setAlignment(Qt::AlignCenter);
        m_visualCompoundIcon->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_visualCompoundIcon->setScaledContents(true);
        m_visualCompoundIcon->setKeepAspectRatio(true);
        m_visualCompoundIcon->hide();

    }
    m_actualCompoundText = new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::TyreInfo, parent);
    Q_ASSERT(m_actualCompoundText);
    if (m_actualCompoundText) {

        m_actualCompoundText->setAlignment(Qt::AlignCenter);
        m_actualCompoundText->setFontThickness(UserInterface::Widget::FontThickness::ExtraBold);
        m_actualCompoundText->setFontSize(12);
        m_actualCompoundText->setText("?");
        m_actualCompoundText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_actualCompoundText->setScaledContents(true);
        m_actualCompoundText->hide();

    }
    m_lapsText = new UserInterface::Widget::TextInterface(UserInterface::Widget::ID::TyreInfo, parent);
    Q_ASSERT(m_lapsText);
    if (m_lapsText) {

        m_lapsText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        m_actualCompoundText->setFontThickness(UserInterface::Widget::FontThickness::ExtraBold);
        m_lapsText->setFontSize(18);
        m_lapsText->setText(QString::number(m_numLaps));
        m_lapsText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_lapsText->setScaledContents(true);
        m_lapsText->hide();

    }

    QGridLayout* layout = new QGridLayout;
    setLayout(layout);
    layout->addWidget(m_visualCompoundIcon, 0, 0, Qt::AlignCenter);
    layout->addWidget(m_actualCompoundText, 0, 0, Qt::AlignCenter);
    layout->addWidget(m_lapsText, 0, 1, Qt::AlignLeft | Qt::AlignVCenter);
    setMaximumWidth(120);
    setMaximumHeight(48);

}



void UserInterface::Widget::TyreInfoContainer::Init(Tyre::Internal::Actual actualTyreCompound, Tyre::Internal::Visual visualTyreCompound, uint8_t numLapsAtStart, uint8_t stintNo) {

    if (m_actualCompoundText) {

        /*switch (actualTyreCompound) {

            case Tyre::Internal::Actual::F1_C6:
                m_actualCompoundText->setText("C6");
                break;
            case Tyre::Internal::Actual::F1_C5:
                m_actualCompoundText->setText("C5");
                break;
            case Tyre::Internal::Actual::F1_C4:
                m_actualCompoundText->setText("C4");
                break;
            case Tyre::Internal::Actual::F1_C3:
                m_actualCompoundText->setText("C3");
                break;
            case Tyre::Internal::Actual::F1_C2:
                m_actualCompoundText->setText("C2");
                break;
            case Tyre::Internal::Actual::F1_C1:
                m_actualCompoundText->setText("C1");
                break;
            case Tyre::Internal::Actual::F1_C0:
                m_actualCompoundText->setText("C0");
                break;
            case Tyre::Internal::Actual::F1_Intermediate:
            case Tyre::Internal::Actual::F2_Intermediate:
                m_actualCompoundText->setText("I");
                break;
            case Tyre::Internal::Actual::F1_ExtremeWet:
            case Tyre::Internal::Actual::F2_ExtremeWet:
                m_actualCompoundText->setText("W");
                break;
            case Tyre::Internal::Actual::F2_HyperSoft:
                m_actualCompoundText->setText("HS");
                break;
            case Tyre::Internal::Actual::F2_SuperSoft:
                m_actualCompoundText->setText("SS");
                break;
            case Tyre::Internal::Actual::F2_Soft:
                m_actualCompoundText->setText("S");
                break;
            case Tyre::Internal::Actual::F2_Medium:
                m_actualCompoundText->setText("M");
                break;
            case Tyre::Internal::Actual::F2_Hard:
                m_actualCompoundText->setText("H");
                break;
            default:
                m_actualCompoundText->setText("?");

        }*/
        m_actualCompoundText->setText(QString::number(stintNo));

        m_actualCompoundText->show();

    }

    if (m_visualCompoundIcon) {

        m_visualCompoundIcon->SetType(visualTyreCompound);
        m_visualCompoundIcon->show();

    }

    m_numLaps = numLapsAtStart;

    if (m_lapsText) {

        m_lapsText->setText(QString::number(m_numLaps));
        m_lapsText->show();

    }

}


void UserInterface::Widget::TyreInfoContainer::IncrementLap() {

    ++m_numLaps;
    if (m_lapsText) {

        m_lapsText->setText(QString::number(m_numLaps));

    }

}