#include <math.h>
#include "GainPlugin.h"


GainPluginAudio::GainPluginAudio()
:SynchronBlockProcessor()
{
}

void GainPluginAudio::prepareToPlay(double sampleRate, int max_samplesPerBlock, int max_channels)
{
    juce::ignoreUnused(max_samplesPerBlock,max_channels);
    int synchronblocksize;
    synchronblocksize = (g_desired_blocksize_ms*sampleRate*0.001);
    if (g_forcePowerOf2)
    {
        int nextpowerof2 = int(log2(synchronblocksize))+1;
        synchronblocksize = int(pow(2,nextpowerof2));
    }
    prepareSynchronProcessing(max_channels,synchronblocksize);
    m_Latency += synchronblocksize;
    // here your code
    m_smoothedGain.reset(sampleRate,0.0015); // 50ms is enough for a smooth gain, 

}

int GainPluginAudio::processSynchronBlock(juce::AudioBuffer<float> & buffer, juce::MidiBuffer &midiMessages)
{
    // check parameter update
    if (*m_gainParam != m_gainParamOld)
    {
        m_gainParamOld = *m_gainParam;
        m_gain = powf(10.f,m_gainParamOld/20.f);
    }

    int NrOfSamples = buffer.getNumSamples();
    int chns = buffer.getNumChannels();

    //m_smoothedGain.setTargetValue(m_gain);
    m_smoothedGain.setTargetValue(m_gain);
    float curGain;
    for (int channel = 0; channel < chns; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        // ..do something to the data...
        for (int kk = 0; kk < NrOfSamples; ++kk)
        {
            if (channel == 0)
                curGain = m_smoothedGain.getNextValue();
            channelData[kk] *= curGain;
        }
    }

    return 0;
}

void GainPluginAudio::addParameter(std::vector<std::unique_ptr<juce::RangedAudioParameter>> &paramVector)
{
    paramVector.push_back(std::make_unique<juce::AudioParameterFloat>(g_paramGain.ID,            // parameterID
                                                        g_paramGain.name,            // parameter name
                                                        g_paramGain.minValue,              // minimum value
                                                        g_paramGain.maxValue,              // maximum value
                                                        g_paramGain.defaultValue));

// these are to additional lines wit lambdas to convert data
        // [](float value, int MaxLen) { value = int(exp(value) * 10) * 0.1;  return (String(value, MaxLen) + " Hz"); },
        // [](const String& text) {return text.getFloatValue(); }));




}

void GainPluginAudio::prepareParameter(std::unique_ptr<juce::AudioProcessorValueTreeState> &vts)
{
    m_gainParam = vts->getRawParameterValue(g_paramGain.ID);
 
}


GainPluginGUI::GainPluginGUI(juce::AudioProcessorValueTreeState& apvts)
:m_apvts(apvts)
{
    m_GainSlider.setRange (g_paramGain.minValue, g_paramGain.maxValue);         
    m_GainSlider.setTextValueSuffix (g_paramGain.unitName);    
    m_GainSlider.setSliderStyle(juce::Slider::LinearVertical);
    m_GainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxAbove, true, 60, 20);
    m_GainSlider.setValue(g_paramGain.defaultValue);
	m_GainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, g_paramGain.ID, m_GainSlider);
	addAndMakeVisible(m_GainSlider);
}

void GainPluginGUI::paint(juce::Graphics &g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId).brighter(0.3));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("GainPlugin", getLocalBounds(), juce::Justification::centred, 1);

}

void GainPluginGUI::resized()
{
	auto r = getLocalBounds();
	m_GainSlider.setBounds(r);
}
