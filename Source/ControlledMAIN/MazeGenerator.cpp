// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGenerator.h"
#include "Engine/World.h"
#include "Engine/LevelStreamingDynamic.h"


// Sets default values
AMazeGenerator::AMazeGenerator()
{
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

    int posX = sizeSquare * sizeSquare ;
    int posY = sizeSquare * sizeSquare ;

    int centerY = (posY * SIZE) / 2;
    int centerX = (posX * SIZE) / 2;

    

    for (size_t i = 0; i < _maze.Num(); i++)
    {
        for (size_t j = 0; j < _maze[i].A.Num(); j++)
        {
            //FALTA POSAR EL namemaps[] correcte
            if (_maze[i].A[j] == 1) {
                test->LoadLevelInstance(GetWorld(), nameMaps[11], FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
            }
            if (_maze[i].A[j] == 2) {
                test->LoadLevelInstance(GetWorld(), nameMaps[13], FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
            }
            if (_maze[i].A[j] == 3) {
                test->LoadLevelInstance(GetWorld(), nameMaps[4], FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
            }
            if (_maze[i].A[j] == 4) {
                test->LoadLevelInstance(GetWorld(), nameMaps[14], FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
            }
            if (_maze[i].A[j] == 5) {
                test->LoadLevelInstance(GetWorld(), nameMaps[7], FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
            }
            if (_maze[i].A[j] == 6) {
                test->LoadLevelInstance(GetWorld(), nameMaps[1], FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
            }
            if (_maze[i].A[j] == 7) {
                test->LoadLevelInstance(GetWorld(), nameMaps[8], FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
            }
            if (_maze[i].A[j] == 8) {
                test->LoadLevelInstance(GetWorld(), nameMaps[12], FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
            }
            if (_maze[i].A[j] == 9) {
                test->LoadLevelInstance(GetWorld(), nameMaps[6], FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
            }
            if (_maze[i].A[j] == 10) {
                test->LoadLevelInstance(GetWorld(), nameMaps[0], FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
            }
            if (_maze[i].A[j] == 11) {
                test->LoadLevelInstance(GetWorld(), nameMaps[5], FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
            }
            if (_maze[i].A[j] == 12) {
                test->LoadLevelInstance(GetWorld(), nameMaps[3], FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
            }
            if (_maze[i].A[j] == 13) {
                test->LoadLevelInstance(GetWorld(), nameMaps[10], FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
            }
            if (_maze[i].A[j] == 14) {
                test->LoadLevelInstance(GetWorld(), nameMaps[2], FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
            }
            if (_maze[i].A[j] == 15) {
                test->LoadLevelInstance(GetWorld(), nameMaps[9], FVector((posX * i) - centerX, (posY * j) - centerY, 0), FRotator(0, 0, 0), succes);
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
