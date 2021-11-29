//https://medium.com/geekculture/lets-create-an-equipment-inventory-in-ue4-456c79aa1247

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Item_Granade.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FName ItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FText description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	ItemTypes type;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TSubclassOf<AActor> actor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	UTexture2D* icon;
};

USTRUCT(BlueprintType)
struct FItem_Granades : public FItem
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Granade")
	int baseDMG;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Granade")
		int maxCritDMG;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Granade")
		float range;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Granade")
		float timeOfExplosion;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Granade")
		float timeOfAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Granade")
		UParticleSystem *particles;
	

	
	//UFUNCTION(BlueprintCallable, DeprecationMessage = "Used to cast into")
	bool isGranade() { return true; }
	void Update();
};

USTRUCT(BlueprintType)
struct FItem_Weapon : public FItem
{
	GENERATED_BODY()
		//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Granade")
		//Weapon* pWeapon; //FALTA CREAR LA CLASSE
		
		
		bool isWeapon();
};

USTRUCT(BlueprintType)
struct FItem_Gadget : public FItem
{
	GENERATED_BODY()
		//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Granade")
		//Gadget* pGadget; // FALTA CREAR LA CLASSE
		
		
		bool isGadget();

};

USTRUCT(BlueprintType)
struct FItem_Helpers : public FItem
{
	GENERATED_BODY()
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Granade")
		bool givesVelocity;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Granade")
		int baseHP;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Granade")
		int baseVelocity;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Granade")
		float timeOfUse;


	bool isHelper();

};
/**
 * 
 */
UCLASS(BlueprintType)
class CONTROLLEDMAIN_API UItemDatabase : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
		TArray<FItem> data;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
		TArray <FItem_Granades> data_granades;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
		TArray <FItem_Weapon> data_weapon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
		TArray <FItem_Gadget> data_gadget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
		TArray <FItem_Helpers> data_helper;
};
