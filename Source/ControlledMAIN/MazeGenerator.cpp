// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGenerator.h"
#include "Engine/World.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Math/UnrealMathUtility.h"


// Sets default values
AMazeGenerator::AMazeGenerator()
{
    nameMaps.SetNum(15);
    nameMaps[0] = "LM_LEFT_DOWN";
    nameMaps[1] = "LM_RIGHT_DOWN";
    nameMaps[2] = "LM_RIGHT_DOWN_LEFT";
    nameMaps[3] = "LM_RIGHT_LEFT";
    nameMaps[4] = "LM_TOP_DOWN";
    nameMaps[5] = "LM_TOP_DOWN_LEFT";
    nameMaps[6] = "LM_TOP_LEFT";
    nameMaps[7] = "LM_TOP_RIGHT";
    nameMaps[8] = "LM_TOP_RIGHT_DOWN";
    nameMaps[9] = "LM_TOP_RIGHT_DOWN_LEFT";
    nameMaps[10] = "LM_TOP_RIGHT_LEFT";
    nameMaps[11] = "LM_TOP";
    nameMaps[12] = "LM_LEFT";
    nameMaps[13] = "LM_DOWN";
    nameMaps[14] = "LM_RIGHT";
    
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    _maze.SetNum(SIZE);
    for (size_t i = 0; i < _maze.Num(); i++)
    {
        _maze[i].A.SetNum(SIZE);
    }

    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            _maze[y].A[x] = 0;

        }
    }



    _posCount = 1;
    _currentPos.X = 0;
    _currentPos.Y = 0;
    _randNum = 0;
    for (int i = 0; i < 4; i++)
    {
        _randPrev[i] = false;
    }
    _checkedPos = 0;
}

