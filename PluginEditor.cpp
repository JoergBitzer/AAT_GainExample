
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PluginSettings.h"

//==============================================================================
#if WITH_MIDIKEYBOARD   
YourPluginNameAudioProcessorEditor::YourPluginNameAudioProcessorEditor (YourPluginNameAudioProcessor& p)
    : AudioProcessorEditor (&p), m_processorRef (p), m_presetGUI(p.m_presets),
    	m_keyboard(m_processorRef.m_keyboardState, MidiKeyboardComponent::Orientation::horizontalKeyboard), 
        m_wheels(p.m_wheelState), m_editor(*p.m_parameterVTS)
#else
YourPluginNameAudioProcessorEditor::YourPluginNameAudioProcessorEditor (YourPluginNameAudioProcessor& p)
    : AudioProcessorEditor (&p), m_processorRef (p), m_presetGUI(p.m_presets)
#endif
{
    float scaleFactor = m_processorRef.getScaleFactor();
    setResizeLimits (g_minGuiSize_x,g_minGuiSize_x*g_guiratio , g_maxGuiSize_x, g_maxGuiSize_x*g_guiratio);
    setResizable(true,true);
    getConstrainer()->setFixedAspectRatio(1./g_guiratio);
    setSize (scaleFactor*g_minGuiSize_x, scaleFactor*g_minGuiSize_x*g_guiratio);

	addAndMakeVisible(m_presetGUI);
#if WITH_MIDIKEYBOARD      
	addAndMakeVisible(m_keyboard);
    addAndMakeVisible(m_wheels);    
#endif

    // from here your algo editor ---------
    addAndMakeVisible(m_editor);

}

YourPluginNameAudioProcessorEditor::~YourPluginNameAudioProcessorEditor()
{
}

//==============================================================================
void YourPluginNameAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}
void YourPluginNameAudioProcessorEditor::resized()
{
    int height = getHeight();
    // necessary to change fontsize of comboboxes and PopUpmenus
    // 0.5 is a good compromisecould be slightly higher or lower
    // m_jadeLAF.setFontSize(0.5*height*g_minPresetHandlerHeight/g_minGuiSize_y);
    // top presethandler
    m_presetGUI.setBounds(0, 0, getWidth(), height*g_minPresetHandlerHeight/g_minGuiSize_y);
    // bottom a small midkeyboard
#if WITH_MIDIKEYBOARD    
    m_wheels.setBounds(0, height*(1-g_midikeyboardratio), g_wheelstokeyboardratio*getWidth(), height*g_midikeyboardratio);
    m_keyboard.setBounds(g_wheelstokeyboardratio*getWidth(), height*(1-g_midikeyboardratio), (1.0-g_wheelstokeyboardratio)*getWidth(), height*g_midikeyboardratio);

#endif
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    int width = getWidth();
	float scaleFactor = float(width)/g_minGuiSize_x;
    m_processorRef.setScaleFactor(scaleFactor);
    // use setBounds with scaleFactor
    m_editor.setBounds(0, height*g_minPresetHandlerHeight/g_minGuiSize_y + 1, 
                        getWidth(), height*(1-g_midikeyboardratio) - (height*g_minPresetHandlerHeight/g_minGuiSize_y + 1) );

}
