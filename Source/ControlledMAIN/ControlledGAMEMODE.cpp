// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlledGAMEMODE.h"

FItem AControlledGAMEMODE::FindItem_Implementation(FName ItemID, FName TABLE, bool& Succes)
{
	Succes = false;

	FItem Item;
	if (Database == nullptr)
	{
		return Item;
	}
	if (TABLE.ToString() == "ITEMS")
	{
		for (int i = 0; i < Database->data.Num(); i++)
		{
			if (Database->data[i].ItemID == ItemID)
			{
				Succes = true;
				return Database->data[i];
			}
		}
	}
	if (TABLE.ToString() == "GRANADES")
	{
		for (int i = 0; i < Database->data_granades.Num(); i++)
		{
			if (Database->data_granades[i].ItemID == ItemID)
			{
				Succes = true;
				return Database->data_granades[i];
			}
		}
	}
	if (TABLE.ToString() == "WEAPONS")
	{
		for (int i = 0; i < Database->data_weapon.Num(); i++)
		{
			if (Database->data_weapon[i].ItemID == ItemID)
			{
				Succes = true;
				return Database->data_weapon[i];
			}
		}
	}
	if (TABLE.ToString() == "GADGETS")
	{
		for (int i = 0; i < Database->data_gadget.Num(); i++)
		{
			if (Database->data_gadget[i].ItemID == ItemID)
			{
				Succes = true;
				return Database->data_gadget[i];
			}
		}
	}
	if (TABLE.ToString() == "HELPERS")
	{
		for (int i = 0; i < Database->data_helper.Num(); i++)
		{
			if (Database->data_helper[i].ItemID == ItemID)
			{
				Succes = true;
				return Database->data_helper[i];
			}
		}
	}
	return Item;
}
