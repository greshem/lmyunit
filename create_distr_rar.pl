#!/usr/bin/perl
$svnR=undef;
if (! -f "C:\\Program Files\\Subversion\\bin\\svn.exe")
{
	logger("svn.exe û��, û�а�װ svn \n");
}
system('"C:\\Program Files\\WinRAR\\WinRar.exe" a  lmyunit.rar  lmyunit');

if( ! -f "lmyunit".$svnR.".rar")
{
	logger("ѹ����lmyunit.rar ʧ��\n");
}
else
{
	logger("ѹ����lmyunit.rar �ɹ�\n");
}

sub get_svnR()
{
	return $undef;
}

#windows �� ��򵥵�, ��d:\\log Ŀ¼
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