// Called when the game starts or when spawned
void AMazeGenerator::BeginPlay()
{
    Super::BeginPlay();

    init();

    ULevelStreamingDynamic* test;
    bool succes;

    int posX = sizeSquare * SIZE * SIZE ;
    int posY = sizeSquare * SIZE * SIZE;

    int centerY =0; 
    int centerX =0; 

    int randX = FMath::RandRange((int)SIZE/4,(int)SIZE);
    int randY = FMath::RandRange((int)SIZE / 4, (int)SIZE);

    boss.x = randX;
    boss.y = randY;

    FString aux;
   
    switch (biomes) {
    case Bottom_Sewer:
        aux = "BS_";
        break;
    case High_Sewer:
        aux = "HS_";
        break;
    case City_Suburb:
        aux = "CS_";
        break;
    case Fabric_Armament:
        aux = "FA_";
        break;
    case Fabric_BIOS:
        aux = "FB_";
        break;
    case City_Mainstreet:
        aux = "CM_";
        break;
    case BluBuilding_Hall:
        aux = "BH_";
        break;
    case BluBuilding_Middlefloor:
        aux = "BM_";
        break;
    case BluBuilding_Penthouse:
        aux = "BP_";
        break;
    case none:
        aux = "";
        break;
    default:
        aux = "";
        break;
    }
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("HOLAAAA"));
    for (size_t i = 0; i < _maze.Num(); i++)
    {
        for (size_t j = 0; j < _maze[i].A.Num(); j++)
        {
            //FALTA POSAR EL namemaps[] correcte

            //NORD: 1
            //SOUTH: 2
            //EST: 4
            //WEST: 8


            //TOP
            if (_maze[i].A[j] == 1) {
                aux.Append(nameMaps[11]);
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TOP"));
                //                                  BIOMA_nameMaps[]
                test->LoadLevelInstance(GetWorld(), aux, FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
            }
            
            //DOWN
            if (_maze[i].A[j] == 2) {
                aux.Append(nameMaps[13]);
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("DOWN"));
                test->LoadLevelInstance(GetWorld(), aux, FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
            }
            
            //TOP-DOWN
            if (_maze[i].A[j] == 3) {
                aux.Append(nameMaps[4]);
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TOP-DOWN"));
                test->LoadLevelInstance(GetWorld(), aux, FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
            }
            
            //RIGHT
            if (_maze[i].A[j] == 4) {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("RIGHT"));
                aux.Append(nameMaps[14]);
                test->LoadLevelInstance(GetWorld(), aux, FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
            }
            
            //RIGHT-TOP
            if (_maze[i].A[j] == 5) {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("RIGHT-TOP"));
                aux.Append(nameMaps[7]);
                test->LoadLevelInstance(GetWorld(), aux, FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
            }
            
            //RIGHT-DOWN
            if (_maze[i].A[j] == 6) {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ROGHT-DOWN"));
                aux.Append(nameMaps[1]);
                test->LoadLevelInstance(GetWorld(), aux, FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
            }
            
            //TOP-DOWN-RIGHT
            if (_maze[i].A[j] == 7) {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TOP-DOWN-RIGHT"));
                aux.Append(nameMaps[8]);
                test->LoadLevelInstance(GetWorld(), aux, FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
            }
            
            //LEFT
            if (_maze[i].A[j] == 8) {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("LEFT"));
                aux.Append(nameMaps[12]);
                test->LoadLevelInstance(GetWorld(), aux, FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
            }

            //TOP-LEFT
            if (_maze[i].A[j] == 9) {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TOP-LEFT"));
                aux.Append(nameMaps[6]);
                test->LoadLevelInstance(GetWorld(), aux, FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
            }

            //LEFT-DOWN
            if (_maze[i].A[j] == 10) {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("LEFT-DOWN"));
                aux.Append(nameMaps[0]);
                test->LoadLevelInstance(GetWorld(), aux, FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
            }

            //TOP-DOWN-LEFT
            if (_maze[i].A[j] == 11) {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TOP-DOWN-LEFT"));
                aux.Append(nameMaps[5]);
                test->LoadLevelInstance(GetWorld(), aux, FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
            }

            //RIGHT-LEFT
            if (_maze[i].A[j] == 12) {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("RIGHT-LEFT"));
                aux.Append(nameMaps[3]);
                test->LoadLevelInstance(GetWorld(), aux, FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
            }

            //TOP-RIGHT-LEFT
            if (_maze[i].A[j] == 13) {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TOP-RIGHT-LEFT"));
                aux.Append(nameMaps[10]);
                test->LoadLevelInstance(GetWorld(), aux, FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
            }

            //RIGHT-DOWN-LEFT
            if (_maze[i].A[j] == 14) {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("RIGHT-DOWN-LEFT"));
                aux.Append(nameMaps[2]);
                test->LoadLevelInstance(GetWorld(), aux, FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
            }

            //TOP-RIGHT-DOWN-LEFT
            if (_maze[i].A[j] == 15) {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ALL"));
                aux.Append(nameMaps[9]);
                test->LoadLevelInstance(GetWorld(), aux, FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
            }

        }
    }






}

void AMazeGenerator::generator()
{
    if (_checkedPos >= 15)
    {
        //2.4 al llibre SOME THING IT OUT OF TABLE
        if (_prevPosList.Num() != 0)
        {
            _currentPos = _prevPosList[_prevPosList.Num() - 1];
            _prevPosList.RemoveAt(_prevPosList.Num() - 1);
            for (int i = 0; i < 4; i++)
            {
                _randPrev[i] = false;
            }
        }
        _checkedPos = 0;
    }
    _randNum = getRandomDirection();
    switch (_randNum)//1  2  4  8
    {
    case 1:
        if (!isWalOnPos(_currentPos.X, _currentPos.Y - 1))
        {
            canContinue(0, -1);
        }
        else
        {
            //Check we dont add more tries if it is the same rand number 
            addToCount(0);
        }
        break;
    case 2:
        if (!isWalOnPos(_currentPos.X, _currentPos.Y + 1))
        {
            canContinue(0, 1);
        }
        else
        {
            addToCount(1);
        }
        break;
    case 4:
        if (!isWalOnPos(_currentPos.X + 1, _currentPos.Y))
        {
            canContinue(1, 0);
        }
        else
        {
            addToCount(2);
        }
        break;
    case 8:
        if (!isWalOnPos(_currentPos.X - 1, _currentPos.Y))
        {
            canContinue(-1, 0);
        }
        else
        {
            addToCount(3);
        }
        break;
    default:
        break;
    }
}

int AMazeGenerator::getRandomDirection()
{
    bool reset = true;
    int tempN = 0;
    do
    {
        tempN = rand() % 4;//0 1 2 3
        if (_randPrev[tempN] == false)
        {
            reset = false;
        }
    } while (reset);
    return (int)(FMath::Pow(2, tempN));//0=1  1=2  2=4  3=8
}

void AMazeGenerator::addToCount(int i)
{
    _randPrev[i] = true;
}

void AMazeGenerator::canContinue(int x, int y)
{
    _posCount += 1;
    _prevPosList.Add(_currentPos);

    _maze[_currentPos.X].A[_currentPos.Y] += _randNum;
    _currentPos.X = _currentPos.X + x;
    _currentPos.Y = _currentPos.Y + y;

    switch (_randNum)
    {
    case 1:
        _randNum = 2;
        break;
    case 2:
        _randNum = 1;
        break;
    case 4:
        _randNum = 8;
        break;
    case 8:
        _randNum = 4;
        break;
    default:
        break;
    }
    _maze[_currentPos.X].A[_currentPos.Y] += _randNum;
    _checkedPos = 0;
    for (int i = 0; i < 4; i++)
    {
        _randPrev[i] = false;
    }
}

// Called every frame
void AMazeGenerator::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}
void AMazeGenerator::init()
{
    _maze.SetNum(SIZE);
    for (size_t i = 0; i < _maze.Num(); i++)
    {
        _maze[i].A.SetNum(SIZE);
    }

    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            _maze[y].A[x] = 0;

        }
    }

    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            _maze[y].A[x] = 0;

        }
    }


    _posCount = 1;
    _currentPos.X = 0;
    _currentPos.Y = 0;
    _randNum = 0;
    for (int i = 0; i < 4; i++)
    {
        _randPrev[i] = false;
    }
    _checkedPos = 0;
    _currentPos.X = rand() % SIZE;
    _currentPos.Y = rand() % SIZE;
    _prevPosList.Add(_currentPos);
    while (_posCount != (SIZE * SIZE))
    {
        generator();
    }
}
bool AMazeGenerator::isWalOnPos(int x, int y)
{
    if (x >= SIZE || y >= SIZE || y < 0 || x < 0)
    {
        _checkedPos += _randNum;
        return true;
    }
    if (_maze[x].A[y] != 0)
    {
        _checkedPos += _randNum;
        return true;
    }
    return false;
}
