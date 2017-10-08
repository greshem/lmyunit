//--------------------------------------------------------------------------------------------------------------------------------
#include "mexcelfile.h"
//--------------------------------------------------------------------------------------------------------------------------------
#ifdef WINDOWSPROGRAMS
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MExcelFile,MFile)

END_LMYUNIT
//..............................................................................................................................
MExcelFile::MExcelFile(void)
{

}
//..............................................................................................................................
MExcelFile::~MExcelFile()
{

}
//..............................................................................................................................
int  MExcelFile::CreateFile(MString FileName)
{
	tagExcelBof							bofinfo;
	register int						errorcode;

	if ( (errorcode = MFile::Create(FileName)) < 0 )
	{
		return(errorcode);
	}

	bofinfo.OptionCode = 0x09;
	bofinfo.Length = 4;
	bofinfo.Type = 0x02;
	bofinfo.Version = 0x10;

	if ( (errorcode = MFile::Write((char *)&bofinfo,sizeof(tagExcelBof))) < 0 )
	{
		MFile::Close();
		return(errorcode);
	}

	return(1);
}
//..............................................................................................................................
void MExcelFile::CloseFile(void)
{
	tagExcelEof							eofinfo;

	eofinfo.OptionCode = 0x0A;
	eofinfo.Length = 0x00;
	
	MFile::Write((char *)&eofinfo,sizeof(tagExcelEof));

	MFile::Close();
}
//..............................................................................................................................
int  MExcelFile::SetDefaultHeight(unsigned short Height)
{
	tagExcelDefaultHeight				defaultheight;
	register int						errorcode;

	defaultheight.OptionCode = 0x25;
	defaultheight.Length = 2;
	defaultheight.Height = Height * 20;

	if ( (errorcode = MFile::Write((char *)&defaultheight,sizeof(tagExcelDefaultHeight))) < 0 )
	{
		return(errorcode);
	}

	return(1);
}
//..............................................................................................................................
int  MExcelFile::SetColumnWidth(unsigned char FirstColumn,unsigned char LastColumn,unsigned char Width)
{
	tagExcelColumnWidth					widthinfo;
	register int						errorcode;

	widthinfo.OptionCode = 0x24;
	widthinfo.Length = 4;				
	widthinfo.FirstColumn = FirstColumn;
	widthinfo.LastColumn = LastColumn;
	widthinfo.Width = (unsigned short)Width * 256;

	if ( (errorcode = MFile::Write((char *)&widthinfo,sizeof(tagExcelColumnWidth))) < 0 )
	{
		return(errorcode);
	}

	return(1);
}
//..............................................................................................................................
int  MExcelFile::SetFont(unsigned short FontHeight,unsigned short FontAttr,MString FontName)
{
	tagExcelFont						fontinfo;
	register int						errorcode;
	
	fontinfo.OptionCode = 0x31;
	
	fontinfo.FontHeight = FontHeight * 20;
	fontinfo.FontAttr = FontAttr;
	strncpy(fontinfo.FontName,FontName.c_str(),256);
	fontinfo.FontNameLength  = strlen(fontinfo.FontName);
	fontinfo.Length = 5 + strlen(fontinfo.FontName);

	if ( (errorcode = MFile::Write((char *)&fontinfo,fontinfo.Length + 4)) < 0 )
	{
		return(errorcode);
	}

	return(1);
}
//..............................................................................................................................
int  MExcelFile::WriteInteger(unsigned short Row,unsigned short Column,unsigned short Value,unsigned long CellAttr)
{
	tagExcelInteger						integerinfo;
	register int						errorcode;

	integerinfo.OptionCode = 0x02;
	integerinfo.Length = 9;
	integerinfo.Row = Row;
	integerinfo.Column = Column;

	memset((char *)&integerinfo.CellAttr,0,sizeof(tagExcelCellAttr));
	integerinfo.CellAttr.Hidden = ((CellAttr & EXCELCELL_HIDDEN) == 0)?0:1;
    integerinfo.CellAttr.Locked = ((CellAttr & EXCELCELL_LOCKED) == 0)?0:1;
    integerinfo.CellAttr.Font_Num  = (CellAttr & 0x0000000C) >> 2;
    integerinfo.CellAttr.Shaded = ((CellAttr & EXCELCELL_SHADED) == 0)?0:1;
    integerinfo.CellAttr.Bottom_Border = ((CellAttr & EXCELCELL_BOTTOMLINE) == 0)?0:1;
    integerinfo.CellAttr.Top_Border = ((CellAttr & EXCELCELL_TOPLINE) == 0)?0:1;
    integerinfo.CellAttr.Right_Border = ((CellAttr & EXCELCELL_RIGHTLINE) == 0)?0:1;
    integerinfo.CellAttr.Left_Border = ((CellAttr & EXCELCELL_LEFTLINE) == 0)?0:1;
    integerinfo.CellAttr.Align_Code = (CellAttr & 0x00000600) >> 9;

	integerinfo.Value = Value;

	if ( (errorcode = MFile::Write((char *)&integerinfo,sizeof(tagExcelInteger))) < 0 )
	{
		return(errorcode);
	}

	return(1);
}
//..............................................................................................................................
int  MExcelFile::WriteFloat(unsigned short Row,unsigned short Column,float Value,unsigned long CellAttr)
{
	tagExcelFloat							floatinfo;
	register int							errorcode;

	floatinfo.OptionCode = 0x03;
	floatinfo.Length = 15;
	floatinfo.Row = Row;
	floatinfo.Column = Column;

	memset((char *)&floatinfo.CellAttr,0,sizeof(tagExcelCellAttr));
	floatinfo.CellAttr.Hidden = ((CellAttr & EXCELCELL_HIDDEN) == 0)?0:1;
    floatinfo.CellAttr.Locked = ((CellAttr & EXCELCELL_LOCKED) == 0)?0:1;
    floatinfo.CellAttr.Font_Num  = (CellAttr & 0x0000000C) >> 2;
    floatinfo.CellAttr.Shaded = ((CellAttr & EXCELCELL_SHADED) == 0)?0:1;
    floatinfo.CellAttr.Bottom_Border = ((CellAttr & EXCELCELL_BOTTOMLINE) == 0)?0:1;
    floatinfo.CellAttr.Top_Border = ((CellAttr & EXCELCELL_TOPLINE) == 0)?0:1;
    floatinfo.CellAttr.Right_Border = ((CellAttr & EXCELCELL_RIGHTLINE) == 0)?0:1;
    floatinfo.CellAttr.Left_Border = ((CellAttr & EXCELCELL_LEFTLINE) == 0)?0:1;
    floatinfo.CellAttr.Align_Code = (CellAttr & 0x00000600) >> 9;

	floatinfo.Value = Value;

	if ( (errorcode = MFile::Write((char *)&floatinfo,sizeof(tagExcelFloat))) < 0 )
	{
		return(errorcode);
	}

	return(1);
}
//..............................................................................................................................
int  MExcelFile::WriteString(unsigned short Row,unsigned short Column,MString Value,unsigned long CellAttr)
{
	tagExcelConstString						stringinfo;
	register int							errorcode;

	stringinfo.OptionCode = 0x04;
	strncpy(stringinfo.Value,Value.c_str(),256);
	stringinfo.StringLength = strlen(stringinfo.Value);
	stringinfo.Length = stringinfo.StringLength + 8;
	stringinfo.Row = Row;
	stringinfo.Column = Column;

	memset((char *)&stringinfo.CellAttr,0,sizeof(tagExcelCellAttr));
	stringinfo.CellAttr.Hidden = ((CellAttr & EXCELCELL_HIDDEN) == 0)?0:1;
    stringinfo.CellAttr.Locked = ((CellAttr & EXCELCELL_LOCKED) == 0)?0:1;
    stringinfo.CellAttr.Font_Num  = (CellAttr & 0x0000000C) >> 2;
    stringinfo.CellAttr.Shaded = ((CellAttr & EXCELCELL_SHADED) == 0)?0:1;
    stringinfo.CellAttr.Bottom_Border = ((CellAttr & EXCELCELL_BOTTOMLINE) == 0)?0:1;
    stringinfo.CellAttr.Top_Border = ((CellAttr & EXCELCELL_TOPLINE) == 0)?0:1;
    stringinfo.CellAttr.Right_Border = ((CellAttr & EXCELCELL_RIGHTLINE) == 0)?0:1;
    stringinfo.CellAttr.Left_Border = ((CellAttr & EXCELCELL_LEFTLINE) == 0)?0:1;
    stringinfo.CellAttr.Align_Code = (CellAttr & 0x00000600) >> 9;

	if ( (errorcode = MFile::Write((char *)&stringinfo,stringinfo.Length + 4)) < 0 )
	{
		return(errorcode);
	}
	return(1);
}
//..............................................................................................................................
int  MExcelFile::WriteBool(unsigned short Row,unsigned short Column,bool Value,unsigned long CellAttr)
{
	tagExcelBool							boolinfo;
	register int							errorcode;

	boolinfo.OptionCode = 0x05;
	boolinfo.Length = 9;
	boolinfo.Row = Row;
	boolinfo.Column = Column;

	memset((char *)&boolinfo.CellAttr,0,sizeof(tagExcelCellAttr));
	boolinfo.CellAttr.Hidden = ((CellAttr & EXCELCELL_HIDDEN) == 0)?0:1;
    boolinfo.CellAttr.Locked = ((CellAttr & EXCELCELL_LOCKED) == 0)?0:1;
    boolinfo.CellAttr.Font_Num  = (CellAttr & 0x0000000C) >> 2;
    boolinfo.CellAttr.Shaded = ((CellAttr & EXCELCELL_SHADED) == 0)?0:1;
    boolinfo.CellAttr.Bottom_Border = ((CellAttr & EXCELCELL_BOTTOMLINE) == 0)?0:1;
    boolinfo.CellAttr.Top_Border = ((CellAttr & EXCELCELL_TOPLINE) == 0)?0:1;
    boolinfo.CellAttr.Right_Border = ((CellAttr & EXCELCELL_RIGHTLINE) == 0)?0:1;
    boolinfo.CellAttr.Left_Border = ((CellAttr & EXCELCELL_LEFTLINE) == 0)?0:1;
    boolinfo.CellAttr.Align_Code = (CellAttr & 0x00000600) >> 9;

	boolinfo.Value = Value;

	if ( (errorcode = MFile::Write((char *)&boolinfo,sizeof(tagExcelBool))) < 0 )
	{
		return(errorcode);
	}
	return(1);
}
//--------------------------------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------------------------------
