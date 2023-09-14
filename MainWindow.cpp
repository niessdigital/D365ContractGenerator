//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <string>
#include "clplib.h"
#include <cstdlib>
#include <cwchar>
#include "defval.h"
#include "MainWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainWin *MainWin;
//---------------------------------------------------------------------------
__fastcall TMainWin::TMainWin(TComponent* Owner)
        : TForm(Owner)
{
}
char* wchar_to_char(const wchar_t* wstr) {
        // Get the required buffer size
        size_t bufferSize = wcstombs(NULL, wstr, 0) + 1;

        // Allocate the buffer
        char* buffer = new char[bufferSize];

        // Perform the conversion
        wcstombs(buffer, wstr, bufferSize);

        return buffer;
}
//---------------------------------------------------------------------------
bool checkdupl(TListBox*List)
{
        std::string strList="";
        for(int i = 0; i < List->Items->Count;i++)
        {                     
				if (strList.find(wchar_to_char(List->Items->Strings[i].c_str()))!=-1) {
						strList+=wchar_to_char(List->Items->Strings[i].c_str());
                        strList+="\n";
                }
                else {
                        return false;
                }
        }
        return true;
}
void __fastcall TMainWin::NewDataMemberKeyPress(TObject *Sender, char &Key)
{
if (Key == VK_RETURN && NewDataMember->Text!="")
{                              
        Members->AddItem(NewDataMember->Text,0);
		MemberType->AddItem(NewMemberDataTypes->Text,0);
				defval->AddItem("",0);
		NewDataMember->Text="";
}
}
//---------------------------------------------------------------------------

void __fastcall TMainWin::Button1Click(TObject *Sender)
{

		defval->Items->Delete(Members->ItemIndex);
        MemberType->Items->Delete(Members->ItemIndex);
		Members->Items->Delete(Members->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TMainWin::MembersClick(TObject *Sender)
{
MemberType->ItemIndex = Members->ItemIndex;
defval->ItemIndex = Members->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TMainWin::MemberTypeClick(TObject *Sender)
{
Members->ItemIndex = MemberType->ItemIndex;
defval->ItemIndex = Members->ItemIndex;
}
//---------------------------------------------------------------------------
std::string str(const char*s){
 return s;
}
std::string generateCode(TListBox*mem, TListBox*memtypes, std::string classtype, std::string classname, TListBox*defval){
        std::string code = "// Code generated with ContractBuilder by NIESS DIGITAL\n\n/// <summary>\n/// Data contract "+classname+"\n/// </summary>\n\n";
        std::string vardef;
        std::string parms;
        if(classtype == "Custom Service Contract") {
                code += "[DataContractAttribute]\nclass "+classname+ "\n{\n";
        }
        if(classtype == "Business Event Contract") {
                code += "[DataContract]\npublic final class "+classname+ " extends businesseventscontract\n{\n";
        }
		for(int i = 0; i < mem->Items->Count;i++){
				parms += "\t/// <summary>\n\t/// "+str(wchar_to_char(mem->Items->Strings[i].c_str()))+"\n\t/// </summary>\n\t/// <param name = \"_"+str(wchar_to_char(mem->Items->Strings[i].c_str()))+"\">"+str(wchar_to_char(mem->Items->Strings[i].c_str()))+"</param>\n\t/// <returns>"+str(wchar_to_char(mem->Items->Strings[i].c_str()))+"</returns>\n";
                if(classtype == "Custom Service Contract") {
						parms+="\t[DataMember(\""+ str(wchar_to_char(mem->Items->Strings[i].c_str())) + "\")]\n";
                }
                if(classtype == "Business Event Contract") {
						parms+="\t[DataMember(\""+ str(wchar_to_char(mem->Items->Strings[i].c_str())) + "\"), BusinessEventsDataMember(\""+ str(wchar_to_char(mem->Items->Strings[i].c_str())) + "\")]\n";
				}
				std::string defaultval = "";
				if(defval->Items->Strings[i]!="")
					defaultval = " = "+str(wchar_to_char(defval->Items->Strings[i].c_str()));
				vardef+="\t"+str(wchar_to_char(memtypes->Items->Strings[i].c_str()))+" "+str(wchar_to_char(mem->Items->Strings[i].c_str()))+defaultval+";\n";
				parms+="\t"+str(wchar_to_char(memtypes->Items->Strings[i].c_str()))+" parm"+str(wchar_to_char(mem->Items->Strings[i].c_str()))+"("+str(wchar_to_char(memtypes->Items->Strings[i].c_str()))+" _"+str(wchar_to_char(mem->Items->Strings[i].c_str()))+" = " + str(wchar_to_char(mem->Items->Strings[i].c_str()))+")\n\t{\n\t\t"+
						str(wchar_to_char(mem->Items->Strings[i].c_str()))+" = _"+str(wchar_to_char(mem->Items->Strings[i].c_str()))+";\n\t\treturn "+str(wchar_to_char(mem->Items->Strings[i].c_str()))+";\n\t}\n";
		}
		code += vardef + "\n\n" + parms+"\n}";
		return code;
}
void __fastcall TMainWin::Button2Click(TObject *Sender)
{
std::string code = generateCode(Members, MemberType, wchar_to_char(ClassType->Text.c_str()), wchar_to_char(ClassName->Text.c_str()),defval).c_str();
std::string msgboxcode = code;
if(msgboxcode.length()>400)msgboxcode = msgboxcode.substr(0, 400)+" ...";
MessageBox(this->Handle, (str("Der Code wurde in die Zwischenablage kopiert.\n\n")+msgboxcode).c_str(), "Erfolg", 0);
SetClipboardText(code);
}
//---------------------------------------------------------------------------
void __fastcall TMainWin::ClassTypeChange(TObject *Sender)
{
Button2->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TMainWin::NewMemberDataTypesKeyPress(TObject *Sender,
      char &Key)
{
if (Key == VK_RETURN && NewDataMember->Text!="")
{
                Members->AddItem(NewDataMember->Text,0);
				MemberType->AddItem(NewMemberDataTypes->Text,0);
				defval->AddItem("",0);
				NewDataMember->Text="";

}            
}
//---------------------------------------------------------------------------


void __fastcall TMainWin::defvalDblClick(TObject *Sender)
{
TGetVal*v = new TGetVal(this);
v->ShowModal();
defval->Items->Strings[defval->ItemIndex] = v->v.c_str();
delete v;
}
//---------------------------------------------------------------------------


void __fastcall TMainWin::defvalClick(TObject *Sender)
{

Members->ItemIndex = defval->ItemIndex;
MemberType->ItemIndex = defval->ItemIndex;
}
//---------------------------------------------------------------------------

