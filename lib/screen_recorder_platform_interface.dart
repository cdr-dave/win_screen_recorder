import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'screen_recorder_method_channel.dart';

abstract class ScreenRecorderPlatform extends PlatformInterface {
  /// Constructs a ScreenRecorderPlatform.
  ScreenRecorderPlatform() : super(token: _token);

  static final Object _token = Object();

  static ScreenRecorderPlatform _instance = MethodChannelScreenRecorder();

  /// The default instance of [ScreenRecorderPlatform] to use.
  ///
  /// Defaults to [MethodChannelScreenRecorder].
  static ScreenRecorderPlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [ScreenRecorderPlatform] when
  /// they register themselves.
  static set instance(ScreenRecorderPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<bool?> startRecord(String strPath) async {
    throw UnimplementedError('startRecord() has not been implemented.');
  }

  void stopRecord() {
    throw UnimplementedError('stopRecord() has not been implemented.');
  }
}
