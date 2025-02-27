// Copyright (c) 2012, Willow Garage, Inc.
// Copyright (c) 2017, Open Source Robotics Foundation, Inc.
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


#include "failed_view_controller.hpp"

#include <QMessageBox>
#include <QString>

#include "rviz_common/display_context.hpp"
#include "rviz_common/window_manager_interface.hpp"

namespace rviz_common
{

FailedViewController::FailedViewController(
  const QString & desired_class_id,
  const QString & error_message)
: error_message_(error_message)
{
  setClassId(desired_class_id);
}

QString FailedViewController::getDescription() const
{
  return "The class required for this view controller, '" + getClassId() +
         "', could not be loaded.<br><b>Error:</b><br>" + error_message_;
}

void FailedViewController::load(const Config & config)
{
  saved_config_ = config;
  ViewController::load(config);
}

void FailedViewController::save(Config config) const
{
  if (saved_config_.isValid() ) {
    config.copy(saved_config_);
  } else {
    ViewController::save(config);
  }
}

void FailedViewController::onActivate()
{
  QWidget * parent = nullptr;
  if (context_->getWindowManager() ) {
    parent = context_->getWindowManager()->getParentWindow();
  }
  QMessageBox::critical(
    parent, "ViewController '" + getName() + "'unavailable.",
    getDescription() );
}

void FailedViewController::lookAt(const Ogre::Vector3 & point)
{
  Q_UNUSED(point);
}

}  // end namespace rviz_common
