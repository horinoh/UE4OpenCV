# UE4OpenCV

* http://opencv.org/ v3.0 を DL してビルド (download v3.0 and build)
* コピーする (copy)
~~~
copy C:\opencv\build\bin\Debug\*.dll UE4OpenCV\ThirdParty\opencv\build\bin\Debug\
copy C:\opencv\build\bin\Release\*.dll UE4OpenCV\ThirdParty\opencv\build\bin\Release\
~~~
~~~
copy C:\opencv\build\include\opencv\*.h UE4OpenCV\ThirdParty\opencv\build\include\opencv\
copy C:\opencv\build\include\opencv2\* UE4OpenCV\ThirdParty\opencv\build\include\opencv2\
~~~
~~~
copy C:\opencv\build\lib\Debug\*.lib UE4OpenCV\ThirdParty\opencv\build\lib\Debug\
copy C:\opencv\build\lib\Release\*.lib UE4OpenCV\ThirdParty\opencv\build\lib\Release\
~~~
* .uproject を右クリック(right click .uproject) → Generate Visual Studio project files → .sln を開いてビルド (open .sln and build)