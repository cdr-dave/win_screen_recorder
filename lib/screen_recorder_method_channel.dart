import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'screen_recorder_platform_interface.dart';

/// An implementation of [ScreenRecorderPlatform] that uses method channels.
class MethodChannelScreenRecorder extends ScreenRecorderPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('screen_recorder');

  @override
  Future<bool?> startRecord(String strPath) async {
    return methodChannel.invokeMethod<bool?>('start', {"path": strPath});
  }

  @override
  void stopRecord() {
    methodChannel.invokeMethod('stop');
  }
}
