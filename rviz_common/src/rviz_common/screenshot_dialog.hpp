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


#ifndef RVIZ_COMMON__SCREENSHOT_DIALOG_HPP_
#define RVIZ_COMMON__SCREENSHOT_DIALOG_HPP_

#include <QString>
#include <QWidget>

class QAbstractButton;
class QDialogButtonBox;

namespace rviz_common
{

class ScaledImageWidget;

/// A dialog for grabbing a screen shot.
/**
 * Takes the screenshot while in the constructor, then shows a half-size view
 * of the screenshot in the dialog with buttons for save/try-again/cancel.
 */
class ScreenshotDialog : public QWidget
{
  Q_OBJECT

public:
  ScreenshotDialog(
    QWidget * main_window,
    QWidget * render_window,
    const QString & default_save_dir = QString());
  virtual ~ScreenshotDialog() {}

Q_SIGNALS:
  /// Emitted when the user saves a file.
  void savedInDirectory(const QString & directory);

protected Q_SLOTS:
  void takeScreenshot();
  void onTimeout();
  void takeScreenshotNow();
  void save();
  void onButtonClicked(QAbstractButton * clicked);
  void setSaveFullWindow(bool save_full_window);

protected:
  virtual void showEvent(QShowEvent * event);

private:
  ScaledImageWidget * image_widget_;
  QWidget * main_window_;
  QWidget * render_window_;
  QPixmap screenshot_;
  QDialogButtonBox * button_box_;
  bool save_full_window_;
  QTimer * delay_timer_;
  QSize saved_size_;
  bool first_time_;
  QString default_save_dir_;
};

}  // namespace rviz_common

#endif  // RVIZ_COMMON__SCREENSHOT_DIALOG_HPP_
