#include "multiplayer_session/tyres/TyreInfoArray.h"
#include "multiplayer_session/tyres/TyreInfoContainer.h"

#include <cstdint>
#include <QList>
#include "base/Container.h"
#include "data/internal/Tyre.h"




UserInterface::Widget::TyreInfoArray::TyreInfoArray(QWidget* parent) :
	UserInterface::Widget::Container(UserInterface::Widget::ID::TyreInfo, parent),
	m_tyres(),
	m_stintIndex(UINT8_MAX) {

	for (size_t i = 0; i < 5; ++i) {

		auto* tyre = new UserInterface::Widget::TyreInfoContainer(this);
		Q_ASSERT(tyre);
		if (tyre) {

			tyre->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
			m_tyres.push_back(tyre);
			tyre->hide();

		}

	}

}



void UserInterface::Widget::TyreInfoArray::TyreChange(Tyre::Internal::Actual actualTyreCompound, Tyre::Internal::Visual visualTyreCompound, uint8_t tyreAge, bool pitBeforeLine) {

	// increment the index, as this member starts at UINT8_MAX, it'll go to 0 for stint number 1
	++m_stintIndex;

	// TODO implement logic related to pitBeforeLine
	auto* tyre = new UserInterface::Widget::TyreInfoContainer(this);
	Q_ASSERT(tyre);
	if (tyre) {

		m_tyres.push_back(tyre);
		tyre->Init(actualTyreCompound, visualTyreCompound, tyreAge, m_stintIndex + 1);

	}

	// cycle the layout, moving all entries one to the right
	RedoDisplay();

}



void UserInterface::Widget::TyreInfoArray::LapCompletedWithTyre() {

	// always update the last tyre in the list, as it is the one that was used for the lap
	auto* tyre = m_tyres.last();
	if (tyre) {

		tyre->IncrementLap();

	}

}



void UserInterface::Widget::TyreInfoArray::RedoDisplay() {

	// no need for anything if there have been no stints
	if (m_stintIndex == UINT8_MAX) {

		return;

	}
	for (size_t i = m_tyres.size() - 1; i > 0; --i) {

		auto* tyre = m_tyres[i];
		tyre->move(x(), y())

	}

}