#ifndef USERINTERFACE_INCLUDE_STYLE_INTERFACE_H_
#define USERINTERFACE_INCLUDE_STYLE_INTERFACE_H_




namespace UserInterface {

    namespace Style {

        class ILoading;
        class IRaceStanding;

        class Interface {

            public:
            Interface() = default;
            virtual ~Interface() = default;

            virtual UserInterface::Style::ILoading* GetLoadingStyle() const = 0;
            virtual UserInterface::Style::IRaceStanding* GetRaceStandingStyle() const = 0;

        };

    }

}

#endif // USERINTERFACE_INCLUDE_STYLE_INTERFACE_H_