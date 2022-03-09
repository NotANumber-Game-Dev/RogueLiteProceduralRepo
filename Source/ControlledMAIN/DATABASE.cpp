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
	STARTGAMECOPY_DATABASE_QUEST_LIST = DATABASE_QUEST_LIST;
}

void UDATABASE::AddEnemiesKilledCounter()
{
	for (TPair<int32, int32>& pair : CounterEnemiesKilled)
	{
		pair.Value = pair.Value+1;
	}
	CheckAndUpdateQuests();
}

void UDATABASE::AddRecolectionItem(const TSubclassOf<AActor>& Item,int quantity)
{
	for (TPair<int32, int32>& pair : CounterRecolectionItem)
	{
		//mirem misssions
		for (int i = 0; i < DATABASE_QUEST_LIST.Num(); i++) ///Get Database
		{
			//miro
			for (int x = 0; x < DATABASE_QUEST_LIST[i].Quest_List.Num(); x++) //Get quests
			{
				if (DATABASE_QUEST_LIST[i].Quest_List[x].State == EQuest_State::Grabbed) {
					for (int y = 0; y < DATABASE_QUEST_LIST[i].Quest_List[x].Objectives.Num(); y++) {
						if (Item->IsChildOf(DATABASE_QUEST_LIST[i].Quest_List[x].Objectives[y].What_to_recollect)) {
							pair.Value += quantity;
						}
					}
				}
			}
		}
	}
	CheckAndUpdateQuests();
}

void UDATABASE::AddKillSpecificEnemyCounter(const TSubclassOf<AActor>& Item)
{
	for (TPair<int32, int32>& pair : CounterKillSpecificEnemy) {
		for (int i = 0; i < DATABASE_QUEST_LIST.Num(); i++) ///Get Database
		{
			for (int x = 0; x < DATABASE_QUEST_LIST[i].Quest_List.Num(); x++) //Get quests
			{
				if (DATABASE_QUEST_LIST[i].Quest_List[x].State == EQuest_State::Grabbed) {
					for (int y = 0; y < DATABASE_QUEST_LIST[i].Quest_List[x].Objectives.Num(); y++) {
						
						if (Item->IsChildOf(DATABASE_QUEST_LIST[i].Quest_List[x].Objectives[y].What_to_Kill)) {
							pair.Value += 1;
						}
					}
				}
			}
		}
	}
	CheckAndUpdateQuests();
}

void UDATABASE::AddNSpecificEnemiesKilledCounter(const TSubclassOf<AActor>& Item)
{
	for (TPair<int32, int32>& pair : CounterNSpecificEnemiesKilled) {
		for (int i = 0; i < DATABASE_QUEST_LIST.Num(); i++) ///Get Database
		{
			for (int x = 0; x < DATABASE_QUEST_LIST[i].Quest_List.Num(); x++) //Get quests
			{
				if (DATABASE_QUEST_LIST[i].Quest_List[x].State == EQuest_State::Grabbed) {
					for (int y = 0; y < DATABASE_QUEST_LIST[i].Quest_List[x].Objectives.Num(); y++) {
						if (Item->IsChildOf(DATABASE_QUEST_LIST[i].Quest_List[x].Objectives[y].What_to_Kill)) {
							pair.Value += 1;
						}
					}
				}
			}
		}
	}
	CheckAndUpdateQuests();
}

void UDATABASE::AddInteractWithItem(const TSubclassOf<AActor>& Item)
{
	
	for (TPair<int32, bool>& pair : CounterInteractWithObject)
	{
		//mirem misssions
		for (int i = 0; i < DATABASE_QUEST_LIST.Num(); i++) ///Get Database
		{
			for (int x = 0; x < DATABASE_QUEST_LIST[i].Quest_List.Num(); x++) //Get quests
			{
				if (DATABASE_QUEST_LIST[i].Quest_List[x].State == EQuest_State::Grabbed) {
					for (int y = 0; y < DATABASE_QUEST_LIST[i].Quest_List[x].Objectives.Num(); y++) {
						if (Item->IsChildOf(DATABASE_QUEST_LIST[i].Quest_List[x].Objectives[y].What_to_Interact)) {
							pair.Value = true;
						}
					}
				}
			}
		}
	}
	CheckAndUpdateQuests();
}

void UDATABASE::ResetCurrentLaodedProggress()
{
	DATABASE_QUEST_LIST = STARTGAMECOPY_DATABASE_QUEST_LIST;
}

