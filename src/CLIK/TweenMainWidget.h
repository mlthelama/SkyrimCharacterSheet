#include "CLIK/MovieClip.h"

namespace CLIK {
    class TweenMainWidget : public MovieClip {
    public:
        [[nodiscard]] Object data_provider() const { return GetObject("dataProvider"); }
        void data_provider(const Object& a_data_provider) { SetObject("dataProvider", a_data_provider); }
    };
}  // CLIK
