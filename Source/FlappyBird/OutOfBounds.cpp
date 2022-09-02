// Fill out your copyright notice in the Description page of Project Settings.


#include "OutOfBounds.h"

AOutOfBounds::AOutOfBounds()
{
    GetRootComponent()->ComponentTags.Add(FName("Death"));

}
