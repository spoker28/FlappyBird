// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockDeleter.h"

ABlockDeleter::ABlockDeleter()
{
    GetRootComponent()->ComponentTags.Add(FName("Destroy Block"));
}
