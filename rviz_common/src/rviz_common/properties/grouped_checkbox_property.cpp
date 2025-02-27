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

#include "rviz_common/properties/grouped_checkbox_property.hpp"

#include <memory>

#include <QString>  // NOLINT: cpplint is unable to handle the include order here

#include "rviz_common/properties/grouped_checkbox_property_group.hpp"

namespace rviz_common
{
namespace properties
{

GroupedCheckboxProperty::GroupedCheckboxProperty(
  std::shared_ptr<GroupedCheckboxPropertyGroup> group,
  const QString & name,
  bool default_value,
  const QString & description,
  Property * parent,
  const char * changed_slot,
  QObject * receiver
)
: BoolProperty(name, default_value, description, parent, changed_slot, receiver), group_(group)
{
  group->addProperty(this);
}

bool GroupedCheckboxProperty::setValue(const QVariant & new_value)
{
  Q_UNUSED(new_value);
  return true;
}

bool GroupedCheckboxProperty::setRawValue(const QVariant & new_value)
{
  return Property::setValue(new_value);
}

void GroupedCheckboxProperty::checkPropertyInGroup()
{
  group_->setChecked(this);
}

}  // namespace properties
}  // namespace rviz_common
