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
enum												//��Ԫ������
{
	EXCELCELL_HIDDEN = 0x00000001,					//���ر��
	EXCELCELL_LOCKED = 0x00000002,					//�������
	EXCELCELL_FONT1 = 0x00000000,					//����1��
	EXCELCELL_FONT2 = 0x00000004,					//����2��
	EXCELCELL_FONT3 = 0x00000008,					//����3��
	EXCELCELL_FONT4 = 0x0000000C,					//����4��
	EXCELCELL_SHADED = 0x00000010,					//��Ӱ���
	EXCELCELL_BOTTOMLINE = 0x00000020,				//�߿�����
	EXCELCELL_TOPLINE = 0x00000040,					//�߿�����
	EXCELCELL_RIGHTLINE = 0x00000080,				//�߿�����
	EXCELCELL_LEFTLINE = 0x00000100,				//�߿�����
	EXCELCELL_NORMALALIGN = 0x00000000,				//��ͨ����
	EXCELCELL_LEFTALIGN = 0x00000200,				//�����
	EXCELCELL_CENTERALIGN = 0x00000400,				//�ж���
	EXCELCELL_RIGHTALIGN = 0x00000600,				//�Ҷ���
};
//................................................................................................................................
enum												//��������
{
	EXCELFONT_BOLD = 0x0100,						//����
	EXCELFONT_ITALIC = 0x0200,						//б��
	EXCELFONT_UNDERLINE = 0x0400,					//�»���
	EXCELFONT_STRIKEOUT = 0x0800,					//ɾ����
};
//................................................................................................................................
typedef struct
{
	unsigned char				Hidden : 1;			//���ر��
    unsigned char				Locked : 1;			//�������
    unsigned char				Reserved : 6;		//����
    unsigned char				Font_Num : 2;		//������
    unsigned char				Format_Code : 6;    //��Ԫ��ʽ
    unsigned char				Shaded : 1;			//��Ӱ���
    unsigned char				Bottom_Border : 1;  //�߿�����
    unsigned char				Top_Border : 1;		//�߿�����
    unsigned char				Right_Border : 1;	//�߿�����
    unsigned char				Left_Border : 1;	//�߿�����
    unsigned char				Align_Code : 3;		//���뷽ʽ
													//0x00 ��ͨ
													//0x01 �����
													//0x02 �ж���
													//0x03 �Ҷ���
													//0x04 ȫ���
													//0x07 ȴʡ
} tagExcelCellAttr;
//................................................................................................................................
//�ļ���ʼʱʹ��
typedef struct										//0x09
{
	unsigned short				OptionCode;			//������
	unsigned short				Length;				//��¼����
	unsigned short				Version;			//�汾
													//0x0500 BIFF7
													//0x0600 BIFF8
	unsigned short				Type;				//��¼����
													//0x10 worksheet
													//0x20 chart
													//0x40 macro sheet
} tagExcelBof;
//................................................................................................................................
//�ļ�����ʱʹ��
typedef struct										//0x0A
{
	unsigned short				OptionCode;			//������
	unsigned short				Length;				//��¼����
} tagExcelEof;
//................................................................................................................................
//�������
typedef struct										//0x00
{
	unsigned short				OptionCode;			//������
	unsigned short				Length;				//��¼����
	unsigned short				FirstRow;			//��ʼ�к�
	unsigned short				LastRow;			//�����к�
	unsigned short				FirstColumn;		//��ʼ�к�
	unsigned short				LastColumn;			//�����к�
} tagExcelDimensions;
//................................................................................................................................
//�հ�����
typedef struct										//0x01
{
	unsigned short				OptionCode;			//������
	unsigned short				Length;				//��¼����
	unsigned short				Row;				//��
	unsigned short				Column;				//��
	tagExcelCellAttr			CellAttr;			//��Ԫ������
} tagExcelBlank;
//................................................................................................................................
//��������
typedef struct										//0x02
{
	unsigned short				OptionCode;			//������
	unsigned short				Length;				//��¼����
	unsigned short				Row;				//��
	unsigned short				Column;				//��
	tagExcelCellAttr			CellAttr;			//��Ԫ������
	unsigned short				Value;				//ֵ
} tagExcelInteger;
//................................................................................................................................
//��������
typedef struct										//0x03
{
	unsigned short				OptionCode;			//������
	unsigned short				Length;				//��¼����
	unsigned short				Row;				//��
	unsigned short				Column;				//��
	tagExcelCellAttr			CellAttr;			//��Ԫ������
	float						Value;				//ֵ
} tagExcelFloat;
//................................................................................................................................
//�����ַ�������									//0x04
typedef struct
{
	unsigned short				OptionCode;			//������
	unsigned short				Length;				//��¼����
	unsigned short				Row;				//��
	unsigned short				Column;				//��
	tagExcelCellAttr			CellAttr;			//��Ԫ������
	unsigned char				StringLength;		//�ַ�������
	char						Value[256];			//�ַ�����ֵ
} tagExcelConstString;
//................................................................................................................................
//����������										//0x05
typedef struct
{
	unsigned short				OptionCode;			//������
	unsigned short				Length;				//��¼����
	unsigned short				Row;				//��
	unsigned short				Column;				//��
	tagExcelCellAttr			CellAttr;			//��Ԫ������
	unsigned char				Value;				//ֵ
													//�������ݣ�0x01 TRUE
													//�������ݣ�0x00 FALSE
													//�������ݣ�0x00 #NULL!
													//�������ݣ�0x07 #DIV/0!
													//�������ݣ�0x0F #VALUE!
													//�������ݣ�0x17 #REF!
													//�������ݣ�0x1D #NAME?
													//�������ݣ�0x24 #NUM!
													//�������ݣ�0x2A #N/A
	unsigned char				ValueType;			//ֵ����
													//0x00 ��ʾ��������
													//0x01 ��ʾ��������
} tagExcelBool;
//................................................................................................................................
//����ȴʡ�еĸ߶�
typedef struct										//0x25
{
	unsigned short				OptionCode;			//������
	unsigned short				Length;				//��¼����
	unsigned short				Height;				//ȴʡ�и߶�[1--20]
} tagExcelDefaultHeight;
//................................................................................................................................
//�����еĿ��
typedef struct										//0x24
{
	unsigned short				OptionCode;			//������
	unsigned short				Length;				//��¼����
	unsigned char				FirstColumn;		//��ʼ��
	unsigned char				LastColumn;			//������
	unsigned short				Width;				//���[1--256]
} tagExcelColumnWidth;
//................................................................................................................................
//��������[һ��Excel�ļ����4������]
typedef struct										//0x31
{
	unsigned short				OptionCode;			//������
	unsigned short				Length;				//��¼����
	unsigned short				FontHeight;			//����߶�[1--20]
	unsigned short				FontAttr;			//��������
													//0x0100 ����
													//0x0200 б��
													//0x0400 �»���
													//0x0800 ɾ����
	unsigned char				FontNameLength;		//�������Ƴ���
	char						FontName[256];		//���峤��
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
