#include "gestureformdialog.h"

#include <gtk-3.0/gdk/gdkkeysyms.h>
#include <linux/input-event-codes.h>
#include <wx/wx.h>

#include <algorithm>
#include <string>

#include "../core/gesture.h"
#include "../core/gesturesfile.h"
#include "../core/utilities.h"

GestureFormDialog::GestureFormDialog(wxWindow* parent, const wxString& title,
                                     int32_t finger_count)
    : wxDialog{parent, wxID_ANY, title, wxDefaultPosition, wxSize{500, 400}},
      finger_count_{finger_count} {
  auto panel = new wxPanel{this, wxID_ANY};

  // ==================
  // Section: DIRECTION
  // ==================
  auto direction_text = new wxStaticText{panel, wxID_ANY, "Direction"};

  direction_choice_ = new wxChoice{panel, wxID_ANY};
  for (auto direction : Utilities::EnumRange(Gesture::Direction::kNone,
                                             Gesture::Direction::kOut)) {
    direction_choice_->Append(Utilities::ConvertDirectionToString(direction));
  }

  // Sets displayed text to first item.
  direction_choice_->SetSelection(0);

  // =================
  // Section: KEYCODES
  // =================
  auto keycodes_text = new wxStaticText{panel, wxID_ANY, "Key Combination"};

  auto keycodes_text_ctrl = new wxTextCtrl{panel, wxID_ANY};
  keycodes_text_ctrl->Bind(wxEVT_KEY_DOWN, &GestureFormDialog::OnKeyDown, this);
  keycodes_text_ctrl->Bind(wxEVT_TEXT, &GestureFormDialog::OnTextEnter, this);

  auto keycodes_text_ctrl_text =
    new wxStaticText{panel, wxID_ANY, "Type keys one at a time."};
  keycodes_text_ctrl_text->SetForegroundColour(wxColour{156, 156, 156});

  key_combination_text_ = new wxStaticText{panel, wxID_ANY, ""};

  auto keycodes_clear_button = new wxButton{panel, wxID_ANY, "Clear"};
  keycodes_clear_button->Bind(wxEVT_BUTTON,
                              &GestureFormDialog::OnClearButtonClick, this);

  // ================
  // Section: BUTTONS
  // ================
  auto cancel_button = new wxButton{panel, wxID_ANY, "Cancel"};
  cancel_button->Bind(wxEVT_BUTTON, &GestureFormDialog::OnCancelButtonClick,
                      this);
  auto save_button = new wxButton{panel, wxID_ANY, "Save"};
  save_button->Bind(wxEVT_BUTTON, &GestureFormDialog::OnSaveButtonClick, this);

  // ======
  // LAYOUT
  // ======
  auto outer = new wxBoxSizer{wxVERTICAL};
  inner_ = new wxBoxSizer{wxVERTICAL};
  outer->Add(inner_, 0, wxEXPAND | wxALL, 20);
  panel->SetSizerAndFit(outer);

  // Handles layout for section DIRECTION.
  inner_->Add(direction_text);
  inner_->AddSpacer(5);  // Must be called in between.
  inner_->Add(direction_choice_, 0, wxEXPAND | wxRIGHT | wxLEFT);

  inner_->AddSpacer(20);

  // Handles layout for section KEYCODES.
  inner_->Add(keycodes_text);
  inner_->AddSpacer(5);  // Must be called in between.
  inner_->Add(keycodes_text_ctrl, 0, wxEXPAND | wxRIGHT | wxLEFT);
  inner_->Add(keycodes_text_ctrl_text);
  inner_->AddSpacer(10);  // Must be called in between.
  inner_->Add(key_combination_text_, 0, wxALIGN_CENTER_HORIZONTAL | wxALL);
  inner_->AddSpacer(5);  // Must be called in between.
  inner_->Add(keycodes_clear_button, 0, wxALIGN_CENTER_HORIZONTAL | wxALL);

  inner_->AddSpacer(25);

  // Handles layout for section BUTTONS.
  auto buttons_sizer = new wxBoxSizer{wxHORIZONTAL};
  buttons_sizer->Add(cancel_button);
  buttons_sizer->AddSpacer(5);
  buttons_sizer->Add(save_button);
  inner_->Add(buttons_sizer, 0, wxALIGN_RIGHT);
}

GestureFormDialog::GestureFormDialog(wxWindow* parent, const wxString& title,
                                     const Gesture& gesture)
    : GestureFormDialog{parent, title, gesture.GetFingerCount()} {
  is_editing_ = true;
  previous_gesture_ = gesture;

  // Sets the displayed label for the wxChoice direction widget to the one in
  // the gesture instance.
  auto direction = gesture.GetDirection();
  auto direction_str = Utilities::ConvertDirectionToString(direction);
  if (auto n = direction_choice_->FindString(direction_str); n != wxNOT_FOUND) {
    direction_choice_->SetSelection(n);
  }

  key_codes_ = gesture.GetKeyCodes();

  SetKeyCombinationText();
}

/**
 * @brief Converts a GTK keyval to its corresponding Linux input event code
 * @param keyval The GTK keyval to convert
 * @return The corresponding Linux input event code, or 0 if no mapping exists
 */
