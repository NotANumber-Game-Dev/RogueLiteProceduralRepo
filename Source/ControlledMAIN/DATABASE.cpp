// All rigths reserved Not a Number Co


#include "DATABASE.h"

#include "Engine/Engine.h"
#include "GameFramework/Actor.h"

void UDATABASE::Start()
{
	for (int i = 0; i < DATABASE_QUEST_LIST.Num(); i++)
	{
		for (int x = 0; x < DATABASE_QUEST_LIST[i].Quest_List.Num(); x++)
		{
			DATABASE_QUEST_LIST[i].Quest_List[x].ID = ((1000 * i) + x);
		}
	}
}

void UDATABASE::AddEnemiesKilledCounter()
{
	for (TPair<int32, int32>& pair : CounterEnemiesKilled)
	{
		pair.Value++;
	}
	CheckAndUpdateQuests();
}

void UDATABASE::SetCounterForEnemiesKilled(const TSubclassOf<AActor> &Instigator, int Current_Quest, int Amount)
{
	for (int i = 0; i < DATABASE_QUEST_LIST.Num(); i++)
	{
		if (Instigator->IsChildOf(DATABASE_QUEST_LIST[i].Actor_Assigned))
		{
			CounterEnemiesKilled.Add(DATABASE_QUEST_LIST[i].Quest_List[DATABASE_QUEST_LIST[i].Mission_Index].ID, Amount);
		}
	}
}

void UDATABASE::GetNextQuest(const TSubclassOf<AActor> &Instigator, bool& noMoreMisions)
{
	for (int i = 0; i < DATABASE_QUEST_LIST.Num(); i++)
	{
		if (Instigator->IsChildOf(DATABASE_QUEST_LIST[i].Actor_Assigned))
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

void UDATABASE::SetStateQuest(const TSubclassOf<AActor> &Instigator, int QuestIndex, EQuest_State inState)
{
	for (int i = 0; i < DATABASE_QUEST_LIST.Num(); i++)
	{
		if (Instigator->IsChildOf(DATABASE_QUEST_LIST[i].Actor_Assigned))
		{
			DATABASE_QUEST_LIST[i].Quest_List[DATABASE_QUEST_LIST[i].Mission_Index].State = inState;
		}
	}
}

void UDATABASE::CheckAndUpdateQuests()
{
	bool DoesntHaveAllObjectivesDone = false;
	for (int i = 0; i < DATABASE_QUEST_LIST.Num(); i++) ///Get Database
		{
		for (int x = 0; x < DATABASE_QUEST_LIST[i].Quest_List.Num(); x++) //Get quests
		{
			switch (DATABASE_QUEST_LIST[i].Quest_List[x].State)
			{
			default:
				break;
			case EQuest_State::Grabbed:
				for (int y = 0; y < DATABASE_QUEST_LIST[i].Quest_List[x].Objectives.Num(); y++) //Get Objectives
					{
					switch (DATABASE_QUEST_LIST[i].Quest_List[x].Objectives[y].Type)
					{
					default:
						break;
					case EQuest_Objective_Type::KILL_N_ENEMIES:
						 int32 temp = *CounterEnemiesKilled.Find(DATABASE_QUEST_LIST[i].Quest_List[x].ID);
						if(temp
							>= DATABASE_QUEST_LIST[i].Quest_List[x].Objectives[y].What_to_Kill_Amount)
						{
							DATABASE_QUEST_LIST[i].Quest_List[x].Objectives[y].IsCompleted = true;
						}
						break;
						//ADD Other Types here
					}
				}
				break;
				//ADD HERE IF QUEST ISN'T GRABBED
			}
		}
		
		//Check Objectives are done to complete Quest
		for (int x = 0; x < DATABASE_QUEST_LIST[i].Quest_List.Num(); x++) //Get quests
		{
			for (int y = 0; y < DATABASE_QUEST_LIST[i].Quest_List[x].Objectives.Num(); y++) //Get Objectives
			{
				if (!DATABASE_QUEST_LIST[i].Quest_List[x].Objectives[y].IsCompleted )
				{
					DoesntHaveAllObjectivesDone = true;
				}
			}
			if (!DoesntHaveAllObjectivesDone)
			{
				DATABASE_QUEST_LIST[i].Quest_List[x].isCompleted = true;
				UE_LOG(LogTemp,Warning,TEXT("Mission Completed"));
			}
			else
			{
				UE_LOG(LogTemp,Warning,TEXT("Mission Uncompleted"));
			}
			DoesntHaveAllObjectivesDone = false;
		}
	}
}