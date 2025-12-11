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
; jei nenaudoji ikonų, šias dvi palik kaip yra arba ištrink
; SetupIconFile=icons\app.ico
; WizardSmallImageFile=icons\wizard.bmp

[Languages]
Name: "lt"; MessagesFile: "compiler:Languages\Lithuanian.isl"

[Files]
Source: "..\build\bin\vu_student_app.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\build\bin\grades.dll";        DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\Kornelija-Dambrauskaite"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\Pašalinti {#MyAppName}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\Kornelija-Dambrauskaite"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon
; Meninis medis: Start menu: VU -> Kornelija-Dambrauskaite (DefaultGroupName tai užtikrina)

[Tasks]
Name: "desktopicon"; Description: "Sukurti nuorodą darbalaukyje"; GroupDescription: "Nuorodos:"

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "Paleisti programą"; Flags: nowait postinstall skipifsilent


