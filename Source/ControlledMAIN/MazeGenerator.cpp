// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGenerator.h"
#include "Engine/World.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Math/UnrealMathUtility.h"

#include "ReadXMLLevelDetail.h"


// Sets default values
AMazeGenerator::AMazeGenerator()
{
   
    
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

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

    SIZE = 5;
    sizeSquare = 2600;

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


    init();

    UReadXMLLevelDetail::ReadXmlFile(FPaths::ProjectContentDir() + "template.xml");

    UReadXMLLevelDetail::getContent(XMLContent);
    if (XMLContent.IsValidIndex(0))
    {
        setBiomes(XMLContent[0]);
    }
    else
    {
        setBiomes("Bottom Sewer");
    }

    RenderLevels();
}


FVector AMazeGenerator::getBossPosition()
{
    return boss;
}

int AMazeGenerator::getSizeSquare()
{
    return sizeSquare;
}


void AMazeGenerator::setBiomes(FString bioma)
{
    
    if (bioma.Equals("none")) {
        biomes = none;
    }
    else if (bioma.Equals("Bottom Sewer")) {
        biomes = Bottom_Sewer;
    }
    else if (bioma.Equals("High Sewer")) {
        biomes = High_Sewer;
    }
    else if (bioma.Equals("City Suburb")) {
        biomes = City_Suburb;
    }
    else if (bioma.Equals("Fabric Armament")) {
        biomes = Fabric_Armament;
    }
    else if (bioma.Equals("Fabric BIOS")) {
        biomes = Fabric_BIOS;
    }
    else if (bioma.Equals("City Mainstreet")) {
        biomes = City_Mainstreet;
    }
    else if (bioma.Equals("Blu Building Hall")) {
        biomes = BluBuilding_Hall;
    }
    else if (bioma.Equals("Blu Building Middle floor")) {
        biomes = BluBuilding_Middlefloor;
    }
    else if (bioma.Equals("Blu Building Penthouse")) {
        biomes = BluBuilding_Penthouse;
    }
    
}



