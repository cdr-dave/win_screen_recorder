import 'screen_recorder_platform_interface.dart';

class ScreenRecorder {
  static Future<bool?> startRecord(String strPath) {
    return ScreenRecorderPlatform.instance.startRecord(strPath);
  }

  static void stopRecord() {
    ScreenRecorderPlatform.instance.stopRecord();
  }
}
