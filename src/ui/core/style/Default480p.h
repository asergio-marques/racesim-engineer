#ifndef USERINTERFACE_INCLUDE_STYLE_DEFAULT_480P_H_
#define USERINTERFACE_INCLUDE_STYLE_DEFAULT_480P_H_

#include "core/style/Interface.h"




namespace UserInterface {

    namespace Style {

        class ILoading;
        class IRaceStanding;

        class Default480p : public Interface {

            public:
            Default480p();
            virtual ~Default480p() = default;

            UserInterface::Style::ILoading* GetLoadingStyle() const override final;
            UserInterface::Style::IRaceStanding* GetRaceStandingStyle() const override final;

            private:
            UserInterface::Style::ILoading* m_loadingStyle;
            UserInterface::Style::IRaceStanding* m_raceStandingStyle;

        };

    }

}

#endif // USERINTERFACE_INCLUDE_STYLE_DEFAULT_480P_H_