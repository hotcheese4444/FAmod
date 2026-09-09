module;
#include <xbyak/xbyak.h>

export module patch.reclaim_camera_distance;
import core;
import std;

namespace {

constexpr float kReclaimCameraDistance = 500.0f;

struct ReclaimCameraDistanceValuePatch : public Xbyak::CodeGenerator {
  ReclaimCameraDistanceValuePatch()
      : Xbyak::CodeGenerator(
            sizeof(kReclaimCameraDistance),
            reinterpret_cast<void *>(0x00E4F988)) {
    setProtectMode(PROTECT_RWE);
    dd(std::bit_cast<std::uint32_t>(kReclaimCameraDistance));
    setProtectModeRE();
  }
};

} // namespace

export class ReclaimCameraDistancePatch : public IPatch {
public:
  [[nodiscard]] std::string_view Name() const noexcept override {
    return tr("Extended Reclaim Camera Distance");
  }

  [[nodiscard]] std::string_view Description() const noexcept override {
    return tr("Extends the maximum camera distance for reclaiming from 150 to "
              "500.");
  }

  void Apply() override { ReclaimCameraDistanceValuePatch patch; }
};
