#include "MainComponent.h"
// #include <raylib.h>
#include <iostream>
#include <chrono>

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);
    std::filesystem::path curr_path = std::filesystem::current_path();
    juce::File my_file{juce::String{curr_path.string() + "/tmp.box"}};

    edit_ = createEmptyEdit(engine_, my_file);

    // InitWindow(512, 512, "JuceApp");
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // // (Our component is opaque, so we must completely fill the background with a solid colour)
    // g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // g.setFont (juce::FontOptions (16.0f));
    // g.setColour (juce::Colours::white);
    // g.drawText ("Hello World!", getLocalBounds(), juce::Justification::centred, true);
    test();
}

void MainComponent::test()
{
    // weird way to induce a wait
    while (true) {
        if (n_ < 1e7)
        {
            n_ += 1;
            // std::cout << "n_: " << n_ << std::endl;
        }
        else
        {
            // test ALSA::VirtualMidi
            std::cout << "ALSA::VirtualMidi begin" << std::endl;
            engine_.getDeviceManager().createVirtualMidiDevice("box_midi");
            engine_.getDeviceManager().setDefaultMidiInDevice("box_midi");
            auto ptr = engine_.getDeviceManager().getDefaultMidiInDevice();
            assert(ptr != nullptr);
            std::cout << "ALSA::VirtualMidi end" << std::endl;
            exit(0);
        }
    }
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
