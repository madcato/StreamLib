// PruPrintTemplate.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

DOCINFO docInfo;
PRINTDLG printDlg;

void initPrint()
{
	
   ZeroMemory(&docInfo, sizeof(docInfo));
   docInfo.cbSize = sizeof(docInfo);
   docInfo.lpszDocName = "GdiplusPrint";

   
   ZeroMemory(&printDlg, sizeof(printDlg));
   printDlg.lStructSize = sizeof(printDlg);
   printDlg.Flags = PD_RETURNDC;
   
   // Display a print dialog box.
   if(!PrintDlg(&printDlg))
   {
     // CQQPH Throws an exception
   }
   else
   {
		StartDoc(printDlg.hDC, &docInfo);
		StartPage(printDlg.hDC);  

   }
}

void endPrint()
{

	EndPage(printDlg.hDC);
	EndDoc(printDlg.hDC); 
   
   if(printDlg.hDevMode) 
      GlobalFree(printDlg.hDevMode);
   if(printDlg.hDevNames) 
      GlobalFree(printDlg.hDevNames);
   if(printDlg.hDC)
      DeleteDC(printDlg.hDC);
}

int main(int argc, char* argv[])
{
	try
	{
		util::PersistentProperties properties;

		properties.load(std::auto_ptr<io::IInputStream>(new io::FileInputStream("print.tmpl")));


		ulong etiPointerX = (ulong)sstring(properties["ini.x"]);
		ulong etiPointerY = (ulong)sstring(properties["ini.y"]);

		ulong columns = (ulong)sstring(properties["columns"]);
		ulong rows = (ulong)sstring(properties["rows"]);

		initPrint();
		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	
		CodeBar code;
		std::string str = "8850300604000022";
		vector<string> codebar = code.generate(str,CodeBar::TypeB);


		ulong anchoUnidad = (ulong)sstring(properties["CodeBar.unit"]);

		ulong altura = (ulong)sstring(properties["CodeBar.height"]);


		for(ulong row = 0 ; row < rows ; row++)
		{
			for(ulong column = 0 ; column < columns ; column++)
			{
				bool black = false;
				ulong pointerX = etiPointerX + (ulong)sstring(properties["CodeBar.x"]);
				ulong pointerY = etiPointerY + (ulong)sstring(properties["CodeBar.y"]);

				for(int i = 0 ; i < codebar.size() ; i++)
				{

					string str = codebar[i];
					for(int s = 0 ; s < str.length() ; s++)
					{
						if(black)
						{
							int c = str[s];
							FillRgn(printDlg.hDC,CreateRectRgn(pointerX, pointerY,  pointerX+ c * anchoUnidad, pointerY +altura),brush);
							pointerX += c * anchoUnidad;
							black = false;
						}
						else
						{
							int c = str[s];
							pointerX += c * anchoUnidad;
							black = true;
						}
					}
				}

				// Y ahora el texto
				pointerX = etiPointerX + (ulong)sstring(properties["Text.x"]);
				pointerY = etiPointerY + (ulong)sstring(properties["Text.y"]);

				TextOut(printDlg.hDC,pointerX,pointerY,str.c_str(),str.length());
				
				etiPointerX += (ulong)sstring(properties["eti.width"]) + (ulong)sstring(properties["inter.x"]);
			}
			etiPointerX = (ulong)sstring(properties["ini.x"]);
			etiPointerY += (ulong)sstring(properties["eti.height"]) + (ulong)sstring(properties["inter.y"]) ;

		}

		endPrint();
	}catch(exception* e)
	{
		console << e->what();
	}
	return 0;
}
