#pragma once

#include "CLIK/GFx/Core/UIComponent.h"

namespace CLIK {
    namespace GFx {
        namespace Controls {
            class ButtonBar : public Core::UIComponent {
            private:
                using super = Core::UIComponent;

            public:
                ButtonBar() = default;
                ButtonBar(const ButtonBar&) = default;
                ButtonBar(ButtonBar&&) = default;
                using super::super;

                ButtonBar(const super& a_rhs) : super(a_rhs) {}

                ButtonBar(super&& a_rhs) : super(move(a_rhs)) {}

                ~ButtonBar() = default;

                ButtonBar& operator=(const ButtonBar&) = default;
                ButtonBar& operator=(ButtonBar&&) = default;
                using super::operator=;

                ButtonBar& operator=(const super& a_rhs) {
                    super::operator=(a_rhs);
                    return *this;
                }

                ButtonBar& operator=(super&& a_rhs) {
                    super::operator=(move(a_rhs));
                    return *this;
                }

                bool Disabled() { return GetBoolean("disabled"); }
                void Disabled(bool a_value) { return SetBoolean("disabled", a_value); }

                Object DataProvider() { return GetObject("dataProvider"); }
                void DataProvider(const Object& a_value) { return SetObject("dataProvider", a_value); }

                void InvalidateData() {
                    [[maybe_unused]] const auto success = Invoke("invalidateData");
                    assert(success);
                }

                string ItemRenderer() { return GetString("itemRenderer"); }
                void ItemRenderer(string_view a_value) { return SetString("itemRenderer", move(a_value)); }

                double Spacing() { return GetNumber("spacing"); }
                void Spacing(double a_value) { return SetNumber("spacing", a_value); }

                string Direction() { return GetString("direction"); }
                void Direction(string_view a_value) { return SetString("direction", a_value); }

                string AutoSize() { return GetString("autoSize"); }
                void AutoSize(string_view a_value) { return SetString("autoSize", a_value); }

                double ButtonWidth() { return GetNumber("buttonWidth"); }
                void ButtonWidth(double a_value) { return SetNumber("buttonWidth", a_value); }

                double SelectedIndex() { return GetNumber("selectedIndex"); }
                void SelectedIndex(double a_value) { return SetNumber("selectedIndex", a_value); }

                Object SelectedItem() { return GetObject("selectedItem"); }

                Object Data() { return GetObject("data"); }

                string LabelField() { return GetString("labelField"); }
                void LabelField(string_view a_value) { return SetString("labelField", a_value); }

                // CLIK::Function LabelFunction() { return GetObject("labelFunction"); }
                // void LabelFunction(CLIK::Function a_value) { return SetObject("labelFunction", a_value); }

                string ItemToLabel(Object a_item) {
                    enum { kItem, kNumArgs };

                    array<RE::GFxValue, kNumArgs> args;

                    args[kItem] = a_item.GetInstance();
                    assert(args[kItem].IsObject());

                    RE::GFxValue str;
                    [[maybe_unused]] const auto success =
                        Invoke("itemToLabel", addressof(str), args.data(), args.size());
                    assert(success);

                    return str.GetString();
                }

                //bool handleInput(CLIK::GFx::UI::InputDetails a_details, CLIK::Array a_pathToFocus);

                string ToString() {
                    RE::GFxValue str;
                    [[maybe_unused]] const auto success = Invoke("toString", addressof(str));
                    assert(success);
                    return str.GetString();
                }
            };
        }
    }
}
