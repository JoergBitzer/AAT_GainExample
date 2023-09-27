#pragma once
// ------------Audio -----------------
const int g_desired_blocksize_ms(2); // its in ms to be independent from the sampling rate
const bool g_forcePowerOf2(false); // should be true for FFT Processing

// -------------- GUI -----------------
// global GUI setting for GainPlugin
const int g_minGuiSize_x(200);
const int g_maxGuiSize_x(500);
const int g_minGuiSize_y(400);
const float g_guiratio = float(g_minGuiSize_y)/g_minGuiSize_x;

// ---------- presethandler ----------
//const StringArray g_PresetCategories("Unknown", "Lead", "Brass", "Template", "Bass",
//	"Key", "Organ" , "Pad", "Drums_Perc", "SpecialEffect","Sequence", "String" );
const StringArray g_PresetCategories(""); // keep empty for "no categories"

const int g_minPresetHandlerHeight(20); // in pixels
#define MIN_COMBO_WITH_PRESET 120
#define MIN_ELEMENT_DIST_PRESET 10
#define MIN_BUTTON_WIDTH_PRESET 40
#define MIN_ELEMENT_HEIGHT_PRESET 20

// ------- Midi Keyboard display-------
const float g_midikeyboardratio(0.13); // in percent of height()
const float g_wheelstokeyboardratio(0.1);

// -------Your defines for GUI --------

