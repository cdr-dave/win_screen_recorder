#include "include/screen_recorder/screen_recorder_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "screen_recorder_plugin.h"

void ScreenRecorderPluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  screen_recorder::ScreenRecorderPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
