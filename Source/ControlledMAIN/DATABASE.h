// All rigths reserved Not a Number Co

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "UObject/Object.h"
#include "DATABASE.generated.h"

UENUM(BlueprintType,Blueprintable)
enum EQuest_State
{
	Not_Grabbed,
	Grabbed,
	Complete
};

UENUM(BlueprintType,Blueprintable)
enum EQuest_Story_Priority
{
	Main,
	Secundary
};

UENUM(BlueprintType,Blueprintable)
enum EQuest_Objective_Type
{
	RECOLECCTION,
	INTERACT_WITH_OBJECT,
	KILL_N_ENEMIES,
	KILL_N_ENEMIES_SPECIFIC,
	KILL_SPECIFIC_ENEMY
};

USTRUCT(BlueprintType,Blueprintable)
struct FQuest_Objective
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere, meta = (TitleProperty = "Is Completed"))
	bool IsCompleted = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,meta = (TitleProperty = "Type"))
	TEnumAsByte<EQuest_Objective_Type> Type;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere, meta = (TitleProperty = "UI Player Instruction"))
	FText UI_Player_Instruction;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,meta = (TitleProperty = "What to recolect"))
	TSubclassOf<AActor> What_to_recollect; //RECOLECCTION Has to be BP_ITEM
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (TitleProperty = "What to recolect Amount"))
	int32 What_to_recollect_Amount; //RECOLECCTION
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,meta = (TitleProperty = "What to interact"))
	TSubclassOf<AActor> What_to_Interact; //INTERACT_WITH_OBJECT Has to be BP_Quest_Interactuable
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere, meta = (TitleProperty = "What to kill"))
	TSubclassOf<AActor> What_to_Kill; //KILL_N_ENEMIES_SPECIFIC Has to be BP_ENEMY
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere, meta = (TitleProperty = "What to kill Amount"))
	int32 What_to_Kill_Amount; //KILL_N_ENEMIES

};

USTRUCT(BlueprintType,Blueprintable)
struct FQuest
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere, meta = (TitleProperty = "isCompleted"))
	bool isCompleted = false;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, meta = (TitleProperty = "ID"))
	int32 ID;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, meta = (TitleProperty = "Title"))
	FText Title;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere, meta = (TitleProperty = "Description"))
	FText Description;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, meta = (TitleProperty = "Objectives"))
	TArray<FQuest_Objective> Objectives;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, meta = (TitleProperty = "NPC Dialogues"))
	TArray<FText> NPC_Dialogues;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,meta = (TitleProperty = "Priority"))
	TEnumAsByte <EQuest_Story_Priority> Priority;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, meta = (TitleProperty = "ID"))
	TEnumAsByte <EQuest_State> State = EQuest_State::Not_Grabbed;
};

USTRUCT(BlueprintType,Blueprintable)
struct FNPC_Quest_List
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (TitleProperty = "Assigned Actor"))
	TSubclassOf<AActor> Actor_Assigned;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (TitleProperty = "Quest List"))
	TArray<FQuest> Quest_List;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (TitleProperty = "Mission Index"))
	int32 Mission_Index = -1;
};

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDataUpdated);


UCLASS(BlueprintType,Blueprintable)
class CONTROLLEDMAIN_API UDATABASE : public UObject
{
	GENERATED_BODY()

protected:
	bool debug;
	
public:
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (TitleProperty = "Database Quest (Enemies N Killed)"))
	TMap<int32,int32> CounterEnemiesKilled;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,meta = (TitleProperty = "Database Quest List"))
	TArray<FNPC_Quest_List> DATABASE_QUEST_LIST;

		TArray<FNPC_Quest_List> STARTGAMECOPY_DATABASE_QUEST_LIST;


	UFUNCTION(BlueprintCallable)
	void Start();
	
	///Adds 1 to all quests that are kill any Enemies
	UFUNCTION(BlueprintCallable)
	void AddEnemiesKilledCounter();
	
	///For New Game, in case player went back to the menu and started a new game having progress on a previous one
	UFUNCTION(BlueprintCallable)
	void ResetCurrentLaodedProggress();
	
	UFUNCTION(BlueprintCallable)
	void SetCounterForEnemiesKilled(const TSubclassOf<AActor> &Instigator, int Current_Quest, int Amount = 0);

	UFUNCTION(BlueprintCallable)
	void GetNextQuest(const TSubclassOf<AActor> &Instigator, bool &noMoreMisions);

	UFUNCTION(BlueprintCallable)
	void SetStateQuest(const TSubclassOf<AActor> &Instigator,int QuestIndex, EQuest_State inState);
	
	
	void CheckAndUpdateQuests();

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FDataUpdated UpdateData;
	
};
