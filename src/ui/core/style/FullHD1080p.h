#ifndef USERINTERFACE_INCLUDE_STYLE_FULLHD_1080P_H_
#define USERINTERFACE_INCLUDE_STYLE_FULLHD_1080P_H_

#include "core/style/Interface.h"




namespace UserInterface {

    namespace Style {

        class ILoading;
        class IRaceStanding;

        class FullHD1080p : public Interface {

            public:
            FullHD1080p();
            virtual ~FullHD1080p() = default;

            UserInterface::Style::ILoading* GetLoadingStyle() const override final;
            UserInterface::Style::IRaceStanding* GetRaceStandingStyle() const override final;

            private:
            UserInterface::Style::ILoading* m_loadingStyle;
            UserInterface::Style::IRaceStanding* m_raceStandingStyle;

        };

    }

}

#endif // USERINTERFACE_INCLUDE_STYLE_FULLHD_1080P_H_