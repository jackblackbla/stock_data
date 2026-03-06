#ifndef MyAppVersion
  #define MyAppVersion "1.0.0"
#endif

#define MyAppName "NH 매매일지 자동화"
#define MyAppPublisher "NH Trade Logger"
#define MyAppExeName "nh-trade-logger.exe"
#define MyAppDirName "NHTradeLogger"

[Setup]
AppId={{D85C0E54-53FA-4C0A-8C3B-FC923E97C7AB}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}
DefaultDirName={localappdata}\Programs\{#MyAppDirName}
DefaultGroupName={#MyAppName}
DisableProgramGroupPage=yes
PrivilegesRequired=lowest
PrivilegesRequiredOverridesAllowed=dialog
ArchitecturesAllowed=x86compatible
Compression=lzma2
SolidCompression=yes
WizardStyle=modern
OutputDir=..\dist\installer
OutputBaseFilename=nh-trade-logger-setup-{#MyAppVersion}
UninstallDisplayIcon={app}\{#MyAppExeName}
InfoBeforeFile=PREREQUISITES.txt
UsedUserAreasWarning=no

[Languages]
Name: "korean"; MessagesFile: "compiler:Languages\Korean.isl"

[Tasks]
Name: "desktopicon"; Description: "바탕화면 바로가기 만들기"; Flags: unchecked

[Files]
Source: "..\dist\x86\nh-trade-logger\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

[Dirs]
Name: "{localappdata}\NHTradeLogger"
Name: "{localappdata}\NHTradeLogger\data"
Name: "{localappdata}\NHTradeLogger\data\json"
Name: "{localappdata}\NHTradeLogger\data\output"
Name: "{localappdata}\NHTradeLogger\logs"

[Icons]
Name: "{autoprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon
Name: "{autoprograms}\{#MyAppName} 사용자 안내"; Filename: "{app}\USER_GUIDE.txt"

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "설치 후 NH 매매일지 자동화 실행"; Flags: nowait postinstall skipifsilent
