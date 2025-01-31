/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

  name:             DemoRunner
  version:          0.0.1
  vendor:           Tracktion
  website:          www.tracktion.com
  description:      This example simply loads a project from the command line and plays it back in a loop.

  dependencies:     juce_audio_basics, juce_audio_devices, juce_audio_formats, juce_audio_processors, juce_audio_utils,
                    juce_core, juce_data_structures, juce_dsp, juce_events, juce_graphics,
                    juce_gui_basics, juce_gui_extra, juce_osc, tracktion_engine, tracktion_graph
  exporters:        linux_make, vs2017, xcode_iphone, xcode_mac

  moduleFlags:      JUCE_STRICT_REFCOUNTEDPOINTER=1, JUCE_PLUGINHOST_AU=1, JUCE_PLUGINHOST_VST3=1
  defines:          JUCE_MODAL_LOOPS_PERMITTED=1

  type:             Component
  mainClass:        DemoRunner

 END_JUCE_PIP_METADATA

*******************************************************************************/

#pragma once

using namespace tracktion::literals;
using namespace std::literals;

//==============================================================================

//==============================================================================
//==============================================================================
// Include demo files to register them

//==============================================================================
//==============================================================================
class DemoRunner  : public Component
{
public:
    //==============================================================================
    DemoRunner()
    {
        // Helpers::addAndMakeVisible (*this, { &loadButton, &pluginListButton, &audioSettingsButton, &currentDemoName });

        // loadButton.onClick = [this] { showLoadDemoMenu(); };

        // // Show the plugin scan dialog
        // // If you're loading an Edit with plugins in, you'll need to perform a scan first
        // pluginListButton.onClick = [this]
        // {
        //     DialogWindow::LaunchOptions o;
        //     o.dialogTitle                   = TRANS("Plugins");
        //     o.dialogBackgroundColour        = juce::Colours::black;
        //     o.escapeKeyTriggersCloseButton  = true;
        //     o.useNativeTitleBar             = true;
        //     o.resizable                     = true;
        //     o.useBottomRightCornerResizer   = true;

        //     auto v = new PluginListComponent (engine.getPluginManager().pluginFormatManager,
        //                                       engine.getPluginManager().knownPluginList,
        //                                       engine.getTemporaryFileManager().getTempFile ("PluginScanDeadMansPedal"),
        //                                       std::addressof (engine.getPropertyStorage().getPropertiesFile()));
        //     v->setSize (800, 600);
        //     o.content.setOwned (v);
        //     o.launchAsync();
        // };

        // audioSettingsButton.onClick = [this] { EngineHelpers::showAudioDeviceSettings (engine); };

        // currentDemoName.setJustificationType (juce::Justification::centred);

        // setSize (800, 600);
    }

    ~DemoRunner() override
    {
        // engine.getTemporaryFileManager().getTempDirectory().deleteRecursively();
    }

    //==============================================================================
    void paint (Graphics& g) override
    {
        // const auto backgroundCol = getLookAndFeel().findColour (ResizableWindow::backgroundColourId);
        // g.fillAll (backgroundCol);

        // auto r = getLocalBounds();
        // g.setColour (backgroundCol.darker());
        // g.fillRect (r.removeFromTop (30));

        // if (demo)
        //     return;

        // g.setColour (getLookAndFeel().findColour (Label::textColourId));
        g.drawText ("Select a demo above to begin", r, juce::Justification::centred);
    }

    void resized() override
    {
        // auto r = getLocalBounds();
        // auto topR = r.removeFromTop (30);
        // const int buttonW = topR.getWidth() / 3;
        // loadButton.setBounds (topR.removeFromLeft (buttonW).reduced (2));
        // pluginListButton.setBounds (topR.removeFromRight (buttonW / 2).reduced (2));
        // audioSettingsButton.setBounds (topR.removeFromRight (buttonW / 2).reduced (2));
        // currentDemoName.setBounds (topR.reduced (2));

        // if (demo)
        //     demo->setBounds (r.reduced (2));
    }

private:
    //==============================================================================
    te::Engine engine { ProjectInfo::projectName, std::make_unique<ExtendedUIBehaviour>(), nullptr };

    TextButton loadButton { "Load Demo" }, pluginListButton { "Plugin List" }, audioSettingsButton { "Audio Settings" };
    Label currentDemoName { {}, "No demo loaded" };
    std::unique_ptr<Component> demo;

    //==============================================================================
    // void showLoadDemoMenu()
    // {
    //     juce::PopupMenu m;

    //     for (auto type : DemoTypeManager::getNames())
    //         m.addItem (type, [this, type] { loadDemo (type); });

    //     m.showMenuAsync ({});
    // }

    // void loadDemo (const String& type)
    // {
    //     if ((demo = DemoTypeManager::createDemo (type, engine)))
    //     {
    //         addAndMakeVisible (*demo);
    //         currentDemoName.setText (juce::String ("Running Demo: {}").replace ("{}", type), dontSendNotification);
    //         resized();
    //     }
    //     else
    //     {
    //         currentDemoName.setText ("Error: Unable to load demo", dontSendNotification);
    //     }
    // }

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DemoRunner)
};
