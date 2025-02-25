// Copyright (c) 2018, Bosch Software Innovations GmbH.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//    * Neither the name of the copyright holder nor the names of its
//      contributors may be used to endorse or promote products derived from
//      this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.


#ifndef RVIZ_DEFAULT_PLUGINS__MOCK_HANDLER_MANAGER_HPP_
#define RVIZ_DEFAULT_PLUGINS__MOCK_HANDLER_MANAGER_HPP_

#include <gmock/gmock.h>

#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "rviz_common/interaction/forwards.hpp"
#include "rviz_common/interaction/handler_manager_iface.hpp"
#include "rviz_common/interaction/selection_handler.hpp"

class MockHandlerManager : public rviz_common::interaction::HandlerManagerIface
{
public:
  MOCK_METHOD0(createHandle, rviz_common::interaction::CollObjectHandle());

  MOCK_METHOD2(
    addHandler, void(rviz_common::interaction::CollObjectHandle,
    rviz_common::interaction::SelectionHandlerWeakPtr));
  MOCK_METHOD1(removeHandler, void(rviz_common::interaction::CollObjectHandle));
  MOCK_METHOD1(addListener, void(rviz_common::interaction::HandlerManagerListener *));
  MOCK_METHOD1(removeListener, void(rviz_common::interaction::HandlerManagerListener *));
  MOCK_METHOD1(
    getHandler,
    rviz_common::interaction::SelectionHandlerPtr(rviz_common::interaction::CollObjectHandle));

  MOCK_METHOD1(enableInteraction, void(bool));
  MOCK_CONST_METHOD0(getInteractionEnabled, bool());
  MOCK_METHOD0(handlers, rviz_common::interaction::HandlerRange());

  MOCK_METHOD0(lock, std::unique_lock<std::recursive_mutex>());
  MOCK_METHOD1(lock, std::unique_lock<std::recursive_mutex>(std::defer_lock_t));
};

#endif  // RVIZ_DEFAULT_PLUGINS__MOCK_HANDLER_MANAGER_HPP_
