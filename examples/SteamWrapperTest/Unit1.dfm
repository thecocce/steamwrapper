object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 406
  ClientWidth = 682
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  DesignSize = (
    682
    406)
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 8
    Top = 8
    Width = 193
    Height = 65
    Caption = 'Test CreateItemResult'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 216
    Top = 8
    Width = 185
    Height = 65
    Caption = 'Test QueryUGC'
    TabOrder = 1
    OnClick = Button2Click
  end
  object mm: TMemo
    Left = 8
    Top = 88
    Width = 666
    Height = 310
    Anchors = [akLeft, akTop, akRight, akBottom]
    TabOrder = 2
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 30
    OnTimer = Timer1Timer
    Left = 536
    Top = 8
  end
end
