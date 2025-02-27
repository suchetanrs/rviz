// Copyright (c) 2008, Willow Garage, Inc.
// Copyright (c) 2017, Open Source Robotics Foundation, Inc.
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


#ifndef RVIZ_COMMON__ADD_DISPLAY_DIALOG_HPP_
#define RVIZ_COMMON__ADD_DISPLAY_DIALOG_HPP_

#include <memory>
#include <string>

#include <QComboBox>  // NOLINT: cpplint is unable to handle the include order here
#include <QDialog>  // NOLINT: cpplint is unable to handle the include order here
#include <QMultiMap>  // NOLINT: cpplint is unable to handle the include order here
#include <QString>  // NOLINT: cpplint is unable to handle the include order here
#include <QTreeWidget>  // NOLINT: cpplint is unable to handle the include order here

#include "rviz_common/factory/factory.hpp"
#include "rviz_common/ros_integration/ros_node_abstraction_iface.hpp"

class QCheckBox;
class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QTextBrowser;

namespace rviz_common
{

class DisplayFactory;
class Display;

/// Meta-data needed to pick a plugin and optionally a topic.
struct SelectionData
{
  QString whats_this;
  QString lookup_name;
  QString display_name;
  QString topic;
  QString datatype;
};

class AddDisplayDialog : public QDialog
{
  Q_OBJECT

public:
  ///  Dialog for choosing a new object to load with a pluginlib ClassLoader.
  /**
   * \param disallowed_display_names set of display names to prevent
   *        the user from using.
   *
   * \param disallowed_class_lookup_names set of class lookup names to
   *        prevent the user from selecting.  Names found in the class loader
   *        which are in this list will appear disabled.
   *
   * \param lookup_name_output Pointer to a string where dialog will
   *        put the class lookup name chosen.
   *
   * \param display_name_output Pointer to a string where dialog will
   *        put the display name entered, or NULL (default) if display
   *        name entry field should not be shown.
   */
  AddDisplayDialog(
    DisplayFactory * factory,
    const QStringList & disallowed_display_names,
    const QStringList & disallowed_class_lookup_names,
    QString * lookup_name_output,
    ros_integration::RosNodeAbstractionIface::WeakPtr rviz_ros_node,
    QString * display_name_output = 0,
    QString * topic_output = 0,
    QString * datatype_output = 0,
    QWidget * parent = 0);

  QSize sizeHint() const override;

public Q_SLOTS:
  void accept() override;

private Q_SLOTS:
  void onDisplaySelected(SelectionData * data);
  void onTopicSelected(SelectionData * data);
  void onTabChanged(int index);
  void onNameChanged();

private:
  /// Fill the tree widget with classes from the class loader.
  void fillTree(QTreeWidget * tree);

  /// Return true if entered display name is non-empty and unique and if lookup name is non-empty.
  bool isValid();

  /// Display an error message, or clear the previous error message if error_text is empty.
  void setError(const QString & error_text);

  /// Populate text boxes based on current tab and selection.
  void updateDisplay();

  Factory * factory_;
  const QStringList & disallowed_display_names_;
  const QStringList & disallowed_class_lookup_names_;

  QString * lookup_name_output_;
  QString * display_name_output_;
  QString * topic_output_;
  QString * datatype_output_;

  /// Widget holding tabs.
  QTabWidget * tab_widget_;
  /// Index of tab for selection by topic.
  int topic_tab_;
  /// Index of tab for selection by display.
  int display_tab_;
  /// Current data for display tab.
  SelectionData display_data_;
  /// Current data for topic tab.
  SelectionData topic_data_;

  /// Widget showing description of the class.
  QTextBrowser * description_;

  QLineEdit * name_editor_;

  /// Widget with OK and CANCEL buttons.
  QDialogButtonBox * button_box_;

  /// Current value of selected class-lookup name.
  /**
   * Copied to *lookup_name_output_ when "ok" is clicked.
   */
  QString lookup_name_;
};

/// Widget for selecting a display by display type.
class DisplayTypeTree : public QTreeWidget
{
  Q_OBJECT

public:
  DisplayTypeTree();

  void fillTree(Factory * factory);

Q_SIGNALS:
  void itemChanged(SelectionData * selection);

private Q_SLOTS:
  void onCurrentItemChanged(QTreeWidgetItem * curr, QTreeWidgetItem * prev);
};

/// Widget for selecting a display by topic.
class TopicDisplayWidget : public QWidget
{
  Q_OBJECT

public:
  explicit TopicDisplayWidget(ros_integration::RosNodeAbstractionIface::WeakPtr rviz_ros_node);
  void fill(DisplayFactory * factory);

Q_SIGNALS:
  void itemChanged(SelectionData * selection);
  void itemActivated(QTreeWidgetItem * item, int column);

private Q_SLOTS:
  void stateChanged(int state);
  void onCurrentItemChanged(QTreeWidgetItem * curr);
  void onComboBoxClicked(QTreeWidgetItem * curr);

private:
  void findPlugins(DisplayFactory *);

  /// Insert a topic into the tree.
  /**
   * \param topic Topic to be inserted.
   * \param disabled If true, set all created widgets as disabled.
   */
  QTreeWidgetItem * insertItem(const QString & topic, bool disabled);

  QTreeWidget * tree_;
  QCheckBox * enable_hidden_box_;

  // Map from ROS topic type to all displays that can visualize it.
  // One key may have multiple values.
  QMultiMap<QString, QString> datatype_plugins_;
  ros_integration::RosNodeAbstractionIface::WeakPtr rviz_ros_node_;
};

/// A combo box that can be inserted into a QTreeWidgetItem.
/**
 * Identical to QComboBox except that when it clicks it emits a signal
 * containing the QTreeWidgetItem that it's given at construction.
 */
class EmbeddableComboBox : public QComboBox
{
  Q_OBJECT

public:
  EmbeddableComboBox(QTreeWidgetItem * parent, int col)
  : parent_(parent), column_(col)
  {
    connect(this, SIGNAL(activated(int)), this, SLOT(onActivated(int)));
  }

Q_SIGNALS:
  void itemClicked(QTreeWidgetItem * item, int column);

private Q_SLOTS:
  void onActivated(int index)
  {
    Q_UNUSED(index);
    Q_EMIT itemClicked(parent_, column_);
  }

private:
  QTreeWidgetItem * parent_;
  int column_;
};

}  // namespace rviz_common

#endif  // RVIZ_COMMON__ADD_DISPLAY_DIALOG_HPP_
