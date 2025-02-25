// Copyright (c) 2012, Willow Garage, Inc.
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


#ifndef RVIZ_DEFAULT_PLUGINS__DISPLAYS__POSE_ARRAY__FLAT_ARROWS_ARRAY_HPP_
#define RVIZ_DEFAULT_PLUGINS__DISPLAYS__POSE_ARRAY__FLAT_ARROWS_ARRAY_HPP_

#include <vector>

#include <OgreManualObject.h>
#include <OgreMaterialManager.h>
#include <OgreSceneNode.h>
#include <OgreVector.h>
#include <OgreQuaternion.h>

#include "rviz_default_plugins/displays/pose_array/pose_array_display.hpp"
#include "rviz_default_plugins/visibility_control.hpp"

namespace rviz_default_plugins
{
namespace displays
{
struct OgrePose;

class RVIZ_DEFAULT_PLUGINS_PUBLIC FlatArrowsArray
{
public:
  explicit FlatArrowsArray(Ogre::SceneManager * scene_manager_);
  ~FlatArrowsArray();

  void createAndAttachManualObject(Ogre::SceneNode * scene_node);
  void updateManualObject(
    Ogre::ColourValue color,
    float alpha,
    float length,
    const std::vector<rviz_default_plugins::displays::OgrePose> & poses);
  void clear();

private:
  void setManualObjectMaterial();
  void setManualObjectVertices(
    const Ogre::ColourValue & color,
    float length,
    const std::vector<rviz_default_plugins::displays::OgrePose> & poses);

  Ogre::SceneManager * scene_manager_;
  Ogre::ManualObject * manual_object_;
  Ogre::MaterialPtr material_;
};

}  // namespace displays
}  // namespace rviz_default_plugins

#endif  // RVIZ_DEFAULT_PLUGINS__DISPLAYS__POSE_ARRAY__FLAT_ARROWS_ARRAY_HPP_
