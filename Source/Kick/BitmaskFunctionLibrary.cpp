// Fill out your copyright notice in the Description page of Project Settings.

#include "Kick.h"
#include "BitmaskFunctionLibrary.h"

int32 UBitmaskFunctionLibrary::ToBitmask(uint8 Enum) {
	return 1 << Enum;
}

bool UBitmaskFunctionLibrary::HasEnum(int32 Bitmask, uint8 Enum) {
	int32 Byte = ToBitmask(Enum);
	return (Bitmask & Byte) == Byte;
}

int32 UBitmaskFunctionLibrary::AddEnum(int32 Bitmask, uint8 Enum) {
	return Bitmask | ToBitmask(Enum);
}

int32 UBitmaskFunctionLibrary::RemoveEnum(int32 Bitmask, uint8 Enum) {
	return Bitmask & (~ToBitmask(Enum));
}

int32 UBitmaskFunctionLibrary::FlipEnum(int32 Bitmask, uint8 Enum) {
	return Bitmask ^ ToBitmask(Enum);
}

int32 UBitmaskFunctionLibrary::EnumCount(int32 Bitmask) {
	int32 val = Bitmask;
	int count = 0;

	while (val > 0)
	{
		if ((val & 1) != 0)
		{
			count++;
		}

		val = val >> 1;
	}
	return count;
}