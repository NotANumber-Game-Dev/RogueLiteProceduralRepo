// All rigths reserved Not a Number Co

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TableSellingObjects.generated.h"

/**
 * 
 */

 //----------CODEX STRUCTS------------
USTRUCT(BlueprintType, Blueprintable)
struct FShop_Item {
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (TitleProperty = "Shop Item"))
		TSubclassOf<AActor> item;
};



UCLASS(BlueprintType, Blueprintable)
class CONTROLLEDMAIN_API UTableSellingObjects : public UDataAsset
{
	GENERATED_BODY()
public:
		UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (TitleProperty = "Shop Item"))
		TArray<FShop_Item> items;
};
