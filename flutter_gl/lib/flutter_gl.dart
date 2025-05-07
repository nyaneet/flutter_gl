import 'dart:async';

//import 'flutter_gl_platform_interface.dart';
import 'package:flutter_gl_platform_interface/flutter_gl_platform_interface.dart';

import 'openGL/OpenGL.dart';
export './openGL/OpenGL.dart';
export './native-array/index.dart';

/// FlutterGlPlugin
///
/// FlutterGlPlugin = FlutterGlPlugin();
/// Map<String, dynamic> _options = {
///     "width": width,
///     "height": height,
///     "antialias": true,
///     "alpha": false
/// };
/// await FlutterGlPlugin.initialize(options: _options);
class FlutterGlPlugin extends FlutterGlPlatform {
  late dynamic openGL;

  late List<int> egls;

  dynamic get gl => openGL.gl;

  // for web
  dynamic get element => openGL.element;

  FlutterGlPlugin();

  Future<Map<String, dynamic>> initialize(
      {Map<String, dynamic>? options}) async {
   // print("main fluttergl initalize");
    Map<String, dynamic> _options = {};

    _options.addAll(options ?? {});

    final resp = await FlutterGlPlatform.instance.initialize_interface(options: _options);
   // if (resp.containsKey('textureid'))
      textureId = resp["textureId"];
   // else
   //   textureId=  resp;
    // used for web
    _options["divId"] = textureId.toString();
    openGL = OpenGL().init(_options);

    return resp;
  }

  /// set opengl context for ffi thread
  prepareContext() async {
 //  print("prepare context main texture "+this.textureId!.toString());
  //  try {
   // print("preparecontext");
    egls = await FlutterGlPlatform.instance.getEgl_interface(this.textureId!);
   // print("preparecontextii"+egls.toString());

   // await FlutterGlPlatform.instance.getEgl_interface(this.textureId!);
    await Future.delayed(const Duration(milliseconds: 1000), () async {
      openGL.makeCurrent(egls);
    });
    //print("preparecontextiii");
    //} catch (error) {
    //  ... // executed for errors of all types other than Exception
    // print('errr!');
    //}
  }

  /// get created opengl context from native
  Future<List<int>> getEgl(int textureId) async {
    var result =
        List<int>.from(await FlutterGlPlatform.instance.getEgl_interface(textureId));
    return result;
  }

  /// update texture to flutter
  Future updateTexture(sourceTexture) async {
    //print("updatetext in flutter_gl"+this.textureId.toString()+ " "+sourceTexture.toString());
    return await FlutterGlPlatform.instance.updateTexture_interface(this.textureId!, sourceTexture);
  }

  dispose() {
  //  print("main dispose");
    return FlutterGlPlatform.instance.dispose_interface(this.textureId!);
  }
}
