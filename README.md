# UE4OpenCV

## OpenCV をクローンしてビルド
* https://github.com/opencv/opencv.git からクローン
* CMake
    * Where is the source code にそのフォルダを指定
    * Where to build the binary に適当なフォルダを指定 (例えば D:\opencv)
    * Configure - Specify the generator for this project で Visual Studio 14 2015 Win64 を選択
    * WITH_CUDA のチェックを外して 赤くなくなるまで Configure
    * Generate
* Visual Studio
    * opencv/OpenCV.sln が出来るので開いて CMakeTargets - INSTALL プロジェクトをビルド(Debug, Release)する
    * opencv/install 以下へ色々出力される

## 必要なものをコピーする
~~~
copy opencv\install\include\* UE4OpenCV\ThirdParty\opencv\install\include\
copy opencv\install\x64\vc14\lib\*.lib UE4OpenCV\ThirdParty\opencv\install\x64\vc14\lib\
copy opencv\install\x64\vc14\bin\*.dll UE4OpenCV\ThirdParty\opencv\install\x64\vc14\bin\
~~~
* opencv2/core/utilities.hpp の check() が UE4 の check() と被って、コンパイルが通らないのでコメントアウト
	* 本当にコメントアウトしていいのかは分からない…
~~~
#if defined(check)
//#  warning Detected Apple 'check' macro ...
#endif
...
//bool check() const;
~~~
