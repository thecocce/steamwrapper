//----------------------------------------------------
// © 2015 Andrey Volia
// © 2017 TheCocce
//
// License: MIT
// Site: https://github.com/thecocce/steamwrapper
//----------------------------------------------------
unit uMainForm;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Steamworks, SteamworksTypes, StdCtrls, ExtCtrls, ComCtrls, Grids,
  ValEdit;

type
  TForm2 = class(TForm)
    Memo1: TMemo;
    Timer1: TTimer;
    Button11: TButton;
    Button12: TButton;
    Button17: TButton;
    Button18: TButton;
    Label1: TLabel;
    Edit1: TEdit;
    Button1: TButton;
    procedure FormCreate(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure Button11Click(Sender: TObject);
    procedure Button12Click(Sender: TObject);
    procedure Button17Click(Sender: TObject);
    procedure Button18Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
  private

    function GetSteamUserAuthToken: string;
  public
  end;

// TByteArr = array of Byte;

var
  Form2: TForm2;
  SteamCallbacks: TSteamCallbacks;
  r: TSteamAPICall;
  CurrentLeaderboard: uint64;
  FIsSteamWaiting:Boolean;

implementation

{$R *.dfm}

procedure Log(s: string);
begin
  Form2.Memo1.Lines.Add(s);
end;

procedure OnGetAuthSessionTicketResponse(AuthTicket: uint32; eResult: integer); cdecl;
begin
  FIsSteamWaiting := False;
  Log( 'OnGetAuthSessionTicketResponse - AuthTicket: ' + AuthTicket.ToString + '  - Result:'+ eResult.ToString);
end;

procedure WarnHook(a: integer; b: pAnsiChar); cdecl;
begin
  if a = 0 then
    Form2.Memo1.Lines.Add('[Info] ' + b)
  else
    Form2.Memo1.Lines.Add('[Warn] ' + b);
end;

procedure TForm2.Button11Click(Sender: TObject);
var
  sID, x: TSteamID;
  name:PAnsiChar;
begin
  SteamUser_GetSteamID(sID);

  if SteamUser_IsLoggedOn then
    Log('SteamUser: is logged on')
  else
    Log('SteamUser: is not logged on');

  Log('SteamUser: steamID-> ' + inttostr(sID.GetAccountID)); //Data = AccountId
  name := SteamFriends_GetFriendPersonaName(sID);
  Log('SteamFriends_GetFriendPersonaName -> ' + name);
  Log('SteamUser: steam level-> ' + inttostr(SteamUser_GetPlayerSteamLevel));
end;

procedure TForm2.Timer1Timer(Sender: TObject);
begin
  System_RunCallbacks;
end;

procedure OnLeaderboardFindResult(SteamLeaderboard: uint64; LeaderboardFod: uint8); cdecl;
begin
  Log('Callback: OnLeaderboardFindResult ' + inttostr(LeaderboardFod));

  if LeaderboardFod = 1 then
    CurrentLeaderboard := SteamLeaderboard;
end;

procedure OnLeaderboardScoreUploaded(Success: uint8; SteamLeaderboard: uint64; Score: int32; ScoreChanged: uint8; GlobalRankNew: integer; GlobalRankPrevious: integer); cdecl;
begin
 //not work - must be fixed callback
  Log('Callback: OnLeaderboardScoreUploaded; GlobalRankNew=' + inttostr(GlobalRankNew) + '  GlobalRankPrevious=' + inttostr(GlobalRankPrevious));
end;

procedure OnLeaderboardScoreDownloaded(SteamLeaderboard: uint64; SteamLeaderboardEntries: uint64; EntryCount: integer); cdecl;
var
  i: integer;
  LeaderboardEntry: TLeaderboardEntry;
begin
 //not work - must be fixed callback

  Log('Callback: OnLeaderboardScoresDownloaded; EntryCount=' + inttostr(EntryCount));

 //parse entry (!!!must be tested!!!)
  if EntryCount > 0 then
    for i := 0 to EntryCount - 1 do
      if SteamUserStats_GetDownloadedLeaderboardEntry(SteamLeaderboardEntries, i{index}, @LeaderboardEntry, 0, 0) then
      begin
        //show entry
        Log(inttostr(LeaderboardEntry.GlobalRank) + '. ' + SteamFriends_GetFriendPersonaName(LeaderboardEntry.steamIDUser) + ' score: ' + inttostr(LeaderboardEntry.Score));
      end;

end;

procedure TForm2.FormCreate(Sender: TObject);
begin
  CurrentLeaderboard := 0;

  if not (System_InitWrapper) then
  begin
    Showmessage('Steam wrapper init error. Please check your steam client and/or steam_appid.txt');
    Halt;
  end;

  SteamUtils_SetWarningMessageHook(WarnHook);

  SteamCallbacks.OnLeaderboardFindResult := OnLeaderboardFindResult;
  SteamCallbacks.OnLeaderboardScoreUploaded := OnLeaderboardScoreUploaded;
  SteamCallbacks.OnLeaderboardScoresDownloaded := OnLeaderboardScoreDownloaded;

  SteamCallbacks.OnGetAuthSessionTicketResponse := OnGetAuthSessionTicketResponse;


  System_RegisterCallbacks(SteamCallbacks);

  Timer1.Enabled := true;
end;

procedure TForm2.Button12Click(Sender: TObject);
var
  myString: AnsiString;
  myCharPtr: PAnsiChar;
  //r: TSteamAPICall;
begin

  myString := 's';
  myCharPtr := Addr(myString[1]);

  SteamUserStats_FindOrCreateLeaderboard(myCharPtr, k_ELeaderboardSortMethodAscending, k_ELeaderboardDisplayTypeNumeric);

  Log('Connecting Leaderboard...');
end;

procedure TForm2.Button17Click(Sender: TObject);
var
  score: integer;
begin
  if CurrentLeaderboard <> 0 then
  begin

    score := strtoint(edit1.text); //

    SteamUserStats_UploadLeaderboardScore(CurrentLeaderboard, {k_ELeaderboardUploadScoreMethodKeepBest}k_ELeaderboardUploadScoreMethodForceUpdate, score, 0, 0);

    Log('Uploading score...');

  end
  else
    showmessage('Use FindOrCreateLeaderboard first!');
end;

procedure TForm2.Button18Click(Sender: TObject);
begin
  if CurrentLeaderboard <> 0 then
  begin

    SteamUserStats_DownloadLeaderboardEntries(CurrentLeaderboard, k_ELeaderboardDataRequestGlobal, 0, 100); //0-100 entries

    Log('Downloading leaderboard...');

  end
  else
    showmessage('Use FindOrCreateLeaderboard first!');
end;

procedure TForm2.Button1Click(Sender: TObject);
begin
 GetSteamUserAuthToken();
end;

function EncodeBase16(const Data : TBytes) : string;
var
  Text : PWideChar;
begin
  SetLength(Result, Length(Data) * 2);
  Text := @Result[1];
  BinToHex(Data, Text, Length(Data));
end;

function TForm2.GetSteamUserAuthToken: string;
var
  bufTicket : TBytes;
begin
  Log('GetSteamUserAuthToken...');
  result := '';

  // Steam must be connected and running etc.
  result := '';
  SetLength(bufTicket, 1024);
  var cTicketSize : uint32;
  var FSteamTicketHandle := SteamUser_GetAuthSessionTicket(@bufTicket[0], 1024, @cTicketSize);
  Log('FSteamTicketHandle: ' + FSteamTicketHandle.ToString);

  if FSteamTicketHandle <> k_HAuthTicketInvalid then begin
  
//    --> DISABLED BECAUSE IN THIS DEMO THE TIMER Timer1 IS ALIVE
//    var ct := 0;
//    while FIsSteamWaiting and (ct < 20) do
//    begin
//      System_RunCallbacks;
//      Inc(ct);
//      Sleep(10);
//    end;

    if not FIsSteamWaiting then
    begin
      setLength(bufTicket, cTicketSize);
      //Your mode - using IntToHex
      for var i := low(bufTicket) to high(bufTicket) do
         result := result + IntToHex(bufTicket[i], 2);
      Log('Result TOKEN mode 1: '#13#10+ result);

      //Using function - BinToHex
      var EncodedSteamTicket : string;
      EncodedSteamTicket := EncodeBase16(bufTicket);
      Log('Result TOKEN mode 2: '#13#10+ EncodedSteamTicket);
    end
  end;
end;

end.

