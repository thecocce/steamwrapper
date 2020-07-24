program SteamWrapperTest;

uses
  Vcl.Forms,
  Unit1 in 'Unit1.pas' {Form1},
  SteamworksClasses in '..\..\includes\SteamworksClasses.pas',
  SteamworksTypes in '..\..\includes\SteamworksTypes.pas',
  Steamworks in '..\..\includes\Steamworks.pas';

{$R *.res}

begin
  ReportMemoryLeaksOnShutdown  := DebugHook <> 0;
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
