// Copyright (c) 2017, Bosch Software Innovations GmbH.
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


#ifndef RVIZ_DEFAULT_PLUGINS__MOCK_WINDOW_MANAGER_INTERFACE_HPP_
#define RVIZ_DEFAULT_PLUGINS__MOCK_WINDOW_MANAGER_INTERFACE_HPP_

#include <gmock/gmock.h>

#include <QString>

#include "rviz_common/panel_dock_widget.hpp"

#include "rviz_common/window_manager_interface.hpp"

class MockWindowManagerInterface : public rviz_common::WindowManagerInterface
{
public:
  MOCK_METHOD0(getParentWindow, QWidget * ());

  MOCK_METHOD4(
    addPane,
    rviz_common::PanelDockWidget * (
      const QString & name, QWidget * pane, Qt::DockWidgetArea area, bool floating));

  MOCK_METHOD1(setStatus, void(const QString & message));
};


#endif  // RVIZ_DEFAULT_PLUGINS__MOCK_WINDOW_MANAGER_INTERFACE_HPP_
