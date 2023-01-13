#include "screen_recorder_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

// For getPlatformVersion; remove unless needed for your plugin implementation.
#include <VersionHelpers.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <memory>
#include <sstream>
#include <thread>
#include <codecvt>


#include "MP4File.h"

using flutter::EncodableMap;
using flutter::EncodableValue;

namespace screen_recorder {

// static
void ScreenRecorderPlugin::RegisterWithRegistrar(
    flutter::PluginRegistrarWindows *registrar) {
  auto channel =
      std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
          registrar->messenger(), "screen_recorder",
          &flutter::StandardMethodCodec::GetInstance());

  auto plugin = std::make_unique<ScreenRecorderPlugin>();

  channel->SetMethodCallHandler(
      [plugin_pointer = plugin.get()](const auto &call, auto result) {
        plugin_pointer->HandleMethodCall(call, std::move(result));
      });

  registrar->AddPlugin(std::move(plugin));
}

ScreenRecorderPlugin::ScreenRecorderPlugin() {}

ScreenRecorderPlugin::~ScreenRecorderPlugin() {}


static std::string strPath;

const EncodableValue* ValueOrNull(const EncodableMap& map, const char* key)
{
    auto it = map.find(EncodableValue(key));
    if (it == map.end())
    {
        return nullptr;
    }
    return &(it->second);
}


HBITMAP GetBitmap(int width, int height)
{
    // Get Cursor Size
    int cursorWidth = GetSystemMetrics(SM_CXCURSOR);
    int cursorHeight = GetSystemMetrics(SM_CYCURSOR);

	HDC hScreen = GetDC(NULL);
	HDC hDC = CreateCompatibleDC(hScreen);


	HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, width, height);
	HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
	BOOL bRet = BitBlt(hDC, 0, 0, width, height, hScreen, 0, 0, SRCCOPY);

    CURSORINFO ci;
    ci.cbSize = sizeof(ci);
    GetCursorInfo(&ci);
    DrawIcon(hDC, ci.ptScreenPos.x, ci.ptScreenPos.y, ci.hCursor);

	SelectObject(hDC, old_obj);
	DeleteDC(hDC);
	ReleaseDC(NULL, hScreen);

	return hBitmap;
}

static bool isRecording = false;

void run() {
    HDC window_dc = ::GetDC(::GetDesktopWindow());
    int width = GetDeviceCaps(window_dc, HORZRES);
    int height = GetDeviceCaps(window_dc, VERTRES);

    std::wstring wstr =
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t>{}
    .from_bytes(strPath.c_str());

	MP4File file(wstr, width, height); // Do not specify file extension. You will get an mp4 file regardless

    if (!file.IsInitialized()) {
	    isRecording = false;
	    return;
    }

    isRecording = true;
    HRESULT hr = NULL;

    while (isRecording)
    {
	    HBITMAP hBitmap = GetBitmap(width, height);
	    hr = file.AppendFrame(hBitmap);

	    if (FAILED(hr))
		    isRecording = false;
    }
  
	file.Finalize();
}

void stop() {
	isRecording = false;
}


void ScreenRecorderPlugin::HandleMethodCall(
    const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  if (method_call.method_name().compare("start") == 0) {
    if(isRecording){
      result->Success(false);
      return;
    }

    const auto *data =
            std::get_if<EncodableMap>(method_call.arguments());

    const std::string *strTemp = std::get_if<std::string>(
            ValueOrNull(*data, "path"));

    strPath = *strTemp;

    std::thread th(run);
    th.detach();
    result->Success(true);
  } 
  else if (method_call.method_name().compare("stop") == 0) {
    stop();
    result->Success();
  } 
  else {
    result->NotImplemented();
  }
}

}  // namespace screen_recorder
