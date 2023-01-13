#ifndef FLUTTER_PLUGIN_SCREEN_RECORDER_PLUGIN_H_
#define FLUTTER_PLUGIN_SCREEN_RECORDER_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>

#include <memory>

namespace screen_recorder {

class ScreenRecorderPlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  ScreenRecorderPlugin();

  virtual ~ScreenRecorderPlugin();

  // Disallow copy and assign.
  ScreenRecorderPlugin(const ScreenRecorderPlugin&) = delete;
  ScreenRecorderPlugin& operator=(const ScreenRecorderPlugin&) = delete;

 private:
  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
};

}  // namespace screen_recorder

#endif  // FLUTTER_PLUGIN_SCREEN_RECORDER_PLUGIN_H_
