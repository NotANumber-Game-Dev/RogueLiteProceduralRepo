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
		int32 pesActual = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		int32 pesMaxim = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		int32 indexCurrentlyHandedWeapon = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		int32 indexCurrentlyHandedHelper = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		int32 indexCurrentlyHandedGranade = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		int32 maxSelectedWeaponCount = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		int32 maxIndividualGranadesCount = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		int32 maxSelectedModifiersCount = 4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		int32 maxSelectedGadgetsCount = 2;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		bool bHasItemOnHands = false;

	//Array of FNames of items of type // weapon // granade // helper // gadgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		TArray<FName> EquippedWeapons;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		TArray<FName> EquippedGranade;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		TArray<FName> EquippedHlepers;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		TArray<FName> EquippedGadgets;

public:
	//Data //Granades // Weapon // Gadget //Helper
	void AddItem(FName ItemID, FName TableName);

	void RemoveItem(FName ItemID);

	bool HasFreeInventory();

	bool HasItemOnHands(FName ItemID);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Events")
		void OnRefreshInventory();

public:
	void SwitchItem();

	void FreeHands();

};
