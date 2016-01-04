;
; RedSquare windows installer configurationm file.
;
; The file can be processed with "Inno Setup Compiler v5.3.11"
;
; All Copyrights Reserved (c) PlaatSoft 2008-2011

[Setup]
AppPublisher=PlaatSoft
AppPublisherURL=http://www.plaatsoft.nl
AppName=RedSquare
AppVerName=PlaatSoft RedSquare v1.0
AppVersion=1.0
AppCopyright=Copyright (C) 2008-2011 PlaatSoft

DefaultDirName={pf}\RedSquare
DefaultGroupName=PlaatSoft
UninstallDisplayIcon={app}\RedSquare.exe
Compression=lzma
SolidCompression=yes
OutputDir=release\

[Files]
Source: "src\release\RedSquare.exe"; DestDir: "{app}"
Source: "src\release\libgcc_s_dw2-1.dll"; DestDir: "{app}"
Source: "src\release\mingwm10.dll"; DestDir: "{app}"
Source: "src\release\QtCore4.dll"; DestDir: "{app}"
Source: "src\release\QtGui4.dll"; DestDir: "{app}"
Source: "src\release\QtNetwork4.dll"; DestDir: "{app}"
Source: "src\release\QtXml4.dll"; DestDir: "{app}"
Source: "src\release\imageformats\qgif4.dll"; DestDir: "{app}\imageformats"
Source: "src\release\imageformats\qico4.dll"; DestDir: "{app}\imageformats"
Source: "src\release\imageformats\qjpeg4.dll"; DestDir: "{app}\imageformats"
Source: "src\release\imageformats\qmng4.dll"; DestDir: "{app}\imageformats"
Source: "src\release\imageformats\qsvg4.dll"; DestDir: "{app}\imageformats"
Source: "src\release\imageformats\qtiff4.dll"; DestDir: "{app}\imageformats"
Source: "src\snd\start.wav"; DestDir: "{app}\snd"
Source: "src\snd\border.wav"; DestDir: "{app}\snd"
Source: "src\snd\gameover.wav"; DestDir: "{app}\snd"
Source: "src\release\license.txt"; DestDir: "{app}"; Flags: isreadme

[Icons]
Name: "{group}\RedSquare\RedSquare"; Filename: "{app}\RedSquare.exe"
Name: "{commondesktop}\PlaatSoft RedSquare"; Filename: "{app}\RedSquare.exe"
Name: "{group}\RedSquare\Uninstaller"; Filename: "{uninstallexe}"

[Registry]
Root: HKCU; Subkey: "Software\PlaatSoft\RedSquare"; ValueName: "target"; ValueData: {app}; ValueType: string;  Flags: uninsdeletekeyifempty
Root: HKCU; Subkey: "Software\PlaatSoft\RedSquare"; ValueName: "username"; ValueData: {username}; ValueType: string;  Flags: uninsdeletekeyifempty