void UDATABASE::SetCounterForEnemiesKilled(const TSubclassOf<AActor> &Instigator, int Current_Quest, int Amount)
{
	for (int i = 0; i < DATABASE_QUEST_LIST.Num(); i++)
	{
		if (Instigator->IsChildOf(DATABASE_QUEST_LIST[i].Actor_Assigned))
		{
			if (CounterEnemiesKilled.Find(DATABASE_QUEST_LIST[i].Quest_List[DATABASE_QUEST_LIST[i].Mission_Index].ID) == nullptr) {
				CounterEnemiesKilled.Add(DATABASE_QUEST_LIST[i].Quest_List[DATABASE_QUEST_LIST[i].Mission_Index].ID, Amount);
			}
		}
	}
}

void UDATABASE::SetCounterForKillSpecificEnemy(const TSubclassOf<AActor>& Instigator, int Current_Quest, int Amount)
{
	for (int i = 0; i < DATABASE_QUEST_LIST.Num(); i++) {
		if (Instigator->IsChildOf(DATABASE_QUEST_LIST[i].Actor_Assigned)) {

			if (CounterKillSpecificEnemy.Find(DATABASE_QUEST_LIST[i].Quest_List[DATABASE_QUEST_LIST[i].Mission_Index].ID) == nullptr) {

				CounterKillSpecificEnemy.Add(DATABASE_QUEST_LIST[i].Quest_List[DATABASE_QUEST_LIST[i].Mission_Index].ID, Amount);
			}
		}
	}
}

void UDATABASE::SetCounterForRecolectionItems(const TSubclassOf<AActor>& Instigator, int Current_Quest, int Amount)
{
	for (int i = 0; i < DATABASE_QUEST_LIST.Num(); i++) {
		if (Instigator->IsChildOf(DATABASE_QUEST_LIST[i].Actor_Assigned)) {
			if (CounterRecolectionItem.Find(DATABASE_QUEST_LIST[i].Quest_List[DATABASE_QUEST_LIST[i].Mission_Index].ID) == nullptr) {

				CounterRecolectionItem.Add(DATABASE_QUEST_LIST[i].Quest_List[DATABASE_QUEST_LIST[i].Mission_Index].ID, Amount);
			}
		}
	}
}

void UDATABASE::SetCounterNSpecificEnemiesKilled(const TSubclassOf<AActor>& Instigator, int Current_Quest, int Amount)
{
	for (int i = 0; i < DATABASE_QUEST_LIST.Num(); i++) {
		if (Instigator->IsChildOf(DATABASE_QUEST_LIST[i].Actor_Assigned)) {
			if (CounterNSpecificEnemiesKilled.Find(DATABASE_QUEST_LIST[i].Quest_List[DATABASE_QUEST_LIST[i].Mission_Index].ID) == nullptr) {
				CounterNSpecificEnemiesKilled.Add(DATABASE_QUEST_LIST[i].Quest_List[DATABASE_QUEST_LIST[i].Mission_Index].ID, Amount);
			}
		}
	}
}

void UDATABASE::SetCounterForInteractWithItem(const TSubclassOf<AActor>& Instigator, int Current_Quest, bool isInteracted)
{
	for (int i = 0; i < DATABASE_QUEST_LIST.Num(); i++) {
		if (Instigator->IsChildOf(DATABASE_QUEST_LIST[i].Actor_Assigned)) {
			if (CounterInteractWithObject.Find(DATABASE_QUEST_LIST[i].Quest_List[DATABASE_QUEST_LIST[i].Mission_Index].ID) == nullptr) {
				CounterInteractWithObject.Add(DATABASE_QUEST_LIST[i].Quest_List[DATABASE_QUEST_LIST[i].Mission_Index].ID, isInteracted);
			}
		}
	}
}


