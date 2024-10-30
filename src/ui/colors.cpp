#include "colors.h"

#include <wx/settings.h>

#include <cstdint>

wxColour Colors::GetSecondaryTextColor() {
  auto appearance = wxSystemSettings::GetAppearance();
  auto value = appearance.IsDark() ? uint8_t{156} : uint8_t{149};
  return wxColour{value, value, value};
}
