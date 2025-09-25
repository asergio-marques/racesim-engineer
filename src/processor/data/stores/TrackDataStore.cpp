#include "data/stores/TrackDataStore.h"

#include <future>
#include <map>
#include <thread>
#include "data/internal/Session.h"
#include "data/holders/TrackData.h"
#include "utilities/ConfigFileMaps.h"
#include "utilities/TrackConfigLoader.h"




Processor::Data::TrackDataStore::TrackDataStore() :
    m_tracks(),
    m_invalid(Session::Internal::Track::InvalidUnknown, 0) {



}



bool Processor::Data::TrackDataStore::Initialized() const{

    if (m_tracks.empty()) return false;

    bool ok = true;
    // check if all supported tracks have detailed data
    for (const auto& track : Processor::Utility::ConfigFileMaps::SUPPORTED_TRACKS) {

        auto it = m_tracks.find(track);
        if (it == m_tracks.end()) {

            ok = false;
            break;

        }

    }

    return ok;

}



void Processor::Data::TrackDataStore::Build() {

    for (const auto& track : Processor::Utility::ConfigFileMaps::SUPPORTED_TRACKS) {

        Processor::Utility::TrackConfigLoader loader{track};
        std::future<Processor::Data::TrackData> ret = std::async(std::launch::async, &Processor::Utility::TrackConfigLoader::readConfig, &loader);
        auto data = ret.get();
        m_tracks.emplace(track, data);        

    }


}



const Processor::Data::TrackData& Processor::Data::TrackDataStore::GetTrackData(
    const Session::Internal::Track track, bool& ok) const {

    auto it = m_tracks.find(track);
    if (it != m_tracks.end()){

        ok = true;
        return it->second;

    }

    ok = false;
    return m_invalid;

}