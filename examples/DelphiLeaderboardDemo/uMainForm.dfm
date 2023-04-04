object Form2: TForm2
  Left = 343
  Top = 140
  Caption = '[ASTRON3D Steamworks Wrapper] Various features demo'
  ClientHeight = 399
  ClientWidth = 741
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Position = poScreenCenter
  OnCreate = FormCreate
  TextHeight = 13
  object Label1: TLabel
    Left = 192
    Top = 178
    Width = 30
    Height = 13
    Caption = 'score:'
  end
  object Memo1: TMemo
    Left = 0
    Top = 210
    Width = 741
    Height = 189
    Align = alBottom
    ScrollBars = ssVertical
    TabOrder = 5
    ExplicitWidth = 684
  end
  object Button11: TButton
    Left = 8
    Top = 8
    Width = 142
    Height = 25
    Caption = 'Get user status and ID'
    TabOrder = 0
    OnClick = Button11Click
  end
  object Button12: TButton
    Left = 8
    Top = 88
    Width = 177
    Height = 25
    Caption = 'FindOrCreateLeaderboard'
    TabOrder = 1
    OnClick = Button12Click
  end
  object Button17: TButton
    Left = 8
    Top = 128
    Width = 177
    Height = 25
    Caption = 'UploadLeaderboardScore'
    TabOrder = 2
    OnClick = Button17Click
  end
  object Button18: TButton
    Left = 8
    Top = 168
    Width = 177
    Height = 25
    Caption = 'DownloadLeaderboardScore'
    TabOrder = 3
    OnClick = Button18Click
  end
  object Edit1: TEdit
    Left = 232
    Top = 170
    Width = 153
    Height = 21
    TabOrder = 4
    Text = '100'
  end
  object Button1: TButton
    Left = 440
    Top = 8
    Width = 142
    Height = 25
    Caption = 'Get Steam User Auth Token'
    TabOrder = 6
    OnClick = Button1Click
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 30
    OnTimer = Timer1Timer
    Left = 168
    Top = 8
  end
end
