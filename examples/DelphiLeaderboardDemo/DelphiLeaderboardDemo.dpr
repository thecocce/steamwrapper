//----------------------------------------------------
// © 2015 Andrey Volia
// 
// License: MIT
// Site: https://github.com/voliaandrey/steamwrapper
//----------------------------------------------------
program DelphiLeaderboardDemo;

uses
  Forms,
  uMainForm in 'uMainForm.pas' {Form2},
  Steamworks in '..\..\includes\Steamworks.pas',
  SteamworksClasses in '..\..\includes\SteamworksClasses.pas',
  SteamworksTypes in '..\..\includes\SteamworksTypes.pas';

{,
  SteamworksTypes in 'SteamworksTypes.pas',
  Steamworks in 'Steamworks.pas';}

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm2, Form2);
  Application.Run;
end.
