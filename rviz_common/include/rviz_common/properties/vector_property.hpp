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


#ifndef RVIZ_COMMON__PROPERTIES__VECTOR_PROPERTY_HPP_
#define RVIZ_COMMON__PROPERTIES__VECTOR_PROPERTY_HPP_

#include <OgreVector.h>

#include <QString>

#include "rviz_common/properties/property.hpp"
#include "rviz_common/visibility_control.hpp"

namespace rviz_common
{
namespace properties
{

class RVIZ_COMMON_PUBLIC VectorProperty : public Property
{
  Q_OBJECT

public:
  explicit
  VectorProperty(
    const QString & name = QString(),
    const Ogre::Vector3 & default_value = Ogre::Vector3::ZERO,
    const QString & description = QString(),
    Property * parent = 0,
    const char * changed_slot = 0,
    QObject * receiver = 0);

  virtual
  bool
  setVector(const Ogre::Vector3 & vector);

  virtual
  Ogre::Vector3
  getVector() const;

  bool
  add(const Ogre::Vector3 & offset);

  virtual
  bool
  setValue(const QVariant & new_value);

  virtual
  void
  load(const Config & config);

  virtual
  void
  save(Config config) const;

  /// Overridden from Property to propagate read-only-ness to children.
  virtual
  void
  setReadOnly(bool read_only);

private Q_SLOTS:
  void
  updateFromChildren();

  void
  emitAboutToChange();

private:
  void
  updateString();

  Ogre::Vector3 vector_;
  Property * x_;
  Property * y_;
  Property * z_;

  bool ignore_child_updates_;
};

}  // namespace properties
}  // namespace rviz_common

#endif  // RVIZ_COMMON__PROPERTIES__VECTOR_PROPERTY_HPP_
