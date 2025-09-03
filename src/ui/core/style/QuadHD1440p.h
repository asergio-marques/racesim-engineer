#ifndef USERINTERFACE_INCLUDE_STYLE_QUAD_HD_1440P_H_
#define USERINTERFACE_INCLUDE_STYLE_QUAD_HD_1440P_H_

#include "core/style/Interface.h"




namespace UserInterface {

    namespace Style {

        class ILoading;
        class IRaceStanding;

        class QuadHD1440p : public Interface {

            public:
            QuadHD1440p();
            virtual ~QuadHD1440p() = default;

            UserInterface::Style::ILoading* GetLoadingStyle() const override final;
            UserInterface::Style::IRaceStanding* GetRaceStandingStyle() const override final;

            private:
            UserInterface::Style::ILoading* m_loadingStyle;
            UserInterface::Style::IRaceStanding* m_raceStandingStyle;

        };

    }

}

#endif // USERINTERFACE_INCLUDE_STYLE_QUAD_HD_1440P_H_