// Called when the game starts or when spawned
void AMazeGenerator::BeginPlay()
{
    Super::BeginPlay();

    /*
    //init();

    ULevelStreamingDynamic* test;
    bool succes;

    int posX = sizeSquare;// * 10 * 10;
    int posY = sizeSquare;// * 10 * 10;

     

    

    int randX = FMath::RandRange(0, (int)SIZE / 2);
    int randY = FMath::RandRange(0, (int)SIZE / 2);

    //(randX, randY, 400);
    playerStart.X = randX;
    playerStart.Y = randY;
    playerStart.Z = 400;


    randX = FMath::RandRange((int)SIZE / 2, (int)SIZE - (int)playerStart.X);
    randY = FMath::RandRange((int)SIZE / 2, (int)SIZE - (int)playerStart.Y);

    boss.X = randX - playerStart.X;
    boss.Y = randY - playerStart.Y;
    boss.Z = 400;

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


    //afegim el prefix a tots els noms del nivell
    for (size_t i = 0; i < nameMaps.Num(); i++)
    {
        nameMaps[i].InsertAt(0, aux);
    }

    float rX=((float)playerStart.X * sizeSquare);
    float rY= ((float)playerStart.Y * sizeSquare);

    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("HOLAAAA"));
    for (size_t i = 0; i < _maze.Num(); i++)
    {
        for (size_t j = 0; j < _maze[i].A.Num(); j++)
        {
            

            //NORD: 1
            //SOUTH: 2
            //EST: 4
            //WEST: 8


            //TOP
            if (_maze[i].A[j] == 1) {
                
                //                                  BIOMA_nameMaps[]
                test->LoadLevelInstance(GetWorld(), nameMaps[11], FVector((posX * i) - rX, (posY * j) - rY, 0), FRotator(0, 0, 0), succes);
                
            }
            
            //DOWN
            if (_maze[i].A[j] == 2) {
                
                test->LoadLevelInstance(GetWorld(), nameMaps[13], FVector((posX * i) - rX, (posY * j) - rY, 0), FRotator(0, 0, 0), succes);
               
            }
            
            //TOP-DOWN
            if (_maze[i].A[j] == 3) {
                
                test->LoadLevelInstance(GetWorld(), nameMaps[4], FVector((posX * i) - rX, (posY * j) - rY, 0), FRotator(0, 0, 0), succes);
               
            }
            
            //RIGHT
            if (_maze[i].A[j] == 4) {
                
                test->LoadLevelInstance(GetWorld(), nameMaps[14], FVector((posX * i) - rX, (posY * j) - rY, 0), FRotator(0, 0, 0), succes);
                
            }
            
            //RIGHT-TOP
            if (_maze[i].A[j] == 5) {
                
                test->LoadLevelInstance(GetWorld(), nameMaps[7], FVector((posX * i) - rX, (posY * j) - rY, 0), FRotator(0, 0, 0), succes);
                
            }
            
            //RIGHT-DOWN
            if (_maze[i].A[j] == 6) {
                
                test->LoadLevelInstance(GetWorld(), nameMaps[1], FVector((posX * i) - rX, (posY * j) - rY, 0), FRotator(0, 0, 0), succes);
               
            }
            
            //TOP-DOWN-RIGHT
            if (_maze[i].A[j] == 7) {
                
                test->LoadLevelInstance(GetWorld(), nameMaps[8], FVector((posX* i) - rX, (posY* j) - rY, 0), FRotator(0, 0, 0), succes);
                
            }
            
            //LEFT
            if (_maze[i].A[j] == 8) {
                
                test->LoadLevelInstance(GetWorld(), nameMaps[12], FVector((posX* i) - rX, (posY* j) - rY, 0), FRotator(0, 0, 0), succes);
                
            }

            //TOP-LEFT
            if (_maze[i].A[j] == 9) {
                
                test->LoadLevelInstance(GetWorld(), nameMaps[6], FVector((posX* i) - rX, (posY* j) - rY, 0), FRotator(0, 0, 0), succes);
               
            }

            //LEFT-DOWN
            if (_maze[i].A[j] == 10) {
                
                test->LoadLevelInstance(GetWorld(), nameMaps[0], FVector((posX* i) - rX, (posY* j) - rY, 0), FRotator(0, 0, 0), succes);
                
            }

            //TOP-DOWN-LEFT
            if (_maze[i].A[j] == 11) {
                
                test->LoadLevelInstance(GetWorld(), nameMaps[5], FVector((posX* i) - rX, (posY* j) - rY, 0), FRotator(0, 0, 0), succes);
                
            }

            //RIGHT-LEFT
            if (_maze[i].A[j] == 12) {
                
                test->LoadLevelInstance(GetWorld(), nameMaps[3], FVector((posX* i) - rX, (posY* j) - rY, 0), FRotator(0, 0, 0), succes);
                
            }

            //TOP-RIGHT-LEFT
            if (_maze[i].A[j] == 13) {
                
                test->LoadLevelInstance(GetWorld(), nameMaps[10], FVector((posX * i) - rX, (posY * j) - rY, 0), FRotator(0, 0, 0), succes);
               
            }

            //RIGHT-DOWN-LEFT
            if (_maze[i].A[j] == 14) {
                
                test->LoadLevelInstance(GetWorld(), nameMaps[2], FVector((posX * i) - rX, (posY * j) - rY, 0), FRotator(0, 0, 0), succes);
               
            }

            //TOP-RIGHT-DOWN-LEFT
            if (_maze[i].A[j] == 15) {
                
                test->LoadLevelInstance(GetWorld(), nameMaps[9], FVector((posX* i) - rX, (posY* j) - rY, 0), FRotator(0, 0, 0), succes);
               
            }

        }
    }



    */


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
void AMazeGenerator::RenderLevels()
{
    ULevelStreamingDynamic* test;
    bool succes;

    int posX = sizeSquare;// * 10 * 10;
    int posY = sizeSquare;// * 10 * 10;





    int randX = FMath::RandRange(0, (int)SIZE / 2);
    int randY = FMath::RandRange(0, (int)SIZE / 2);

    //(randX, randY, 400);
    playerStart.X = randX;
    playerStart.Y = randY;
    playerStart.Z = 400;


    randX = FMath::RandRange((int)SIZE / 2, (int)SIZE - (int)playerStart.X);
    randY = FMath::RandRange((int)SIZE / 2, (int)SIZE - (int)playerStart.Y);

    boss.X = randX - playerStart.X;
    boss.Y = randY - playerStart.Y;
    boss.Z = 400;

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


    //afegim el prefix a tots els noms del nivell
    for (size_t i = 0; i < nameMaps.Num(); i++)
    {
        nameMaps[i].InsertAt(0, aux);
    }

    float rX = ((float)playerStart.X * sizeSquare);
    float rY = ((float)playerStart.Y * sizeSquare);

    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("HOLAAAA"));
    for (size_t i = 0; i < _maze.Num(); i++)
    {
        for (size_t j = 0; j < _maze[i].A.Num(); j++)
        {


            //NORD: 1
            //SOUTH: 2
            //EST: 4
            //WEST: 8


            //TOP
            if (_maze[i].A[j] == 1) {

                //                                  BIOMA_nameMaps[]
                test->LoadLevelInstance(GetWorld(), nameMaps[11], FVector((posX * i) - rX, (posY * j) - rY, 0), FRotator(0, 0, 0), succes);

            }

            //DOWN
            if (_maze[i].A[j] == 2) {

                test->LoadLevelInstance(GetWorld(), nameMaps[13], FVector((posX * i) - rX, (posY * j) - rY, 0), FRotator(0, 0, 0), succes);

            }

            //TOP-DOWN
            if (_maze[i].A[j] == 3) {

                test->LoadLevelInstance(GetWorld(), nameMaps[4], FVector((posX * i) - rX, (posY * j) - rY, 0), FRotator(0, 0, 0), succes);

            }

            //RIGHT
            if (_maze[i].A[j] == 4) {

                test->LoadLevelInstance(GetWorld(), nameMaps[14], FVector((posX * i) - rX, (posY * j) - rY, 0), FRotator(0, 0, 0), succes);

            }

            //RIGHT-TOP
            if (_maze[i].A[j] == 5) {

                test->LoadLevelInstance(GetWorld(), nameMaps[7], FVector((posX * i) - rX, (posY * j) - rY, 0), FRotator(0, 0, 0), succes);

            }

            //RIGHT-DOWN
            if (_maze[i].A[j] == 6) {

                test->LoadLevelInstance(GetWorld(), nameMaps[1], FVector((posX * i) - rX, (posY * j) - rY, 0), FRotator(0, 0, 0), succes);

            }

            //TOP-DOWN-RIGHT
            if (_maze[i].A[j] == 7) {

                test->LoadLevelInstance(GetWorld(), nameMaps[8], FVector((posX * i) - rX, (posY * j) - rY, 0), FRotator(0, 0, 0), succes);

            }

            //LEFT
            if (_maze[i].A[j] == 8) {

                test->LoadLevelInstance(GetWorld(), nameMaps[12], FVector((posX * i) - rX, (posY * j) - rY, 0), FRotator(0, 0, 0), succes);

            }

            //TOP-LEFT
            if (_maze[i].A[j] == 9) {

                test->LoadLevelInstance(GetWorld(), nameMaps[6], FVector((posX * i) - rX, (posY * j) - rY, 0), FRotator(0, 0, 0), succes);

            }

            //LEFT-DOWN
            if (_maze[i].A[j] == 10) {

                test->LoadLevelInstance(GetWorld(), nameMaps[0], FVector((posX * i) - rX, (posY * j) - rY, 0), FRotator(0, 0, 0), succes);

            }

            //TOP-DOWN-LEFT
            if (_maze[i].A[j] == 11) {

                test->LoadLevelInstance(GetWorld(), nameMaps[5], FVector((posX * i) - rX, (posY * j) - rY, 0), FRotator(0, 0, 0), succes);

            }

            //RIGHT-LEFT
            if (_maze[i].A[j] == 12) {

                test->LoadLevelInstance(GetWorld(), nameMaps[3], FVector((posX * i) - rX, (posY * j) - rY, 0), FRotator(0, 0, 0), succes);

            }

            //TOP-RIGHT-LEFT
            if (_maze[i].A[j] == 13) {

                test->LoadLevelInstance(GetWorld(), nameMaps[10], FVector((posX * i) - rX, (posY * j) - rY, 0), FRotator(0, 0, 0), succes);

            }

            //RIGHT-DOWN-LEFT
            if (_maze[i].A[j] == 14) {

                test->LoadLevelInstance(GetWorld(), nameMaps[2], FVector((posX * i) - rX, (posY * j) - rY, 0), FRotator(0, 0, 0), succes);

            }

            //TOP-RIGHT-DOWN-LEFT
            if (_maze[i].A[j] == 15) {

                test->LoadLevelInstance(GetWorld(), nameMaps[9], FVector((posX * i) - rX, (posY * j) - rY, 0), FRotator(0, 0, 0), succes);

            }

        }
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
