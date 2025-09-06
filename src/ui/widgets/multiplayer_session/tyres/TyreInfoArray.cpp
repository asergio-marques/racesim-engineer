#include "multiplayer_session/tyres/TyreInfoArray.h"
#include "multiplayer_session/tyres/TyreInfoContainer.h"

#include <cstdint>
#include <QList>
#include "base/Container.h"
#include "data/internal/Tyre.h"
#include "styles/DriverInfoRace.h"




UserInterface::Widget::TyreInfoArray::TyreInfoArray(QWidget* parent) :
	UserInterface::Widget::Container(UserInterface::Widget::ID::TyreInfo),
	m_widgetParent(parent),
	m_tyres(),
	m_numStints(0) {



}



void UserInterface::Widget::TyreInfoArray::move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) {

	if (m_tyres.size() == 0) {

		return;

	}

	RedoDisplay(x, y);

}



void UserInterface::Widget::TyreInfoArray::scale(const uint8_t percent) {

	// TODO

}



void UserInterface::Widget::TyreInfoArray::scale(const uint8_t percentX, const uint8_t percentY) {

	// TODO

}



void UserInterface::Widget::TyreInfoArray::setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) {

	if (m_tyres.size() == 0) {

		return;

	}

	for (uint8_t i = 0; i < m_tyres.size(); ++i) {

		auto* tyre = m_tyres[i];
		if (tyre) {
			
			// heights calculated inside
			tyre->setSize(UserInterface::Style::TyreInfoContainerMaxX.GetValue(newWidth), newHeight, false);

		}

	}

}

void UserInterface::Widget::TyreInfoArray::show() {

	RedoDisplay(x(), y());

}



void UserInterface::Widget::TyreInfoArray::hide() {

	for (const auto tyre : m_tyres) {

		if (tyre) {

			tyre->Hide();

		}

	}

}



void UserInterface::Widget::TyreInfoArray::raise() {

	// TODO

}



void UserInterface::Widget::TyreInfoArray::lower() {

	// TODO

}



const int16_t UserInterface::Widget::TyreInfoArray::width() const {

	int16_t xMin = INT16_MAX;
	int16_t xMax = INT16_MIN;
	int16_t lastWidth = INT16_MIN;
	for (const auto tyre : m_tyres) {

		if (tyre) {

			xMin = qMin(xMin, tyre->x());
			xMax = qMax(xMax, tyre->x());
			if (xMax == tyre->x()) {

				lastWidth = tyre->width();

			}

		}

	}

	return xMax - xMin + lastWidth;

}



const int16_t UserInterface::Widget::TyreInfoArray::height() const {

	int16_t yMin = INT16_MAX;
	int16_t yMax = INT16_MIN;
	int16_t lastHeight = INT16_MIN;
	for (const auto tyre : m_tyres) {

		if (tyre) {

			yMin = qMin(yMin, tyre->y());
			yMax = qMax(yMax, tyre->y());
			if (yMax == tyre->y()) {

				lastHeight = tyre->height();

			}

		}

	}

	return yMax - yMin + lastHeight;

}



const int16_t UserInterface::Widget::TyreInfoArray::x() const {

	int16_t xMin = 0;
	for (const auto tyre : m_tyres) {

		if (tyre && tyre->HasBeenRedoneAtLeastOnce()) {

			xMin = qMin(xMin, tyre->x());

		}

	}

	return xMin;

}



const int16_t UserInterface::Widget::TyreInfoArray::y() const {

	int16_t yMin = 0;
	for (const auto tyre : m_tyres) {

		if (tyre && tyre->HasBeenRedoneAtLeastOnce()) {

			yMin = qMin(yMin, tyre->y());

		}

	}

	return yMin;

}



void UserInterface::Widget::TyreInfoArray::Init() {

	for (size_t i = 0; i < MAX_TYRE_DISPLAY; ++i) {

		auto* tyre = new UserInterface::Widget::TyreInfoContainer(m_widgetParent);
		Q_ASSERT(tyre);
		if (tyre) {

			m_tyres.push_back(tyre);
			tyre->Hide();

		}

	}

	RedoDisplay();

}



void UserInterface::Widget::TyreInfoArray::TyreChange(Tyre::Internal::Actual actualTyreCompound, Tyre::Internal::Visual visualTyreCompound, uint8_t tyreAge, bool pitBeforeLine) {

	// TODO implement logic related to pitBeforeLine
    auto* tyre = m_tyres[m_numStints % 3];
	if (tyre) {

		tyre->Init(actualTyreCompound, visualTyreCompound, tyreAge);
		tyre->Show();
		++m_numStints;

	}

	// cycle the layout, moving all entries one to the right
	RedoDisplay();

}



void UserInterface::Widget::TyreInfoArray::LapCompletedWithTyre() {

    if (m_numStints == 0) return;

	const size_t index = (m_numStints - 1) % 3;
    if (index >= m_tyres.size()) return;

	auto* tyre = m_tyres[index];
	if (tyre) {

		tyre->IncrementLap();

	}

}



void UserInterface::Widget::TyreInfoArray::RedoDisplay() {

	RedoDisplay(x(), y());

}



void UserInterface::Widget::TyreInfoArray::RedoDisplay(const uint16_t x, const uint16_t y) {

	// no need for anything if this hasn't been init
	if (m_tyres.empty()) return;

	// if there were 0 stints thus far, then safeguard, otherwise we want to go 2, 1, 0 order of indexes
	uint8_t count = (m_numStints == 0) ? 0 : (m_numStints - 1) % 3;

	for (uint8_t i = count; ; --i) {

		auto* tyre = m_tyres[i];
		uint16_t baseX = x + (count * tyre->width());
		tyre->move(baseX, y, false, false);
		tyre->RedoneOnce();

		if (i == 0) break;

	}

}