#pragma once

#include <memory>

#include "AraelConfig.h"
#include "BpfAdapter.h"

namespace arael {

class AraelController {
 public:
  AraelController() = delete;

  explicit AraelController(const AraelConfig &config);

  ~AraelController();

  void openBpfProgs();

  void loadBpfProgs();

  void attachBpfProgs();

  void destroyBpfProgs();

 private:
  std::unique_ptr<BpfAdapter> adapter_;
};

}  // namespace arael