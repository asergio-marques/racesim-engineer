#include "tyres/TyreInfoArray.h"

#include <cstdint>
#include <QList>
#include "base/Container.h"
#include "data/internal/Tyre.h"
#include "styles/General.h"
#include "styles/DriverInfo.h"
#include "tyres/TyreInfoContainer.h"




UserInterface::Widget::TyreInfoArray::TyreInfoArray(QWidget* parent) :
	UserInterface::Widget::Container(UserInterface::Widget::ID::TyreInfo),
	m_widgetParent(parent),
	m_tyres() {



}



void UserInterface::Widget::TyreInfoArray::move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) {

    m_x = centerAlignmentX ? x - (width() / 2) : x;
    m_y = centerAlignmentY ? y - (height() / 2) : y;

	RedoDisplay();

}



void UserInterface::Widget::TyreInfoArray::scale(const uint8_t percent) {

	// TODO

}



void UserInterface::Widget::TyreInfoArray::scale(const uint8_t percentX, const uint8_t percentY) {

	// TODO

}



void UserInterface::Widget::TyreInfoArray::setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) {

	m_width = newWidth;
	m_height = newHeight;

	RedoDisplay();

}



void UserInterface::Widget::TyreInfoArray::show() {

	RedoDisplay();

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

	return (UserInterface::Style::TyreInfoContainerMaxX.GetValue(m_width) + UserInterface::Style::PaddingReference.GetValue(m_width))
		* UserInterface::Style::TyreInfoContainerMaxNum;

}



const int16_t UserInterface::Widget::TyreInfoArray::height() const {

	return m_height;

}



const int16_t UserInterface::Widget::TyreInfoArray::x() const {

	return m_x;

}



const int16_t UserInterface::Widget::TyreInfoArray::y() const {

	return m_y;

}



void UserInterface::Widget::TyreInfoArray::TyreChange(Tyre::Internal::Actual actualTyreCompound, Tyre::Internal::Visual visualTyreCompound, uint8_t tyreAge, uint8_t stintNo, bool pitBeforeLine) {

	// TODO implement logic related to pitBeforeLine
	auto* tyre = new UserInterface::Widget::TyreInfoContainer(m_widgetParent);
	Q_ASSERT(tyre);
	if (tyre) {

		m_tyres.push_back(tyre);
		tyre->Init(actualTyreCompound, visualTyreCompound, tyreAge, stintNo);

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
	if (m_tyres.size() == 0) {

		return;

	}

	uint8_t displayCount = 0;
	uint16_t calculateSingleWidth = UserInterface::Style::TyreInfoContainerMaxX.GetValue(m_width);
	uint16_t calcPadding = UserInterface::Style::PaddingReference.GetValue(m_width);

	for (uint8_t i = m_tyres.size() - 1; displayCount < UserInterface::Style::TyreInfoContainerMaxNum; --i, ++displayCount) {

		auto* tyre = m_tyres[i];
		tyre->setSize(calculateSingleWidth - calcPadding, m_height, false);

		uint16_t baseX = x() + ((calculateSingleWidth + calcPadding) * displayCount);
		tyre->move(baseX, y(), false, false);

		if (i == 0) break;

	}
	// hide any remaining tyres that are not supposed to be displayed
	if (m_tyres.size() < UserInterface::Style::TyreInfoContainerMaxNum) return;
	for (uint8_t i = 0; i < m_tyres.size() - UserInterface::Style::TyreInfoContainerMaxNum; ++i) {

		auto* tyre = m_tyres[i];

		if (tyre) {

			tyre->Hide();

		}

	}

}