#include "starterBrightnessAdjustment.h"

void StarterAdjustedBrightness::setupAdjustmentParameters(uint8_t newDivisor, uint8_t newMultiplier) {
	divisor = newDivisor;
	multiplier = newMultiplier;
}

void StarterAdjustedBrightness::setStarterState(bool active) {
	isStarterActive = active;
}

void StarterAdjustedBrightness::configureBrightnessLevels(LightType type, LightModes mode, uint8_t brightness) {
	brightnessConfig[type][mode] = brightness;
}

uint8_t StarterAdjustedBrightness::getBrightnessLevel(LightType type, LightModes mode) {
	if(isStarterActive) return brightnessConfig[type][mode] / divisor * multiplier;

	return brightnessConfig[type][mode];
}