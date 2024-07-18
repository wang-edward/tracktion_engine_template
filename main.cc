#include <tracktion_engine/tracktion_engine.h>

namespace te = tracktion;
using namespace std::literals;
using namespace te::literals;

static void addNoteToClip(
    te::MidiClip *midiClip,
    int noteNumber,
    int velocity,
    te::BeatPosition start,
    te::BeatDuration duration)
{
    midiClip->getSequence().addNote(
        noteNumber,
        start,
        duration,
        velocity,
        0,
        nullptr);
}

void setupAudioDevice(te::Engine& engine, const std::string& backendType){ 
    auto& deviceManager = engine.getDeviceManager();

    // Shut down the current audio device
    deviceManager.closeDevices();

    // Set the desired backend type
    // Initialize the default audio device with the selected backend
    deviceManager.initialise();

    // Optionally, handle specific device settings or customizations here
}

int main()
{
    // Create the engine
    te::Engine engine{"Tracktion Hello World"};

    // Create an edit
    te::Edit edit{
        engine,
        te::createEmptyEdit(engine),
        te::Edit::forEditing,
        nullptr,
        0};

    // Create a track
    edit.ensureNumberOfAudioTracks(1);
    auto track = te::getAudioTracks(edit)[0];

    // Get length of 1 bar
    const tracktion::TimeRange oneBarTimeRange(
        0s,
        edit.tempoSequence.toTime({1, tracktion::BeatDuration()}));

    // Insert a 1 bar long Midi clip
    auto clip = track->insertNewClip(
        te::TrackItem::Type::midi,
        "Midi Clip",
        oneBarTimeRange,
        nullptr);
    auto midiClip = static_cast<te::MidiClip *>(clip);

    // Add a 4-note C-E-G-C sequence to the clip
    // Note the use of Tracktion's beat position/duration literals
    addNoteToClip(midiClip, 60, 100, 0_bp, 0.5_bd);
    addNoteToClip(midiClip, 64, 100, 1_bp, 0.5_bd);
    addNoteToClip(midiClip, 67, 100, 2_bp, 0.5_bd);
    addNoteToClip(midiClip, 72, 100, 3_bp, 0.5_bd);

    // Create a built-in synth plugin instance to play the sequence on
    auto plugin = edit.getPluginCache().createNewPlugin(te::FourOscPlugin::xmlTypeName, {}).get();
    auto fourOscPlugin = static_cast<te::FourOscPlugin *>(plugin);

    auto plugin2 = edit.getPluginCache().createNewPlugin(te::FourOscPlugin::xmlTypeName, {}).get();
    auto fourOscPlugin2 = static_cast<te::FourOscPlugin *>(plugin2);

    auto plugin3 = edit.getPluginCache().createNewPlugin(te::DelayPlugin::xmlTypeName, {}).get();
    auto delayPlugin = static_cast<te::DelayPlugin *>(plugin3);

    auto plugin4 = edit.getPluginCache().createNewPlugin(te::PhaserPlugin::xmlTypeName, {}).get();
    auto phaserPlugin = static_cast<te::PhaserPlugin *>(plugin4);
                    

    // Insert the plugin to the track
    // track->pluginList.insertPlugin(*fourOscPlugin, 0, nullptr);
    // track->pluginList.insertPlugin(*delayPlugin, 1, nullptr);
    
    for (int i = 0; i < fourOscPlugin->oscParams.size(); i++) {
        fourOscPlugin->oscParams[i]->waveShapeValue.setValue(2, nullptr);
    }
    track->pluginList.insertPlugin(*fourOscPlugin, 0, nullptr);
    track->pluginList.insertPlugin(*delayPlugin, 1, nullptr);
    track->pluginList.insertPlugin(*phaserPlugin, 2, nullptr);

    // Get the transport & set it to the start of the edit
    auto &transport = edit.getTransport();
    transport.setPosition(0s);

    // Set the transport to loop our clip
    transport.setLoopRange(clip->getEditTimeRange());
    transport.looping = true;

    // Begin playback
    transport.play(false);

    // Dance while the record spins
    while (true)
    {
    }

    return 0;
}
