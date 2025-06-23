#include "multiplayer_session/tyres/TyreInfoArray.h"
#include "multiplayer_session/tyres/TyreInfoContainer.h"

#include <QHBoxLayout>
#include <QList>

UserInterface::Widget::TyreInfoArray::TyreInfoArray(QWidget* parent) :
    QWidget(parent),
    m_tyres(),
    m_stintIndex(-1) {

    QHBoxLayout* layout = new QHBoxLayout;

    for (size_t i = 0; i < 5; ++i) {

        auto* tyre = new UserInterface::Widget::TyreInfoContainer(this);
        Q_ASSERT(tyre);
        if (tyre) {

            layout->addWidget(tyre);
            tyre->hide();

        }

    }

    setLayout(layout);

}



void UserInterface::Widget::TyreInfoArray::TyreChange(Tyre::Internal::Actual actualTyreCompound, Tyre::Internal::Visual visualTyreCompound, uint8_t tyreAge, bool pitBeforeLine) {

    // increment the index, as this member starts at UINT8_MAX, it'll go to 0 for stint number 1
    ++m_stintIndex;

    // TODO implement logic related to pitBeforeLine
    // always take heed of the maximum of 5 tyres to be displayed, and the fact this has been incremented already
    // this logic gets index 0, 1, etc when stint index < 5 correctly
    // once we reach stint index = 5 (stint 6), we reset the "old" stint info in the display
    auto* tyre = m_tyres[m_stintIndex % 5];
    if (tyre) {

        tyre->Init(actualTyreCompound, visualTyreCompound, tyreAge);
        tyre->show();

    }

    // cycle the layout, moving all entries one to the right
    CycleLayout();

}


void UserInterface::Widget::TyreInfoArray::LapCompletedWithTyre() {
    
    auto* tyre = m_tyres[m_stintIndex];
    if (tyre) {

        tyre->IncrementLap();

    }

}
void UserInterface::Widget::TyreInfoArray::CycleLayout() {

    if (m_stintIndex == 0) {
        
        // do nothing, as we don't have to cycle things when doing the first stint widgets, saves extra processing
        return;

    }

    // invalidate previous layout, construct new
    QHBoxLayout* layout = new QHBoxLayout;
    for (size_t i = 0; i < 5; ++i) {

        // When m_stintIndex is 0 (1st stint), this means the layout will have widgets in index 0, 4, 3, 2, 1, in this order.
        // When m_stintIndex is 1 (2nd stint), this means the layout will have widgets in index 1, 0, 4, 3, 2, in this order.
        // When m_stintIndex is 5 (6th stint), this means the layout will have widgets in index 0, 4, 3, 2, 1, in this order.
        auto* tyre = m_tyres[(m_stintIndex + 5 - i) % 5];
        layout->addWidget(tyre);

    }

    setLayout(layout);


}