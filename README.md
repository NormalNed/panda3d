<img src="https://avatars2.githubusercontent.com/u/590956?v=3&s=500" align="right" width="200"/>

# Panda3D

Upstream Branch of Astron Panda3D for [Normal Ned](https://github.com/NormalNed) [Toontown Stride](https://github.com/NormalNed/ToontownStride)

Panda3D is licensed under the Modified BSD License.  See the LICENSE file for
more details.

# 🔨 Building
Below you will find anything you need to know. If you want to download a build you can do it via CurseForge. 

## 💻 Windows

You can build Panda3D with the Microsoft Visual C++ 2015, 2017 or 2019 compiler,
which can be downloaded for free from the [Visual Studio site](https://visualstudio.microsoft.com/downloads/).
You will also need to install the [Windows 10 SDK](https://developer.microsoft.com/en-us/windows/downloads/windows-10-sdk),
and if you intend to target Windows Vista, you will also need the
[Windows 8.1 SDK](https://go.microsoft.com/fwlink/p/?LinkId=323507).

You will also need to have the third-party dependency libraries available for
the build scripts to use.  These are available from one of these two URLs,
depending on whether you are on a 32-bit or 64-bit system, or you can
[click here](https://github.com/rdb/panda3d-thirdparty) for instructions on
building them from source.

- https://www.panda3d.org/download/panda3d-1.10.5/panda3d-1.10.5-tools-win64.zip
- https://www.panda3d.org/download/panda3d-1.10.5/panda3d-1.10.5-tools-win32.zip

After acquiring these dependencies, you can build Panda3D from the command
prompt using the following command.  Change the `--msvc-version` option based
on your version of Visual C++; 2019 is 14.2, 2017 is 14.1, and 2015 is 14.
Remove the `--windows-sdk=10` option if you need to support Windows Vista,
which requires the Windows 8.1 SDK.

```bash
makepanda\makepanda.bat --everything --installer --msvc-version=14.2 --windows-sdk=10 --no-eigen --threads=2
```

## 🐧 Linux

Building Panda3D on Linux is easy.  All you need is to invoke the makepanda
script using the version of Python that you want Panda3D to be built against.

The following command illustrates how to build Panda3D for [Normal Ned](https://github.com/NormalNed) [Toontown Stride](https://github.com/NormalNed/ToontownStride)
```bash
python2 makepanda/makepanda.py --everything --installer --no-egl --no-gles --no-gles2 --no-opencv
```
