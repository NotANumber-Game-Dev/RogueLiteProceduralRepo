// All rigths reserved Not a Number Co


#include "DATABASE.h"

void UDATABASE::Start()
{
	for (int i = 0; i< DATABASE_QUEST_LIST.Num();i++)
	{
		for (int x = 0; x< DATABASE_QUEST_LIST[i].Quest_List.Num();x++)
		{
			DATABASE_QUEST_LIST[i].Quest_List[x].ID = ((1000*i)+x);
		}
	}
}

void UDATABASE::AddEnemiesKilledCounter()
{
	for (TPair<int32, int32>& pair : CounterEnemiesKilled)
	{      
		pair.Value++;  
	} 
}

void UDATABASE::SetCounterForEnemiesKilled(TSubclassOf<AActor> Instigator, int Current_Quest, int Amount)
{
	for (int i = 0; i< DATABASE_QUEST_LIST.Num();i++)
	{
		if (DATABASE_QUEST_LIST[i].Actor_Assigned->GetClass() == Instigator->GetClass() )
		{
			CounterEnemiesKilled.Add(DATABASE_QUEST_LIST[i].Quest_List[Current_Quest].ID,Amount);
		}
	}
}

void UDATABASE::GetNextQuest(TSubclassOf<AActor> Instigator, bool& noMoreMisions)
{
	for (int i = 0; i< DATABASE_QUEST_LIST.Num();i++)
	{
		if (DATABASE_QUEST_LIST[i].Actor_Assigned->GetClass() == Instigator->GetClass() )
		{
			if (DATABASE_QUEST_LIST[i].Quest_List.Num() > DATABASE_QUEST_LIST[i].Mission_Index + 1)
			{
				DATABASE_QUEST_LIST[i].Mission_Index = DATABASE_QUEST_LIST[i].Mission_Index + 1;
				noMoreMisions = false;
				return;
			}
			else
			{
				noMoreMisions = true;
				return;
			}
		}
	}
}

void UDATABASE::SetStateQuest(TSubclassOf<AActor> Instigator, int QuestIndex, EQuest_State inState)
{
	for (int i = 0; i< DATABASE_QUEST_LIST.Num();i++)
	{
		if (DATABASE_QUEST_LIST[i].Actor_Assigned->GetClass() == Instigator->GetClass() )
		{
			DATABASE_QUEST_LIST[i].Quest_List[QuestIndex].State = inState;
			if(GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
					*UEnum::GetDisplayValueAsText(DATABASE_QUEST_LIST[i].Quest_List[QuestIndex].State).ToString());
		}
	}
}

void UDATABASE::CheckAndUpdateQuests()
{
	
}

void UDATABASE::SetObjectiveToComplete(FQuest& questToCheck, int IndexOfObjective)
{
	questToCheck.isCompleted = true;
	questToCheck.Objectives[IndexOfObjective].IsCompleted = true;
}
