#include <stdio.h>
#include "Framework/AyaFramework.h"

void main()
{
	

	AYA::Framework aya_framework;

	AYA::FrameworkInfo framework_info;
	framework_info.Worker_Thread_Count = 8;

	aya_framework.Init(framework_info);

	aya_framework.Start();

	// frame work init 

	// frame work start 

	return;
}