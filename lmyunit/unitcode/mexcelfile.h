//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
#ifndef __LmyUnitMExcelFileH__
#define __LmyUnitMExcelFileH__
//--------------------------------------------------------------------------------------------------------------------------------
#ifdef WINDOWSCODE
//--------------------------------------------------------------------------------------------------------------------------------
#include "mfile.h"
//--------------------------------------------------------------------------------------------------------------------------------
#pragma pack(1)
//--------------------------------------------------------------------------------------------------------------------------------
enum												//单元格属性
{
	EXCELCELL_HIDDEN = 0x00000001,					//隐藏标记
	EXCELCELL_LOCKED = 0x00000002,					//加锁标记
	EXCELCELL_FONT1 = 0x00000000,					//字体1号
	EXCELCELL_FONT2 = 0x00000004,					//字体2号
	EXCELCELL_FONT3 = 0x00000008,					//字体3号
	EXCELCELL_FONT4 = 0x0000000C,					//字体4号
	EXCELCELL_SHADED = 0x00000010,					//阴影标记
	EXCELCELL_BOTTOMLINE = 0x00000020,				//边框下线
	EXCELCELL_TOPLINE = 0x00000040,					//边框上线
	EXCELCELL_RIGHTLINE = 0x00000080,				//边框右线
	EXCELCELL_LEFTLINE = 0x00000100,				//边框左线
	EXCELCELL_NORMALALIGN = 0x00000000,				//普通对齐
	EXCELCELL_LEFTALIGN = 0x00000200,				//左对齐
	EXCELCELL_CENTERALIGN = 0x00000400,				//中对齐
	EXCELCELL_RIGHTALIGN = 0x00000600,				//右对齐
};
//................................................................................................................................
enum												//字体属性
{
	EXCELFONT_BOLD = 0x0100,						//粗体
	EXCELFONT_ITALIC = 0x0200,						//斜体
	EXCELFONT_UNDERLINE = 0x0400,					//下划线
	EXCELFONT_STRIKEOUT = 0x0800,					//删除线
};
//................................................................................................................................
typedef struct
{
	unsigned char				Hidden : 1;			//隐藏标记
    unsigned char				Locked : 1;			//加锁标记
    unsigned char				Reserved : 6;		//保留
    unsigned char				Font_Num : 2;		//字体标记
    unsigned char				Format_Code : 6;    //单元格式
    unsigned char				Shaded : 1;			//阴影标记
    unsigned char				Bottom_Border : 1;  //边框下线
    unsigned char				Top_Border : 1;		//边框上线
    unsigned char				Right_Border : 1;	//边框右线
    unsigned char				Left_Border : 1;	//边框左线
    unsigned char				Align_Code : 3;		//对齐方式
													//0x00 普通
													//0x01 左对齐
													//0x02 中对齐
													//0x03 右对齐
													//0x04 全填充
													//0x07 却省
} tagExcelCellAttr;
//................................................................................................................................
//文件开始时使用
typedef struct										//0x09
{
	unsigned short				OptionCode;			//操作码
	unsigned short				Length;				//纪录长度
	unsigned short				Version;			//版本
													//0x0500 BIFF7
													//0x0600 BIFF8
	unsigned short				Type;				//纪录类型
													//0x10 worksheet
													//0x20 chart
													//0x40 macro sheet
} tagExcelBof;
//................................................................................................................................
//文件结束时使用
typedef struct										//0x0A
{
	unsigned short				OptionCode;			//操作码
	unsigned short				Length;				//纪录长度
} tagExcelEof;
//................................................................................................................................
//表格区域
typedef struct										//0x00
{
	unsigned short				OptionCode;			//操作码
	unsigned short				Length;				//纪录长度
	unsigned short				FirstRow;			//起始行号
	unsigned short				LastRow;			//结束行号
	unsigned short				FirstColumn;		//起始列号
	unsigned short				LastColumn;			//结束列号
} tagExcelDimensions;
//................................................................................................................................
//空白区域
typedef struct										//0x01
{
	unsigned short				OptionCode;			//操作码
	unsigned short				Length;				//纪录长度
	unsigned short				Row;				//行
	unsigned short				Column;				//列
	tagExcelCellAttr			CellAttr;			//单元格属性
} tagExcelBlank;
//................................................................................................................................
//整型数据
typedef struct										//0x02
{
	unsigned short				OptionCode;			//操作码
	unsigned short				Length;				//纪录长度
	unsigned short				Row;				//行
	unsigned short				Column;				//列
	tagExcelCellAttr			CellAttr;			//单元格属性
	unsigned short				Value;				//值
} tagExcelInteger;
//................................................................................................................................
//浮点数据
typedef struct										//0x03
{
	unsigned short				OptionCode;			//操作码
	unsigned short				Length;				//纪录长度
	unsigned short				Row;				//行
	unsigned short				Column;				//列
	tagExcelCellAttr			CellAttr;			//单元格属性
	float						Value;				//值
} tagExcelFloat;
//................................................................................................................................
//常量字符串数据									//0x04
typedef struct
{
	unsigned short				OptionCode;			//操作码
	unsigned short				Length;				//纪录长度
	unsigned short				Row;				//行
	unsigned short				Column;				//列
	tagExcelCellAttr			CellAttr;			//单元格属性
	unsigned char				StringLength;		//字符串长度
	char						Value[256];			//字符串的值
} tagExcelConstString;
//................................................................................................................................
//布尔型数据										//0x05
typedef struct
{
	unsigned short				OptionCode;			//操作码
	unsigned short				Length;				//纪录长度
	unsigned short				Row;				//行
	unsigned short				Column;				//列
	tagExcelCellAttr			CellAttr;			//单元格属性
	unsigned char				Value;				//值
													//布尔数据：0x01 TRUE
													//布尔数据：0x00 FALSE
													//错误数据：0x00 #NULL!
													//错误数据：0x07 #DIV/0!
													//错误数据：0x0F #VALUE!
													//错误数据：0x17 #REF!
													//错误数据：0x1D #NAME?
													//错误数据：0x24 #NUM!
													//错误数据：0x2A #N/A
	unsigned char				ValueType;			//值类型
													//0x00 表示布尔数据
													//0x01 表示错误数据
} tagExcelBool;
//................................................................................................................................
//设置却省行的高度
typedef struct										//0x25
{
	unsigned short				OptionCode;			//操作码
	unsigned short				Length;				//纪录长度
	unsigned short				Height;				//却省行高度[1--20]
} tagExcelDefaultHeight;
//................................................................................................................................
//设置列的宽度
typedef struct										//0x24
{
	unsigned short				OptionCode;			//操作码
	unsigned short				Length;				//纪录长度
	unsigned char				FirstColumn;		//起始列
	unsigned char				LastColumn;			//结束列
	unsigned short				Width;				//宽度[1--256]
} tagExcelColumnWidth;
//................................................................................................................................
//设置字体[一个Excel文件最多4中字体]
typedef struct										//0x31
{
	unsigned short				OptionCode;			//操作码
	unsigned short				Length;				//纪录长度
	unsigned short				FontHeight;			//字体高度[1--20]
	unsigned short				FontAttr;			//字体属性
													//0x0100 粗体
													//0x0200 斜体
													//0x0400 下划线
													//0x0800 删除线
	unsigned char				FontNameLength;		//字体名称长度
	char						FontName[256];		//字体长度
} tagExcelFont;
//--------------------------------------------------------------------------------------------------------------------------------
#pragma pack()
//--------------------------------------------------------------------------------------------------------------------------------
class MExcelFile : public MFile
{
protected:
public:
	MExcelFile(void);
	~MExcelFile();
public:
	int  CreateFile(MString FileName);
	void CloseFile(void);
public:
	int  SetDefaultHeight(unsigned short Height);
	int  SetColumnWidth(unsigned char FirstColumn,unsigned char LastColumn,unsigned char Width);
	int  SetFont(unsigned short FontHeight,unsigned short FontAttr,MString FontName);
public:
	int  WriteInteger(unsigned short Row,unsigned short Column,unsigned short Value,unsigned long CellAttr = 0);
	int  WriteFloat(unsigned short Row,unsigned short Column,float Value,unsigned long CellAttr = 0);
	int  WriteString(unsigned short Row,unsigned short Column,MString Value,unsigned long CellAttr = 0);
	int  WriteBool(unsigned short Row,unsigned short Column,bool Value,unsigned long CellAttr = 0);

	DECLARE_LMYUNIT(MExcelFile)
};
//--------------------------------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------------------------------
