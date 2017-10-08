#!/usr/bin/perl
use strict;
#testunit();
#exit(0);

my $each;
my @function_name;
for $each (grep {-d } glob("compile_bench/*"))
{
	#print "$each \n";
	if(-f $each."/test.cpp")
	{
		my $cpp_file=$each."/test.cpp";
		my $path=$each;
		#$each=~s/\//\\\//g;
		$each=~s/\//_/g;
		if( !defined(have_Subclass($cpp_file)))  #cpp subclass µÄ²âÊÔÌø¹ý. 
		{
		print 	 "sed '/int.*main\(.*argc.*argv/{s/.*/int test_$each()/g}' ".$path."/test.cpp    \>\> compile_bench/test.cpp \n";
		#print "int test_$each() ;\n";
			push(@function_name,  "int test_$each() ;\n");
		}
		else
		{
			#print "$path Subclass test , skip \n";
		}
	}

}

put_to_main_file(@function_name);

sub put_to_main_file(@)
{
	(my @lines)=@_;

	open(FILE, "> compile_bench/main.cpp") or die("create file error \n");
	for(@lines)
	{
		print FILE $_;
	}
	close(FILE);
}

sub have_Subclass($)
{
	(my $input_file)=@_;
	open(FILE,  $input_file) or die("Open $input_file error \n");
	
	for(<FILE>)
	{
		if($_=~/class.*SubClass.*public.*/)
		{
			#print $_;
			close(FILE);
			return 1;
		}

	}
	close(FILE);
	return undef;
}

sub testunit()
{
	if("class MIniFile_SubClass: public MIniFile" =~/class.*SubClass.*public.*/)
	{
		print "success \n";
	}
}

