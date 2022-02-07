// All rigths reserved Not a Number Co

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "UObject/Object.h"
#include "DATABASE.generated.h"


USTRUCT(BlueprintType)
struct FQuest
{
	GENERATED_BODY()
	int ID;
	FText Title;
	FText Description;
	//TODO STRUCT ARRAY OBJECTIVES
	TArray<FText> NPC_Dialogues;
	//TODO Enum Priority
	//TODO Enum Quest State
};

USTRUCT(BlueprintType)
struct FNPC_Quest_List
{
	GENERATED_BODY()
	TSubclassOf<AActor> Actor_Assigned;
	TArray<FQuest> Quest_List;
};



/**
 * 
 */
UCLASS()
class CONTROLLEDMAIN_API UDATABASE : public UObject
{
	GENERATED_BODY()
};
