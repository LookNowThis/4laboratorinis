#define MyAppName "VU Kornelija-Dambrauskaite"
#define MyAppExeName "vu_student_app.exe"
#define MyAppPublisher "Vilniaus universitetas"
#define MyAppVersion "3.0.0"
#define MyDirName "VU\\Kornelija-Dambrauskaite"

[Setup]
AppId={{A4C8B0D0-1234-4E00-9C11-FAKE-UUID-000001}}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}
DefaultDirName={pf}\{#MyDirName}
DefaultGroupName=VU\Kornelija-Dambrauskaite
OutputDir=.
OutputBaseFilename=setup
ArchitecturesInstallIn64BitMode=x64
Compression=lzma
SolidCompression=yes
PrivilegesRequired=admin
DisableProgramGroupPage=yes
; Panaikinta: SetupIconFile=icons\app.ico

[Languages]
Name: "lt"; MessagesFile: "compiler:Languages\Lithuanian.isl"

[Files]
Source: "..\build\bin\vu_student_app.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\build\bin\grades.dll";        DestDir: "{app}"; Flags: ignoreversion
; Panaikinta: Source: "icons\app.ico"; DestDir: "{app}"

[Icons]
Name: "{group}\Kornelija-Dambrauskaite"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\Kornelija-Dambrauskaite"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Tasks]
Name: "desktopicon"; Description: "Sukurti nuorodą darbalaukyje"; GroupDescription: "Nuorodos:"

[Run]
; Jei reikia, galite paleisti priklausomybes (VC++ redist) prieš pirmą startą.

