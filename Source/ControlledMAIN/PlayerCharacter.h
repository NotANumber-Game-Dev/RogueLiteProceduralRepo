// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ItemDatabase.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class CONTROLLEDMAIN_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	/// Inventory
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		TArray<FItem> EquipmentInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		int32 TotalEquipmentSlots = 6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		bool bHasItemOnHands = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		int32 IndexItemOnHands;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		FName ItemIDOnHands;

public:

	void AddItem(FName ItemID);

	void RemoveItem(FName ItemID);

	bool HasFreeInventory();

	bool HasItemOnHands(FName ItemID);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Events")
		void OnRefreshInventory();

public:
	void SwitchItem();

	void FreeHands();

};
