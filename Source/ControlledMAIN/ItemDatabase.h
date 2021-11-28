// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDatabase.generated.h"
UENUM(BlueprintType)
enum class ItemTypes : uint8
{
	Useless  UMETA(DisplayName = "Useless"),
	Material UMETA(DisplayName = "Material"),
	Weapon  UMETA(DisplayName = "Weapon"),
	Gadget  UMETA(DisplayName = "Gadget"),
	Helper UMETA(DisplayName = "Helper")
};
USTRUCT(BlueprintType)
struct FItem
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Catagory = "Item")
	FName ItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Catagory = "Item")
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Catagory = "Item")
	FText description;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Catagory = "Item")
	//ItemTypes type;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Catagory = "Item")
	TSubclassOf<AActor> actor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Catagory = "Item")
	UTexture2D* icon;


};
/**
 * 
 */
UCLASS(BlueprintType)
class CONTROLLEDMAIN_API UItemDatabase : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Catagory = "Item Data")
		TArray<FItem> data;
};
