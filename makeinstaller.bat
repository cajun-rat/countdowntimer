set WIX=C:\Program Files (x86)\WiX Toolset v3.7\bin

set /p version="Enter build version (x.x.x):"

"%WIX%\candle" -arch x64 -dPlatform=x64 -dVersion=%version% -o installer-64.wixobj installer.wxs
"%WIX%\light" -nologo -out countdowntimer-%version%-x64.msi installer-64.wixobj

"%WIX%\candle" -arch x86 -dPlatform=x86 -dVersion=%version% -o installer-32.wixobj installer.wxs
"%WIX%\light" -nologo -out countdowntimer-%version%-x86.msi installer-32.wixobj
@pause