//TODO comprovar si la quest s'ha fet, llavors donar nova missió. Mirar que no sigui negatiu
void UDATABASE::GetNextQuest(const TSubclassOf<AActor> &Instigator, bool& noMoreMisions)
{


	for (int i = 0; i < DATABASE_QUEST_LIST.Num(); i++)
	{
		if (Instigator->IsChildOf(DATABASE_QUEST_LIST[i].Actor_Assigned))
		{
			if (DATABASE_QUEST_LIST[i].Mission_Index < 0) {
				if (DATABASE_QUEST_LIST[i].Quest_List.Num() > DATABASE_QUEST_LIST[i].Mission_Index + 1)
				{
					DATABASE_QUEST_LIST[i].Mission_Index = DATABASE_QUEST_LIST[i].Mission_Index + 1;
					DATABASE_QUEST_LIST[i].Quest_List[DATABASE_QUEST_LIST[i].Mission_Index].State = EQuest_State::Grabbed;
					noMoreMisions = false;
					return;
				}
				else
				{
					noMoreMisions = true;
					return;
				}
			}
			else {
				if (DATABASE_QUEST_LIST[i].Quest_List[DATABASE_QUEST_LIST[i].Mission_Index].State == EQuest_State::Complete) {
					if (DATABASE_QUEST_LIST[i].Quest_List.Num() > DATABASE_QUEST_LIST[i].Mission_Index + 1)
					{
						DATABASE_QUEST_LIST[i].Mission_Index = DATABASE_QUEST_LIST[i].Mission_Index + 1;
						DATABASE_QUEST_LIST[i].Quest_List[DATABASE_QUEST_LIST[i].Mission_Index].State = EQuest_State::Grabbed;
						noMoreMisions = false;
						return;
					}
					else
					{
						noMoreMisions = true;
						return;
					}
				}
				else {
					return;
				}
			}
			
		}
	}
	UpdateData.Broadcast();
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
					int32 recolection = 0;
					int32 nEnemiesKilled = 0;
					int32 nSpeceificEnemy = 0;
					int32 KillSpecificEnemy = 0;
					bool isInteracted = false;
					switch (DATABASE_QUEST_LIST[i].Quest_List[x].Objectives[y].Type)
					{
						default:
							break;
						case EQuest_Objective_Type::KILL_N_ENEMIES:
							
							if (CounterEnemiesKilled.Find(DATABASE_QUEST_LIST[i].Quest_List[x].ID)!=nullptr) {
								nEnemiesKilled = *CounterEnemiesKilled.Find(DATABASE_QUEST_LIST[i].Quest_List[x].ID);
							}
											
							if(nEnemiesKilled
								>= DATABASE_QUEST_LIST[i].Quest_List[x].Objectives[y].What_to_Kill_Amount)
							{
								DATABASE_QUEST_LIST[i].Quest_List[x].Objectives[y].IsCompleted = true;
							}
							break;
							//ADD Other Types here
						case EQuest_Objective_Type::RECOLECCTION:
							if (CounterRecolectionItem.Find(DATABASE_QUEST_LIST[i].Quest_List[x].ID)!=nullptr) {
								recolection = *CounterRecolectionItem.Find(DATABASE_QUEST_LIST[i].Quest_List[x].ID);
							}
							
							if (recolection>= DATABASE_QUEST_LIST[i].Quest_List[x].Objectives[y].What_to_recollect_Amount) {
								
								DATABASE_QUEST_LIST[i].Quest_List[x].Objectives[y].IsCompleted = true;
							}
							break;
						case EQuest_Objective_Type::INTERACT_WITH_OBJECT:
							if (CounterInteractWithObject.Find(DATABASE_QUEST_LIST[i].Quest_List[x].ID) != nullptr) {
								isInteracted=*CounterInteractWithObject.Find(DATABASE_QUEST_LIST[i].Quest_List[x].ID);
							}

							if (isInteracted) {
								DATABASE_QUEST_LIST[i].Quest_List[x].Objectives[y].IsCompleted = true;
							}
							break;
						case EQuest_Objective_Type::KILL_N_ENEMIES_SPECIFIC:
							if (CounterNSpecificEnemiesKilled.Find(DATABASE_QUEST_LIST[i].Quest_List[x].ID) != nullptr) {
								nSpeceificEnemy=*CounterNSpecificEnemiesKilled.Find(DATABASE_QUEST_LIST[i].Quest_List[x].ID);
							}

							if (nSpeceificEnemy >= DATABASE_QUEST_LIST[i].Quest_List[x].Objectives[y].What_to_Kill_Amount) {
								DATABASE_QUEST_LIST[i].Quest_List[x].Objectives[y].IsCompleted = true;
							}
							break;
						case EQuest_Objective_Type::KILL_SPECIFIC_ENEMY:
							if (CounterKillSpecificEnemy.Find(DATABASE_QUEST_LIST[i].Quest_List[x].ID) != nullptr) {
								KillSpecificEnemy=*CounterKillSpecificEnemy.Find(DATABASE_QUEST_LIST[i].Quest_List[x].ID);
							}

							if (KillSpecificEnemy > 0) {
								DATABASE_QUEST_LIST[i].Quest_List[x].Objectives[y].IsCompleted = true;

							}
							break;
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
				DATABASE_QUEST_LIST[i].Quest_List[x].State = EQuest_State::Complete;
				UE_LOG(LogTemp,Warning,TEXT("Mission Completed"));
				MissionsCompleted.Broadcast();
			}
			else
			{
				UE_LOG(LogTemp,Warning,TEXT("Mission Uncompleted"));
			}
			DoesntHaveAllObjectivesDone = false;
		}
	}
	UpdateData.Broadcast();
}
