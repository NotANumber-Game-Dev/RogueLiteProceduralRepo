// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ItemDatabase.h"
#include "ControlledGAMEMODE.generated.h"

/**
 * 
 */
UCLASS()
class CONTROLLEDMAIN_API AControlledGAMEMODE : public AGameMode
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item System")
		class UItemDatabase* Database;
};
