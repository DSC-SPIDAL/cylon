/*
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TWISTERX_SRC_TWISTERX_COMM_COMMUNICATOR_H_
#define TWISTERX_SRC_TWISTERX_COMM_COMMUNICATOR_H_

#include "comm_config.h"
#include "channel.hpp"
namespace twisterx {
namespace net {

class Communicator {

 protected:
  int rank = -1;
  int world_size = -1;
 public:
  virtual void Init(CommConfig *config) = 0;
  virtual Channel *CreateChannel() = 0;
  virtual int GetRank() = 0;
  virtual int GetWorldSize() = 0;
  virtual void Finalize() = 0;
  virtual void Barrier() = 0;
};
}
}

#endif //TWISTERX_SRC_TWISTERX_COMM_COMMUNICATOR_H_
