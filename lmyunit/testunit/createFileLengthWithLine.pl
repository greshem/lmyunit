#!/usr/bin/perl
$file=shift or die("Usage: $0 length oneLineLength\n");
$lineLen=shift or die("Usage: $0 length oneLineLength\n");

#�ļ���Ƭ�Ĵ�С�� �ķ�Ƭ�Ĵ�С��Ĭ���� 4k.  #

$segment=4096;
$segment=3804;
$segment=4082;
print $file/1024/1024," M\n";

@array=(1..9, a..z, A..Z);
$size=scalar(@array);
$biggest_size=$segment*$size*$size*$size;
if( $file > $biggest_size)
{
	print "Error  $file is bigger than ", $biggest_size/1024/1024 ,"M\n";
	exit(-1);
}

$writeLength=0;
$end=0;
open(FILE,">$file");
for $first (@array)
{	
	for $second (@array)
	{		
		for $third  (@array)
		{
			if( $file-$writeLength <$segment )
			{
				$a=genOneFrame($first, $second, $third, $file-$writeLength);
				print FILE $a;
				#$writeLength+=$length;
				$end=1;			
				last;
			}
			else
			{
				$a=genOneFrame($first, $second, $third, $segment);	
				print FILE $a;
				$writeLength+=$segment
			}
		}
		
		last if($end);
	}
	last if ($end);
}

close(FILE);

if ((-s $file) != $file)
{
	print "Error $file\n";
}
#################################
#һ֡�Ĵ�С��ע�����ﻹ��һ�����з� 
# ���� $$$ ǰ3����ĸ�ظ����ɵ��ַ����� 
# getOneFrame(a,b,c,10) ���� abcabcabca  �������ַ����� 
sub genOneFrame($$$$)
{
	my ($first, $second, $third, $size)=@_;
	$word=$first.$second.$third;
	$content=$word x(int($size/3)+1);
	$content=substr($content, 0, $size-1);
	$content.="\n";
	return $content;
}

