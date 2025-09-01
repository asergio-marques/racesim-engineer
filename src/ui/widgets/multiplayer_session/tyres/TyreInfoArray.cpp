#include "multiplayer_session/tyres/TyreInfoArray.h"
#include "multiplayer_session/tyres/TyreInfoContainer.h"

#include <cstdint>
#include <QList>
#include "base/Container.h"
#include "data/internal/Tyre.h"
#include "styles/Standings.h"




UserInterface::Widget::TyreInfoArray::TyreInfoArray(QWidget* parent) :
	UserInterface::Widget::Container(UserInterface::Widget::ID::TyreInfo),
	m_tyres(),
	m_widgetParent(parent) {



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

	// TODO ignoring parameters, just doing the basic logic right now
	if (m_tyres.size() == 0) {

		return;

	}

	uint8_t displayCount = 0;
	UserInterface::Style::Standings style;

	for (uint8_t i = m_tyres.size() - 1; i > 0 && displayCount < 5; --i, ++displayCount) {

		auto* tyre = m_tyres[i];
		if (tyre) {

			tyre->setSize(style.TyreInfoContainerMaxX.m_value, style.TyreInfoContainerMaxY.m_value, false);

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

	int16_t xMin = INT16_MAX;
	for (const auto tyre : m_tyres) {

		if (tyre && tyre->HasBeenRedoneAtLeastOnce()) {

			xMin = qMin(xMin, tyre->x());

		}

	}

	return xMin;

}



const int16_t UserInterface::Widget::TyreInfoArray::y() const {

	int16_t yMin = INT16_MAX;
	for (const auto tyre : m_tyres) {

		if (tyre && tyre->HasBeenRedoneAtLeastOnce()) {

			yMin = qMin(yMin, tyre->y());

		}

	}

	return yMin;

}



void UserInterface::Widget::TyreInfoArray::TyreChange(Tyre::Internal::Actual actualTyreCompound, Tyre::Internal::Visual visualTyreCompound, uint8_t tyreAge, bool pitBeforeLine) {

	// TODO implement logic related to pitBeforeLine
	auto* tyre = new UserInterface::Widget::TyreInfoContainer(m_widgetParent);
	Q_ASSERT(tyre);
	if (tyre) {

		m_tyres.push_back(tyre);
		tyre->Init(actualTyreCompound, visualTyreCompound, tyreAge);

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

	RedoDisplay(x(), y());

}



void UserInterface::Widget::TyreInfoArray::RedoDisplay(const uint16_t x, const uint16_t y) {

	// no need for anything if there have been no stints
	if (m_tyres.size() == 0) {

		return;

	}

	uint8_t displayCount = 0;
	UserInterface::Style::Standings style;

	for (uint8_t i = m_tyres.size() - 1; displayCount < style.TyreInfoArrayMaxNum.m_value; --i, ++displayCount) {

		uint16_t baseX = x + (displayCount * style.TyreInfoContainerMaxX.m_value);
		auto* tyre = m_tyres[i];
		tyre->Show();
		tyre->move(baseX, y, false, false);
		tyre->RedoneOnce();

		if (i == 0) break;

	}
	// hide any remaining tyres that are not supposed to be displayed
	if (m_tyres.size() < style.TyreInfoArrayMaxNum.m_value) return;
	for (uint8_t i = 0; i < m_tyres.size() - style.TyreInfoArrayMaxNum.m_value; ++i) {

		auto* tyre = m_tyres[i];

		if (tyre) {

			tyre->Hide();

		}

	}

}