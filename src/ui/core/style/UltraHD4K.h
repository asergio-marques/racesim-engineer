#ifndef USERINTERFACE_INCLUDE_STYLE_ULTRA_HD_4K_H_
#define USERINTERFACE_INCLUDE_STYLE_ULTRA_HD_4K_H_

#include "core/style/Interface.h"




namespace UserInterface {

    namespace Style {

        class ILoading;
        class IRaceStanding;

        class UltraHD4K : public Interface {

            public:
            UltraHD4K();
            virtual ~UltraHD4K() = default;

            UserInterface::Style::ILoading* GetLoadingStyle() const override final;
            UserInterface::Style::IRaceStanding* GetRaceStandingStyle() const override final;

            private:
            UserInterface::Style::ILoading* m_loadingStyle;
            UserInterface::Style::IRaceStanding* m_raceStandingStyle;

        };

    }

}

#endif // USERINTERFACE_INCLUDE_STYLE_ULTRA_HD_4K_H_