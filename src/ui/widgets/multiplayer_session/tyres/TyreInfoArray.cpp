#include "multiplayer_session/tyres/TyreInfoArray.h"
#include "multiplayer_session/tyres/TyreInfoContainer.h"

#include <QGridLayout>
#include <QList>




UserInterface::Widget::TyreInfoArray::TyreInfoArray(QWidget* parent) :
    QWidget(parent),
    m_tyres(),
    m_stintIndex(UINT8_MAX),
    m_gridLayout(nullptr) {

    m_gridLayout = new QGridLayout;
    Q_ASSERT(m_gridLayout);
    if (m_gridLayout) {

        m_gridLayout->setSpacing(0);

        for (size_t i = 0; i < 5; ++i) {

            auto* tyre = new UserInterface::Widget::TyreInfoContainer(this);
            Q_ASSERT(tyre);
            if (tyre) {

                tyre->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                m_tyres.push_back(tyre);
                m_gridLayout->addWidget(tyre, 0, i, Qt::AlignLeft | Qt::AlignVCenter);
                tyre->hide();

            }

        }

        setLayout(m_gridLayout);

    }

}



void UserInterface::Widget::TyreInfoArray::TyreChange(Tyre::Internal::Actual actualTyreCompound, Tyre::Internal::Visual visualTyreCompound, uint8_t tyreAge, bool pitBeforeLine) {

    // increment the index, as this member starts at UINT8_MAX, it'll go to 0 for stint number 1
    ++m_stintIndex;

    // TODO implement logic related to pitBeforeLine
    // always take heed of the maximum of 5 tyres to be displayed, and the fact this has been incremented already
    // this logic gets index 0, 1, etc when stint index < 5 correctly
    // once we reach stint index = 5 (stint 6), we reset the "old" stint info in the display
    uint8_t index = m_stintIndex % 5;
    auto* tyre = m_tyres[index];
    if (tyre) {

        tyre->Init(actualTyreCompound, visualTyreCompound, tyreAge, m_stintIndex + 1);
        tyre->show();

    }

    // cycle the layout, moving all entries one to the right
    CycleLayout();

}



void UserInterface::Widget::TyreInfoArray::LapCompletedWithTyre() {

    auto* tyre = m_tyres[m_stintIndex % 5];
    if (tyre) {

        tyre->IncrementLap();

    }

}



void UserInterface::Widget::TyreInfoArray::CycleLayout() {

    // no need for evil operations when there's only a single stint
    if (m_stintIndex == 0) {

        return;

    }
    // hide widgets not in use, and delete items in the layout for a complete reset
    while (QLayoutItem* item = m_gridLayout->takeAt(0)) {

        if (item && item->widget()) {

            item->widget()->hide(); 

        }

        delete item;

    }
    // don't ask me why it only works like this, if activeStints actually represents how many stint icons
    // are active, this all goes tits up
    uint8_t activeStints = std::min<uint8_t>(m_stintIndex, 4);
    for (uint8_t i = 0; i < activeStints + 1; ++i) {

        // evil but genius; adding 5 does nothing to the final result, and prevents (m_stintIndex - i) from underflowing
        size_t index = (m_stintIndex + 5 - i) % 5;

        auto* tyre = m_tyres[index];
        tyre->show();
        m_gridLayout->addWidget(tyre, 0, i, Qt::AlignLeft | Qt::AlignVCenter);

    }
    if (activeStints < 4) {

        // one spacer item with the width of the leftover columns coming right up
        m_gridLayout->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, activeStints, 1, 5 - activeStints);

    }

    m_gridLayout->invalidate();
    updateGeometry();

}