uint32_t GestureFormDialog::GtkKeyvalToLinuxInputEventCode(uint32_t keyval) {
  switch (keyval) {
    // Letters
    case GDK_KEY_a:
      return KEY_A;
    case GDK_KEY_b:
      return KEY_B;
    case GDK_KEY_c:
      return KEY_C;
    case GDK_KEY_d:
      return KEY_D;
    case GDK_KEY_e:
      return KEY_E;
    case GDK_KEY_f:
      return KEY_F;
    case GDK_KEY_g:
      return KEY_G;
    case GDK_KEY_h:
      return KEY_H;
    case GDK_KEY_i:
      return KEY_I;
    case GDK_KEY_j:
      return KEY_J;
    case GDK_KEY_k:
      return KEY_K;
    case GDK_KEY_l:
      return KEY_L;
    case GDK_KEY_m:
      return KEY_M;
    case GDK_KEY_n:
      return KEY_N;
    case GDK_KEY_o:
      return KEY_O;
    case GDK_KEY_p:
      return KEY_P;
    case GDK_KEY_q:
      return KEY_Q;
    case GDK_KEY_r:
      return KEY_R;
    case GDK_KEY_s:
      return KEY_S;
    case GDK_KEY_t:
      return KEY_T;
    case GDK_KEY_u:
      return KEY_U;
    case GDK_KEY_v:
      return KEY_V;
    case GDK_KEY_w:
      return KEY_W;
    case GDK_KEY_x:
      return KEY_X;
    case GDK_KEY_y:
      return KEY_Y;
    case GDK_KEY_z:
      return KEY_Z;

    // Numbers
    case GDK_KEY_0:
      return KEY_0;
    case GDK_KEY_1:
      return KEY_1;
    case GDK_KEY_2:
      return KEY_2;
    case GDK_KEY_3:
      return KEY_3;
    case GDK_KEY_4:
      return KEY_4;
    case GDK_KEY_5:
      return KEY_5;
    case GDK_KEY_6:
      return KEY_6;
    case GDK_KEY_7:
      return KEY_7;
    case GDK_KEY_8:
      return KEY_8;
    case GDK_KEY_9:
      return KEY_9;

    // Function keys
    case GDK_KEY_F1:
      return KEY_F1;
    case GDK_KEY_F2:
      return KEY_F2;
    case GDK_KEY_F3:
      return KEY_F3;
    case GDK_KEY_F4:
      return KEY_F4;
    case GDK_KEY_F5:
      return KEY_F5;
    case GDK_KEY_F6:
      return KEY_F6;
    case GDK_KEY_F7:
      return KEY_F7;
    case GDK_KEY_F8:
      return KEY_F8;
    case GDK_KEY_F9:
      return KEY_F9;
    case GDK_KEY_F10:
      return KEY_F10;
    case GDK_KEY_F11:
      return KEY_F11;
    case GDK_KEY_F12:
      return KEY_F12;

    // Special keys
    case GDK_KEY_Return:
      return KEY_ENTER;
    case GDK_KEY_space:
      return KEY_SPACE;
    case GDK_KEY_BackSpace:
      return KEY_BACKSPACE;
    case GDK_KEY_Tab:
      return KEY_TAB;
    case GDK_KEY_Escape:
      return KEY_ESC;
    case GDK_KEY_Delete:
      return KEY_DELETE;
    case GDK_KEY_Home:
      return KEY_HOME;
    case GDK_KEY_End:
      return KEY_END;
    case GDK_KEY_Page_Up:
      return KEY_PAGEUP;
    case GDK_KEY_Page_Down:
      return KEY_PAGEDOWN;
    case GDK_KEY_Insert:
      return KEY_INSERT;

    // Arrow keys
    case GDK_KEY_Left:
      return KEY_LEFT;
    case GDK_KEY_Right:
      return KEY_RIGHT;
    case GDK_KEY_Up:
      return KEY_UP;
    case GDK_KEY_Down:
      return KEY_DOWN;

    // Modifier keys
    case GDK_KEY_Shift_L:
      return KEY_LEFTSHIFT;
    case GDK_KEY_Shift_R:
      return KEY_RIGHTSHIFT;
    case GDK_KEY_Control_L:
      return KEY_LEFTCTRL;
    case GDK_KEY_Control_R:
      return KEY_RIGHTCTRL;
    case GDK_KEY_Alt_L:
      return KEY_LEFTALT;
    case GDK_KEY_Alt_R:
      return KEY_RIGHTALT;
    case GDK_KEY_Super_L:
      return KEY_LEFTMETA;
    case GDK_KEY_Super_R:
      return KEY_RIGHTMETA;
    case GDK_KEY_Caps_Lock:
      return KEY_CAPSLOCK;
    case GDK_KEY_Num_Lock:
      return KEY_NUMLOCK;
    case GDK_KEY_Scroll_Lock:
      return KEY_SCROLLLOCK;

    // Punctuation and symbols
    case GDK_KEY_minus:
      return KEY_MINUS;
    case GDK_KEY_equal:
      return KEY_EQUAL;
    case GDK_KEY_bracketleft:
      return KEY_LEFTBRACE;
    case GDK_KEY_bracketright:
      return KEY_RIGHTBRACE;
    case GDK_KEY_semicolon:
      return KEY_SEMICOLON;
    case GDK_KEY_apostrophe:
      return KEY_APOSTROPHE;
    case GDK_KEY_grave:
      return KEY_GRAVE;
    case GDK_KEY_backslash:
      return KEY_BACKSLASH;
    case GDK_KEY_comma:
      return KEY_COMMA;
    case GDK_KEY_period:
      return KEY_DOT;
    case GDK_KEY_slash:
      return KEY_SLASH;

    // Numpad
    case GDK_KEY_KP_0:
      return KEY_KP0;
    case GDK_KEY_KP_1:
      return KEY_KP1;
    case GDK_KEY_KP_2:
      return KEY_KP2;
    case GDK_KEY_KP_3:
      return KEY_KP3;
    case GDK_KEY_KP_4:
      return KEY_KP4;
    case GDK_KEY_KP_5:
      return KEY_KP5;
    case GDK_KEY_KP_6:
      return KEY_KP6;
    case GDK_KEY_KP_7:
      return KEY_KP7;
    case GDK_KEY_KP_8:
      return KEY_KP8;
    case GDK_KEY_KP_9:
      return KEY_KP9;
    case GDK_KEY_KP_Decimal:
      return KEY_KPDOT;
    case GDK_KEY_KP_Divide:
      return KEY_KPSLASH;
    case GDK_KEY_KP_Multiply:
      return KEY_KPASTERISK;
    case GDK_KEY_KP_Subtract:
      return KEY_KPMINUS;
    case GDK_KEY_KP_Add:
      return KEY_KPPLUS;
    case GDK_KEY_KP_Enter:
      return KEY_KPENTER;

    default:
      return 0;  // Return 0 for unmapped keys
  }
}

