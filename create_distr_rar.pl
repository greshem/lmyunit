#!/usr/bin/perl
$svnR=undef;
if (! -f "C:\\Program Files\\Subversion\\bin\\svn.exe")
{
	logger("svn.exe 没有, 没有安装 svn \n");
}
system('"C:\\Program Files\\WinRAR\\WinRar.exe" a  lmyunit.rar  lmyunit');

if( ! -f "lmyunit".$svnR.".rar")
{
	logger("压缩到lmyunit.rar 失败\n");
}
else
{
	logger("压缩到lmyunit.rar 成功\n");
}

sub get_svnR()
{
	return $undef;
}

#windows 下 最简单的, 到d:\\log 目录
sub logger($)
{
	if(! -d ("d:\\log"))
	{
		mkdir("d:\\log");
	}

	(my $log_str)=@_;
	open(FILE, ">> d:\\log\\create_distr_rar.log") or warn("open name.log error\n");
	print FILE $log_str;
	close(FILE);
}
