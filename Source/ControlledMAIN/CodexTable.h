// All rigths reserved Not a Number Co

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CodexTable.generated.h"

/**
 * 
 */



//----------CODEX STRUCTS------------
USTRUCT(BlueprintType,Blueprintable)
struct FCodex_Article{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere, meta = (TitleProperty = "Title"))
	FText Title;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere, meta = (TitleProperty = "Body"))
	FText Body;
};
USTRUCT(BlueprintType,Blueprintable)
struct FCodex_Category{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere, meta = (TitleProperty = "Category Title"))
	FText Category_Title;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere, meta = (TitleProperty = "Article list"))
	TArray<FCodex_Article> Articles;
};


UCLASS(BlueprintType,Blueprintable)
class CONTROLLEDMAIN_API UCodexTable : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere,meta = (TitleProperty = "Categories"))
	TMap<FString, FCodex_Category> Categories;

	//UFUNCTION(BlueprintCallable)
	
};