void GestureFormDialog::OnCancelButtonClick(wxCommandEvent& event) { Close(); }

void GestureFormDialog::OnClearButtonClick(wxCommandEvent& event) {
  key_codes_.clear();
  key_combination_text_->SetLabel({});
}

void GestureFormDialog::OnSaveButtonClick(wxCommandEvent& event) {
  auto selection = direction_choice_->GetStringSelection();
  auto direction = Utilities::ConvertStringToDirection(selection.ToStdString());
  auto gesture = Gesture{direction, finger_count_, key_codes_};

  is_editing_ ? GesturesFile::ReplaceGesture(previous_gesture_, gesture)
              : GesturesFile::AddGesture(gesture);
  GesturesFile::Save();
  Close();
}

void GestureFormDialog::OnKeyDown(wxKeyEvent& event) {
  // Limits the possible key combinations to a size of 5.
  if (key_codes_.size() >= 5) {
    return;
  }

  // Prevents uppercase characters.
  auto linux_key_code = GtkKeyvalToLinuxInputEventCode(event.GetRawKeyCode());
  if (linux_key_code == 0) {
    return;
  }

  // Exits if the key code is already in the key code vector.
  if (auto it = std::find(key_codes_.begin(), key_codes_.end(), linux_key_code);
      it != key_codes_.end()) {
    return;
  }

  // If the key code is a modifier key...
  if (Utilities::IsModifierKey(linux_key_code)) {
    // ...and if the modifier key is a shift key...
    if (Utilities::IsShiftKey(linux_key_code)) {
      // ...then insert it right before the first non-modifier key code.
      auto index = size_t{0};
      for (auto kc : key_codes_) {
        if (!Utilities::IsModifierKey(kc)) {
          break;
        }

        ++index;
      }

      key_codes_.insert(key_codes_.begin() + index, linux_key_code);
    } else {
      // ...otherwise, insert it before the first shift or non-modifier key
      // code.
      auto index = size_t{0};
      for (auto kc : key_codes_) {
        if (Utilities::IsShiftKey(kc) || !Utilities::IsModifierKey(kc)) {
          break;
        }

        ++index;
      }

      key_codes_.insert(key_codes_.begin() + index, linux_key_code);
    }
  } else {
    key_codes_.push_back(linux_key_code);
  }

  SetKeyCombinationText();

  // Centers key combination text (by recalculating the layout of the sizer
  // and its children).
  inner_->Layout();
}

void GestureFormDialog::OnTextEnter(wxCommandEvent& event) {
  // The only purpose of this function is ensure that no text appears inside
  // the wxTextCtrl as the user records a key combination.
  // This is intended to give the appearance of a text control that cannot
  // receive text input.

  auto text_ctrl = static_cast<wxTextCtrl*>(event.GetEventObject());
  if (auto text = text_ctrl->GetValue(); !text.IsEmpty()) {
    text_ctrl->Clear();
  }
}

void GestureFormDialog::SetKeyCombinationText() {
  auto representations = std::vector<std::string>{};
  representations.reserve(key_codes_.size());
  for (auto key_code : key_codes_) {
    representations.push_back(Utilities::KeyCodeToString(key_code));
  }

  key_combination_text_->SetLabel(Utilities::Join(" + ", representations));
}
