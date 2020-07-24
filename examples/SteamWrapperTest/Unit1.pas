unit Unit1;

interface

uses
  Steamworks, SteamworksTypes,
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants,
  System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.ExtCtrls;

type
  TForm1 = class(TForm)
    Button1: TButton;
    Button2: TButton;
    mm: TMemo;
    Timer1: TTimer;
    procedure Timer1Timer(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure FormShow(Sender: TObject);
  private
    procedure InitAccountInfo;
  public
  end;

var
  Form1: TForm1;
  SteamCallbacks: TSteamCallbacks;
procedure Log(s: string);
procedure WarnHook(a: integer; b: pAnsiChar); cdecl;
procedure OnCreateItemResult(eResult: TResult; PublishedFileId: uint64;
  bUserNeedsToAcceptWorkshopLegalAgreement: boolean); cdecl;

implementation

{$R *.dfm}

procedure OnCreateItemResult(eResult: TResult; PublishedFileId: uint64;
  bUserNeedsToAcceptWorkshopLegalAgreement: boolean); cdecl;
begin
  Log('Callback: OnCreateItemResult!!!');
end;

procedure OnSteamUGCQueryCompleted(Handle: uint64; eResult: TResult;
  NumResultsReturned, TotalMatchingResults: uint32; CachedData: boolean); cdecl;
begin
  Log('Callback: QueryCompleted  handle=' + Handle.ToString);
end;

procedure OnSteamUGCRequestUGCDetailsResult(Details: TSteamUGCDetails;
  CachedData: boolean); cdecl;
begin
  Log('Callback: UGCDetailsResult  handle=' + Details.result.ToString);
end;

procedure TForm1.Button1Click(Sender: TObject);
var
  hd: uint64;
begin
  hd := SteamUGC_CreateItem(SteamUtils_GetAppID, 0);
  Log('Begin Test CreateItem and Waiting for CallBack ... ' + hd.ToString);
end;

procedure TForm1.Button2Click(Sender: TObject);
var
  hd: uint64;
  ret: integer;
begin
  hd := SteamUGC_CreateQueryAllUGCRequest(1, 0, SteamUtils_GetAppID,
    SteamUtils_GetAppID, 1);
  ret := SteamUGC_SendQueryUGCRequest(hd);
  Log('Begin Test Send UGC Query ... hd=' + hd.ToString + '   ret=' +
    ret.ToString);

  SteamUGC_RequestUGCDetails(1, 1);
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
  try
    if not(System_InitWrapper) then
    begin
      Showmessage
        ('Steam wrapper init error. Please check your steam client and/or steam_appid.txt');
      Halt;
    end;

    SteamUtils_SetWarningMessageHook(WarnHook);

    SteamCallbacks.OnCreateItemResult := OnCreateItemResult;
    SteamCallbacks.OnSteamUGCQueryCompleted := OnSteamUGCQueryCompleted;
    SteamCallbacks.OnSteamUGCRequestUGCDetailsResult :=
      OnSteamUGCRequestUGCDetailsResult;

    System_RegisterCallbacks(SteamCallbacks);

    Timer1.Enabled := true;
  except
    on e: Exception do
    begin
        Beep;
    end;

  end;
end;

procedure TForm1.FormShow(Sender: TObject);
begin
  InitAccountInfo;
end;

procedure TForm1.InitAccountInfo;
var
  sID: TSteamID;
  val:uint64;
  at: TAccountType;
  univ: TUniverse;
  s: AnsiString;
begin
  SteamUser_GetSteamID(sID);

  if SteamUser_IsLoggedOn then
    Log('SteamUser: is logged on')
  else
    Log('SteamUser: is not logged on');
  Log('SteamUser: steamID-> ' + inttostr(sID.GetAccountID));
  Log('SteamUser: account instance-> ' + inttostr(sID.GetAccountInstance));

  at := sID.GetAccountType;
  univ := sID.GetUniverse;
  case univ of
    k_EUniverseInvalid:
      Log('SteamUser: Universe-> Invalid');
    k_EUniversePublic:
      Log('SteamUser: Universe-> Public');
    k_EUniverseBeta:
      Log('SteamUser: Universe-> Beta');
    k_EUniverseInternal:
      Log('SteamUser: Universe-> Internal');
    k_EUniverseDev:
      Log('SteamUser: Universe-> Dev');
    k_EUniverseMax:
      Log('SteamUser: Universe-> M');
  end;
  case at of
    k_EAccountTypeInvalid:
      Log('SteamUser: AccountTypeInvalid');
    k_EAccountTypeIndividual:
      Log('SteamUser: AccountTypeIndividual');
    k_EAccountTypeMultiseat:
      Log('SteamUser: AccountTypeMultiseat');
    k_EAccountTypeGameServer:
      Log('SteamUser: AccountTypeGameServer');
    k_EAccountTypeAnonGameServer:
      Log('SteamUser: AccountTypeAnonGameServer');
    k_EAccountTypePending:
      Log('SteamUser: AccountTypePending');
    k_EAccountTypeContentServer:
      Log('SteamUser: AccountTypeContentServer');
    k_EAccountTypeClan:
      Log('SteamUser: AccountTypeClan');
    k_EAccountTypeChat:
      Log('SteamUser: AccountTypeChat');
    k_EAccountTypeConsoleUser:
      Log('SteamUser: AccountTypeConsoleUser');
    k_EAccountTypeAnonUser:
      Log('SteamUser: AccountTypeAnonUser');
    k_EAccountTypeMax:
      Log('SteamUser: AccountTypeM');
  end;
  setlength(s, 128);
  SteamUser_GetUserDataFolder(@s[1], 128);

  Log('SteamUser: data folder-> ' + s);
  if SteamUser_IsBehindNAT then
    Log('SteamUser: is behind NAT ')
  else
    Log('SteamUser: is not behind NAT ');
  Log('SteamUser: steam level-> ' + inttostr(SteamUser_GetPlayerSteamLevel));

end;

procedure TForm1.Timer1Timer(Sender: TObject);
begin
  System_RunCallbacks;
end;

procedure Log(s: string);
begin
  Form1.mm.Lines.Add(s);
end;

procedure WarnHook(a: integer; b: pAnsiChar); cdecl;
begin
  if a = 0 then
    Log('[Info] ' + b)
  else
    Log('[Warn] ' + b);
end;

end.
