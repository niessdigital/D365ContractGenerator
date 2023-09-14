//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DefVal.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TGetVal *GetVal;
//--------------------------------------------------------------------- 
__fastcall TGetVal::TGetVal(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------

void __fastcall TGetVal::FormClose(TObject *Sender, TCloseAction &Action)
{
Action = caHide;
}
//---------------------------------------------------------------------------

char* wchar_to_charx(const wchar_t* wstr) {
        // Get the required buffer size
        size_t bufferSize = wcstombs(NULL, wstr, 0) + 1;

        // Allocate the buffer
        char* buffer = new char[bufferSize];

        // Perform the conversion
        wcstombs(buffer, wstr, bufferSize);

        return buffer;
}
void __fastcall TGetVal::OKBtnClick(TObject *Sender)
{
v = wchar_to_charx(this->Edit1->Text.c_str());
this->Close();
}
//---------------------------------------------------------------------------

